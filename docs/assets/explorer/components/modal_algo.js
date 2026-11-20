/**
 * MIPP API Explorer - "Algorithm" modal.
 * Shows the code of one function for one ISA, datatype, mask variant, LMUL and set of compiler
 * flags, taken from the generated headers (algo_source.js): the Abstract C++ view (C++ Functional
 * API) and the Flat C view (self-contained, runs on Compiler Explorer).
 */
import { escapeHtml, ICON_COPY, ICON_GODBOLT } from "../explorer.config.js";
import { highlightCpp } from "../syntax.js";
import { SIMD_EXT_DISPLAY_NAMES, ALL_MASK_MODES, LEVEL_DESCRIPTIONS, apiMetadata, apiData, maskSupportOf, isLmulUndefined, undefinedLmulNotice } from "../data.js";
import { state } from "../state.js";
import { getCompilerConfigForFlat, buildGodboltUrlForFlat } from "../codegen.js";
import { getLoadedSources, buildAbstractCode, buildFlatCode, parseCName } from "../algo_source.js";

export function getAllModalIsas() {
  return Object.keys(apiMetadata.isas || {});
}

/** ISA shown by the modal (the one of modalData, or the first ISA). */
export function algoModalIsa(modalData) {
  const all = getAllModalIsas();
  const raw = modalData && (modalData.isa || modalData.simdExt);
  return all.includes(raw) ? raw : (all[0] || "");
}

