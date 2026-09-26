/**
 * MIPP API Explorer - Tab 2: C/C++ Prototypes
 */
import { escapeHtml, ICON_COPY } from "../explorer.config.js";
import { highlightCpp, formatCppObjProto } from "../syntax.js";
import { state } from "../state.js";
import { ALL_MASK_MODES } from "../data.js";

function cleanProto(str) {
  if (!str) return "";
  let s = str.replace(/\binline\s+/g, "").trim();
  return s.replace(/^(template\s*<[^>]+>)\s+/m, "$1\n");
}

export function renderTabProto(entry) {
  const lmulKey = state.lmul;
  const protoData = entry.prototypes;
  if (!protoData) return `<p>No prototype definitions available.</p>`;

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));

  const maskSupport = entry.mask_support || {};
  const availableVariants = ALL_MASK_MODES.filter(
    (m) => m === "unmasked" || maskSupport[m]
  );

  const globalVariant = state.flavor === "cpp_obj" ? "unmasked" : (state.maskVariant || "unmasked");
  const targetMask = availableVariants.includes(globalVariant) ? globalVariant : "unmasked";

  let codeText = "";
  if (state.flavor === "c99") {
    const samplesForLmul = protoData.c99_samples ? protoData.c99_samples[lmulKey] : null;
    let lines = [];
    if (samplesForLmul) {
      if (Array.isArray(samplesForLmul)) {
        lines = samplesForLmul;
      } else if (typeof samplesForLmul === "object") {
        lines = samplesForLmul[targetMask] || samplesForLmul["unmasked"] || [];
      }
    }
    if (lines.length > 0) {
      let cleanLines = lines.map(cleanProto);
      if (activeDts.length > 0) {
        const filtered = cleanLines.filter((sig) =>
          activeDts.some((dt) => sig.includes(`_${dt}_`) || sig.includes(`_${dt}(`) || sig.includes(`_${dt};`) || sig.includes(`_${dt}`))
        );
        if (filtered.length > 0) cleanLines = filtered;
      }
      codeText = cleanLines.join("\n");
    } else {
      codeText = cleanProto(protoData.c99 || `mipp_${entry.name}(...)`);
    }
  } else if (state.flavor === "cpp") {
    const cppSample = protoData.cpp_samples ? protoData.cpp_samples[lmulKey] : null;
    let proto = "";
    if (typeof cppSample === "object" && cppSample !== null) {
      proto = cleanProto(cppSample[targetMask] || cppSample["unmasked"] || "");
    } else if (typeof cppSample === "string") {
      proto = cleanProto(cppSample);
    }
    if (!proto) {
      proto = cleanProto(protoData.cpp || `mipp::${entry.name}(...)`);
    }
    codeText = proto;
  } else {
    // C++ Object
    let proto = "";
    if (protoData.cpp_obj_samples && protoData.cpp_obj_samples[lmulKey]) {
      proto = protoData.cpp_obj_samples[lmulKey];
    } else {
      proto = protoData.cpp_obj || `r0.${entry.name}(...)`;
    }
    codeText = formatCppObjProto(proto, lmulKey);
  }

  const isUnsupported = !availableVariants.includes(globalVariant);
  const title = state.flavor === "c99"
    ? "C99 Declarations"
    : state.flavor === "cpp"
      ? "C++ Function Templates"
      : "C++ Object Methods";

  return `
    <div class="mipp-proto-group" style="margin-bottom: 0.75rem;">
      <div class="mipp-code-box">
        <div class="mipp-code-box-header">
          <div class="mipp-code-box-header-left" style="display: flex; align-items: center; gap: 0.5rem;">
            <span class="mipp-code-box-title">${title}</span>
            ${isUnsupported
              ? `<span style="font-size: 0.75rem; color: #f59e0b; font-style: italic;">(${globalVariant} unsupported, showing unmasked)</span>`
              : ""
            }
          </div>
          <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(codeText)}" title="Copy prototype">
            ${ICON_COPY}
          </button>
        </div>
        <pre><code>${highlightCpp(codeText)}</code></pre>
      </div>
    </div>
  `;
}
