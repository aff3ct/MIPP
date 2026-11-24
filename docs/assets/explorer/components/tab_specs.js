/**
 * MIPP API Explorer - Tab 4: Verification Specs
 * How the unit tests draw the inputs and compare each lane with the scalar reference, resolved with
 * the test generator (generator/helpers_docs/test_specs.py), for the selected mask variant.
 */
import { escapeHtml } from "../explorer.config.js";
import { getDtBadgeClass } from "../syntax.js";
import { state } from "../state.js";
import { ALL_MASK_MODES, maskSupportOf, apiDetailsLoaded } from "../data.js";
import { detailsLoadingNote } from "./tab_algos.js";

const VARIANT_TITLES = {
  unmasked: "Unmasked (U)",
  mask: "Merge-Masked (M)",
  maskz: "Zero-Masked (Z)",
  masks: "Source-Masked (S)",
};

function datatypeLabel(dt) {
  const [from, to] = String(dt).split(",").map((s) => s.trim());
  if (!to || to === from) return `<span class="mipp-dt-badge ${getDtBadgeClass(from)}">${escapeHtml(from)}</span>`;
  return `<span class="mipp-dt-badge ${getDtBadgeClass(from)}">${escapeHtml(from)}</span> → `
    + `<span class="mipp-dt-badge ${getDtBadgeClass(to)}">${escapeHtml(to)}</span>`;
}

export function renderTabSpecs(entry) {
  // The test specification is in the details, loaded after the first display
  if (!apiDetailsLoaded) return detailsLoadingNote("verification specification");
  const testSpecs = entry.test_specs || {};
  const variants = testSpecs.variants || {};
  if (!variants.unmasked) {
    return `<p class="mipp-specs-note">No unit test is generated for this function.</p>`;
  }

  const maskSupport = maskSupportOf(entry);
  const availableVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const globalVariant = state.maskVariant || "unmasked";
  const currentVariant = availableVariants.includes(globalVariant) && variants[globalVariant] ? globalVariant : "unmasked";
  const variantSpec = variants[currentVariant];
  const rows = variantSpec.rows || [];

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  const shownRows = activeDts.length > 0
    ? rows.filter((row) => {
      const parts = String(row.datatype).split(",").map((s) => s.trim());
      return activeDts.some((dt) => parts.includes(dt));
    })
    : rows;

  const notes = testSpecs.notes || [];
  const special = testSpecs.special_values || {};
  const specialDts = Object.keys(special);

  return `
    <div class="mipp-specs">
      <p class="mipp-specs-note">
        How the unit tests draw the inputs (random values) and compare each lane of the result with the scalar
        reference, as in the generated C API tests: <strong>${escapeHtml(VARIANT_TITLES[currentVariant])}</strong>
        variant${availableVariants.length > 1 ? " (variant selector of the search bar)" : ""}.
      </p>
      ${variantSpec.mask_text
        ? `<div class="mipp-specs-chip"><strong>Input masks:</strong> ${escapeHtml(variantSpec.mask_text)}</div>`
        : ""}
      <div class="mipp-specs-table-wrapper">
        <table class="mipp-specs-table">
          <thead>
            <tr>
              <th>Datatype</th>
              <th>Inputs</th>
              <th>Comparison with the reference</th>
            </tr>
          </thead>
          <tbody>
            ${shownRows.map((row) => `
              <tr>
                <td class="mipp-specs-dt">${datatypeLabel(row.datatype)}</td>
                <td>${(row.inputs || []).map((t) => `<code>${escapeHtml(t)}</code>`).join("<br>")}</td>
                <td>${escapeHtml(row.comparison)}</td>
              </tr>
            `).join("")}
          </tbody>
        </table>
      </div>
      ${notes.length
        ? `<ul class="mipp-specs-notes">${notes.map((n) => `<li>${escapeHtml(n)}</li>`).join("")}</ul>`
        : ""}
      ${specialDts.length
        ? `<details class="mipp-specs-special">
            <summary>Special values</summary>
            <p>Every other iteration, the lanes of the inputs take these values (cycling, each further input
            one value later in the list), to cover the cases that random values never hit:</p>
            <ul>${specialDts.map((dt) => `<li><span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${escapeHtml(dt)}</span>
              <code>${special[dt].map((v) => escapeHtml(String(v))).join(", ")}</code></li>`).join("")}</ul>
          </details>`
        : ""}
    </div>
  `;
}
