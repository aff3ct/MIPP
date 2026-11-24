/**
 * MIPP API Explorer - Syntax Highlighter & Typography
 */
import { escapeHtml, ICON_COPY } from "./explorer.config.js";
import { isIntrinsicName } from "./components/intrinsic_tooltip.js";

export function formatCppObjProto(str, lmulKey = "1") {
  if (!str) return "";
  let s = str.replace(/\binline\s+/g, "").trim();
  // Ensure space after commas
  s = s.replace(/,(\S)/g, ", $1");
  if (lmulKey === "1") {
    return s.replace(/<([^,>]+),\s*LMUL>/g, "<$1>");
  } else {
    return s.replace(/<([^,>]+),\s*LMUL>/g, `<$1, ${lmulKey}>`);
  }
}

export function getDtBadgeClass(dt) {
  if (!dt) return "";
  if (dt.includes(",")) {
    const parts = dt.split(",").map((p) => p.trim());
    if (parts.length >= 2 && parts.every((p) => p === parts[0])) {
      return `dt-${parts[0]}`;
    }
    return "dt-mixed";
  }
  return `dt-${dt}`;
}

/**
 * "Mathematical Semantics" formula: the LaTeX of the function registry
 * (generator/helpers_headers/funcs_docs.json), typeset by MathJax like the
 * formulas of the other pages (span.arithmatex, see javascripts/mathjax.js).
 * formatMathHtml() is only the fallback of an entry without LaTeX: its
 * regex-based conversion does not handle environments such as cases.
 */
export function renderMathFormula(entry) {
  if (entry && entry.latex) {
    return `<span class="arithmatex mipp-math-formula mipp-math-tex">\\(${escapeHtml(entry.latex)}\\)</span>`;
  }
  return `<span class="mipp-math-formula">${formatMathHtml(entry && entry.math_semantics)}</span>`;
}

/**
 * Description of a function (generator/helpers_headers/funcs_docs.json): text
 * with code between backticks (`vd0`) and math between dollars ($0 \le s0 < N$),
 * as in the Markdown pages. The math is typeset by MathJax (typesetMath).
 */
export function renderDescription(text) {
  return String(text || "").split(/(`[^`]+`|\$[^$]+\$)/).map((part) => {
    if (part.length > 2 && part[0] === "`" && part[part.length - 1] === "`") {
      return `<code class="mipp-desc-code">${escapeHtml(part.slice(1, -1))}</code>`;
    }
    if (part.length > 2 && part[0] === "$" && part[part.length - 1] === "$") {
      return `<span class="arithmatex mipp-desc-math">\\(${escapeHtml(part.slice(1, -1))}\\)</span>`;
    }
    return escapeHtml(part);
  }).join("");
}

/** The same description without its markup: the text the search runs on. */
export function plainDescription(text) {
  return String(text || "").replace(/`([^`]+)`/g, "$1").replace(/\$([^$]+)\$/g, "$1");
}

/**
 * Typesets the formulas of `el` (an element or a list of elements) once MathJax
 * has started (CDN script loaded).
 */
export function typesetMath(el) {
  const mj = typeof window !== "undefined" ? window.MathJax : null;
  const els = (Array.isArray(el) ? el : [el]).filter(Boolean);
  if (!mj || !els.length) return;
  const run = () => {
    if (mj.typesetPromise) mj.typesetPromise(els).catch(() => {});
  };
  if (mj.startup && mj.startup.promise) {
    mj.startup.promise.then(run).catch(() => {});
  } else {
    run();
  }
}

export function formatMathHtml(expr) {
  if (!expr) return "";
  let clean = String(expr)
    .replace(/\\mathrm\{([^}]+)\}/g, "$1")
    .replace(/\\text\{([^}]+)\}/g, "$1")
    .replace(/\\operatorname\{([^}]+)\}/g, "$1")
    .replace(/\ba_i\b/g, "vd0<sub>i</sub>")
    .replace(/\bb_i\b/g, "vd1<sub>i</sub>")
    .replace(/\bc_i\b/g, "vd2<sub>i</sub>")
    .replace(/\\cdot/g, " · ")
    .replace(/\\times/g, " × ")
    .replace(/\\le/g, " ≤ ")
    .replace(/\\ge/g, " ≥ ")
    .replace(/\\neq/g, " ≠ ")
    .replace(/\\infty/g, "∞")
    .replace(/\\sqrt\{([^}]+)\}/g, "√($1)")
    .replace(/\\exp\b/g, "exp")
    .replace(/\\ln\b/g, "ln")
    .replace(/\\log\b/g, "log")
    .replace(/\\cos\b/g, "cos")
    .replace(/\\sin\b/g, "sin")
    .replace(/\\tan\b/g, "tan")
    .replace(/\\arccos\b/g, "arccos")
    .replace(/\\arcsin\b/g, "arcsin")
    .replace(/\\arctan\b/g, "arctan")
    .replace(/\\cosh\b/g, "cosh")
    .replace(/\\sinh\b/g, "sinh")
    .replace(/\\tanh\b/g, "tanh")
    .replace(/\\arcosh\b/g, "arcosh")
    .replace(/\\arsinh\b/g, "arsinh")
    .replace(/\\artanh\b/g, "artanh")
    .replace(/\\left\|/g, "|")
    .replace(/\\right\|/g, "|")
    .replace(/\\left/g, "")
    .replace(/\\right/g, "")
    .replace(/\\\{/g, "{")
    .replace(/\\\}/g, "}")
    .replace(/_\{([^}]+)\}/g, "<sub>$1</sub>")
    .replace(/_([a-zA-Z0-9]+)/g, "<sub>$1</sub>")
    .replace(/\^\{([^}]+)\}/g, "<sup>$1</sup>")
    .replace(/\^([a-zA-Z0-9]+)/g, "<sup>$1</sup>");
  return clean;
}

