/**
 * MIPP API Explorer - Tab 1: Hardware Matrix
 */
import { escapeHtml } from "../explorer.config.js";
import { ALL_SIMD_EXTS, SIMD_EXT_DISPLAY_NAMES, ALL_MASK_MODES } from "../data.js";
import { getDtBadgeClass } from "../syntax.js";
import { state } from "../state.js";

export function renderTabHw(entry) {
  const extsList = ALL_SIMD_EXTS;
  const namesMap = SIMD_EXT_DISPLAY_NAMES;
  const selectedExts = state.selectedSimdExts || [];
  const activeExts = extsList.filter((ext) => selectedExts.includes(ext));
  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));

  if (activeExts.length === 0) {
    return `
      <div style="padding: 1.5rem; text-align: center; color: var(--md-default-fg-color--lighter);">
        <p style="margin: 0;">No target SIMD extensions selected in the sidebar filter. Enable at least one SIMD extension to view hardware mappings.</p>
      </div>
    `;
  }

  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const activeSidebarMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
  const effectiveMasks = activeSidebarMasks.length > 0 ? activeSidebarMasks : allVariants;

  if (!state.cardHwMask) state.cardHwMask = {};
  const curCardMask = state.cardHwMask[entry.name];
  const currentMask = curCardMask && effectiveMasks.includes(curCardMask)
    ? curCardMask
    : (effectiveMasks[0] || "unmasked");
  state.cardHwMask[entry.name] = currentMask;

  return `
    <div>
      <!-- Mask Variant Toolbar -->
      <div style="display: flex; align-items: center; justify-content: space-between; flex-wrap: wrap; gap: 0.75rem; margin-bottom: 0.75rem; padding-bottom: 0.35rem; border-bottom: 1px solid var(--mipp-card-border, #e2e8f0);">
        <div style="display: flex; align-items: center; gap: 0.4rem; flex-wrap: wrap;">
          <span style="font-size: 0.78rem; font-weight: 600; color: var(--md-default-fg-color--lighter);">Mask Variant:</span>
          ${effectiveMasks.map((v) => {
            const isActive = v === currentMask;
            return `
              <button class="mipp-mask-badge mask-${v} mipp-test-variant-btn ${isActive ? "active" : ""}"
                      data-hw-mask="${v}" data-card="${escapeHtml(entry.name)}" title="Switch Hardware Matrix to ${v}">
                ${v} ${isActive ? "✓" : ""}
              </button>
            `;
          }).join("")}
        </div>
      </div>

      <div class="mipp-hw-table-wrapper">
        <table class="mipp-hw-table">
          <thead>
            <tr>
              <th class="mipp-hw-col-ext">
                <span class="mipp-hw-header-full">SIMD Extension</span>
                <span class="mipp-hw-header-short">Ext</span>
              </th>
              <th class="mipp-hw-col-tier">Tier</th>
              <th class="mipp-hw-col-mapping">Hardware Mapping & Emulation Logic</th>
            </tr>
          </thead>
          <tbody>
            ${activeExts.map((isa) => {
              const info = entry.isa_support ? entry.isa_support[isa] : null;
              if (!info) {
                return `
                  <tr>
                    <td class="mipp-hw-col-ext" style="font-weight: 700; font-family: var(--md-code-font, monospace);">${namesMap[isa] || isa.toUpperCase()}</td>
                    <td class="mipp-hw-col-tier"><span class="mipp-isa-badge lvl-na">N/A</span></td>
                    <td class="mipp-hw-col-mapping"><span style="color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">Not Supported</span></td>
                  </tr>
                `;
              }

              const currentLmul = Number(state.lmul);
              const hwLmuls = info.hw_lmul || (isa === "rvv" ? [1, 2, 4, 8, -2] : [1]);
              const isLmulEmulated = currentLmul !== 1 && !hwLmuls.includes(currentLmul) && (info.overall_level < 2);

              const lmulKey = String(state.lmul);
              const nativeDict = (info.native_instructions_by_lmul && info.native_instructions_by_lmul[lmulKey])
                || info.native_instructions
                || {};
              let instrs = Object.entries(nativeDict);
              if (activeDts.length > 0) {
                instrs = instrs.filter(([dt]) => activeDts.includes(dt));
              }

              const snippetDict = (info.code_snippets_by_lmul && info.code_snippets_by_lmul[lmulKey])
                || info.code_snippets
                || {};
              const sampleCode = snippetDict ? (
                activeDts.length > 0 && activeDts[0] in snippetDict
                  ? snippetDict[activeDts[0]]
                  : Object.values(snippetDict)[0]
              ) : null;

              const hasEmulationAlgos = info.emulation_algorithms && Object.keys(info.emulation_algorithms).length > 0;
              const dtsToConsider = activeDts.length > 0 ? activeDts : (entry.datatypes || []);

              const getDtLevel = (dt) => {
                let lvl;
                if (currentMask === "unmasked") {
                  lvl = info.by_datatype && info.by_datatype[dt] !== undefined
                    ? info.by_datatype[dt]
                    : (info.overall_level !== undefined ? info.overall_level : 3);
                } else {
                  const maskedDict = info.masked_by_datatype ? info.masked_by_datatype[currentMask] : null;
                  lvl = maskedDict && maskedDict[dt] !== undefined
                    ? maskedDict[dt]
                    : 2;
                }
                if (isLmulEmulated && lvl < 2) lvl = 2;
                return lvl;
              };

              let baseLevel = 3;
              if (dtsToConsider.length > 0) {
                const levels = dtsToConsider.map(getDtLevel);
                baseLevel = Math.min(...levels);
              } else {
                baseLevel = getDtLevel(activeDts[0] || "float32");
              }

              // Partition datatypes into L0 native vs. L1/L2 emulated
              let l0Instrs = instrs.filter(([dt]) => getDtLevel(dt) === 0);
              if (l0Instrs.length === 0 && instrs.length > 0 && baseLevel === 0) {
                l0Instrs = instrs;
              }

              const emuDts = dtsToConsider.filter((dt) => {
                const lvl = getDtLevel(dt);
                return lvl === 1 || lvl === 2;
              });
              const emuLevels = emuDts.map(getDtLevel);
              const emuLevel = emuLevels.length > 0 ? Math.min(...emuLevels) : 2;

              const l3Dts = dtsToConsider.filter((dt) => getDtLevel(dt) === 3);
              const l3Html = (l3Dts.length > 0 && (l0Instrs.length > 0 || emuDts.length > 0)) ? `
                <div style="margin-top: 0.35rem; color: var(--md-default-fg-color--lighter, #94a3b8); font-size: 0.72rem; font-style: italic;">
                  Scalar fallback (L3): ${l3Dts.join(", ")}
                </div>
              ` : "";

              let mappingHtml = '<span style="color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">Scalar Fallback Loop (L3)</span>';

              if (l0Instrs.length > 0 && emuDts.length > 0) {
                // Heterogeneous case: some types native L0, some types emulated L1/L2
                const nativeHtml = l0Instrs.map(([dt, iname]) => `
                  <div style="display: flex; align-items: center; gap: 0.5rem; margin: 0.25rem 0;">
                    <span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${dt}</span>
                    <code class="mipp-hw-intrinsic-code">${escapeHtml(iname)}</code>
                  </div>
                `).join("");

                const l0Dt = l0Instrs[0][0];
                const l0SampleCode = (snippetDict && l0Dt in snippetDict) ? snippetDict[l0Dt] : sampleCode;
                const sampleCodeHtml = l0SampleCode ? `
                  <div style="margin-top: 0.35rem; font-family: var(--md-code-font, monospace); font-size: 0.72rem; opacity: 0.75; overflow-x: auto;">
                    ↳ <code>${escapeHtml(l0SampleCode)}</code>
                  </div>
                ` : "";

                const emuLabel = isLmulEmulated
                  ? `LMUL=${state.lmul} software-emulated vector sequence`
                  : (emuLevel === 1 ? "Target-specific multi-instruction emulation" : "Generic portable vector AST algorithm");
                const defaultAlgoDt = emuDts[0] || "float32";

                const emuBtnHtml = (hasEmulationAlgos || isLmulEmulated || currentMask !== "unmasked" || emuLevel === 1 || emuLevel === 2) ? `
                  <div style="margin-top: 0.5rem;">
                    <button class="mipp-algo-modal-btn lvl-${emuLevel}" title="${escapeHtml(emuLabel)}" data-algo-card="${entry.name}" data-algo-func="${entry.name}" data-algo-isa="${isa}" data-algo-level="${emuLevel}" data-algo-dt="${defaultAlgoDt}" data-algo-mask="${currentMask}">
                      🔍 View Algorithm (${emuDts.join(", ")})
                    </button>
                  </div>
                ` : `
                  <div style="margin-top: 0.5rem;">
                    <span style="color: ${emuLevel === 1 ? '#2563eb' : '#f59e0b'}; font-weight: 500; font-size: 0.85rem;">${emuLabel} (${emuDts.join(", ")})</span>
                  </div>
                `;

                mappingHtml = nativeHtml + sampleCodeHtml + emuBtnHtml + l3Html;

              } else if (l0Instrs.length > 0) {
                // Pure L0 native
                const nativeHtml = l0Instrs.map(([dt, iname]) => `
                  <div style="display: flex; align-items: center; gap: 0.5rem; margin: 0.25rem 0;">
                    <span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${dt}</span>
                    <code class="mipp-hw-intrinsic-code">${escapeHtml(iname)}${currentMask !== "unmasked" ? ` (${currentMask})` : ""}</code>
                  </div>
                `).join("");

                const l0Dt = l0Instrs[0][0];
                const l0SampleCode = (snippetDict && l0Dt in snippetDict) ? snippetDict[l0Dt] : sampleCode;
                const sampleCodeHtml = l0SampleCode ? `
                  <div style="margin-top: 0.35rem; font-family: var(--md-code-font, monospace); font-size: 0.72rem; opacity: 0.75; overflow-x: auto;">
                    ↳ <code>${escapeHtml(l0SampleCode)}</code>
                  </div>
                ` : "";

                mappingHtml = nativeHtml + sampleCodeHtml + l3Html;

              } else if (emuDts.length > 0 || baseLevel === 1 || baseLevel === 2) {
                // Pure emulated L1/L2
                const effectiveLevel = emuDts.length > 0 ? emuLevel : baseLevel;
                const label = isLmulEmulated
                  ? `LMUL=${state.lmul} software-emulated vector sequence`
                  : (effectiveLevel === 1 ? "Target-specific multi-instruction emulation" : "Generic portable vector AST algorithm");

                if (hasEmulationAlgos || isLmulEmulated || currentMask !== "unmasked" || effectiveLevel === 1 || effectiveLevel === 2) {
                  const defaultAlgoDt = (activeDts.length > 0 ? activeDts[0] : null)
                    || (info.emulation_algorithms && Object.keys(info.emulation_algorithms)[0])
                    || (entry.datatypes && entry.datatypes[0])
                    || "";
                  const btnLabel = currentMask !== "unmasked" ? `🔍 View Algorithm (${currentMask})` : "🔍 View Algorithm";
                  mappingHtml = `
                    <button class="mipp-algo-modal-btn lvl-${effectiveLevel}" title="${escapeHtml(label)}" data-algo-card="${entry.name}" data-algo-func="${entry.name}" data-algo-isa="${isa}" data-algo-level="${effectiveLevel}" data-algo-dt="${defaultAlgoDt}" data-algo-mask="${currentMask}">
                      ${btnLabel}
                    </button>
                  ` + l3Html;
                } else {
                  mappingHtml = `<span style="color: ${effectiveLevel === 1 ? '#2563eb' : '#f59e0b'}; font-weight: 500;">${label}</span>` + l3Html;
                }
              }

              return `
                <tr>
                  <td class="mipp-hw-col-ext" style="font-weight: 700; font-family: var(--md-code-font, monospace);">${namesMap[isa] || isa.toUpperCase()}</td>
                  <td class="mipp-hw-col-tier">
                    <span class="mipp-isa-badge lvl-${baseLevel}">L${baseLevel}</span>
                  </td>
                  <td class="mipp-hw-col-mapping">
                    ${mappingHtml}
                  </td>
                </tr>
              `;
            }).join("")}
          </tbody>
        </table>
      </div>
    </div>
  `;
}
