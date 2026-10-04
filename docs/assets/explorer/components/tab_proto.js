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
  // Ensure space after commas in types and parameter lists
  s = s.replace(/,(\S)/g, ", $1");
  // When there are operator overloads (multiple lines), keep template on one line
  if (s.includes("\n")) {
    return s;
  }
  // Single prototype without operator overloads: format template on 2 lines
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

  const globalVariant = state.maskVariant || "unmasked";
  const targetMask = availableVariants.includes(globalVariant) ? globalVariant : "unmasked";

  // Headers: from coarsest to finest grain
  const maskVariantCode = {
    unmasked: "u",
    mask: "m",
    maskz: "z",
    masks: "s",
  }[targetMask] || "u";

  const lmulCode = {
    "-2": "d2",
    "1": "m1",
    "2": "m2",
    "4": "m4",
    "8": "m8",
  }[String(state.lmul)] || "m1";

  const lmulLabel = String(state.lmul) === "-2" ? "LMUL=1/2" : `LMUL=${state.lmul}`;

  let flavorDir = "cpp";
  let ext = "hpp";
  let monoHeader = "mipp.hpp";
  if (state.flavor === "c99") {
    flavorDir = "c";
    ext = "h";
    monoHeader = "mipp.h";
  } else if (state.flavor === "obj") {
    flavorDir = "obj";
    ext = "hpp";
    monoHeader = "mipp_obj.hpp";
  }

  const cat = entry.category || "arithmetic";
  const pad = (s, width = 52) => (s.length < width ? s + " ".repeat(width - s.length) : s + " ");

  const headersText = [
    "// Option 1: Monolithic (entire library)",
    `#include <${monoHeader}>`,
    "",
    "// Option 2: Category level",
    `${pad(`#include <mipp/${flavorDir}/cat/${cat}.${ext}>`)}// all variants & LMULs`,
    `${pad(`#include <mipp/${flavorDir}/cat/${maskVariantCode}/${cat}.${ext}>`)}// 1D: '${maskVariantCode}' variant only (*)`,
    `${pad(`#include <mipp/${flavorDir}/cat/${lmulCode}/${cat}.${ext}>`)}// 1D: ${lmulLabel} only (*)`,
    `${pad(`#include <mipp/${flavorDir}/cat/${maskVariantCode}/${lmulCode}/${cat}.${ext}>`)}// 2D: '${maskVariantCode}' + ${lmulLabel} (*)`,
    "",
    "// Option 3: Function level (recommended for minimal dependencies)",
    `${pad(`#include <mipp/${flavorDir}/fun/${entry.name}.${ext}>`)}// all variants & LMULs`,
    `${pad(`#include <mipp/${flavorDir}/fun/${maskVariantCode}/${entry.name}.${ext}>`)}// 1D: '${maskVariantCode}' variant only (*)`,
    `${pad(`#include <mipp/${flavorDir}/fun/${lmulCode}/${entry.name}.${ext}>`)}// 1D: ${lmulLabel} only (*)`,
    `${pad(`#include <mipp/${flavorDir}/fun/${maskVariantCode}/${lmulCode}/${entry.name}.${ext}>`)}// 2D atomic: '${maskVariantCode}' + ${lmulLabel} (fastest compilation) (*)`,
    "",
    "// (*) Fine-grained headers require MIPP generated with '--granularity fine'",
  ].join("\n");

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
    if (proto.includes("\n") && !proto.includes("template <")) {
      let cleanLines = proto.split("\n");
      if (activeDts.length > 0) {
        const filtered = cleanLines.filter((sig) =>
          activeDts.some((dt) => sig.includes(`<${dt}_t`) || sig.includes(`_${dt}(`))
        );
        if (filtered.length > 0) cleanLines = filtered;
      }
      codeText = cleanLines.join("\n");
    } else {
      codeText = proto;
    }
  } else {
    // C++ Object API
    const objSamples = protoData.obj_samples || protoData.cpp_obj_samples;
    const objSample = objSamples ? objSamples[lmulKey] : null;
    let proto = "";
    if (typeof objSample === "object" && objSample !== null) {
      proto = cleanProto(objSample[targetMask] || objSample["unmasked"] || "");
    } else if (typeof objSample === "string") {
      proto = cleanProto(objSample);
    }
    if (!proto) {
      proto = cleanProto(protoData.obj || protoData.cpp_obj || `mipp::${entry.name}(...)`);
    }
    codeText = formatCppObjProto(proto, lmulKey);
  }

  const isUnsupported = !availableVariants.includes(globalVariant);
  const title = state.flavor === "c99"
    ? "C99 API"
    : state.flavor === "cpp"
      ? "C++ Functional API"
      : "C++ Object API";

  return `
    <div class="mipp-proto-group" style="margin-bottom: 0.75rem;">
      <div class="mipp-code-box">
        <div class="mipp-code-box-header">
          <div class="mipp-code-box-header-left">
            <span class="mipp-code-box-title">Headers</span>
          </div>
          <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(headersText)}" title="Copy headers">
            ${ICON_COPY}
          </button>
        </div>
        <pre><code>${highlightCpp(headersText)}</code></pre>
      </div>
    </div>

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
