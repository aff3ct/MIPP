/**
 * MIPP API Explorer - Syntax Highlighter & Typography
 */
import { escapeHtml, ICON_COPY } from "./explorer.config.js";

export function formatCppObjProto(str, lmulKey = "1") {
  if (!str) return "";
  let s = str.replace(/\binline\s+/g, "").trim();
  if (lmulKey === "1") {
    return s.replace(/<([^,>]+),\s*LMUL>/g, "<$1>");
  } else {
    return s.replace(/<([^,>]+),\s*LMUL>/g, `<$1, LMUL=${lmulKey}>`);
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

export function formatMathHtml(expr) {
  if (!expr) return "";
  let clean = String(expr)
    .replace(/\\mathrm\{([^}]+)\}/g, "$1")
    .replace(/\\text\{([^}]+)\}/g, "$1")
    .replace(/\\operatorname\{([^}]+)\}/g, "$1")
    .replace(/\ba_i\b/g, "r0<sub>i</sub>")
    .replace(/\bb_i\b/g, "r1<sub>i</sub>")
    .replace(/\bc_i\b/g, "r2<sub>i</sub>")
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

export function highlightCpp(code, customMacros = {}) {
  if (!code) return "";
  const cleanCode = code.replace(/\binline\s+/g, "").trim();

  const tokenPatterns = [
    // 1. Comments
    '(//[^\n]*|/\\*[\\s\\S]*?\\*/)',
    // 2. Preprocessor
    '(#[a-zA-Z_]+[^\n]*)',
    // 3. Strings
    '("(?:\\\\.|[^"\\\\])*")',
    // 4. Numbers
    '\\b(0x[0-9a-fA-F]+|\\d+(?:\\.\\d+)?(?:[eE][+-]?\\d+)?[fFulUL]*)\\b',
    // 5. Types (MIPP SIMD types, Rvd, rvd, Rvm, rvm, C/C++ primitives)
    '\\b(MKIND|rvd_[a-z0-9_]+_t|rvm_[a-z0-9_]+_t|Rvd|rvd|Rvm|rvm|__m128[a-z0-9_]*|__m256[a-z0-9_]*|__m512[a-z0-9_]*|float32x4_t|float32x8_t|sv[a-z0-9_]+_t|v[a-z0-9_]+_t|reg|msk|void|bool|bool_t|char|int|short|long|float|double|float32_t|float64_t|uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t|size_t)\\b',
    // 6. Keywords
    '\\b(const|static|return|if|else|for|while|do|switch|case|default|break|continue|struct|class|template|typename|auto|sizeof|typedef|namespace|using|constexpr|extern)\\b',
    // 7. Functions / Hardware Intrinsics / MIPP / Function declarations & calls
    '(\\b_mm256_[a-zA-Z0-9_]+|\\b_mm512_[a-zA-Z0-9_]+|\\b_mm_[a-zA-Z0-9_]+|\\bv[a-z0-9_]+|\\bsv[a-z0-9_]+|\\b__riscv_[a-z0-9_]+|\\bmipp::[a-zA-Z0-9_]+|\\bmipp_[a-zA-Z0-9_]+|\\b[a-zA-Z_][a-zA-Z0-9_]*(?=\\s*\\())',
    // 8. Template parameters (T, T1, T2, LMUL, LDIV, N, MK, M, Z, S, U)
    '\\b(T|T1|T2|LMUL|LDIV|N|MK|M|Z|S|U)\\b',
  ];

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

    if (customMacros && customMacros[token]) {
      const macroInfo = customMacros[token];
      const macroDef = typeof macroInfo === "object" ? (macroInfo.definition || macroInfo.body || "") : String(macroInfo);
      html += `<span class="mipp-hl-macro mipp-macro-ref" data-macro-name="${escapeHtml(token)}" data-macro-def="${escapeHtml(macroDef)}" tabindex="0" role="button" title="Click to view macro definition">${escapeHtml(token)}</span>`;
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

export function toggleMacroTooltip(macroEl, macroName, macroDef) {
  if (!macroEl) return;
  const existing = document.querySelector(".mipp-macro-tooltip");
  if (existing && existing._targetMacro === macroEl) {
    hideMacroTooltip();
    return;
  }
  showMacroTooltip(macroEl, macroName, macroDef);
}

export function showMacroTooltip(macroEl, macroName, macroDef) {
  if (!macroEl) return;
  hideMacroTooltip();

  if (!macroName && macroEl) macroName = macroEl.getAttribute("data-macro-name") || "";
  if (!macroDef && macroEl) macroDef = macroEl.getAttribute("data-macro-def") || "";
  if (!macroDef) return;

  const tooltip = document.createElement("div");
  tooltip.className = "mipp-macro-tooltip";
  tooltip._targetMacro = macroEl;
  macroEl.classList.add("active");

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

  document.body.appendChild(tooltip);

  const rect = macroEl.getBoundingClientRect();
  const pad = 12;
  const maxW = Math.min(650, window.innerWidth - 2 * pad);
  tooltip.style.maxWidth = `${maxW}px`;
  tooltip.style.boxSizing = "border-box";

  let top = rect.bottom + window.scrollY + 6;
  let left = rect.left + window.scrollX;

  const tooltipWidth = tooltip.offsetWidth || maxW;
  const viewportRight = window.scrollX + window.innerWidth - pad;

  if (left + tooltipWidth > viewportRight) {
    left = Math.max(window.scrollX + pad, viewportRight - tooltipWidth);
  }
  if (left < window.scrollX + pad) {
    left = window.scrollX + pad;
  }

  tooltip.style.top = `${top}px`;
  tooltip.style.left = `${left}px`;

  tooltip.querySelector(".mipp-macro-tooltip-close").addEventListener("click", (ev) => {
    ev.stopPropagation();
    macroEl.classList.remove("active");
    tooltip.remove();
  });
}

export function hideMacroTooltip() {
  const existing = document.querySelector(".mipp-macro-tooltip");
  if (existing) {
    if (existing._targetMacro) {
      existing._targetMacro.classList.remove("active");
    }
    existing.remove();
  }
}
