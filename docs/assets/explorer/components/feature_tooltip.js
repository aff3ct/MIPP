/**
 * MIPP API Explorer - tooltip of a hardware feature of the Algorithm modal ("HW Features": the
 * tiers and the flags of an ISA, from simd_ext/<isa>/<isa>_explorer.json). It says what the
 * feature is, the macro the implementations test and the compiler flag that defines it.
 *
 * Shown on hover and on keyboard focus only: a click on the button switches the feature.
 */
import { escapeHtml } from "../explorer.config.js";
import { SIMD_EXT_DISPLAY_NAMES, apiMetadata } from "../data.js";
import { tooltipWanted, openTooltip } from "../syntax.js";

/** Opens the tooltip of a feature button (`data-feature-isa`, `data-feature-id`). */
export function showFeatureTooltip(el) {
  const isa = el.getAttribute("data-feature-isa");
  const id = el.getAttribute("data-feature-id");
  const fMeta = (apiMetadata.isas && apiMetadata.isas[isa] && apiMetadata.isas[isa].features) || {};
  const item = (fMeta.items || []).find((it) => it.id === id);
  if (!item || !tooltipWanted(el, false)) return;

  const isaLabel = SIMD_EXT_DISPLAY_NAMES[isa] || isa.toUpperCase();
  const isTier = fMeta.mode === "hierarchy" || (fMeta.mode === "mixed" && item.type === "tier");
  const notes = [];
  if (isTier) notes.push("A tier: it includes the ones before it.");
  if (item.locked) notes.push(`Always enabled on ${isaLabel}.`);

  const t = document.createElement("div");
  t.className = "mipp-macro-tooltip mipp-feature-tooltip";
  t.innerHTML = `
    <div class="mipp-macro-tooltip-header">
      <span class="mipp-macro-tooltip-title">${escapeHtml(isaLabel)} feature: ${escapeHtml(item.label || item.id)}</span>
    </div>
    <div class="mipp-feature-body">
      ${item.description ? `<p>${escapeHtml(item.description)}.</p>` : ""}
      <dl>
        <dt>Macro</dt><dd><code>${escapeHtml(item.define)}</code></dd>
        <dt>Compiler flag</dt><dd>${item.flag ? `<code>${escapeHtml(item.flag)}</code>` : "none: it follows the target"}</dd>
      </dl>
      ${notes.length ? `<p class="mipp-feature-note">${escapeHtml(notes.join(" "))}</p>` : ""}
    </div>`;
  openTooltip(t, el, false, 560, false);
}
