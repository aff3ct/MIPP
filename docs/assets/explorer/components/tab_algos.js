/**
 * MIPP API Explorer - Tab 3: Scalar C Reference
 */
import { escapeHtml, ICON_COPY, ICON_CLOCK } from "../explorer.config.js";
import { highlightCpp, renderMathFormula, getDtBadgeClass } from "../syntax.js";
import { state } from "../state.js";
import { ALL_MASK_MODES, MASK_MODES_INFO, maskSupportOf, isLmulUndefined, undefinedLmulNotice, apiDetailsLoaded } from "../data.js";

// Note shown until mipp_api_details.json is loaded (data.js, loadApiDetails)
export function detailsLoadingNote(what) {
  return `<div class="mipp-algo-note"><span class="mipp-algo-note-icon">${ICON_CLOCK}</span><span>Loading the ${what}…</span></div>`;
}

export function renderTabAlgos(entry) {
  const cardName = entry.name;
  const lmulKey = state.lmul;
  if (isLmulUndefined(entry, lmulKey)) return undefinedLmulNotice(entry, lmulKey);

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  const dtsToDisplay = activeDts.length > 0 ? activeDts : (entry.datatypes || []);
  const selectedDt = state.cardScalarTypes[cardName] && dtsToDisplay.includes(state.cardScalarTypes[cardName])
    ? state.cardScalarTypes[cardName]
    : (dtsToDisplay[0] || "float32");

  const mathHtml = (entry.latex || entry.math_semantics)
    ? `
          <div class="mipp-math-semantics" style="font-size: var(--mipp-fs-md, 0.8rem); padding: 0.5rem 0.8rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 6px; margin-bottom: 0.6rem;">
            <strong>Mathematical Semantics:</strong>
            ${renderMathFormula(entry)}
          </div>
        `
    : "";
  // The scalar reference is in the details, loaded after the first display
  if (!apiDetailsLoaded) return `<div>${mathHtml}${detailsLoadingNote("scalar reference")}</div>`;

  const lmulAlgos = entry.reference_algos && entry.reference_algos[lmulKey] ? entry.reference_algos[lmulKey] : (entry.reference_algos || {});
  const dtAlgos = lmulAlgos[selectedDt] || {};

  const maskSupport = maskSupportOf(entry);
  const availableVariants = ALL_MASK_MODES.filter(
    (m) => m === "unmasked" || maskSupport[m]
  );

  const globalVariant = state.maskVariant || "unmasked";
  const targetMask = availableVariants.includes(globalVariant) ? globalVariant : "unmasked";
  const isUnsupported = !availableVariants.includes(globalVariant);

  let code = "";
  if (typeof dtAlgos === "object" && dtAlgos !== null) {
    code = dtAlgos[targetMask] || dtAlgos["unmasked"] || "// No scalar reference implementation for this variant";
  } else if (typeof dtAlgos === "string") {
    code = dtAlgos;
  } else {
    code = entry.reference_algo || "// No scalar reference code available";
  }
  code = code.replace(/^[ \t]*\/\/[ \t]*Level[ \t]+\d[^\n]*\r?\n?/gm, "").trim();

  return `
    <div>
      ${mathHtml}

      <div class="mipp-scalar-header" style="display: flex; align-items: center; justify-content: space-between; flex-wrap: wrap; gap: 0.75rem; margin-bottom: 0.75rem; padding-bottom: 0.35rem; border-bottom: 1px solid var(--mipp-card-border, #e2e8f0);">
        <div style="display: flex; align-items: center; gap: 0.75rem; flex-wrap: wrap;">
          <div style="display: flex; align-items: center; gap: 0.45rem;">
            <span style="font-size: var(--mipp-fs-base, 0.72rem); font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
              Datatype:
            </span>
            <select class="mipp-scalar-dt-select" data-card="${escapeHtml(entry.name)}">
              ${dtsToDisplay.map((dt) => `
                <option value="${dt}" ${dt === selectedDt ? "selected" : ""}>${dt}</option>
              `).join("")}
            </select>
          </div>
        </div>
      </div>

      <!-- Single Code Box for Globally Selected Variant -->
      <div class="mipp-scalar-group" style="margin-bottom: 0.75rem;">
        <div class="mipp-code-box">
          <div class="mipp-code-box-header">
            <div class="mipp-code-box-header-left" style="display: flex; align-items: center; gap: 0.5rem;">
              <span class="mipp-code-box-title">Scalar C Reference</span>
              ${isUnsupported
                ? `<span style="font-size: var(--mipp-fs-base, 0.72rem); color: #f59e0b; font-style: italic;">(${globalVariant} unsupported, showing unmasked)</span>`
                : ""
              }
            </div>
            <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(code)}" title="Copy scalar reference">
              ${ICON_COPY}
            </button>
          </div>
          <pre><code>${highlightCpp(code, entry.scalar_macros)}</code></pre>
        </div>
      </div>
    </div>
  `;
}