const DOCS = "../user/";
const ISA_LABEL = () => ({ ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" });
const levelBadge = (lvl, title) => `<span class="mipp-isa-badge lvl-${lvl === null || lvl === undefined ? "na" : lvl}" title="${escapeHtml(title || "")}">${lvl === null || lvl === undefined ? "–" : `L${lvl}`}</span>`;

/** One or two lines on the LMUL and the mask variant of the shown code, with links to the docs. */
function contextNotes(isa, lmul, mask, maskBySelect) {
  const notes = [];
  const l = String(lmul);
  const name = ISA_LABEL()[isa] || isa.toUpperCase();
  if (l === "-2") {
    const how = {
      avx: "a register of the narrower ISA (an SSE register for AVX)", avx512: "a register of the narrower ISA (an AVX register for AVX-512)",
      rvv: "a native fractional register group (mf2)", scalar: "an array of N/2 elements",
    }[isa] || "the lower half of a full register (the upper lanes are ignored)";
    notes.push(`<strong>LMUL 1/2</strong> (half-vector, <code>d2</code>): on ${escapeHtml(name)}, ${how}. <a href="${DOCS}vector_types_and_lmul/" target="_blank">Vector types &amp; LMUL</a>`);
  } else if (l !== "1") {
    notes.push(isa === "rvv"
      ? `<strong>LMUL ${l}</strong>: one group of ${l} hardware registers (RVV register grouping), handled by the instructions themselves. <a href="${DOCS}vector_types_and_lmul/" target="_blank">Vector types &amp; LMUL</a>`
      : `<strong>LMUL ${l}</strong>: ${l} registers (<code>r1</code>, <code>r2</code>, ...) processed one after the other by the LMUL ${Number(l) / 2} function. <a href="${DOCS}vector_types_and_lmul/" target="_blank">Vector types &amp; LMUL</a>`);
  }
  const maskText = {
    mask: "<strong>mask</strong> (merge): the inactive lanes keep the value of the first operand",
    maskz: "<strong>maskz</strong> (zeroing): the inactive lanes are set to zero",
    masks: "<strong>masks</strong> (source): the inactive lanes are taken from <code>src</code>",
  }[mask];
  if (maskText) {
    const how = maskBySelect
      ? "Here the operation is computed on all the lanes, then a <code>select</code> keeps the active ones"
      : "Here the target applies the mask itself (predicated instruction or masked memory access)";
    notes.push(`${maskText}. ${how}. <a href="${DOCS}masking_semantics/" target="_blank">Masking semantics</a>`);
  }
  return notes;
}

/** Navigation target of a function of the call tree (null when it is not a public function). */
function navTarget(cName) {
  const p = parseCName(cName);
  if (!p) return null;
  const entry = apiData.find((e) => e.name === p.func);
  if (!entry) return null;
  const dts = entry.datatypes || [];
  const dt = dts.includes(p.dt) ? p.dt : (dts.includes(p.dt.split(",")[0]) ? p.dt.split(",")[0] : null);
  return dt ? { ...p, dt } : null;
}

function treeLabel(cName) {
  const p = parseCName(cName);
  if (!p) return escapeHtml(cName);
  const lm = p.lmul === "1" ? "" : (p.lmul === "-2" ? " · d2" : ` · m${p.lmul}`);
  const v = p.mask === "unmasked" ? "" : `_${p.mask}`;
  return `${escapeHtml(p.func)}${v}&lt;${escapeHtml(p.dt.replace(",", ", "))}&gt;${lm}`;
}

/** Call tree: each function with its own level and its effective level, clickable. */
function renderTree(node, currentIsa, depth = 0) {
  if (!node) return "";
  const nav = navTarget(node.cName);
  const isaTag = node.table !== currentIsa ? `<span class="mipp-algo-tree-isa">${escapeHtml(ISA_LABEL()[node.table] || node.table)}</span>` : "";
  const KINDS = {
    native: ["native", "Instructions of the ISA"],
    dedicated: ["dedicated emulation", "A sequence of instructions written for this ISA"],
    composition: ["composition", "Calls other MIPP functions"],
    fallback: ["scalar fallback", "Copies the registers to arrays and calls the scalar reference"],
    lanewise: ["from LMUL 1", "Generated from the LMUL 1 function on the same register"],
    wrapper: ["LMUL wrapper", "One call per register of the LMUL below"],
    scalar: ["scalar code", "Plain C loop of the MIPP scalar target"],
  };
  const k = KINDS[node.kind] || [node.kind, ""];
  const own = `<span class="mipp-algo-tree-own" title="${escapeHtml(k[1])}">${escapeHtml(k[0])}</span>`;
  const label = nav && depth > 0
    ? `<button type="button" class="mipp-algo-tree-link" data-algo-nav-func="${escapeHtml(nav.func)}" data-algo-nav-isa="${escapeHtml(nav.isa)}" data-algo-nav-dt="${escapeHtml(nav.dt)}" data-algo-nav-mask="${escapeHtml(nav.mask)}" data-algo-nav-lmul="${escapeHtml(nav.lmul)}" title="Open ${escapeHtml(node.cName)}">${treeLabel(node.cName)}</button>`
    : `<span class="mipp-algo-tree-name" title="${escapeHtml(node.cName)}">${treeLabel(node.cName)}</span>`;
  const kids = node.repeated ? "" : node.children.map((c) => renderTree(c, currentIsa, depth + 1)).join("");
  return `<li>${label}${isaTag} ${levelBadge(node.effective, "Effective level: the highest level of everything this function uses")} ${own}${node.repeated ? ' <span class="mipp-algo-tree-own">(see above)</span>' : ""}${kids ? `<ul>${kids}</ul>` : ""}</li>`;
}

export function renderAlgoModal(modalData) {
  if (!modalData) return "";
  const { entry } = modalData;
  const allModalIsas = getAllModalIsas();
  const defaultIsa = allModalIsas[0] || "";
  const rawIsa = modalData.isa || modalData.simdExt || defaultIsa;
  const currentIsa = allModalIsas.includes(rawIsa) ? rawIsa : defaultIsa;
  const currentView = ["flat", "compare"].includes(modalData.view) ? modalData.view : "abstract";
  const currentScalarSize = Number(modalData.scalarSize) || 256;
  const namesMap = { ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" };

  const allDts = entry.datatypes || [];
  const activeDts = allDts.filter((d) => state.selectedTypes.includes(d));
  const selectableDts = (state.selectedTypes.length > 0 && activeDts.length > 0) ? activeDts : allDts;
  const defaultDt = selectableDts[0] || "float32";
  const currentDt = (modalData.dt && selectableDts.includes(modalData.dt)) ? modalData.dt : defaultDt;

  const maskSupport = maskSupportOf(entry);
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const defaultMask = (state.maskVariant && allVariants.includes(state.maskVariant))
    ? state.maskVariant
    : (allVariants[0] || "unmasked");
  const currentMask = (modalData.mask && allVariants.includes(modalData.mask)) ? modalData.mask : defaultMask;

  const effectiveLmul = (modalData.lmul !== undefined && modalData.lmul !== null) ? String(modalData.lmul) : (state.lmul || "1");
  // functions that change the LMUL (low, high, combine, wcvt, ncvt) are not defined for every LMUL
  const lmulUndefined = isLmulUndefined(entry, effectiveLmul);

  const isHalfLmul = effectiveLmul === "-2";

  // Features resolution (contextual per ISA)
  const features = modalData.features || {};
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[currentIsa] : null;
  const featuresMeta = (isaMeta && isaMeta.features) ? isaMeta.features : { mode: "none", items: [] };

  // Build flatDefines dynamically across all ISAs from explorer metadata
  const flatDefines = {};
  if (apiMetadata.isas) {
    for (const [isaName, iMeta] of Object.entries(apiMetadata.isas)) {
      const fMeta = iMeta.features;
      if (!fMeta || !Array.isArray(fMeta.items)) continue;
      const isHierarchy = fMeta.mode === "hierarchy";
      const isMixed = fMeta.mode === "mixed";
      const tierItems = fMeta.items.filter((it) => isHierarchy || (isMixed && it.type === "tier"));
      const flagItems = fMeta.items.filter((it) => it.type === "flag" || (!isHierarchy && !isMixed));

      if (tierItems.length > 0) {
        const selectedTier = features[isaName] || fMeta.default || (tierItems.length ? tierItems[tierItems.length - 1].id : "");
        const targetIdx = tierItems.findIndex((it) => it.id === selectedTier);
        const effectiveIdx = targetIdx !== -1 ? targetIdx : (tierItems.length - 1);
        tierItems.forEach((it, idx) => {
          const isPassed = (idx <= effectiveIdx);
          flatDefines[it.define] = isPassed;
          flatDefines[it.id] = isPassed;
        });
      }
      if (flagItems.length > 0) {
        for (const it of flagItems) {
          if (it.locked) {
            flatDefines[it.define] = true;
            flatDefines[it.id] = true;
          } else {
            const val = (features[it.id] !== undefined)
              ? Boolean(features[it.id])
              : (features[it.define] !== undefined ? Boolean(features[it.define]) : (it.default !== false));
            flatDefines[it.define] = val;
            flatDefines[it.id] = val;
          }
        }
      }
    }
  }

  // Effective level of the shown code (set from the real code once the tables are loaded)
  let currentImplLvl = "na";

  // Code of the two views: taken from the generated MIPP headers (algo_source.js)
  const sources = getLoadedSources(currentIsa);
  const compilerCfg = getCompilerConfigForFlat(currentIsa, flatDefines, currentScalarSize);
  const algoCfg = {
    isa: currentIsa, func: entry.name, dt: currentDt, mask: currentMask, lmul: effectiveLmul,
    options: compilerCfg.options, simdWidth: currentScalarSize, overrides: flatDefines,
    compilerLabel: compilerCfg.compilerLabel,
  };
  const isaLabel = namesMap[currentIsa] || currentIsa.toUpperCase();
  const tName = (d) => (d.includes(",") ? d.split(",").map((x) => `${x.trim()}_t`).join(" -> ") : `${d}_t`);
  let fullCode = "";
  let flatStandaloneCode = "";
  let godboltUrl = "";
  let godboltRunUrl = "";
  let abstractCalls = [];
  let callTreeRoot = null;
  let loadingHtml = "";
  if (modalData.loadError) {
    loadingHtml = `<div class="mipp-algo-note"><span class="mipp-algo-note-icon">⚠️</span><span>Unable to load the MIPP source code: ${escapeHtml(modalData.loadError)}</span></div>`;
  } else if (!sources) {
    loadingHtml = `<div class="mipp-algo-note"><span class="mipp-algo-note-icon">⏳</span><span>Loading the MIPP source code of ${escapeHtml(isaLabel)}…</span></div>`;
  } else if (!lmulUndefined) {
    const abs = buildAbstractCode(entry, sources, algoCfg);
    abstractCalls = abs.calls || [];
    callTreeRoot = abs.tree || null;
    if (abs.rootFound) {
      currentImplLvl = abs.effectiveLevel;
    } else {
      currentImplLvl = "na";
    }
    const uses = abstractCalls.filter((c) => !c.scalar).map((c) => `${c.cpp.replace(/<.*$/, "")} (L${c.level === null ? "?" : c.level})`);
    const head = [
      "// =============================================================================",
      `// mipp::${entry.name} | ${isaLabel} | ${tName(currentDt)} | ${currentMask} | LMUL ${isHalfLmul ? "1/2 (-2)" : effectiveLmul}`,
      `// Compiler flags: ${compilerCfg.options}`,
      abs.rootFound ? `// Effective level: ${currentImplLvl} (${LEVEL_DESCRIPTIONS[currentImplLvl] || ""})` : "// Not defined for these compiler flags",
    ];
    if (uses.length) head.push(`// Calls: ${uses.join(", ")}`);
    if (abstractCalls.some((c) => c.scalar)) head.push("// The scalar fallback calls the C API of the scalar target (mipp_scalar_*).");
    head.push("// C++ Functional API (#include <mipp.hpp>): rvd<T, LMUL> = data register, rvm<T, LMUL> = mask.");
    head.push("// =============================================================================", "");
    fullCode = head.join("\n") + "\n" + abs.code;
    if (currentView === "flat") {
      flatStandaloneCode = buildFlatCode(entry, sources, algoCfg).code;
      godboltUrl = buildGodboltUrlForFlat(flatStandaloneCode, currentIsa, flatDefines, currentScalarSize);
      // the same code with a main() that runs it and compares with the scalar reference
      const runCode = buildFlatCode(entry, sources, algoCfg, { verify: true }).code;
      godboltRunUrl = buildGodboltUrlForFlat(runCode, currentIsa, flatDefines, currentScalarSize, { execute: true });
    }
  }
  // Compare view: the same function on several ISAs, side by side
  const compareIsas = (modalData.compareIsas && modalData.compareIsas.length)
    ? modalData.compareIsas.filter((i) => allModalIsas.includes(i))
    : [currentIsa, ...["sse", "neon", "rvv", "avx", "sve"].filter((i) => i !== currentIsa && allModalIsas.includes(i))].slice(0, 3);
  let compareHtml = "";
  if (currentView === "compare" && !lmulUndefined) {
    const cols = compareIsas.map((isa) => {
      const src = getLoadedSources(isa);
      const label = namesMap[isa] || isa.toUpperCase();
      if (!src) return `<div class="mipp-code-box"><div class="mipp-code-box-header"><span class="mipp-code-lang">${escapeHtml(label)}</span></div><pre><code>Loading…</code></pre></div>`;
      const cc = getCompilerConfigForFlat(isa, flatDefines, currentScalarSize);
      const r = buildAbstractCode(entry, src, { ...algoCfg, isa, options: cc.options, compilerLabel: cc.compilerLabel });
      const lv = r.rootFound ? r.effectiveLevel : null;
      return `<div class="mipp-code-box">
        <div class="mipp-code-box-header">
          <div class="mipp-code-box-header-left">
            <span class="mipp-code-lang">${escapeHtml(label)}</span>
            ${levelBadge(lv, lv === null ? "Not defined" : `Effective level ${lv}`)}
            <span class="mipp-algo-tree-own">${escapeHtml(cc.options)}</span>
          </div>
          <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(r.code)}" title="Copy ${escapeHtml(label)} code">${ICON_COPY}</button>
        </div>
        <pre><code>${highlightCpp(r.code, {}, { isa })}</code></pre>
      </div>`;
    }).join("");
    compareHtml = `
      <div class="mipp-modal-ctrl-group mipp-compare-picker">
        <span class="mipp-control-label">Compare:</span>
        <div class="mipp-segmented-group">
          ${allModalIsas.map((isa) => `<button type="button" class="mipp-segment-btn ${compareIsas.includes(isa) ? "active" : ""}" data-modal-compare-isa="${isa}">${escapeHtml((namesMap[isa] || isa.toUpperCase()).replace("ARM ", ""))}</button>`).join("")}
        </div>
      </div>
      <div class="mipp-algo-compare">${cols}</div>`;
  }
  const treeHas = (n, f) => Boolean(n) && (f(n) || n.children.some((c) => treeHas(c, f)));
  const maskBySelect = treeHas(callTreeRoot, (n) => { const p = parseCName(n.cName); return Boolean(p) && p.func === "select"; });
  const notes = contextNotes(currentIsa, effectiveLmul, currentMask, maskBySelect);
  const notesHtml = notes.length ? `<div class="mipp-algo-note mipp-algo-context"><span class="mipp-algo-note-icon">📐</span><span>${notes.join("<br>")}</span></div>` : "";
  const treeHtml = callTreeRoot ? `
    <div class="mipp-algo-tree">
      <div class="mipp-algo-tree-title">How it is built <span class="mipp-algo-tree-own">— each function with what its body is and its level: the highest level of everything it uses (<a href="${DOCS}implementation_levels/" target="_blank">implementation levels</a>)</span></div>
      <ul>${renderTree(callTreeRoot, currentIsa)}</ul>
    </div>` : "";
  const lvlDescFinal = LEVEL_DESCRIPTIONS[currentImplLvl] || (currentImplLvl === "na" ? "Not Supported" : `Level ${currentImplLvl}`);

  const VARIANT_LETTERS = { unmasked: "U", mask: "M", maskz: "Z", masks: "S" };
  const VARIANT_TITLES = {
    unmasked: "Unmasked",
    mask: "Mask (merge)",
    maskz: "Maskz (zeroing)",
    masks: "Masks (sourcing)"
  };

  const simdWidthHtml = `
    <div class="mipp-modal-ctrl-group">
      <span class="mipp-control-label">SIMD Width:</span>
      <div class="mipp-segmented-group" id="mipp-modal-scalarsize-group">
        ${[128, 256, 512, 1024, 2048].map((sz) => `
          <button type="button" class="mipp-segment-btn ${sz === currentScalarSize ? "active" : ""}" data-modal-scalarsize="${sz}" title="${sz} bits">${sz}b</button>
        `).join("")}
      </div>
    </div>
  `;

  let featureControlsHtml = "";

  const isHierarchy = featuresMeta.mode === "hierarchy";
  const isMixed = featuresMeta.mode === "mixed";
  const tierItems = (featuresMeta.items || []).filter((it) => isHierarchy || (isMixed && it.type === "tier"));
  const flagItems = (featuresMeta.items || []).filter((it) => it.type === "flag" || (!isHierarchy && !isMixed));

  if (tierItems.length > 0 || flagItems.length > 0) {
    let tierGroupHtml = "";
    if (tierItems.length > 0) {
      const activeTier = features[currentIsa] || featuresMeta.default || (tierItems.length ? tierItems[tierItems.length - 1].id : "");
      const selectableItems = tierItems.filter((it) => !it.locked);
      tierGroupHtml = `
        <div class="mipp-segmented-group" id="mipp-modal-tier-group">
          ${selectableItems.map((it) => `
            <button type="button" class="mipp-segment-btn ${activeTier === it.id ? "active" : ""}" data-modal-tier="${it.id}" title="${escapeHtml(it.description || it.label)}">${escapeHtml(it.label)}</button>
          `).join("")}
        </div>
      `;
    }

    let flagGroupHtml = "";
    if (flagItems.length > 0) {
      flagGroupHtml = `
        <div class="mipp-segmented-group" id="mipp-modal-features-group">
          ${flagItems.map((it) => {
            const isActive = flatDefines[it.define] !== false;
            const isLocked = Boolean(it.locked);
            const style = isLocked ? 'style="pointer-events: none; opacity: 0.85;"' : '';
            return `
              <button type="button" class="mipp-segment-btn ${isActive ? "active" : ""}" data-modal-toggle-feature="${it.id}" ${isLocked ? 'data-modal-locked="true"' : ""} title="${escapeHtml(it.description || it.label)}" ${style}>
                ${escapeHtml(it.label)}
              </button>
            `;
          }).join("")}
        </div>
      `;
    }

    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        ${tierGroupHtml}
        ${flagGroupHtml}
      </div>
    `;
  }

  if (isaMeta && (isaMeta.is_scalar || isaMeta.vector_size_bits === "scalable")) {
    featureControlsHtml += simdWidthHtml;
  }

  return `
    <div class="mipp-modal-backdrop visible active" id="mipp-algo-modal-backdrop">
      <div class="mipp-modal-container mipp-modal-content mipp-algo-modal-content">
        <!-- Header -->
        <div class="mipp-modal-header">
          <div style="display: flex; gap: 0.65rem; align-items: center; flex-wrap: wrap;">
            <h3 class="mipp-modal-title" style="margin: 0;">Algorithm: <code>mipp::${escapeHtml(entry.name)}</code></h3>
          </div>
          <div style="display: flex; gap: 0.45rem; align-items: center;">
            ${(modalData.history && modalData.history.length) ? `<button class="mipp-modal-share-btn" id="mipp-algo-modal-back" title="Back to ${escapeHtml(modalData.history[modalData.history.length - 1].entry.name)}" aria-label="Back">←</button>` : ""}
            <button class="mipp-modal-share-btn" id="mipp-algo-modal-share" title="Copy direct link to this algorithm" aria-label="Share direct link">🔗</button>
            <button class="mipp-modal-close-btn" id="mipp-algo-modal-close" title="Close modal" aria-label="Close modal">×</button>
          </div>
        </div>

        <div class="mipp-modal-body" style="display: flex; flex-direction: column; gap: 0.85rem; min-width: 0; max-width: 100%; box-sizing: border-box;">
          <!-- Selectors Toolbar: Shared Across Views (Above Tabs) -->
          <div class="mipp-modal-toolbar">
            <!-- ISA Selector -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">SIMD Ext:</span>
              <div class="mipp-segmented-group" id="mipp-modal-isa-group">
                ${allModalIsas.map((ext) => `
                  <button type="button" class="mipp-segment-btn ${ext === currentIsa ? "active" : ""}" data-modal-isa="${ext}" title="${namesMap[ext] || ext.toUpperCase()}">
                    ${(namesMap[ext] || ext.toUpperCase()).replace("ARM ", "")}
                  </button>
                `).join("")}
              </div>
            </div>

            <!-- Datatype Selector -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">Datatype:</span>
              <select class="mipp-scalar-dt-select" id="mipp-algo-modal-dt-select" data-card="${escapeHtml(entry.name)}">
                ${selectableDts.map((d) => `
                  <option value="${d}" ${d === currentDt ? "selected" : ""}>${d}</option>
                `).join("")}
              </select>
            </div>

            <!-- Variant Selector (Segmented buttons) -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">Variant:</span>
              <div class="mipp-segmented-group" id="mipp-modal-mask-group">
                ${allVariants.map((m) => {
                  const isActive = m === currentMask;
                  return `<button type="button" class="mipp-segment-btn ${isActive ? "active" : ""}" data-modal-mask="${m}" title="${VARIANT_TITLES[m] || m}">${VARIANT_LETTERS[m] || m}</button>`;
                }).join("")}
              </div>
            </div>

            <!-- LMUL Selector (Segmented buttons) -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">LMUL:</span>
              <div class="mipp-segmented-group" id="mipp-modal-lmul-group">
                ${["1", "2", "4", "8", "-2"].map((l) => {
                  const isActive = l === String(effectiveLmul);
                  return `<button type="button" class="mipp-segment-btn ${isActive ? "active" : ""}" data-modal-lmul="${l}" title="${l === "-2" ? "Half vector (LMUL=1/2 / d2)" : `LMUL = ${l}`}">${l === "-2" ? "1/2" : l}</button>`;
                }).join("")}
              </div>
            </div>

            <!-- Contextual Features / Target Switcher / SIMD Width -->
            ${featureControlsHtml}
          </div>

          <!-- Modal View Tabs: Abstract C++ Implementation vs Flat C Code -->
          <div class="mipp-modal-tabs" role="tablist">
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'abstract' ? 'active' : ''}" data-modal-view="abstract" role="tab" aria-selected="${currentView === 'abstract'}">
              Abstract C++ Implementation
            </button>
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'flat' ? 'active' : ''}" data-modal-view="flat" role="tab" aria-selected="${currentView === 'flat'}">
              Flat C Code
            </button>
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'compare' ? 'active' : ''}" data-modal-view="compare" role="tab" aria-selected="${currentView === 'compare'}">
              Compare ISAs
            </button>
          </div>

          <!-- Active View Content -->
          ${lmulUndefined ? undefinedLmulNotice(entry, effectiveLmul) : currentView === 'compare' ? `${notesHtml}${compareHtml}` : loadingHtml ? loadingHtml : currentView === 'abstract' ? `
            ${notesHtml}
            <div class="mipp-algo-note">
              <span class="mipp-algo-note-icon">💡</span>
              <span>The code of the MIPP headers for these flags, written with the C++ Functional API: <code>rvd&lt;T, LMUL&gt;</code> is a <strong>data</strong> register, <code>rvm&lt;T, LMUL&gt;</code> a <strong>mask</strong> register. Each <code>mipp::</code> call is another MIPP function, with its own level.</span>
            </div>

            <!-- Abstract C++ Code Box -->
            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left" style="display: flex; gap: 0.55rem; align-items: center; flex-wrap: wrap;">
                  <span class="mipp-code-lang">Abstract C++ Implementation</span>
                  <span class="mipp-isa-badge lvl-${currentImplLvl}" title="Effective implementation level: Level ${currentImplLvl} (${escapeHtml(lvlDescFinal)})">${currentImplLvl === "na" ? "N/A" : `L${currentImplLvl}`}</span>
                </div>
                <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(fullCode)}" title="Copy algorithm code">
                  ${ICON_COPY}
                </button>
              </div>
              <pre><code>${highlightCpp(fullCode, {}, { isa: currentIsa })}</code></pre>
            </div>
            ${treeHtml}
          ` : `
            <div class="mipp-algo-note">
              <span class="mipp-algo-note-icon">💡</span>
              <span>Self-contained C: the function and everything it uses, as in the MIPP headers. Open it in Godbolt and look at the assembly of <code>test</code>: the MIPP calls are inlined, only the instructions of the operation remain in the loop.</span>
            </div>
            ${notesHtml}
            <!-- Flat C99 Code Box -->
            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left" style="display: flex; gap: 0.55rem; align-items: center; flex-wrap: wrap;">
                  <span class="mipp-code-lang">Flat C Code</span>
                  <span class="mipp-isa-badge lvl-${currentImplLvl}" title="Effective implementation level: Level ${currentImplLvl} (${escapeHtml(lvlDescFinal)})">${currentImplLvl === "na" ? "N/A" : `L${currentImplLvl}`}</span>
                </div>
                <div style="display: flex; gap: 0.5rem; align-items: center;">
                  <a href="${godboltRunUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-run-link" title="Open in Godbolt with a main() that runs test() once and compares the result with the scalar reference of MIPP">Run</a>
                  <a href="${godboltUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-btn" title="Open in Godbolt and look at the assembly of test()">
                    ${ICON_GODBOLT}
                    <span>Open in Godbolt</span>
                  </a>
                  <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(flatStandaloneCode)}" title="Copy standalone C code">
                    ${ICON_COPY}
                  </button>
                </div>
              </div>
              <pre><code>${highlightCpp(flatStandaloneCode, entry.scalar_macros || {}, { isa: currentIsa })}</code></pre>
            </div>
          `}
        </div>
      </div>
    </div>
  `;
}
