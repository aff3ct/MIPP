/**
 * MIPP API Explorer - tooltip of a parameter that can be an immediate: the
 * integer parameter of some functions (`"imm"` of the registry) is either a
 * variable or a value known at compile time, an immediate. highlightCpp boxes it
 * where it is declared (span .mipp-imm-ref), in the prototypes and in the code of
 * the Algorithm modal:
 *   - the parameter of the function (`s0`, dashed box): a variable or an immediate;
 *   - the argument of the C++ template version (`S`, solid box): always an immediate.
 * The tooltip opens on hover, and a click keeps it open (to follow its link).
 */
import { escapeHtml } from "../explorer.config.js";
import { renderDescription, typesetMath } from "../syntax.js";
import { SIMD_EXT_DISPLAY_NAMES, apiMetadata } from "../data.js";

/**
 * Where MIPP has a body of its own for an immediate (`imm.isas`, found in the generated
 * headers): on the other targets the same code runs with a variable and with an immediate,
 * e.g. `_mm_slli_epi64(a, n)` on x86, that the compiler turns into the right instruction.
 */
export function immTargetsSentence(imm) {
  const meta = (apiMetadata && apiMetadata.isas) || {};
  const isas = (imm.isas || []).slice().sort((a, b) => ((meta[a] || {}).order || 0) - ((meta[b] || {}).order || 0));
  if (!isas.length) return "MIPP has no body of its own for an immediate: the same code runs in both cases.";
  const names = isas.map((i) => SIMD_EXT_DISPLAY_NAMES[i] || i.toUpperCase());
  const list = names.length > 1 ? `${names.slice(0, -1).join(", ")} and ${names[names.length - 1]}` : names[0];
  return `MIPP has a body of its own for an immediate on ${list}. On the other targets, the same code runs in both cases.`;
}

export function hideImmTooltip({ onlyUnpinned = false } = {}) {
  const t = document.querySelector(".mipp-imm-tooltip");
  if (!t || (onlyUnpinned && t._pinned)) return;
  if (t._target) t._target.classList.remove("active");
  t.remove();
}

/** Opens the tooltip of `el`; `pinned`: stays open until a click outside or Escape. */
export function showImmTooltip(el, pinned = false) {
  const existing = document.querySelector(".mipp-imm-tooltip");
  if (existing && existing._target === el) {
    existing._pinned = existing._pinned || pinned;
    return;
  }
  // one tooltip at a time (macro, intrinsic or parameter)
  document.querySelectorAll(".mipp-macro-tooltip").forEach((x) => {
    if (x._targetMacro) x._targetMacro.classList.remove("active");
    x.remove();
  });
  let imm;
  try {
    imm = JSON.parse(el.getAttribute("data-imm"));
  } catch (e) {
    return;
  }
  const isTemplate = el.getAttribute("data-imm-kind") === "template";
  const name = isTemplate ? "S" : imm.arg;
  const latex = isTemplate ? imm.latex.replace(new RegExp(`\\b${imm.arg}\\b`, "g"), "S") : imm.latex;
  const range = `$${latex}$${imm.bound ? `, with ${imm.bound}` : ""}`;
  const targets = escapeHtml(immTargetsSentence(imm));
  const body = isTemplate
    ? `
      <p>${renderDescription(range)}.</p>
      <p>Always known at compile time: an <strong>immediate</strong>. A value out of the range is a compilation error (<code>static_assert</code>).</p>
      <p>It calls the function with this constant. ${targets}</p>`
    : `
      <p>${renderDescription(range)}.</p>
      <p>An ordinary integer parameter: a <strong>variable</strong>, or a value known at compile time, an <strong>immediate</strong>.</p>
      <p>${targets}</p>
      <p>C++ template version, whose argument is always an immediate: ${renderDescription("`" + imm.template + "`")}.</p>`;

  const t = document.createElement("div");
  t.className = "mipp-macro-tooltip mipp-imm-tooltip";
  t._target = el;
  t._targetMacro = el; // so that hideMacroTooltip() also closes it cleanly
  t._pinned = pinned;
  el.classList.add("active");
  t.innerHTML = `
    <div class="mipp-macro-tooltip-header">
      <span class="mipp-macro-tooltip-title">${isTemplate ? "Template argument" : "Parameter"} <code>${escapeHtml(name)}</code>: ${isTemplate ? "always an immediate" : "variable or immediate"}</span>
      <button class="mipp-macro-tooltip-close" title="Close">×</button>
    </div>
    <div class="mipp-imm-body">${body}
      <a class="mipp-intrinsic-doc" href="../user/rearrangements/#31-constant-counts">Constant Counts →</a>
    </div>`;
  document.body.appendChild(t);
  typesetMath(t);

  const rect = el.getBoundingClientRect();
  const pad = 12;
  const maxW = Math.min(460, window.innerWidth - 2 * pad);
  t.style.maxWidth = `${maxW}px`;
  let left = rect.left + window.scrollX;
  const right = window.scrollX + window.innerWidth - pad;
  if (left + (t.offsetWidth || maxW) > right) left = Math.max(window.scrollX + pad, right - (t.offsetWidth || maxW));
  t.style.top = `${rect.bottom + window.scrollY + 6}px`;
  t.style.left = `${left}px`;

  t.querySelector(".mipp-macro-tooltip-close").addEventListener("click", (ev) => { ev.stopPropagation(); hideImmTooltip(); });
}

/** Click on the parameter: keeps the tooltip open, or closes the one it had kept open. */
export function toggleImmTooltip(el) {
  const existing = document.querySelector(".mipp-imm-tooltip");
  if (existing && existing._target === el && existing._pinned) { hideImmTooltip(); return; }
  showImmTooltip(el, true);
}
