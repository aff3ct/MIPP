/**
 * MIPP API Explorer - "View Algorithm" Modal Component
 * Displays an abstract, conceptual C++ representation of the operation,
 * its LMUL unrolling (including LMUL = -2 note), and mask emulation layers,
 * OR a fully self-contained, standalone Flat C99 Code implementation
 * with direct Compiler Explorer (Godbolt) execution support.
 */
import { escapeHtml, ICON_COPY, ICON_GODBOLT } from "../explorer.config.js";
import { highlightCpp, formatFunctionHeaders } from "../syntax.js";
import { SIMD_EXT_DISPLAY_NAMES, ALL_MASK_MODES, MASK_MODES_INFO, LEVEL_DESCRIPTIONS } from "../data.js";
import { state } from "../state.js";
import { generateFlatSpecializedCode, buildGodboltUrlForFlat } from "../codegen.js";

export const ALL_MODAL_ISAS = ["sse", "avx", "avx512", "neon", "sve", "rvv", "scalar"];

export function renderAlgoModal(modalData) {
  if (!modalData) return "";
  const { entry } = modalData;
  const rawIsa = modalData.isa || modalData.simdExt || "avx";
  const currentIsa = ALL_MODAL_ISAS.includes(rawIsa) ? rawIsa : "avx";
  const currentView = modalData.view === "flat" ? "flat" : "abstract";
  const currentScalarSize = Number(modalData.scalarSize) || 256;
  const namesMap = { ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" };

  const allDts = entry.datatypes || [];
  const activeDts = allDts.filter((d) => state.selectedTypes.includes(d));
  const selectableDts = (state.selectedTypes.length > 0 && activeDts.length > 0) ? activeDts : allDts;
  const defaultDt = selectableDts[0] || "float32";
  const currentDt = (modalData.dt && selectableDts.includes(modalData.dt)) ? modalData.dt : defaultDt;

  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const defaultMask = (state.maskVariant && allVariants.includes(state.maskVariant))
    ? state.maskVariant
    : (allVariants[0] || "unmasked");
  const currentMask = (modalData.mask && allVariants.includes(modalData.mask)) ? modalData.mask : defaultMask;

  const effectiveLmul = (modalData.lmul !== undefined && modalData.lmul !== null) ? String(modalData.lmul) : (state.lmul || "1");

  const numLmul = Number(effectiveLmul) || 1;
  const isHalfLmul = effectiveLmul === "-2";

  // Determine return type and argument names from entry's base C++ prototype
  const baseProto = entry.prototypes?.cpp || "";
  const retMatch = baseProto.match(/^(?:template\s*<[^>]+>\s*)?([a-zA-Z0-9_<>]+)\s+[a-zA-Z0-9_]+\s*\(/);
  const rawRet = retMatch ? retMatch[1].trim() : "rvd<T>";
  const isVoidReturn = rawRet === "void";
  const isRvmReturn = rawRet.startsWith("rvm") || entry.category === "comparison";

  const dtMain = currentDt.includes(",") ? currentDt.split(",")[0].trim() : currentDt;
  const dtIdx = currentDt.includes(",") ? currentDt.split(",")[1].trim() : currentDt;

  const retType1 = isVoidReturn ? "void" : (isRvmReturn ? `rvm<${dtMain}, 1>` : `rvd<${dtMain}, 1>`);
  const retTypeLmul = isVoidReturn ? "void" : (isRvmReturn ? `rvm<${dtMain}, ${effectiveLmul}>` : `rvd<${dtMain}, ${effectiveLmul}>`);

  const paramMatch = baseProto.match(/\(([^)]*)\)/);
  let argNames = [];
  let argTypes = [];
  let rawArgDecls = [];
  if (paramMatch && paramMatch[1].trim()) {
    const parts = paramMatch[1].split(",").map((s) => s.trim());
    parts.forEach((part, idx) => {
      const words = part.split(/\s+/);
      const name = words[words.length - 1].replace(/[^a-zA-Z0-9_]/g, "") || `r${idx}`;
      argNames.push(name);
      rawArgDecls.push(part);
      if (part.includes("*")) {
        argTypes.push(part.includes("const") ? "const_ptr" : "ptr");
      } else if (part.includes("rvm") || part.includes("mask") || part.includes("msk")) {
        argTypes.push("rvm");
      } else if (part.includes("rvd") || part.includes("reg")) {
        argTypes.push("rvd");
      } else {
        argTypes.push("scalar");
      }
    });
  }
  if (argNames.length === 0) {
    argNames = ["r0"];
    argTypes = ["rvd"];
    rawArgDecls = ["const rvd<T> r0"];
  }

  const formatArgDecl = (secLmul) => {
    return argNames.map((a, idx) => {
      const t = argTypes[idx];
      if (t === "const_ptr") return `const ${dtMain}* ${a}`;
      if (t === "ptr") return `${dtMain}* ${a}`;
      if (t === "rvm") return `const rvm<${dtMain}, ${secLmul}> ${a}`;
      if (t === "rvd") {
        const dtArg = (idx > 0 && currentDt.includes(",")) ? dtIdx : dtMain;
        return `const rvd<${dtArg}, ${secLmul}> ${a}`;
      }
      return rawArgDecls[idx] || `const int ${a}`;
    }).join(", ");
  };

  const argDecl1 = formatArgDecl(1);
  const argDeclLmul = formatArgDecl(effectiveLmul);
  const callArgs = argNames.join(", ");

  const isScalar = currentIsa === "scalar";
  const isaInfo = isScalar ? null : (entry.isa_support ? entry.isa_support[currentIsa] : null);
  const hwLmuls = (isaInfo && isaInfo.hw_lmul) || (currentIsa === "rvv" ? [1, 2, 4, 8, -2] : [1]);
  const currentLmulVal = isHalfLmul ? -2 : numLmul;
  const isHwLmul = isScalar ? false : hwLmuls.includes(currentLmulVal);

  // Features resolution (contextual per ISA)
  const features = modalData.features || {};
  const isBW = features.BW !== false;
  const isDQ = features.DQ !== false;
  const isVL = features.VL !== false;
  const isCD = features.CD !== false;
  const isAVX2 = features.AVX2 !== false;
  const isFMA = features.FMA !== false;
  const isAArch64 = features.AArch64 !== false;
  const isRounding = features.Rounding !== false;
  const isSVE2 = features.SVE2 !== false;
  const sseTarget = features.sseTarget || "SSE4.2";

  // Check if current datatype's required feature is satisfied
  const reqFeature = (isaInfo && isaInfo.required_features) ? isaInfo.required_features[currentDt] : null;
  const fallbackLvl = (isaInfo && isaInfo.fallback_levels && isaInfo.fallback_levels[currentDt] !== undefined)
    ? isaInfo.fallback_levels[currentDt]
    : 2;

  let featureSatisfied = true;
  if (reqFeature) {
    if (currentIsa === "avx512") {
      if (reqFeature === "BW" && !isBW) featureSatisfied = false;
      else if (reqFeature === "DQ" && !isDQ) featureSatisfied = false;
      else if (reqFeature === "VL" && !isVL) featureSatisfied = false;
      else if (reqFeature === "CD" && !isCD) featureSatisfied = false;
    } else if (currentIsa === "avx") {
      if (reqFeature === "AVX2" && !isAVX2) featureSatisfied = false;
      else if (reqFeature === "FMA" && !isFMA) featureSatisfied = false;
    } else if (currentIsa === "neon") {
      if (reqFeature === "AArch64" && !isAArch64) featureSatisfied = false;
      else if (reqFeature === "FMA" && !isFMA) featureSatisfied = false;
      else if (reqFeature === "Rounding" && !isRounding) featureSatisfied = false;
    } else if (currentIsa === "sve") {
      if (reqFeature === "SVE2" && !isSVE2) featureSatisfied = false;
    } else if (currentIsa === "sse") {
      const SSE_RANKS = { "SSE": 1, "SSE2": 2, "SSE3": 3, "SSSE3": 4, "SSE4.1": 5, "SSE4.2": 6 };
      const reqRank = SSE_RANKS[reqFeature] || 2;
      const targetRank = SSE_RANKS[sseTarget] || 6;
      if (targetRank < reqRank) featureSatisfied = false;
    }
  }

  // Compute implementation level based on currentDt, currentMask, effectiveLmul, and feature satisfaction
  let currentImplLvl = "na";
  let baseImplLvl = "na";
  let primitiveImplLvl = "na";
  if (isScalar) {
    currentImplLvl = 3;
    baseImplLvl = 3;
    primitiveImplLvl = 3;
  } else if (isaInfo) {
    baseImplLvl = (isaInfo.by_datatype && isaInfo.by_datatype[currentDt] !== undefined)
      ? isaInfo.by_datatype[currentDt]
      : (isaInfo.overall_level !== undefined ? isaInfo.overall_level : 3);
    if (!featureSatisfied && baseImplLvl < fallbackLvl) {
      baseImplLvl = fallbackLvl;
    }

    if (currentMask === "unmasked") {
      primitiveImplLvl = baseImplLvl;
    } else {
      const maskedDict = isaInfo.masked_by_datatype ? isaInfo.masked_by_datatype[currentMask] : null;
      primitiveImplLvl = (maskedDict && maskedDict[currentDt] !== undefined)
        ? maskedDict[currentDt]
        : 2;
      if (!featureSatisfied && primitiveImplLvl < fallbackLvl) {
        primitiveImplLvl = fallbackLvl;
      }
    }

    currentImplLvl = primitiveImplLvl;
    const isLmulEmulated = (currentLmulVal !== 1) && !hwLmuls.includes(currentLmulVal);
    if (isLmulEmulated && currentImplLvl < 2) {
      currentImplLvl = 2;
    }

    if (currentImplLvl > 3 || currentImplLvl === undefined) {
      currentImplLvl = "na";
    }
  }

  const lvlDesc = LEVEL_DESCRIPTIONS[currentImplLvl] || (currentImplLvl === "na" ? "Not Supported" : `Level ${currentImplLvl}`);

  const FEATURE_DEFINES_MAP = {
    F: "__AVX512F__",
    BW: "__AVX512BW__",
    DQ: "__AVX512DQ__",
    VL: "__AVX512VL__",
    CD: "__AVX512CD__",
    AVX2: "__AVX2__",
    FMA: currentIsa === "neon" ? "__ARM_FEATURE_FMA" : "__FMA__",
    "SSE4.2": "__SSE4_2__",
    "SSE4.1": "__SSE4_1__",
    SSSE3: "__SSSE3__",
    SSE3: "__SSE3__",
    SSE2: "__SSE2__",
    AArch64: "__aarch64__",
    Rounding: "__ARM_FEATURE_DIRECTED_ROUNDING",
    SVE: "__ARM_FEATURE_SVE",
    SVE2: "__ARM_FEATURE_SVE2"
  };

  let requiredDefinesStr = "";
  if (isScalar) {
    requiredDefinesStr = `None (Scalar Reference | SIMD Width: ${currentScalarSize} bits)`;
  } else if (reqFeature && featureSatisfied) {
    const macro = FEATURE_DEFINES_MAP[reqFeature] || reqFeature;
    requiredDefinesStr = `${reqFeature} (${macro})`;
  } else if (currentImplLvl === 0) {
    requiredDefinesStr = `None (Baseline ${namesMap[currentIsa] || currentIsa.toUpperCase()})`;
  } else if (currentImplLvl === 1 || currentImplLvl === 2) {
    if (reqFeature && !featureSatisfied) {
      const macro = FEATURE_DEFINES_MAP[reqFeature] || reqFeature;
      requiredDefinesStr = `None (Fallback emulation when ${reqFeature} is disabled)`;
    } else {
      requiredDefinesStr = "None (Generic Emulation)";
    }
  } else if (currentImplLvl === 3) {
    if (reqFeature && !featureSatisfied) {
      const macro = FEATURE_DEFINES_MAP[reqFeature] || reqFeature;
      requiredDefinesStr = `None (Scalar fallback when ${reqFeature} is disabled)`;
    } else {
      requiredDefinesStr = "None (Scalar Fallback)";
    }
  } else {
    requiredDefinesStr = "N/A (Not Supported)";
  }

  // Helper to harmonize register types in emulation algorithms
  const formatEmuAlgo = (rawCode, secLmul) => {
    if (!rawCode) return "";
    const regType = `rvd<${dtMain}, ${secLmul}>`;
    const maskType = `rvm<${dtMain}, ${secLmul}>`;
    return rawCode
      .replace(/\bmipp::reg\b/g, regType)
      .replace(/\bmipp::(?:msk|mask)\b/g, maskType)
      .replace(/\breg\b(?=\s+[a-zA-Z0-9_]+\s*[;=])/g, regType)
      .replace(/\b(?:msk|mask)\b(?=\s+[a-zA-Z0-9_]+\s*[;=])/g, maskType);
  };

  // Build Abstract Layered C++ Code
  const codeLines = [];
  codeLines.push(`// =============================================================================`);
  codeLines.push(`// Conceptual Algorithm: mipp::${entry.name} (${namesMap[currentIsa] || currentIsa.toUpperCase()})`);
  codeLines.push(`// Datatype (T): ${currentDt} | Variant: ${currentMask} | LMUL: ${effectiveLmul}`);
  codeLines.push(`// Implementation Level: ${currentImplLvl === "na" ? "N/A (Not Supported)" : `Level ${currentImplLvl} (${lvlDesc})`}`);
  codeLines.push(`// Required Defines: ${requiredDefinesStr}`);
  if (isHalfLmul) {
    codeLines.push(`// Note: LMUL = -2 represents LMUL = 1/2 (d2)`);
  }
  codeLines.push(`// =============================================================================`);
  codeLines.push("");

  const cleanSnippetForCpp = (snip, dt, secLmul) => {
    if (!snip) return "";
    let s = snip.replace(/;\s*$/, "");
    s = s.replace(/%set0<[^>]*>%\(\)/g, `mipp::set0<${dt}>()`);
    s = s.replace(/%r<[^>]*>%/g, `rvd<${dt}, ${secLmul}>`);
    s = s.replace(/%m<[^>]*>%/g, `rvm<${dt}, ${secLmul}>`);
    s = s.replace(/%cast<[^>]*>%/g, `mipp::cast`);
    s = s.replace(/%([a-zA-Z0-9_]+)<[^>]*>%/g, `mipp::$1`);
    s = s.replace(/%/g, "");
    s = s.replace(/\brsrc\.r\b/g, "src.r").replace(/\brsrc\b/g, "src");
    s = s.replace(/,([^\s])/g, ", $1");
    if (s.startsWith("return ")) {
      s = s.slice(7).trim();
    }
    return s;
  };

  const getSpecializedFuncName = (maskName) => {
    return maskName === "unmasked" ? entry.name : `${entry.name}_${maskName}`;
  };

  const formatSpecializedParams = (secLmul, maskName) => {
    const argsDecl = formatArgDecl(secLmul);
    if (maskName === "mask" || maskName === "maskz") {
      return `const rvm<${dtMain}, ${secLmul}> m0, ${argsDecl}`;
    } else if (maskName === "masks") {
      return `const rvm<${dtMain}, ${secLmul}> m0, const rvd<${dtMain}, ${secLmul}> src, ${argsDecl}`;
    }
    return argsDecl;
  };

  const formatSpecializedCallArgs = (maskName, isUnroll = false) => {
    const innerArgs = argNames.map((a, idx) => {
      const t = argTypes[idx];
      if (isUnroll && (t === "rvd" || t === "rvm")) {
        return `${a}[i]`;
      }
      return a;
    });

    if (maskName === "mask" || maskName === "maskz") {
      const mArg = isUnroll ? "m0[i]" : "m0";
      return [mArg, ...innerArgs].join(", ");
    } else if (maskName === "masks") {
      const mArg = isUnroll ? "m0[i]" : "m0";
      const srcArg = isUnroll ? "src[i]" : "src";
      return [mArg, srcArg, ...innerArgs].join(", ");
    }
    return innerArgs.join(", ");
  };

  const generatePrimitiveBody = (secLmul, secMask) => {
    const lines = [];
    const specFuncName = getSpecializedFuncName(secMask);
    const specCallArgs = formatSpecializedCallArgs(secMask, false);
    const targetLvl = (secMask === "unmasked") ? baseImplLvl : primitiveImplLvl;

    if (isScalar || targetLvl === 3) {
      lines.push(`    // Level 3 (Auto Scalar Fallback)`);
      if (secMask === "mask") {
        lines.push(`    return scalar_${entry.name}_mask(m0.m, ${argNames.map((a) => `${a}.r`).join(", ")});`);
      } else if (secMask === "maskz") {
        lines.push(`    return scalar_${entry.name}_maskz(m0.m, ${argNames.map((a) => `${a}.r`).join(", ")});`);
      } else if (secMask === "masks") {
        lines.push(`    return scalar_${entry.name}_masks(m0.m, src.r, ${argNames.map((a) => `${a}.r`).join(", ")});`);
      } else {
        lines.push(`    return scalar_${entry.name}(${argNames.map((a) => `${a}.r`).join(", ")});`);
      }
    } else if (targetLvl === 0) {
      lines.push(`    // Level 0 (Native Hardware Intrinsic Mapping)`);
      let nativeSnip = null;
      if (secMask === "unmasked") {
        const lmulKey = String(secLmul);
        const snippetDict = (isaInfo && isaInfo.code_snippets_by_lmul && isaInfo.code_snippets_by_lmul[lmulKey])
          || (isaInfo && isaInfo.code_snippets)
          || {};
        nativeSnip = (baseImplLvl === 0 && featureSatisfied)
          ? (snippetDict[currentDt] || (isaInfo && isaInfo.code_snippets && isaInfo.code_snippets[currentDt]) || null)
          : null;
      } else {
        nativeSnip = (featureSatisfied && isaInfo && isaInfo.code_snippets_by_mask && isaInfo.code_snippets_by_mask[secMask])
          ? (isaInfo.code_snippets_by_mask[secMask][currentDt] || isaInfo.code_snippets_by_mask[secMask][dtMain])
          : null;
      }

      if (nativeSnip) {
        const cleaned = cleanSnippetForCpp(nativeSnip, dtMain, secLmul);
        lines.push(`    return ${cleaned};`);
      } else {
        lines.push(`    return mipp::${specFuncName}(${specCallArgs});`);
      }
    } else if (targetLvl === 1) {
      lines.push(`    // Level 1 (Dedicated Hardware Emulation)`);
      let emuSnip = (isaInfo && isaInfo.code_snippets_by_mask && isaInfo.code_snippets_by_mask[secMask])
        ? (isaInfo.code_snippets_by_mask[secMask][currentDt] || isaInfo.code_snippets_by_mask[secMask][dtMain])
        : null;
      const emuAlgo = isaInfo && isaInfo.emulation_algorithms ? (isaInfo.emulation_algorithms[currentDt] || isaInfo.emulation_algorithms[dtMain]) : null;
      if (emuSnip) {
        const cleaned = cleanSnippetForCpp(emuSnip, dtMain, secLmul);
        lines.push(`    return ${cleaned};`);
      } else if (emuAlgo) {
        formatEmuAlgo(emuAlgo, secLmul).split("\n").forEach((l) => lines.push(`    ${l}`));
      } else if (secMask === "maskz") {
        lines.push(`    return mipp::${entry.name}_masks(m0, mipp::set0<${dtMain}>(), ${callArgs});`);
      } else {
        lines.push(`    return mipp::${specFuncName}(${specCallArgs});`);
      }
    } else {
      // Level 2 (Generic Emulated Mapping)
      const emuAlgo = isaInfo && isaInfo.emulation_algorithms ? (isaInfo.emulation_algorithms[currentDt] || isaInfo.emulation_algorithms[dtMain]) : null;
      if (emuAlgo) {
        lines.push(`    // Level 2 (Generic Emulated Mapping)`);
        formatEmuAlgo(emuAlgo, secLmul).split("\n").forEach((l) => lines.push(`    ${l}`));
      } else {
        lines.push(`    // Level 2 (Generic Emulated Mapping)`);
        lines.push(`    return mipp::${specFuncName}(${specCallArgs});`);
      }
    }
    return lines;
  };

  const isLmulDecomposed = !isHwLmul && (numLmul > 1 || isHalfLmul);
  const isMaskDecomposed = (primitiveImplLvl === 2 && currentMask !== "unmasked");
  const isDecomposed = isLmulDecomposed || isMaskDecomposed;

  if (!isDecomposed) {
    const specFuncName = getSpecializedFuncName(currentMask);
    const specParams = formatSpecializedParams(effectiveLmul, currentMask);
    codeLines.push(`${retTypeLmul} ${specFuncName}(${specParams}) {`);
    codeLines.push(...generatePrimitiveBody(effectiveLmul, currentMask));
    codeLines.push(`}`);
  } else {
    let sectionIdx = 1;

    if (isMaskDecomposed) {
      // Step 1: Base Primitive Operation (LMUL = 1, unmasked)
      codeLines.push(`// ${sectionIdx++}. Base Primitive Operation (LMUL = 1, unmasked)`);
      codeLines.push(`${retType1} ${entry.name}(${argDecl1}) {`);
      codeLines.push(...generatePrimitiveBody(1, "unmasked"));
      codeLines.push(`}`);
      codeLines.push("");

      // Step 2: Predicated Execution Layer (LMUL = 1, currentMask)
      const specFuncName1 = getSpecializedFuncName(currentMask);
      const specParams1 = formatSpecializedParams(1, currentMask);
      if (currentMask === "mask") {
        codeLines.push(`// ${sectionIdx++}. Predicated Execution Layer (Blend Preservation)`);
        codeLines.push(`${retType1} ${specFuncName1}(${specParams1}) {`);
        codeLines.push(`    // Level 2 (Generic Emulation with blend)`);
        codeLines.push(`    ${retType1} op = mipp::${entry.name}(${callArgs});`);
        codeLines.push(`    return mipp::blend(op, ${argNames[0]}, m0); // Inactive lanes preserve ${argNames[0]}`);
        codeLines.push(`}`);
      } else if (currentMask === "maskz") {
        codeLines.push(`// ${sectionIdx++}. Predicated Execution Layer (Zeroing False Lanes)`);
        codeLines.push(`${retType1} ${specFuncName1}(${specParams1}) {`);
        codeLines.push(`    // Level 2 (Generic Emulation with andb)`);
        codeLines.push(`    ${retType1} op = mipp::${entry.name}(${callArgs});`);
        if (isRvmReturn) {
          codeLines.push(`    return mipp::andb_k(op, m0); // Inactive lanes set to zero`);
        } else {
          codeLines.push(`    return mipp::andb(mipp::toreg(m0), op); // Inactive lanes set to zero`);
        }
        codeLines.push(`}`);
      } else if (currentMask === "masks") {
        codeLines.push(`// ${sectionIdx++}. Predicated Execution Layer (Source Register Preservation)`);
        codeLines.push(`${retType1} ${specFuncName1}(${specParams1}) {`);
        codeLines.push(`    // Level 2 (Generic Emulation with blend)`);
        codeLines.push(`    ${retType1} op = mipp::${entry.name}(${callArgs});`);
        codeLines.push(`    return mipp::blend(op, src, m0); // Inactive lanes preserve src`);
        codeLines.push(`}`);
      }
    } else {
      // Step 1: Base Primitive Operation (LMUL = 1, currentMask)
      codeLines.push(`// ${sectionIdx++}. Base Primitive Operation (LMUL = 1, ${currentMask})`);
      const specFuncName1 = getSpecializedFuncName(currentMask);
      const specParams1 = formatSpecializedParams(1, currentMask);
      codeLines.push(`${retType1} ${specFuncName1}(${specParams1}) {`);
      codeLines.push(...generatePrimitiveBody(1, currentMask));
      codeLines.push(`}`);
    }

    if (isLmulDecomposed) {
      codeLines.push("");
      const specFuncNameLmul = getSpecializedFuncName(currentMask);
      const specParamsLmul = formatSpecializedParams(effectiveLmul, currentMask);
      const unrollCall = formatSpecializedCallArgs(currentMask, true);

      if (isHalfLmul) {
        codeLines.push(`// ${sectionIdx++}. Sub-vector Specialization (LMUL = -2 / d2)`);
        codeLines.push(`// Note: LMUL = -2 represents LMUL = 1/2 (d2)`);
        codeLines.push(`${retTypeLmul} ${specFuncNameLmul}(${specParamsLmul}) {`);
        codeLines.push(`    // Operation on half-vector via narrower architecture or lower register half`);
        codeLines.push(`    return mipp::${specFuncNameLmul}< -2 >(${formatSpecializedCallArgs(currentMask, false)});`);
        codeLines.push(`}`);
      } else if (numLmul > 1) {
        codeLines.push(`// ${sectionIdx++}. Vectorized Multi-Register Unrolling (LMUL = ${numLmul})`);
        codeLines.push(`${retTypeLmul} ${specFuncNameLmul}(${specParamsLmul}) {`);
        if (isVoidReturn) {
          codeLines.push(`    for (int i = 0; i < ${numLmul}; i++) {`);
          codeLines.push(`        mipp::${specFuncNameLmul}(${unrollCall});`);
          codeLines.push(`    }`);
        } else {
          codeLines.push(`    ${retTypeLmul} res;`);
          codeLines.push(`    for (int i = 0; i < ${numLmul}; i++) {`);
          codeLines.push(`        res[i] = mipp::${specFuncNameLmul}(${unrollCall});`);
          codeLines.push(`    }`);
          codeLines.push(`    return res;`);
        }
        codeLines.push(`}`);
      }
    }
  }

  const fullCode = formatFunctionHeaders(codeLines.join("\n"));

  // Flat C99 Code Configuration & Generation
  const flatDefines = {
    __AVX512F__: true,
    __AVX512BW__: isBW,
    __AVX512DQ__: isDQ,
    __AVX512VL__: isVL,
    __AVX512CD__: isCD,
    __AVX2__: isAVX2,
    __FMA__: isFMA,
    __SSE4_2__: sseTarget === "SSE4.2",
    __SSE4_1__: ["SSE4.2", "SSE4.1"].includes(sseTarget),
    __SSSE3__: ["SSE4.2", "SSE4.1", "SSSE3"].includes(sseTarget),
    __SSE3__: ["SSE4.2", "SSE4.1", "SSSE3", "SSE3"].includes(sseTarget),
    __SSE2__: true,
    __aarch64__: isAArch64,
    __ARM_FEATURE_FMA: isFMA,
    __ARM_FEATURE_DIRECTED_ROUNDING: isRounding,
    __ARM_FEATURE_SVE: true,
    __ARM_FEATURE_SVE2: isSVE2
  };

  const flatCfg = {
    isa: currentIsa,
    defines: flatDefines,
    dt: currentDt,
    mask: currentMask,
    lmul: effectiveLmul,
    scalarSize: currentScalarSize
  };

  let flatStandaloneCode = "";
  let godboltUrl = "";
  if (currentView === "flat") {
    flatStandaloneCode = generateFlatSpecializedCode(entry, flatCfg);
    godboltUrl = buildGodboltUrlForFlat(flatStandaloneCode, currentIsa, flatDefines, currentScalarSize);
  }

  const VARIANT_LETTERS = { unmasked: "U", mask: "M", maskz: "Z", masks: "S" };
  const VARIANT_TITLES = {
    unmasked: "Unmasked",
    mask: "Mask (merge)",
    maskz: "Maskz (zeroing)",
    masks: "Masks (sourcing)"
  };

  const simdWidthHtml = `
    <div class="mipp-modal-ctrl-group">
      <span class="mipp-control-label">SIMD Width:</span>
      <div class="mipp-segmented-group" id="mipp-modal-scalarsize-group">
        ${[128, 256, 512, 1024, 2048].map((sz) => `
          <button type="button" class="mipp-segment-btn ${sz === currentScalarSize ? "active" : ""}" data-modal-scalarsize="${sz}" title="${sz} bits">${sz}b</button>
        `).join("")}
      </div>
    </div>
  `;

  let featureControlsHtml = "";
  if (currentIsa === "scalar" || currentIsa === "rvv") {
    featureControlsHtml += simdWidthHtml;
  }

  if (currentIsa === "avx512") {
    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        <div class="mipp-segmented-group" id="mipp-modal-features-group">
          <button type="button" class="mipp-segment-btn active" data-modal-toggle-feature="F" title="AVX-512 Foundation (Base)" style="pointer-events: none; opacity: 0.85;">F</button>
          <button type="button" class="mipp-segment-btn ${isBW ? "active" : ""}" data-modal-toggle-feature="BW" title="AVX-512 Byte and Word">BW</button>
          <button type="button" class="mipp-segment-btn ${isDQ ? "active" : ""}" data-modal-toggle-feature="DQ" title="AVX-512 Doubleword and Quadword">DQ</button>
          <button type="button" class="mipp-segment-btn ${isVL ? "active" : ""}" data-modal-toggle-feature="VL" title="AVX-512 Vector Length">VL</button>
          <button type="button" class="mipp-segment-btn ${isCD ? "active" : ""}" data-modal-toggle-feature="CD" title="AVX-512 Conflict Detection">CD</button>
        </div>
      </div>
    `;
  } else if (currentIsa === "avx") {
    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        <div class="mipp-segmented-group" id="mipp-modal-features-group">
          <button type="button" class="mipp-segment-btn ${isAVX2 ? "active" : ""}" data-modal-toggle-feature="AVX2" title="Advanced Vector Extensions 2">AVX2</button>
          <button type="button" class="mipp-segment-btn ${isFMA ? "active" : ""}" data-modal-toggle-feature="FMA" title="Fused Multiply-Add">FMA</button>
        </div>
      </div>
    `;
  } else if (currentIsa === "sse") {
    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        <div class="mipp-segmented-group" id="mipp-modal-sse-target-group">
          ${["SSE2", "SSE3", "SSSE3", "SSE4.1", "SSE4.2"].map((t) => `
            <button type="button" class="mipp-segment-btn ${sseTarget === t ? "active" : ""}" data-modal-sse-target="${t}" title="${t} Target">${t}</button>
          `).join("")}
        </div>
      </div>
    `;
  } else if (currentIsa === "neon") {
    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        <div class="mipp-segmented-group" id="mipp-modal-features-group">
          <button type="button" class="mipp-segment-btn ${isAArch64 ? "active" : ""}" data-modal-toggle-feature="AArch64" title="ARM 64-bit Architecture">AArch64</button>
          <button type="button" class="mipp-segment-btn ${isFMA ? "active" : ""}" data-modal-toggle-feature="FMA" title="ARM Fused Multiply-Add">FMA</button>
          <button type="button" class="mipp-segment-btn ${isRounding ? "active" : ""}" data-modal-toggle-feature="Rounding" title="ARM Directed Rounding">Rounding</button>
        </div>
      </div>
    `;
  } else if (currentIsa === "sve") {
    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        <div class="mipp-segmented-group" id="mipp-modal-features-group">
          <button type="button" class="mipp-segment-btn active" data-modal-toggle-feature="SVE" title="Base SVE (locked)" style="pointer-events: none; opacity: 0.85;">SVE</button>
          <button type="button" class="mipp-segment-btn ${isSVE2 ? "active" : ""}" data-modal-toggle-feature="SVE2" title="Scalable Vector Extension 2">SVE2</button>
        </div>
      </div>
    `;
    featureControlsHtml += simdWidthHtml;
  }

  return `
    <div class="mipp-modal-backdrop visible active" id="mipp-algo-modal-backdrop">
      <div class="mipp-modal-container mipp-modal-content mipp-algo-modal-content">
        <!-- Header -->
        <div class="mipp-modal-header">
          <div style="display: flex; gap: 0.65rem; align-items: center; flex-wrap: wrap;">
            <h3 class="mipp-modal-title" style="margin: 0;">Algorithm: <code>mipp::${escapeHtml(entry.name)}</code></h3>
          </div>
          <div style="display: flex; gap: 0.45rem; align-items: center;">
            <button class="mipp-modal-share-btn" id="mipp-algo-modal-share" title="Copy direct link to this algorithm" aria-label="Share direct link">🔗</button>
            <button class="mipp-modal-close-btn" id="mipp-algo-modal-close" title="Close modal" aria-label="Close modal">×</button>
          </div>
        </div>

        <div class="mipp-modal-body" style="display: flex; flex-direction: column; gap: 0.85rem; min-width: 0; max-width: 100%; box-sizing: border-box;">
          <!-- Selectors Toolbar: Shared Across Views (Above Tabs) -->
          <div class="mipp-modal-toolbar">
            <!-- ISA Selector -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">SIMD Ext:</span>
              <div class="mipp-segmented-group" id="mipp-modal-isa-group">
                ${ALL_MODAL_ISAS.map((ext) => `
                  <button type="button" class="mipp-segment-btn ${ext === currentIsa ? "active" : ""}" data-modal-isa="${ext}" title="${namesMap[ext] || ext.toUpperCase()}">
                    ${(namesMap[ext] || ext.toUpperCase()).replace("ARM ", "")}
                  </button>
                `).join("")}
              </div>
            </div>

            <!-- Datatype Selector -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">Datatype:</span>
              <select class="mipp-scalar-dt-select" id="mipp-algo-modal-dt-select" data-card="${escapeHtml(entry.name)}">
                ${selectableDts.map((d) => `
                  <option value="${d}" ${d === currentDt ? "selected" : ""}>${d}</option>
                `).join("")}
              </select>
            </div>

            <!-- Variant Selector (Segmented buttons) -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">Variant:</span>
              <div class="mipp-segmented-group" id="mipp-modal-mask-group">
                ${allVariants.map((m) => {
                  const isActive = m === currentMask;
                  return `<button type="button" class="mipp-segment-btn ${isActive ? "active" : ""}" data-modal-mask="${m}" title="${VARIANT_TITLES[m] || m}">${VARIANT_LETTERS[m] || m}</button>`;
                }).join("")}
              </div>
            </div>

            <!-- LMUL Selector (Segmented buttons) -->
            <div class="mipp-modal-ctrl-group">
              <span class="mipp-control-label">LMUL:</span>
              <div class="mipp-segmented-group" id="mipp-modal-lmul-group">
                ${["1", "2", "4", "8", "-2"].map((l) => {
                  const isActive = l === String(effectiveLmul);
                  return `<button type="button" class="mipp-segment-btn ${isActive ? "active" : ""}" data-modal-lmul="${l}" title="${l === "-2" ? "Half vector (LMUL=1/2 / d2)" : `LMUL = ${l}`}">${l === "-2" ? "1/2" : l}</button>`;
                }).join("")}
              </div>
            </div>

            <!-- Contextual Features / Target Switcher / SIMD Width -->
            ${featureControlsHtml}
          </div>

          <!-- Modal View Tabs: Abstract C++ Implementation vs Flat C99 Code -->
          <div class="mipp-modal-tabs" role="tablist">
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'abstract' ? 'active' : ''}" data-modal-view="abstract" role="tab" aria-selected="${currentView === 'abstract'}">
              Abstract C++ Implementation
            </button>
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'flat' ? 'active' : ''}" data-modal-view="flat" role="tab" aria-selected="${currentView === 'flat'}">
              Flat C99 Code
            </button>
          </div>

          <!-- Active View Content -->
          ${currentView === 'abstract' ? `
            <!-- Register Types Note (Abstract View Only) -->
            <div class="mipp-algo-note">
              <span class="mipp-algo-note-icon">💡</span>
              <span><strong>Registers:</strong> <code>rvd&lt;T, LMUL&gt;</code> represents vector <strong>data</strong> registers, and <code>rvm&lt;T, LMUL&gt;</code> represents vector <strong>mask</strong> registers.</span>
            </div>

            <!-- Abstract C++ Code Box -->
            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left" style="display: flex; gap: 0.55rem; align-items: center; flex-wrap: wrap;">
                  <span class="mipp-code-lang">Abstract C++ Implementation</span>
                  <span class="mipp-isa-badge lvl-${currentImplLvl}" title="Implementation Level: Level ${currentImplLvl} (${escapeHtml(lvlDesc)})">${currentImplLvl === "na" ? "N/A" : `L${currentImplLvl}`}</span>
                </div>
                <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(fullCode)}" title="Copy algorithm code">
                  ${ICON_COPY}
                </button>
              </div>
              <pre><code>${highlightCpp(fullCode)}</code></pre>
            </div>
          ` : `
            <!-- Flat C99 Code Box -->
            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left" style="display: flex; gap: 0.55rem; align-items: center; flex-wrap: wrap;">
                  <span class="mipp-code-lang">Flat C99 Code</span>
                  <span class="mipp-isa-badge lvl-${currentImplLvl}" title="Implementation Level: Level ${currentImplLvl} (${escapeHtml(lvlDesc)})">${currentImplLvl === "na" ? "N/A" : `L${currentImplLvl}`}</span>
                </div>
                <div style="display: flex; gap: 0.5rem; align-items: center;">
                  <a href="${godboltUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-btn" title="Open and compile in Godbolt">
                    ${ICON_GODBOLT}
                    <span>Open in Godbolt</span>
                  </a>
                  <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(flatStandaloneCode)}" title="Copy standalone C code">
                    ${ICON_COPY}
                  </button>
                </div>
              </div>
              <pre><code>${highlightCpp(flatStandaloneCode, entry.scalar_macros || {})}</code></pre>
            </div>
          `}
        </div>
      </div>
    </div>
  `;
}
