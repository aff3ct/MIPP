/**
 * MIPP API Explorer - "View Algorithm" Modal Component
 * Displays an abstract, conceptual C++ representation of the operation,
 * its LMUL unrolling (including LMUL = -2 note), and mask emulation layers.
 */
import { escapeHtml, ICON_COPY } from "../explorer.config.js";
import { highlightCpp } from "../syntax.js";
import { SIMD_EXT_DISPLAY_NAMES, ALL_MASK_MODES, MASK_MODES_INFO } from "../data.js";
import { state } from "../state.js";

export function renderAlgoModal(modalData) {
  if (!modalData) return "";
  const { entry, isa, dt, mask = "unmasked" } = modalData;
  const effectiveLmul = state.lmul || modalData.lmul || "1";
  const namesMap = SIMD_EXT_DISPLAY_NAMES;

  const allDts = entry.datatypes || [];
  const activeDts = allDts.filter((d) => state.selectedTypes.includes(d));
  const selectableDts = (state.selectedTypes.length > 0 && activeDts.length > 0) ? activeDts : allDts;
  const defaultDt = selectableDts[0] || "float32";
  const currentDt = dt && selectableDts.includes(dt) ? dt : defaultDt;

  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const activeMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
  const defaultMask = activeMasks.length > 0 ? activeMasks[0] : (allVariants[0] || "unmasked");
  const currentMask = mask && allVariants.includes(mask) ? mask : defaultMask;

  const numLmul = Number(effectiveLmul) || 1;
  const isHalfLmul = effectiveLmul === "-2";

  // Determine return type and argument names from entry's base C++ prototype
  const baseProto = entry.prototypes?.cpp || "";
  const retMatch = baseProto.match(/^(?:template\s*<[^>]+>\s*)?([a-zA-Z0-9_<>]+)\s+[a-zA-Z0-9_]+\s*\(/);
  const rawRet = retMatch ? retMatch[1].trim() : "rvd<T>";
  const isRvmReturn = rawRet.startsWith("rvm") || entry.category === "comparison";

  const retType1 = isRvmReturn ? `rvm<${currentDt}, 1>` : `rvd<${currentDt}, 1>`;
  const retTypeLmul = isRvmReturn ? `rvm<${currentDt}, ${effectiveLmul}>` : `rvd<${currentDt}, ${effectiveLmul}>`;

  const paramMatch = baseProto.match(/\(([^)]*)\)/);
  let argNames = [];
  if (paramMatch && paramMatch[1].trim()) {
    const parts = paramMatch[1].split(",").map((s) => s.trim());
    argNames = parts.map((part, idx) => {
      const words = part.split(/\s+/);
      return words[words.length - 1].replace(/[^a-zA-Z0-9_]/g, "") || `r${idx}`;
    });
  }
  if (argNames.length === 0) {
    argNames = ["r0"];
  }

  const argDecl1 = argNames.map((a) => `const rvd<${currentDt}, 1> ${a}`).join(", ");
  const argDeclLmul = argNames.map((a) => `const rvd<${currentDt}, ${effectiveLmul}> ${a}`).join(", ");
  const callArgs = argNames.join(", ");

  // Build Abstract Layered C++ Code
  const codeLines = [];
  codeLines.push(`// =============================================================================`);
  codeLines.push(`// Conceptual Algorithm: mipp::${entry.name} (${namesMap[isa] || isa.toUpperCase()})`);
  codeLines.push(`// Datatype (T): ${currentDt} | Variant: ${currentMask} | LMUL: ${effectiveLmul}`);
  codeLines.push(`// rvd<T, LMUL> and rvm<T, LMUL> instantiated with T=${currentDt} and LMUL=${effectiveLmul}`);
  if (isHalfLmul) {
    codeLines.push(`// Note: LMUL = -2 represents LMUL = 1/2 (d2)`);
  }
  codeLines.push(`// =============================================================================`);
  codeLines.push("");

  const isaInfo = entry.isa_support ? entry.isa_support[isa] : null;
  const hwLmuls = (isaInfo && isaInfo.hw_lmul) || (isa === "rvv" ? [1, 2, 4, 8, -2] : [1]);
  const currentLmulVal = isHalfLmul ? -2 : numLmul;
  const isHwLmul = hwLmuls.includes(currentLmulVal);

  let sectionIdx = 1;

  // 1. Base Layer
  if (isHwLmul) {
    const lmulKey = String(effectiveLmul);
    const snippetDict = (isaInfo && isaInfo.code_snippets_by_lmul && isaInfo.code_snippets_by_lmul[lmulKey])
      || (isaInfo && isaInfo.code_snippets)
      || {};
    const nativeSnip = snippetDict[currentDt]
      || (isaInfo && isaInfo.code_snippets && isaInfo.code_snippets[currentDt])
      || null;
    const emuAlgo = isaInfo && isaInfo.emulation_algorithms ? isaInfo.emulation_algorithms[currentDt] : null;

    codeLines.push(`// ${sectionIdx++}. Base Primitive Operation (LMUL = ${effectiveLmul}, unmasked)`);
    codeLines.push(`${retTypeLmul} ${entry.name}(${argDeclLmul}) {`);
    if (nativeSnip) {
      codeLines.push(`    // Level 0 (Native Hardware Intrinsic Mapping)`);
      codeLines.push(`    return ${nativeSnip.replace(/;\s*$/, "")};`);
    } else if (emuAlgo) {
      codeLines.push(`    // Level 1/2 (Emulated Algorithm via MIPP primitives)`);
      emuAlgo.split("\n").forEach((l) => codeLines.push(`    ${l}`));
    } else {
      codeLines.push(`    return mipp::${entry.name}(${callArgs});`);
    }
    codeLines.push(`}`);
    codeLines.push("");
  } else {
    const nativeSnip = isaInfo && isaInfo.code_snippets ? isaInfo.code_snippets[currentDt] : null;
    const emuAlgo = isaInfo && isaInfo.emulation_algorithms ? isaInfo.emulation_algorithms[currentDt] : null;

    codeLines.push(`// ${sectionIdx++}. Base Primitive Operation (LMUL = 1, unmasked)`);
    codeLines.push(`${retType1} ${entry.name}(${argDecl1}) {`);
    if (nativeSnip) {
      codeLines.push(`    // Level 0 (Native Hardware Intrinsic Mapping)`);
      codeLines.push(`    return ${nativeSnip.replace(/;\s*$/, "")};`);
    } else if (emuAlgo) {
      codeLines.push(`    // Level 1/2 (Emulated Algorithm via MIPP primitives)`);
      emuAlgo.split("\n").forEach((l) => codeLines.push(`    ${l}`));
    } else {
      codeLines.push(`    return mipp::${entry.name}(${callArgs});`);
    }
    codeLines.push(`}`);
    codeLines.push("");

    // 2. LMUL Layer (if LMUL != 1 and not hardware native)
    if (isHalfLmul) {
      codeLines.push(`// ${sectionIdx++}. Sub-vector Specialization (LMUL = -2 / d2)`);
      codeLines.push(`// Note: LMUL = -2 represents LMUL = 1/2 (d2)`);
      codeLines.push(`${retTypeLmul} ${entry.name}(${argDeclLmul}) {`);
      codeLines.push(`    // Operation on half-vector via narrower architecture or lower register half`);
      codeLines.push(`    return mipp::${entry.name}< -2 >(${callArgs});`);
      codeLines.push(`}`);
      codeLines.push("");
    } else if (numLmul > 1) {
      codeLines.push(`// ${sectionIdx++}. Vectorized Multi-Register Unrolling (LMUL = ${numLmul})`);
      codeLines.push(`${retTypeLmul} ${entry.name}(${argDeclLmul}) {`);
      codeLines.push(`    ${retTypeLmul} res;`);
      codeLines.push(`    for (int i = 0; i < ${numLmul}; i++) {`);
      codeLines.push(`        res[i] = mipp::${entry.name}(${argNames.map((a) => `${a}[i]`).join(", ")});`);
      codeLines.push(`    }`);
      codeLines.push(`    return res;`);
      codeLines.push(`}`);
      codeLines.push("");
    }
  }

  // Predicated Execution Layer (Mask Layer)
  if (currentMask === "mask") {
    codeLines.push(`// ${sectionIdx++}. Predicated Execution Layer (Blend Preservation)`);
    codeLines.push(`${retTypeLmul} ${entry.name}_mask(const rvm<${currentDt}, ${effectiveLmul}> m0, ${argDeclLmul}) {`);
    codeLines.push(`    ${retTypeLmul} op = mipp::${entry.name}(${callArgs});`);
    codeLines.push(`    return mipp::blend(op, ${argNames[0]}, m0); // Inactive lanes preserve ${argNames[0]}`);
    codeLines.push(`}`);
  } else if (currentMask === "maskz") {
    codeLines.push(`// ${sectionIdx++}. Predicated Execution Layer (Zeroing False Lanes)`);
    codeLines.push(`${retTypeLmul} ${entry.name}_maskz(const rvm<${currentDt}, ${effectiveLmul}> m0, ${argDeclLmul}) {`);
    codeLines.push(`    ${retTypeLmul} op = mipp::${entry.name}(${callArgs});`);
    if (isRvmReturn) {
      codeLines.push(`    return mipp::andb_k(op, m0); // Inactive lanes set to zero`);
    } else {
      codeLines.push(`    return mipp::andb(mipp::toreg(m0), op); // Inactive lanes set to zero`);
    }
    codeLines.push(`}`);
  } else if (currentMask === "masks") {
    codeLines.push(`// ${sectionIdx++}. Predicated Execution Layer (Scalar Condition)`);
    codeLines.push(`${retTypeLmul} ${entry.name}_masks(const rvm<${currentDt}, ${effectiveLmul}> m0, const rvd<${currentDt}, ${effectiveLmul}> src, ${argDeclLmul}) {`);
    codeLines.push(`    ${retTypeLmul} op = mipp::${entry.name}(${callArgs});`);
    codeLines.push(`    return mipp::blend(op, src, m0); // Inactive lanes preserve src`);
    codeLines.push(`}`);
  }

  const fullCode = codeLines.join("\n");

  return `
    <div class="mipp-modal-backdrop visible active" id="mipp-algo-modal-backdrop">
      <div class="mipp-modal-container mipp-modal-content" style="max-width: 780px;">
        <div class="mipp-modal-header">
          <div style="display: flex; gap: 0.6rem; align-items: center; flex-wrap: wrap;">
            <h3 class="mipp-modal-title" style="margin: 0;">Algorithm: <code>mipp::${escapeHtml(entry.name)}</code></h3>
            <span class="mipp-isa-badge mipp-isa-${isa}">${namesMap[isa] || isa.toUpperCase()}</span>
            <span class="mipp-filter-chip" style="font-size: 0.78rem;">LMUL = ${isHalfLmul ? "1/2 (-2)" : effectiveLmul}</span>
          </div>
          <button class="mipp-modal-close-btn" id="mipp-algo-modal-close" title="Close modal">×</button>
        </div>

        <div class="mipp-modal-body" style="display: flex; flex-direction: column; gap: 0.85rem;">
          <!-- Selectors Toolbar: Datatype Dropdown & Mask Variant Badge -->
          <div style="display: flex; align-items: center; justify-content: space-between; flex-wrap: wrap; gap: 0.75rem; padding-bottom: 0.25rem;">
            <!-- Datatype Selector -->
            <div style="display: flex; align-items: center; gap: 0.45rem;">
              <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
                Datatype:
              </span>
              <select class="mipp-scalar-dt-select" id="mipp-algo-modal-dt-select" data-card="${escapeHtml(entry.name)}">
                ${selectableDts.map((d) => `
                  <option value="${d}" ${d === currentDt ? "selected" : ""}>${d}</option>
                `).join("")}
              </select>
            </div>

            <!-- Mask Variant Badge -->
            <div style="display: flex; align-items: center; gap: 0.45rem;">
              <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
                Variant:
              </span>
              <span class="mipp-mask-badge mask-${currentMask}" style="font-size: 0.78rem; padding: 0.2rem 0.6rem;">
                ${currentMask}
              </span>
            </div>
          </div>

          <!-- Code Box -->
          <div class="mipp-code-box">
            <div class="mipp-code-box-header">
              <span class="mipp-code-lang">Abstract C++ Implementation</span>
              <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(fullCode)}" title="Copy algorithm code">
                ${ICON_COPY}
              </button>
            </div>
            <pre><code>${highlightCpp(fullCode)}</code></pre>
          </div>
        </div>
      </div>
    </div>
  `;
}
