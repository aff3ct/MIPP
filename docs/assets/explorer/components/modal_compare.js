/**
 * MIPP API Explorer - Side-by-Side Primitive Comparison Modal
 */
import { escapeHtml } from "../explorer.config.js";
import { highlightCpp, getDtBadgeClass, renderDescription, renderMathFormula } from "../syntax.js";
import { ALL_SIMD_EXTS, SIMD_EXT_DISPLAY_NAMES } from "../data.js";
import { state } from "../state.js";
import { getActivePrototype, computeOptimisticLevel } from "./card.js";

export function renderCompareColumn(entry) {
  const activeProto = getActivePrototype(entry);
  const extsList = ALL_SIMD_EXTS;
  const namesMap = SIMD_EXT_DISPLAY_NAMES;
  const selectedExts = state.selectedSimdExts || [];
  const activeExts = extsList.filter((ext) => selectedExts.includes(ext));

  return `
    <div class="mipp-compare-col">
      <div style="display: flex; align-items: center; justify-content: space-between;">
        <h3 class="mipp-compare-col-name" style="margin: 0; font-family: var(--md-code-font, monospace); font-size: var(--mipp-fs-lg, 0.95rem);">${escapeHtml(entry.name)}</h3>
        <span class="mipp-cat-badge">${escapeHtml(entry.category)}</span>
      </div>

      <p class="mipp-compare-col-desc" style="font-size: var(--mipp-fs-md, 0.8rem); margin: 0; color: var(--md-default-fg-color--light);">${renderDescription(entry.description)}</p>

      <div>
        <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Mathematical Semantics</div>
        <div style="font-size: var(--mipp-fs-md, 0.8rem); background: var(--md-default-bg-color--lighter); padding: 0.4rem; border-radius: 4px;">
          ${(entry.latex || entry.math_semantics) ? renderMathFormula(entry) : "N/A"}
        </div>
      </div>

      <div>
        <div class="mipp-control-label" style="margin-bottom: 0.3rem;">SIMD Extension Support</div>
        <div class="mipp-isa-strip">
          ${activeExts.map((isa) => {
            const lvl = computeOptimisticLevel(entry, isa);
            return `<span class="mipp-isa-badge lvl-${lvl}">${namesMap[isa] || isa.toUpperCase()}${lvl !== "na" ? `: L${lvl}` : ""}</span>`;
          }).join("")}
        </div>
      </div>

      <div>
        <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Active Prototype (${state.flavor.toUpperCase()})</div>
        <div class="mipp-code-box">
          <pre style="padding: 0.5rem; font-size: var(--mipp-fs-base, 0.72rem);"><code>${highlightCpp(activeProto)}</code></pre>
        </div>
      </div>

      <div>
        <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Supported Datatypes</div>
        <div style="display: flex; flex-wrap: wrap; gap: 0.35rem; margin-top: 0.25rem;">
          ${(entry.datatypes || []).map((dt) => `<span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${dt}</span>`).join("")}
        </div>
      </div>
    </div>
  `;
}

export function renderCompareModal(apiData) {
  const selectedEntries = Array.from(state.compareSet)
    .map((name) => apiData.find((e) => e.name === name))
    .filter(Boolean);

  return `
    <div id="mipp-compare-modal-backdrop" class="mipp-modal-backdrop ${state.compareModalOpen ? "visible active" : ""}">
      <div class="mipp-modal-content mipp-compare-modal-content">
        <div class="mipp-modal-header">
          <h2 class="mipp-modal-title" style="margin: 0; font-size: var(--mipp-fs-md, 0.8rem); display: flex; align-items: center; gap: 0.5rem;">
            <span>Side-by-Side Primitive Comparison</span>
          </h2>
          <button id="mipp-close-compare-btn" class="mipp-icon-btn mipp-modal-close-btn" style="font-size: var(--mipp-fs-lg, 0.95rem);" title="Close comparison modal">✕</button>
        </div>
        <div class="mipp-compare-grid">
          ${selectedEntries.map((e) => renderCompareColumn(e)).join("")}
        </div>
      </div>
    </div>
  `;
}
