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
  const availableVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);

  const globalVariant = state.flavor === "cpp_obj" ? "unmasked" : (state.maskVariant || "unmasked");
  const currentVariant = availableVariants.includes(globalVariant) ? globalVariant : "unmasked";
  const isUnsupported = !availableVariants.includes(globalVariant);

  const variantSpec = variants[currentVariant] || variants.unmasked || {};
  const tableRows = variantSpec.table || testSpecs.table || [];

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  const filteredRows = activeDts.length > 0
    ? tableRows.filter((row) => activeDts.some((dt) => row.datatype.startsWith(dt) || row.datatype.endsWith(dt)))
    : tableRows;

  return `
    <div style="display: flex; flex-direction: column; gap: 0.8rem;">
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
