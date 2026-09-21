/**
 * MIPP API Explorer - Tab 4: Verification Specs & Domains
 */
import { escapeHtml } from "../explorer.config.js";
import { getDtBadgeClass } from "../syntax.js";
import { state } from "../state.js";
import { ALL_MASK_MODES, MASK_MODES_INFO } from "../data.js";

export function renderTabSpecs(entry) {
  const cardName = entry.name;
  const testSpecs = entry.test_specs || {};
  const variants = testSpecs.variants || {};

  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const activeMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
  const availableVariants = activeMasks.length > 0 ? activeMasks : allVariants;

  const currentVariant = state.cardTestVariants[cardName] && availableVariants.includes(state.cardTestVariants[cardName])
    ? state.cardTestVariants[cardName]
    : (availableVariants[0] || "unmasked");

  const variantSpec = variants[currentVariant] || variants.unmasked || {};
  const tableRows = variantSpec.table || testSpecs.table || [];

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  const filteredRows = activeDts.length > 0
    ? tableRows.filter((row) => activeDts.some((dt) => row.datatype.startsWith(dt) || row.datatype.endsWith(dt)))
    : tableRows;

  return `
    <div style="display: flex; flex-direction: column; gap: 0.8rem;">
      <!-- Available Test Variants Badges (Clickable per-card switcher) -->
      <div style="display: flex; align-items: center; gap: 0.5rem; margin-bottom: 0.25rem; flex-wrap: wrap;">
        <span style="font-size: 0.78rem; font-weight: 600; color: var(--md-default-fg-color--lighter);">Verification Variant:</span>
        ${availableVariants.map((v) => `
          <button class="mipp-mask-badge mask-${v} mipp-test-variant-btn ${v === currentVariant ? "active" : ""}"
                  data-card="${escapeHtml(cardName)}" data-mask="${escapeHtml(v)}" title="Click to view specs for ${v}">
            ${v} ${v === currentVariant ? "✓" : ""}
          </button>
        `).join("")}
      </div>

      <!-- Overview Badges -->
      <div style="display: flex; gap: 0.5rem; flex-wrap: wrap; font-size: 0.8rem;">
        <div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;">
          <strong>Comparison:</strong> <code>${escapeHtml(variantSpec.comparison || testSpecs.comparison || "exact")}</code>
        </div>
        ${variantSpec.overflow_check
          ? `
            <div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;">
              <strong>Overflow Check:</strong> <code>${escapeHtml(variantSpec.overflow_check)}</code>
            </div>
          `
          : ""
        }
        ${variantSpec.mask_pattern
          ? `
            <div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;">
              <strong>Mask Pattern:</strong> <code>${escapeHtml(variantSpec.mask_pattern)}</code>
            </div>
          `
          : ""
        }
      </div>

      <!-- Domain & Tolerance Table -->
      <div class="mipp-specs-table-wrapper">
        <table class="mipp-specs-table">
          <thead>
            <tr>
              <th style="width: 120px;">Datatype</th>
              <th>Input Domain</th>
              <th>Numerical Tolerance</th>
              <th style="width: 130px;">Strategy</th>
            </tr>
          </thead>
          <tbody>
            ${filteredRows.map((row) => `
              <tr>
                <td><span class="mipp-dt-badge ${getDtBadgeClass(row.datatype)}">${escapeHtml(row.datatype)}</span></td>
                <td><code>${escapeHtml(row.domain)}</code></td>
                <td>${escapeHtml(row.tolerance)}</td>
                <td><span class="mipp-cat-badge">${escapeHtml(row.comparison || variantSpec.comparison || "exact")}</span></td>
              </tr>
            `).join("")}
          </tbody>
        </table>
      </div>
    </div>
  `;
}