/**
 * Highlights C/C++ code. `options.isa`: vendor intrinsics of this ISA become clickable
 * (`.mipp-intrinsic-ref`, see components/intrinsic_tooltip.js).
 */
export function highlightCpp(code, customMacros = {}, options = {}) {
  if (!code) return "";
  const cleanCode = code.trim();

  const tokenPatterns = [
    // 1. Comments
    '(//[^\n]*|/\\*[\\s\\S]*?\\*/)',
    // 2. Preprocessor (stops before inline comment)
    '(#[a-zA-Z_]+(?:[^\\n/]|/(?!/))*?)',
    // 3. Strings
    '("(?:\\\\.|[^"\\\\])*")',
    // 4. Numbers
    '\\b(0x[0-9a-fA-F]+|\\d+(?:\\.\\d+)?(?:[eE][+-]?\\d+)?[fFulUL]*)\\b',
    // 5. Types (MIPP SIMD types, Vd, vd, Vm, vm, C/C++ primitives)
    '\\b(VARIANT|vd_[a-z0-9_]+_t|vm_[a-z0-9_]+_t|Vd|vd|Vm|vm|__m128[a-z0-9_]*|__m256[a-z0-9_]*|__m512[a-z0-9_]*|__mmask8|__mmask16|__mmask32|__mmask64|__mmask[0-9]+|uint8x16_t|uint16x8_t|uint32x4_t|uint64x2_t|int8x16_t|int16x8_t|int32x4_t|int64x2_t|float64x2_t|float32x4_t|float[0-9]+x[0-9]+_t|[u]?int[0-9]+x[0-9]+_t|sv[a-z0-9_]+_t|v[a-z0-9_]+_t|reg|msk|void|bool|bool_t|char|int|short|long|float|double|float32|float64|int8|int16|int32|int64|uint8|uint16|uint32|uint64|float32_t|float64_t|uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t|size_t)\\b',
    // 6. Keywords
    '\\b(const|static|inline|return|if|else|for|while|do|switch|case|default|break|continue|struct|class|template|typename|auto|sizeof|typedef|namespace|using|constexpr|extern)\\b',
    // 7. Functions / Hardware Intrinsics / MIPP / Function declarations & calls
    '(\\b_mm256_[a-zA-Z0-9_]+|\\b_mm512_[a-zA-Z0-9_]+|\\b_mm_[a-zA-Z0-9_]+|\\bv[a-z0-9_]+|\\bsv[a-z0-9_]+|\\b__riscv_[a-z0-9_]+|\\bmipp::[a-zA-Z0-9_]+|\\b(?!mipp_obj\\b)mipp_[a-zA-Z0-9_]+|\\b[a-zA-Z_][a-zA-Z0-9_]*(?=\\s*\\())',
    // 8. Template parameters (T, T1, T2, T_IDX, T_DST, T_SRC, LMUL, LDIV, N, V, M, Z, S, U)
    '\\b(T|T1|T2|T_IDX|T_DST|T_SRC|LMUL|LDIV|N|V|M|Z|S|U)\\b',
  ];

  // Parameter that can be an immediate (options.imm, the "imm" of the entry): its
  // name is a token, boxed where it is declared (see the loop)
  const imm = options.imm && options.imm.arg ? options.imm : null;
  if (imm) tokenPatterns.push('\\b(' + imm.arg + ')\\b');

  if (customMacros && typeof customMacros === "object") {
    const macroNames = Object.keys(customMacros).filter((k) => /^[A-Z0-9_]+$/.test(k));
    if (macroNames.length > 0) {
      tokenPatterns.push('\\b(' + macroNames.join("|") + ')\\b');
    }
  }

  const tokenRegex = new RegExp(tokenPatterns.join("|"), "g");

  let lastIndex = 0;
  let html = "";
  let match;

  while ((match = tokenRegex.exec(cleanCode)) !== null) {
    if (match.index > lastIndex) {
      html += escapeHtml(cleanCode.slice(lastIndex, match.index));
    }
    const token = match[0];
    let cls = "";
    if (match[1]) cls = "mipp-hl-cmt";
    else if (match[2]) cls = "mipp-hl-pp";
    else if (match[3]) cls = "mipp-hl-str";
    else if (match[4]) cls = "mipp-hl-num";
    else if (match[5]) cls = "mipp-hl-type";
    else if (match[6]) cls = "mipp-hl-kw";
    else if (match[7]) cls = "mipp-hl-fn";
    else if (match[8]) cls = "mipp-hl-tmpl";

    // declaration of the parameter (`const int32_t s0`), or of the constant of
    // the C++ template version (`template <int S, ...>`)
    const before = imm ? cleanCode.slice(Math.max(0, match.index - 12), match.index) : "";
    const isImmDecl = imm && ((token === imm.arg && /\bu?int32_t\s+$/.test(before)) || (token === "S" && /<int\s+$/.test(before)));

    if (isImmDecl) {
      // the parameter is a variable or an immediate, the template argument always an immediate
      const isTemplate = token !== imm.arg;
      html += `<span class="mipp-imm-ref${isTemplate ? " mipp-imm-const" : ""}" data-imm="${escapeHtml(JSON.stringify(imm))}" data-imm-kind="${isTemplate ? "template" : "param"}" tabindex="0" role="button" aria-label="${escapeHtml(token)}: ${isTemplate ? "always an immediate" : "variable or immediate"}">${escapeHtml(token)}</span>`;
    } else if (customMacros && customMacros[token]) {
      const macroInfo = customMacros[token];
      const macroDef = typeof macroInfo === "object" ? (macroInfo.definition || macroInfo.body || "") : String(macroInfo);
      html += `<span class="mipp-hl-macro mipp-macro-ref" data-macro-name="${escapeHtml(token)}" data-macro-def="${escapeHtml(macroDef)}" tabindex="0" role="button" aria-label="${escapeHtml(token)}: macro, its definition">${escapeHtml(token)}</span>`;
    } else if (match[7] && options.isa && isIntrinsicName(token, options.isa) && /^\s*\(/.test(cleanCode.slice(tokenRegex.lastIndex))) {
      html += `<span class="mipp-hl-fn mipp-intrinsic-ref" data-intrinsic="${escapeHtml(token)}" data-isa="${escapeHtml(options.isa)}" tabindex="0" role="button" aria-label="${escapeHtml(token)}: intrinsic, its details">${escapeHtml(token)}</span>`;
    } else if (cls) {
      html += `<span class="${cls}">${escapeHtml(token)}</span>`;
    } else {
      html += escapeHtml(token);
    }
    lastIndex = tokenRegex.lastIndex;
  }

  if (lastIndex < cleanCode.length) {
    html += escapeHtml(cleanCode.slice(lastIndex));
  }

  return html;
}

/**
 * Puts a tooltip under the element it describes, inside the viewport. The tooltips are children
 * of the body, in page coordinates: `followTooltipAnchors()` calls this again when something
 * scrolls. `maxWidth` (pixels) is kept for these later calls.
 */
export function placeTooltip(tooltip, anchor, maxWidth) {
  const pad = 12;
  if (maxWidth) tooltip._maxWidth = maxWidth;
  const maxW = Math.min(tooltip._maxWidth || 560, window.innerWidth - 2 * pad);
  tooltip.style.maxWidth = `${maxW}px`;
  tooltip.style.boxSizing = "border-box";
  const rect = anchor.getBoundingClientRect();
  const width = tooltip.offsetWidth || maxW;
  const right = window.scrollX + window.innerWidth - pad;
  let left = rect.left + window.scrollX;
  if (left + width > right) left = right - width;
  left = Math.max(window.scrollX + pad, left);
  tooltip.style.top = `${rect.bottom + window.scrollY + 6}px`;
  tooltip.style.left = `${left}px`;
}

/** True when a scrolling ancestor of `el` hides it entirely (scrolled out of a modal, of a code box...). */
function isScrolledOut(el) {
  const rect = el.getBoundingClientRect();
  for (let p = el.parentElement; p && p !== document.body; p = p.parentElement) {
    const style = getComputedStyle(p);
    if (style.overflowX === "visible" && style.overflowY === "visible") continue;
    const box = p.getBoundingClientRect();
    if (rect.bottom < box.top || rect.top > box.bottom || rect.right < box.left || rect.left > box.right) return true;
  }
  return false;
}

/**
 * Keeps the open tooltip under its element when something scrolls (the page, a modal, a code
 * box) or when the window is resized; closes it when its element is gone or scrolled out of
 * sight. For the scroll and resize listeners of the page.
 */
export function followTooltipAnchors() {
  document.querySelectorAll(".mipp-macro-tooltip").forEach((tooltip) => {
    const anchor = tooltip._targetMacro;
    if (!anchor) return;
    if (!anchor.isConnected || isScrolledOut(anchor)) {
      if (tooltip._marksAnchor) anchor.classList.remove("active");
      tooltip.remove();
    } else {
      placeTooltip(tooltip, anchor);
    }
  });
}

// ---- Tooltips of the code: macros, vendor intrinsics, parameters that can be an immediate ------
// One tooltip at a time, a child of the body with the class .mipp-macro-tooltip. They behave the
// same way: shown while the pointer is on their element, kept open by a click on it (`pinned`),
// until a click elsewhere, Escape, their close button or another click on the element.

const currentTooltip = () => document.querySelector(".mipp-macro-tooltip");

/** Closes the open tooltip; `onlyUnpinned`: unless a click keeps it open. */
export function hideTooltip({ onlyUnpinned = false } = {}) {
  const t = currentTooltip();
  if (!t || (onlyUnpinned && t._pinned)) return;
  if (t._targetMacro && t._marksAnchor) t._targetMacro.classList.remove("active");
  t.remove();
}

/**
 * To call before building the tooltip of `anchor`: false when there is nothing to build. Its
 * tooltip is already open (a click then keeps it open), or the pointer only passes over
 * `anchor` while a click keeps the tooltip of another element open.
 */
export function tooltipWanted(anchor, pinned) {
  const t = currentTooltip();
  if (t && t._targetMacro === anchor) {
    t._pinned = t._pinned || pinned;
    return false;
  }
  if (t && t._pinned && !pinned) return false;
  hideTooltip();
  return true;
}

/**
 * Shows the tooltip built for `anchor` under it, and binds its close button. `markAnchor`: the
 * element gets the class `active` while its tooltip is open (not for a button, where this
 * class says that it is selected).
 */
export function openTooltip(tooltip, anchor, pinned, maxWidth, markAnchor = true) {
  tooltip._targetMacro = anchor;
  tooltip._pinned = pinned;
  tooltip._marksAnchor = markAnchor;
  if (markAnchor) anchor.classList.add("active");
  document.body.appendChild(tooltip);
  placeTooltip(tooltip, anchor, maxWidth);
  const closeBtn = tooltip.querySelector(".mipp-macro-tooltip-close");
  if (closeBtn) closeBtn.addEventListener("click", (ev) => { ev.stopPropagation(); hideTooltip(); });
}

/** Click on `anchor`: keeps its tooltip open (`show(anchor, true)`), or closes the one a click kept open. */
export function toggleTooltip(anchor, show) {
  const t = currentTooltip();
  if (t && t._targetMacro === anchor && t._pinned) {
    hideTooltip();
    return;
  }
  show(anchor, true);
}

/** Opens the tooltip of a macro (its definition); `pinned`: kept open by a click. */
export function showMacroTooltip(macroEl, pinned = false) {
  if (!macroEl) return;
  const macroName = macroEl.getAttribute("data-macro-name") || "";
  const macroDef = macroEl.getAttribute("data-macro-def") || "";
  if (!macroDef || !tooltipWanted(macroEl, pinned)) return;

  const tooltip = document.createElement("div");
  tooltip.className = "mipp-macro-tooltip mipp-macro-def-tooltip";
  tooltip.innerHTML = `
    <div class="mipp-macro-tooltip-header">
      <span class="mipp-macro-tooltip-title">Macro: <code>${escapeHtml(macroName)}</code></span>
      <div style="display: flex; gap: 0.35rem; align-items: center;">
        <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(macroDef)}" title="Copy macro definition">${ICON_COPY}</button>
        <button class="mipp-macro-tooltip-close" title="Close">×</button>
      </div>
    </div>
    <pre class="mipp-macro-tooltip-code"><code>${escapeHtml(macroDef)}</code></pre>
  `;
  openTooltip(tooltip, macroEl, pinned, 650);
}

/**
 * Splits function argument string by commas, respecting template brackets <...> and parentheses (...)
 */
function splitArgs(argStr) {
  const args = [];
  let depthAngle = 0;
  let depthParen = 0;
  let current = "";
  for (let i = 0; i < argStr.length; i++) {
    const ch = argStr[i];
    if (ch === "<") depthAngle++;
    else if (ch === ">") depthAngle = Math.max(0, depthAngle - 1);
    else if (ch === "(") depthParen++;
    else if (ch === ")") depthParen = Math.max(0, depthParen - 1);
    else if (ch === "," && depthAngle === 0 && depthParen === 0) {
      if (current.trim()) args.push(current.trim());
      current = "";
      continue;
    }
    current += ch;
  }
  if (current.trim()) args.push(current.trim());
  return args;
}

/**
 * Parses a parameter declaration like "const vd<T, 1> r0" or "const float64_t* p0"
 * into { type, name }.
 */
function parseParam(paramStr) {
  const trimmed = paramStr.replace(/\s+/g, " ").trim();
  const m = trimmed.match(/^(.*?)(\b[a-zA-Z0-9_]+)$/);
  if (m && m[1].trim()) {
    return { type: m[1].trim(), name: m[2] };
  }
  return { type: "", name: trimmed };
}

/**
 * Exposes and formats function definition and declaration arguments across multiple lines:
 * - Single argument stays on one line.
 * - Multiple arguments (>= 2) split one parameter per line.
 * - Aligns parameter names in a vertical column matching Scalar C Reference styling.
 */
export function formatFunctionHeaders(code) {
  if (!code) return "";
  const funcRegex = /^[ \t]*((?:(?:static|inline|extern)\s+)*[a-zA-Z0-9_]+(?:<[^>\r\n]+>)?(?:\s*\*+)?\s+[a-zA-Z0-9_]+)\s*\(([^;{}]+)\)(\s*(?:\{|\r?\n\{|;))/gm;

  return code.replace(funcRegex, (fullMatch, declPrefix, argsStr, trailingToken) => {
    const words = declPrefix.trim().split(/\s+/);
    const funcName = words[words.length - 1];
    const retType = words.slice(0, words.length - 1).join(" ");
    if (/^(if|for|while|switch|catch|return)$/.test(funcName)) return fullMatch;
    if (/^(if|for|while|switch|catch|return|typedef|struct)$/.test(retType.trim())) return fullMatch;

    const args = splitArgs(argsStr);
    if (args.length <= 1) {
      if (args.length === 1) {
        const a = parseParam(args[0]);
        const singleArg = a.type ? `${a.type} ${a.name}` : a.name;
        const isSemi = trailingToken.trim() === ";";
        return `${declPrefix}(${singleArg})${isSemi ? ";" : trailingToken}`;
      }
      return fullMatch;
    }

    const parsedArgs = args.map(parseParam);
    const maxTypeLen = Math.max(...parsedArgs.map((a) => a.type.length));

    const linePrefix = `${declPrefix}(`;
    const lastLineOfPrefix = linePrefix.includes("\n")
      ? linePrefix.slice(linePrefix.lastIndexOf("\n") + 1)
      : linePrefix;
    const indent = " ".repeat(lastLineOfPrefix.length);

    const isSemi = trailingToken.trim() === ";";
    const formattedLines = [];
    parsedArgs.forEach((a, i) => {
      const alignedType = a.type ? a.type.padEnd(maxTypeLen) : "";
      const sep = alignedType ? " " : "";
      const isLast = i === parsedArgs.length - 1;
      const suffix = isLast ? (isSemi ? ");" : ")") : ",";
      if (i === 0) {
        formattedLines.push(`${linePrefix}${alignedType}${sep}${a.name}${suffix}`);
      } else {
        formattedLines.push(`${indent}${alignedType}${sep}${a.name}${suffix}`);
      }
    });

    return formattedLines.join("\n") + (isSemi ? "" : trailingToken);
  });
}

