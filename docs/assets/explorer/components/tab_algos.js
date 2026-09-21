/**
 * MIPP API Explorer - Tab 3: Scalar C Reference
 */
import { escapeHtml, ICON_COPY } from "../explorer.config.js";
import { highlightCpp, formatMathHtml, getDtBadgeClass } from "../syntax.js";
import { state } from "../state.js";
import { ALL_MASK_MODES, MASK_MODES_INFO } from "../data.js";

export function renderTabAlgos(entry) {
  const cardName = entry.name;
  const lmulKey = state.lmul;

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  const dtsToDisplay = activeDts.length > 0 ? activeDts : (entry.datatypes || []);
  const selectedDt = state.cardScalarTypes[cardName] && dtsToDisplay.includes(state.cardScalarTypes[cardName])
    ? state.cardScalarTypes[cardName]
    : (dtsToDisplay[0] || "float32");

  const lmulAlgos = entry.reference_algos && entry.reference_algos[lmulKey] ? entry.reference_algos[lmulKey] : (entry.reference_algos || {});
  const dtAlgos = lmulAlgos[selectedDt] || {};

  const checkedMasks = state.flavor === "cpp_obj"
    ? ["unmasked"]
    : ["unmasked", "mask", "maskz", "masks"].filter((m) => state.selectedMaskModes.includes(m));

  if (checkedMasks.length === 0) {
    return `
      <div>
        ${entry.math_semantics
          ? `
            <div class="mipp-math-semantics" style="font-size: 0.88rem; padding: 0.5rem 0.8rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 6px; margin-bottom: 0.6rem;">
              <strong>Mathematical Semantics:</strong>
              <span class="arithmatex mipp-math-formula">${formatMathHtml(entry.math_semantics)}</span>
            </div>
          `
          : ""
        }

        <div class="mipp-scalar-header">
          <div style="display: flex; align-items: center; gap: 0.75rem; flex-wrap: wrap;">
            <div style="display: flex; align-items: center; gap: 0.45rem;">
              <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
                Datatype:
              </span>
              <select class="mipp-scalar-dt-select" data-card="${escapeHtml(entry.name)}">
                ${dtsToDisplay.map((dt) => `
                  <option value="${dt}" ${dt === selectedDt ? "selected" : ""}>${dt}</option>
                `).join("")}
              </select>
            </div>
          </div>
          <span style="font-size: 0.75rem; color: var(--md-default-fg-color--lighter);">
            LMUL=${state.lmul}
          </span>
        </div>

        <div style="padding: 1rem; color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">
          ⚠️ No masking mode selected in the left sidebar. Check at least one masking mode in the sidebar to view scalar reference implementations.
        </div>
      </div>
    `;
  }

  const supportedCheckedMasks = checkedMasks.filter(
    (m) => m === "unmasked" || (entry.mask_support && entry.mask_support[m])
  );

  return `
    <div>
      ${entry.math_semantics
        ? `
          <div class="mipp-math-semantics" style="font-size: 0.88rem; padding: 0.5rem 0.8rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 6px; margin-bottom: 0.6rem;">
            <strong>Mathematical Semantics:</strong>
            <span class="arithmatex mipp-math-formula">${formatMathHtml(entry.math_semantics)}</span>
          </div>
        `
        : ""
      }

      <div class="mipp-scalar-header">
        <div style="display: flex; align-items: center; gap: 0.75rem; flex-wrap: wrap;">
          <div style="display: flex; align-items: center; gap: 0.45rem;">
            <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
              Datatype:
            </span>
            <select class="mipp-scalar-dt-select" data-card="${escapeHtml(entry.name)}">
              ${dtsToDisplay.map((dt) => `
                <option value="${dt}" ${dt === selectedDt ? "selected" : ""}>${dt}</option>
              `).join("")}
            </select>
          </div>

          <div style="display: flex; align-items: center; gap: 0.35rem; margin-left: 0.4rem; flex-wrap: wrap;">
            <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
              Variants:
            </span>
            ${checkedMasks.map((m) => {
              const isAvail = m === "unmasked" || (entry.mask_support && entry.mask_support[m]);
              if (isAvail) {
                return `<span class="mipp-mask-badge mask-${m}" title="${m} available">${m}</span>`;
              } else {
                return `<span class="mipp-mask-badge mask-${m} disabled" style="opacity: 0.45; filter: grayscale(1); cursor: not-allowed;" title="${m} not available for ${entry.name}">${m} (N/A)</span>`;
              }
            }).join("")}
          </div>
        </div>
        <span style="font-size: 0.75rem; color: var(--md-default-fg-color--lighter);">
          LMUL=${state.lmul}
        </span>
      </div>

      ${supportedCheckedMasks.length > 0
        ? supportedCheckedMasks.map((m) => {
          let code = "";
          if (typeof dtAlgos === "object" && dtAlgos !== null) {
            code = dtAlgos[m] || dtAlgos["unmasked"] || "// No scalar reference implementation for this variant";
          } else if (typeof dtAlgos === "string") {
            code = dtAlgos;
          } else {
            code = entry.reference_algo || "// No scalar reference code available";
          }
          code = code.replace(/^[ \t]*\/\/[ \t]*Level[ \t]+\d[^\n]*\r?\n?/gm, "").trim();

          return `
            <div class="mipp-scalar-group" style="margin-bottom: 0.75rem;">
              <div class="mipp-code-box">
                <div class="mipp-code-box-header">
                  <div class="mipp-code-box-header-left">
                    <span class="mipp-mask-badge mask-${m}" title="${m}">${m}</span>
                    <span style="font-size: 0.72rem; color: var(--md-default-fg-color--lighter);">Scalar C Reference</span>
                  </div>
                  <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(code)}" title="Copy scalar reference">
                    ${ICON_COPY}
                  </button>
                </div>
                <pre><code>${highlightCpp(code, entry.scalar_macros)}</code></pre>
              </div>
            </div>
          `;
        }).join("")
        : `
          <div style="padding: 1rem; color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">
            ⚠️ None of the selected masking modes (${checkedMasks.join(", ")}) are available for ${entry.name}.
          </div>
        `
      }
    </div>
  `;
}
