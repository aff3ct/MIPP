/**
 * MIPP API Explorer - Code Generation & Compiler Explorer (Godbolt) Integration
 */
import { apiMetadata, DT_INFO, apiData } from "./data.js";
import { formatFunctionHeaders } from "./syntax.js";

export function getHwRegType(isa, dt, defines, currentLmulVal = 1) {
  if (isa === "rvv") {
    const lsuffix = currentLmulVal === -2 ? "mf2" : `m${currentLmulVal}`;
    return `v${dt}${lsuffix}_t`;
  }
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[isa] : null;
  if (isaMeta && isaMeta.datatypes && isaMeta.datatypes[dt] && isaMeta.datatypes[dt].reg) {
    if (isa === "neon" && dt === "float64") {
      return (defines && defines.__aarch64__ !== false) ? isaMeta.datatypes[dt].reg : "double";
    }
    return isaMeta.datatypes[dt].reg;
  }
  const dti = (DT_INFO && DT_INFO[dt]) || { c_type: "float" };
  return dti.c_type || "__m256";
}

export function getHwMaskType(isa, dt, defines, currentLmulVal = 1) {
  if (isa === "rvv") {
    const dti = (DT_INFO && DT_INFO[dt]) || { bits: 32 };
    const numLmul = currentLmulVal === -2 ? 0.5 : Number(currentLmulVal) || 1;
    const eew = Math.round(dti.bits / numLmul);
    return `vbool${eew}_t`;
  }
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[isa] : null;
  if (isaMeta && isaMeta.datatypes && isaMeta.datatypes[dt] && isaMeta.datatypes[dt].msk) {
    if (isa === "neon" && dt === "float64") {
      return (defines && defines.__aarch64__ !== false) ? isaMeta.datatypes[dt].msk : "uint64_t";
    }
    return isaMeta.datatypes[dt].msk;
  }
  const dti = (DT_INFO && DT_INFO[dt]) || { uint_type: "uint32_t" };
  return dti.uint_type || "__m256";
}

export function isFeatureSupported(info, targetDt, targetIsa, targetDefines) {
  if (!info || !info.required_features || !targetDefines) return true;
  let req = info.required_features[targetDt];
  if (!req && targetDt.includes(",")) {
    const parts = targetDt.split(",").map((s) => s.trim());
    req = info.required_features[parts[0]] || info.required_features[parts[1]];
  }
  if (!req) return true;

  if (targetIsa === "avx512") {
    if (req === "BW" && targetDefines.__AVX512BW__ === false) return false;
    if (req === "DQ" && targetDefines.__AVX512DQ__ === false) return false;
    if (req === "VL" && targetDefines.__AVX512VL__ === false) return false;
    if (req === "CD" && targetDefines.__AVX512CD__ === false) return false;
  } else if (targetIsa === "avx") {
    if (req === "AVX2" && targetDefines.__AVX2__ === false) return false;
    if (req === "FMA" && targetDefines.__FMA__ === false) return false;
  } else if (targetIsa === "neon") {
    if (req === "AArch64" && targetDefines.__aarch64__ === false) return false;
    if (req === "FMA" && (targetDefines.__ARM_FEATURE_FMA === false || targetDefines.__ARM_FEATURE_FMA === 0 || targetDefines.__FMA__ === false)) return false;
    if (req === "Rounding" && targetDefines.__ARM_FEATURE_DIRECTED_ROUNDING === false) return false;
  } else if (targetIsa === "sve") {
    if (req === "SVE2" && targetDefines.__ARM_FEATURE_SVE2 === false) return false;
  } else if (targetIsa === "sse") {
    const SSE_RANKS = { "SSE": 1, "SSE2": 2, "SSE3": 3, "SSSE3": 4, "SSE4.1": 5, "SSE4.2": 6 };
    const reqRank = SSE_RANKS[req] || 2;
    let curRank = 6;
    if (targetDefines.sseTarget) {
      curRank = SSE_RANKS[targetDefines.sseTarget] || 6;
    } else if (targetDefines.__SSE4_2__ === false) {
      if (targetDefines.__SSE4_1__ !== false) curRank = 5;
      else if (targetDefines.__SSSE3__ !== false) curRank = 4;
      else if (targetDefines.__SSE3__ !== false) curRank = 3;
      else curRank = 2;
    }
    if (curRank < reqRank) return false;
  }
  return true;
}

export function getCompilerConfigForFlat(isa, defines = {}, scalarSize = 256) {
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[isa] : null;
  const compilerMeta = (isaMeta && isaMeta.compiler) ? isaMeta.compiler : { id: "g142", arch: "x86", base_flags: "-O3", label: "x86-64 GCC" };

  let compiler = compilerMeta.id || "g142";
  let options = compilerMeta.base_flags || "-O3";
  let compilerLabel = compilerMeta.label || "GCC";
  let targetDesc = "GCC / Clang (x86-64)";

  if (isa === "scalar") {
    let archFlags = "-march=native";
    if (scalarSize === 128) archFlags = "-msse4.2";
    else if (scalarSize === 256) archFlags = "-mavx2 -mfma";
    else if (scalarSize >= 512) archFlags = "-mavx512f -mavx512bw -mavx512dq";
    compiler = "g142";
    options = `-O3 -DMIPP_SCALAR -DMIPP_SCALAR_SIZE=${scalarSize} ${archFlags}`;
    compilerLabel = `x86-64 GCC (${options})`;
    targetDesc = "GCC / Clang (x86-64)";
  } else if (isa === "neon") {
    if (defines.__aarch64__ !== false) {
      compiler = "carm64g1420";
      const archExts = [];
      if (defines.__ARM_FEATURE_FMA !== false && defines.__ARM_FEATURE_FMA !== 0) archExts.push("+fma");
      options = `-O3 -march=armv8-a+simd${archExts.join("")}`;
      compilerLabel = `AArch64 GCC (${options})`;
      targetDesc = "GCC / Clang (AArch64 NEON)";
    } else {
      compiler = compilerMeta.id_32 || "arm-gcc-1320";
      const fpu = (defines && (defines.__ARM_FEATURE_FMA !== false && defines.__ARM_FEATURE_FMA !== 0)) ? "neon-vfpv4" : "neon";
      options = `-O3 -march=armv7-a -mfpu=${fpu} -mfloat-abi=hard`;
      compilerLabel = `ARM32 GCC (${options})`;
      targetDesc = "GCC / Clang (ARM32 NEON)";
    }
  } else if (isa === "sve") {
    compiler = "carm64g1420";
    const sveArch = defines.__ARM_FEATURE_SVE2 ? "armv8.2-a+sve2" : "armv8.2-a+sve";
    options = `-O3 -march=${sveArch} -msve-vector-bits=${scalarSize || 256}`;
    compilerLabel = `AArch64 SVE GCC (${options})`;
    targetDesc = "GCC / Clang (AArch64 SVE)";
  } else if (isa === "rvv") {
    compiler = compilerMeta.id || "rv64-clang";
    const zvlWidth = scalarSize || 256;
    options = `-O3 -march=rv64gcv_zvl${zvlWidth}b -mrvv-vector-bits=zvl`;
    compilerLabel = `RISC-V 64 Clang (${options})`;
    targetDesc = "Clang (RISC-V 64 RVV)";
  } else {
    compiler = "g142";
    targetDesc = "GCC / Clang (x86-64)";
    const flags = ["-O3"];
    if (isa === "avx512") {
      if (isaMeta && isaMeta.features) {
        for (const f of isaMeta.features) {
          if (defines[f.name] !== false && f.flag) flags.push(f.flag);
        }
      }
    } else if (isa === "avx") {
      flags.push("-mavx");
      if (defines.__AVX2__ !== false) flags.push("-mavx2");
      if (defines.__FMA__ !== false) flags.push("-mfma");
    } else if (isa === "sse") {
      if (defines.__SSE4_2__ !== false) flags.push("-msse4.2");
      else if (defines.__SSE4_1__ !== false) flags.push("-msse4.1");
      else if (defines.__SSSE3__ !== false) flags.push("-mssse3");
      else if (defines.__SSE3__ !== false) flags.push("-msse3");
      else if (defines.__SSE2__ !== false) flags.push("-msse2");
      else flags.push("-msse");
    }
    options = flags.join(" ");
    compilerLabel = `x86-64 GCC (${options})`;
  }

  return { compiler, options, compilerLabel, targetDesc };
}

export function buildGodboltUrlForFlat(sourceCode, isa, defines = {}, scalarSize = 256) {
  const { compiler, options, compilerLabel } = getCompilerConfigForFlat(isa, defines, scalarSize);

  // In Godbolt Rison strings delimited by '...', ! is the escape prefix character:
  // '!' -> '!!'
  // "'" -> "!'"
  const encodeRisonString = (str) => {
    const escaped = String(str).replace(/!/g, "!!").replace(/'/g, "!'");
    return encodeURIComponent(escaped);
  };

  const lang = "c";
  return (
    "https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUseDefault:true,lang:'" +
    lang +
    "',source:'" +
    encodeRisonString(sourceCode) +
    "'),l:'5',n:'0',o:'MIPP+Specialized+C',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:" +
    compiler +
    ",filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1'),flagsViewOpen:'1',fontScale:14,fontUseDefault:true,lang:'" +
    lang +
    "',options:'" +
    encodeRisonString(options) +
    "'),l:'5',n:'0',o:'" +
    encodeRisonString(compilerLabel) +
    "',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"
  );
}

export function parseCParams(paramList, isa, dtMain, numLmul) {
  const parts = paramList.split(",").map((s) => s.trim()).filter(Boolean);
  const lmulParams = [];
  const callArgs1 = [];
  const callArgs2 = [];

  for (const part of parts) {
    const words = part.split(/\s+/);
    const name = words[words.length - 1].replace(/[^a-zA-Z0-9_]/g, "");
    if (part.includes("rvm_")) {
      const typeMatch = part.match(/(?:const\s+)?(rvm_[a-z0-9_]+?)_t\b/);
      let baseType = typeMatch ? typeMatch[1] : `rvm_${isa}_${dtMain}`;
      baseType = baseType.replace(/_(?:m[0-9]+|d[0-9]+)$/, "");
      lmulParams.push(`const ${baseType}_m${numLmul}_t ${name}`);
      callArgs1.push(`${name}.m1`);
      callArgs2.push(`${name}.m2`);
    } else if (part.includes("rvd_")) {
      const typeMatch = part.match(/(?:const\s+)?(rvd_[a-z0-9_]+?)_t\b/);
      let baseType = typeMatch ? typeMatch[1] : `rvd_${isa}_${dtMain}`;
      baseType = baseType.replace(/_(?:m[0-9]+|d[0-9]+)$/, "");
      lmulParams.push(`const ${baseType}_m${numLmul}_t ${name}`);
      callArgs1.push(`${name}.r1`);
      callArgs2.push(`${name}.r2`);
    } else {
      // pointer or scalar argument
      lmulParams.push(part);
      callArgs1.push(name);
      callArgs2.push(name);
    }
  }

  return {
    lmulParamList: lmulParams.join(", "),
    call1: callArgs1.join(", "),
    call2: callArgs2.join(", ")
  };
}

export function generateTestHarness(targetFuncName, targetRetType, targetParamList, entry, cfg) {
  const { name, category } = entry;
  const parts = targetParamList.split(",").map((s) => s.trim()).filter(Boolean);
  const parsedArgs = parts.map((arg) => {
    const words = arg.split(/\s+/);
    const argName = words[words.length - 1].replace(/[^a-zA-Z0-9_]/g, "");
    const isPtr = arg.includes("*");
    const isMask = arg.includes("rvm_") || arg.includes("vbool") || arg.includes("svbool");
    const isReg = arg.includes("rvd_") || arg.includes("vfloat") || arg.includes("vint") || arg.includes("vuint") || arg.includes("sv");
    const isScalar = !isMask && !isReg && !isPtr;
    const isConst = arg.startsWith("const ");
    let type = arg.replace(/^const\s+/, "").replace(/\s*\*?\s*[a-zA-Z0-9_]+$/, "").trim();
    if (isPtr && !type.includes("*")) type += "*";
    return { raw: arg, name: argName, isPtr, isMask, isReg, isScalar, isConst, type };
  });

  const lines = [];
  lines.push("// -----------------------------------------------------------------------------");
  lines.push("// Test Harness for Inlining Verification");
  lines.push("// -----------------------------------------------------------------------------");

  const isVectorReturn = targetRetType.startsWith("rvd_") || targetRetType.startsWith("rvm_") ||
    targetRetType.startsWith("vfloat") || targetRetType.startsWith("vint") ||
    targetRetType.startsWith("vuint") || targetRetType.startsWith("vbool") ||
    targetRetType.startsWith("sv");
  const isVoidReturn = targetRetType === "void";
  const hasPtrArg = parsedArgs.some((a) => a.isPtr);
  const isMemory = ["load", "store"].includes(category) || name.startsWith("load") || name.startsWith("store") || name === "gather" || name === "scatter";
  const isComparison = category === "comparison" || name.startsWith("cmp");
  const isReduction = category === "reduction" || name.startsWith("hadd") || name.startsWith("hmax") || name.startsWith("hmin") || name.startsWith("hmul") || name.startsWith("testz");
  const isConvert = category === "converts" || name.includes("cvt");
  const isSet = name.startsWith("set");

  const targetTypeArgCount = parsedArgs.filter((a) => a.type === targetRetType).length;
  const canLoop = isVectorReturn && !hasPtrArg && !isMemory && !isComparison && !isReduction && !isConvert && !isSet &&
    targetTypeArgCount >= 2;

  if (canLoop) {
    const extraParams = [];
    const callArgs = [];
    let accUsed = false;

    for (const a of parsedArgs) {
      if (a.isMask) {
        extraParams.push(`const ${a.type} *${a.name}`);
        callArgs.push(`mask_${a.name}`);
      } else if (a.name === "rsrc") {
        extraParams.push(`const ${a.type} *${a.name}`);
        callArgs.push(`src_${a.name}`);
      } else if (a.type === targetRetType) {
        if (!accUsed) {
          callArgs.push("acc");
          accUsed = true;
        } else {
          callArgs.push("step");
        }
      } else if (a.isScalar) {
        callArgs.push("1");
      } else {
        extraParams.push(`const ${a.type} *${a.name}`);
        callArgs.push(`*${a.name}`);
      }
    }

    const testParamStr = [`${targetRetType} *out`, ...extraParams, "int n"].join(", ");
    lines.push(`void test(${testParamStr}) {`);
    lines.push(`\t${targetRetType} acc = *out;`);
    lines.push(`\t${targetRetType} step = acc;`);
    for (const a of parsedArgs) {
      if (a.isMask) lines.push(`\t${a.type} mask_${a.name} = *${a.name};`);
      if (a.name === "rsrc") lines.push(`\t${a.type} src_${a.name} = *${a.name};`);
    }
    lines.push(`\tfor (int i = 0; i < n; i++) {`);
    lines.push(`\t\tacc = ${targetFuncName}(${callArgs.join(", ")});`);
    lines.push(`\t}`);
    lines.push(`\t*out = acc;`);
    lines.push(`}`);
  } else if (isReduction) {
    const inArg = parsedArgs[0] || { type: "void", name: "in0" };
    lines.push(`${targetRetType} test(const ${inArg.type} *${inArg.name}) {`);
    lines.push(`\treturn ${targetFuncName}(*${inArg.name});`);
    lines.push(`}`);
  } else if (isVoidReturn) {
    const testParams = [];
    const callArgs = [];
    parsedArgs.forEach((a) => {
      if (a.isPtr || a.isScalar) {
        testParams.push(a.raw);
        callArgs.push(a.name);
      } else {
        testParams.push(`const ${a.type} *${a.name}`);
        callArgs.push(`*${a.name}`);
      }
    });
    lines.push(`void test(${testParams.join(", ")}) {`);
    lines.push(`\t${targetFuncName}(${callArgs.join(", ")});`);
    lines.push(`}`);
  } else {
    const testParams = [`${targetRetType} *out`];
    const callArgs = [];
    parsedArgs.forEach((a) => {
      if (a.isPtr || a.isScalar) {
        testParams.push(a.raw);
        callArgs.push(a.name);
      } else {
        testParams.push(`const ${a.type} *${a.name}`);
        callArgs.push(`*${a.name}`);
      }
    });
    lines.push(`void test(${testParams.join(", ")}) {`);
    lines.push(`\t*out = ${targetFuncName}(${callArgs.join(", ")});`);
    lines.push(`}`);
  }

  return lines.join("\n");
}

export function getScalarNMacroDef(macroName) {
  const m = macroName.match(/^MIPP_SCALAR_N_([A-Z0-9]+?)(?:_(M1|M2|M4|M8|D2))?$/);
  if (!m) return null;
  const dtStr = m[1].toLowerCase();
  const lmulSuffix = m[2];
  let bits = 32;
  if (dtStr.includes("64")) bits = 64;
  else if (dtStr.includes("32")) bits = 32;
  else if (dtStr.includes("16")) bits = 16;
  else if (dtStr.includes("8")) bits = 8;

  let expr = `(MIPP_SCALAR_SIZE / ${bits})`;
  if (lmulSuffix === "M2") expr = `(${expr} * 2)`;
  else if (lmulSuffix === "M4") expr = `(${expr} * 4)`;
  else if (lmulSuffix === "M8") expr = `(${expr} * 8)`;
  else if (lmulSuffix === "D2") expr = `(${expr} / 2)`;
  return `#define ${macroName} ${expr}`;
}


export function generateFlatSpecializedCode(entry, cfg) {
  const { isa, defines, dt, mask, lmul, scalarSize } = cfg;
  const dtMain = dt.includes(",") ? dt.split(",")[0].trim() : dt;
  const dtSuffix = dt.replace(/,/g, "_");
  const dti = DT_INFO[dtMain] || DT_INFO[dt] || DT_INFO.float32 || { c_type: "float", uint_type: "uint32_t", bits: 32 };
  const isScalar = isa === "scalar";
  let needsMask = mask && mask !== "unmasked";
  const numLmul = Number(lmul) || 1;
  const isaInfo = entry.isa_support ? entry.isa_support[isa] : null;
  const hwLmuls = (isaInfo && isaInfo.hw_lmul) || (isa === "rvv" ? [1, 2, 4, 8, -2] : [1]);
  const currentLmulVal = (lmul === "0.5" || lmul === 0.5 || lmul === -2 || lmul === "-2") ? -2 : numLmul;
  const isHwLmul = !isScalar && hwLmuls.includes(currentLmulVal);
  const isSoftwareLmulWrapper = !isScalar && !isHwLmul && numLmul > 1;
  const lmulSuffix = currentLmulVal === -2 ? "_d2" : `_m${currentLmulVal}`;
  const baseLmulSuffix = isSoftwareLmulWrapper ? "_m1" : lmulSuffix;
  const lmulUpper = lmulSuffix.replace(/^_/, "").toUpperCase();
  const lines = [];

  const findSnippet = (dict) => {
    if (!dict) return null;
    return dict[dt] || dict[dtMain] || dict[`${dtMain},${dtMain}`] || dict[`${dtMain},uint64`] || dict[`${dtMain},uint32`] || Object.entries(dict).find(([k]) => k.startsWith(dtMain))?.[1] || null;
  };

  let nativeSnip = findSnippet(isaInfo && isaInfo.code_snippets);
  if (isHwLmul) {
    const lmulKey = String(currentLmulVal);
    const snippetDict = (isaInfo && isaInfo.code_snippets_by_lmul && isaInfo.code_snippets_by_lmul[lmulKey])
      || (isaInfo && isaInfo.code_snippets)
      || {};
    nativeSnip = findSnippet(snippetDict) || nativeSnip;
  }
  const maskedDict = isaInfo && isaInfo.code_snippets_by_mask && isaInfo.code_snippets_by_mask[mask];
  let maskedSnip = findSnippet(maskedDict);
  const emuAlgo = findSnippet(isaInfo && isaInfo.emulation_algorithms);
  const refAlgos = entry.reference_algos ? entry.reference_algos["1"] : null;
  const scalarRef = refAlgos && refAlgos[dt] ? (refAlgos[dt][mask] || refAlgos[dt]["unmasked"]) : null;

  let currentImplLvl = 3;
  if (!isScalar && isaInfo) {
    const baseLvl = (isaInfo.by_datatype && (isaInfo.by_datatype[dt] !== undefined ? isaInfo.by_datatype[dt] : isaInfo.by_datatype[dtMain])) !== undefined
      ? (isaInfo.by_datatype[dt] !== undefined ? isaInfo.by_datatype[dt] : isaInfo.by_datatype[dtMain])
      : (isaInfo.overall_level !== undefined ? isaInfo.overall_level : 3);
    if (!needsMask) {
      currentImplLvl = baseLvl;
    } else {
      const maskedDict = isaInfo.masked_by_datatype ? isaInfo.masked_by_datatype[mask] : null;
      currentImplLvl = (maskedDict && (maskedDict[dt] !== undefined ? maskedDict[dt] : maskedDict[dtMain])) !== undefined
        ? (maskedDict[dt] !== undefined ? maskedDict[dt] : maskedDict[dtMain])
        : 2;
    }

    const featureSatisfied = isFeatureSupported(isaInfo, dt, isa, defines);
    if (!featureSatisfied) {
      nativeSnip = null;
      maskedSnip = null;
      const fallbackLvl = (isaInfo.fallback_levels && (isaInfo.fallback_levels[dt] !== undefined ? isaInfo.fallback_levels[dt] : isaInfo.fallback_levels[dtMain])) !== undefined
        ? (isaInfo.fallback_levels[dt] !== undefined ? isaInfo.fallback_levels[dt] : isaInfo.fallback_levels[dtMain])
        : (emuAlgo ? 2 : 3);
      currentImplLvl = fallbackLvl;
    }
  }

  const isDedicatedMask = needsMask && (currentImplLvl === 0 || currentImplLvl === 1) && Boolean(maskedSnip);

  // Scan for any helper macros from entry.scalar_macros used in code
  const neededMacros = [];
  const codeToScan = (scalarRef || "") + " " + (emuAlgo || "") + " " + (nativeSnip || "") + " " + (maskedSnip || "");
  if (entry.scalar_macros && typeof entry.scalar_macros === "object") {
    for (const [mName, mObj] of Object.entries(entry.scalar_macros)) {
      if (new RegExp(`\\b${mName}\\b`).test(codeToScan)) {
        neededMacros.push(mObj.definition);
      }
    }
  }

  const hasMemcpy = isScalar || neededMacros.some((m) => m.includes("memcpy"));
  const hasMath = isScalar || neededMacros.some((m) => /exp|log|pow|sin|cos|tan|asin|acos|atan/.test(m));

  // 1. Headers & Overview
  const compilerConfig = getCompilerConfigForFlat(isa, defines, scalarSize);
  const isLengthAgnostic = isScalar || isa === "rvv" || isa === "sve";
  lines.push("// =============================================================================");
  lines.push(`// MIPP Flat Specialized Code: ${entry.name} (${isa.toUpperCase()})`);
  lines.push(`// Datatype: ${dt} | Variant: ${mask} | LMUL: ${lmul}${isLengthAgnostic ? ` | SIMD Width: ${scalarSize || 256} bits` : ""}`);
  lines.push(`// Target Compiler : ${compilerConfig.targetDesc}`);
  lines.push(`// Compiler Flags  : ${compilerConfig.options}`);
  lines.push("// Zero external MIPP headers required - compiles standalone out-of-the-box");
  lines.push("// =============================================================================");
  lines.push("");

  if (isScalar) {
    lines.push("#include <stdint.h>");
    lines.push("#include <string.h>");
    lines.push("#include <math.h>");
  } else {
    const isaMeta = apiMetadata.isas ? apiMetadata.isas[isa] : null;
    const headers = (isaMeta && isaMeta.headers && isaMeta.headers.length > 0)
      ? isaMeta.headers
      : (["sse", "avx", "avx512"].includes(isa) ? ["<immintrin.h>"] : [`<${isa}.h>`]);
    for (const h of headers) {
      if (!h.includes("c/common.h")) {
        lines.push(`#include ${h}`);
      }
    }
    lines.push("#include <stdint.h>");
    lines.push("#include <string.h>");
    if (hasMath || entry.category === "math") lines.push("#include <math.h>");
  }
  lines.push("");

  // Common scalar typedefs for float32_t / float64_t
  lines.push("typedef float float32_t;");
  lines.push("typedef double float64_t;");
  lines.push("");

  // 2. Defines Placeholder (populated at the end after all symbols and macros are resolved)
  lines.push("/* __DEFINES_SECTION__ */");

  // 3. Typedefs
  lines.push("// -----------------------------------------------------------------------------");
  lines.push("// Minimal MIPP Type Definitions");
  lines.push("// -----------------------------------------------------------------------------");
  const regTypeName = `rvd_${isa}_${dtMain}${baseLmulSuffix}_t`;
  const maskTypeName = `rvm_${isa}_${dtMain}${baseLmulSuffix}_t`;
  const hwReg = getHwRegType(isa, dtMain, defines, isHwLmul ? currentLmulVal : 1);
  const hwMask = getHwMaskType(isa, dtMain, defines, isHwLmul ? currentLmulVal : 1);

  // Extract prototype template for parameter signatures and required auxiliary types
  let protoTemplate = "";
  const sampleKey = isHwLmul && currentLmulVal !== 1 ? String(currentLmulVal) : "1";
  if (entry.prototypes && entry.prototypes.c99_samples && entry.prototypes.c99_samples[sampleKey]) {
    const list = entry.prototypes.c99_samples[sampleKey][mask] || entry.prototypes.c99_samples[sampleKey]["unmasked"];
    if (Array.isArray(list) && list.length > 0) {
      protoTemplate = list.find((s) => s.includes(`_${dtMain}_`) || s.includes(`_${dtMain}(`)) ||
        list.find((s) => s.includes(`_${dt}_`) || s.includes(`_${dt}(`)) ||
        list[0];
    } else if (typeof list === "string") {
      protoTemplate = list;
    }
  }
  if (!protoTemplate && entry.prototypes && entry.prototypes.c99_samples && entry.prototypes.c99_samples["1"]) {
    const list = entry.prototypes.c99_samples["1"][mask] || entry.prototypes.c99_samples["1"]["unmasked"];
    if (Array.isArray(list) && list.length > 0) {
      protoTemplate = list.find((s) => s.includes(`_${dtMain}_`) || s.includes(`_${dtMain}(`)) ||
        list.find((s) => s.includes(`_${dt}_`) || s.includes(`_${dt}(`)) ||
        list[0];
    } else if (typeof list === "string") {
      protoTemplate = list;
    }
  }
  if (!protoTemplate && entry.prototypes && entry.prototypes.c99) {
    protoTemplate = entry.prototypes.c99;
  }

  // -----------------------------------------------------------------------------
  // Helper Generator and Dependency Collection
  // -----------------------------------------------------------------------------
  const cleanSnippetForC = (snip) => {
    if (!snip) return "";
    let s = snip.replace(/;\s*$/, "");
    if (isa === "rvv") {
      const rvvLsuffix = currentLmulVal === -2 ? "mf2" : `m${currentLmulVal}`;
      s = s.replace(/%N<tp>%/g, `__riscv_vsetvlmax_e${dti.bits}${rvvLsuffix}()`);
      if (currentLmulVal !== 1) {
        s = s.replace(/(m1|mf2|m2|m4|m8)(_mu|_tum|_tumu|_tu)?\(/g, `${rvvLsuffix}$2(`);
      }
    }
    s = s.replace(/%set0<[^>]*>%\(\)/g, `mipp_${isa}_set0_${dtMain}_m1()`);
    s = s.replace(/%r<[^>]*>%/g, regTypeName);
    s = s.replace(/%m<[^>]*>%/g, maskTypeName);
    s = s.replace(/%([a-zA-Z0-9_]+)<[^>]*>%/g, `mipp_${isa}_$1_${dtMain}_m1`);
    s = s.replace(/%/g, "");
    s = s.replace(/,([^\s])/g, ", $1");
    s = s.replace(/_mm512_gmax_/g, "_mm512_max_");
    s = s.replace(/_mm512_gmin_/g, "_mm512_min_");
    if (s.includes("return ") && !s.trim().endsWith(";")) {
      s = s.trim() + ";";
    }
    return s;
  };

  function splitStatements(str) {
    const result = [];
    const rawLines = str.split("\n");
    for (const line of rawLines) {
      if (!line.trim()) {
        result.push("");
        continue;
      }
      let cur = "";
      let parenDepth = 0;
      for (let i = 0; i < line.length; i++) {
        const ch = line[i];
        if (ch === "(") parenDepth++;
        else if (ch === ")" && parenDepth > 0) parenDepth--;
        cur += ch;
        if (ch === ";" && parenDepth === 0) {
          if (cur.trim()) result.push(cur.trim());
          cur = "";
        }
      }
      if (cur.trim()) result.push(cur.trim());
    }
    return result;
  }

  function fmtHelper(retType, signature, bodyLines) {
    const expandedLines = [];
    for (const line of bodyLines) {
      if (typeof line === "string" && line.includes("; ") && !line.includes("\n")) {
        expandedLines.push(...splitStatements(line));
      } else {
        expandedLines.push(line);
      }
    }
    return [
      "static inline",
      `${retType} ${signature} {`,
      ...expandedLines.map((l) => `\t${l}`),
      "}"
    ].join("\n");
  }

  const neededScalarDts = new Set();
  const neededScalarMasks = new Set();
  const emittedScalarFuncs = new Set();

  function adaptScalarRef(refCode, newFnName) {
    let clean = refCode
      .replace(/^static\s+inline\s+/gm, "")
      .replace(/^static\s+/gm, "")
      .trim();

    if (newFnName) {
      clean = clean.replace(
        /\bmipp_scalar_[a-zA-Z0-9_]+(?=\s*\()/g,
        newFnName
      );
    } else {
      clean = clean.replace(
        /\bmipp_scalar_([a-zA-Z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?(?=\s*\()/g,
        "mipp_scalar_$1_m1"
      );
    }

    clean = clean.replace(
      /\brvd_scalar_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g,
      "rvd_scalar_$1_m1_t"
    );
    clean = clean.replace(
      /\brvm_scalar_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g,
      "rvm_scalar_$1_m1_t"
    );

    clean = clean.replace(
      /\bMIPP_SCALAR_N_([A-Z0-9]+)\b(?![_A-Z0-9])/g,
      (match, p1) => {
        if (p1.endsWith("_M1") || p1.endsWith("_M2") || p1.endsWith("_M4") || p1.endsWith("_M8") || p1.endsWith("_D2")) {
          return match;
        }
        return `MIPP_SCALAR_N_${p1}_M1`;
      }
    );

    return "static inline\n" + clean;
  }

  function extractDeclFromFunc(funcCode) {
    const idx = funcCode.indexOf("{");
    if (idx !== -1) {
      return funcCode.slice(0, idx).trim() + ";";
    }
    return "";
  }

  function buildScalarBridge(targetFnName, targetRetType, targetParamList, scalarFnName) {
    const bridgeLines = [];
    bridgeLines.push(`// Level 3 (Auto Scalar Fallback)`);
    const scalarCallArgs = [];

    const args = targetParamList ? targetParamList.split(",") : [];
    for (const a of args) {
      const trimmed = a.trim();
      if (!trimmed) continue;
      const parts = trimmed.split(/\s+/);
      const argName = parts.pop();
      const argType = parts.join(" ");

      const rvdMatch = argType.match(new RegExp(`rvd_${isa}_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t`));
      const rvmMatch = argType.match(new RegExp(`rvm_${isa}_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t`));

      if (rvdMatch) {
        const sub = rvdMatch[1];
        neededScalarDts.add(sub);
        bridgeLines.push(`rvd_scalar_${sub}_m1_t s_${argName} = {0};`);
        bridgeLines.push(`memcpy(&s_${argName}, &${argName}, sizeof(${argName}));`);
        scalarCallArgs.push(`s_${argName}`);
      } else if (rvmMatch) {
        const sub = rvmMatch[1];
        neededScalarDts.add(sub);
        neededScalarMasks.add(sub);
        bridgeLines.push(`rvm_scalar_${sub}_m1_t s_${argName} = {0};`);
        bridgeLines.push(`memcpy(&s_${argName}, &${argName}, sizeof(${argName}));`);
        scalarCallArgs.push(`s_${argName}`);
      } else {
        scalarCallArgs.push(argName);
      }
    }

    const retRvdMatch = targetRetType.match(new RegExp(`rvd_${isa}_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t`));
    const retRvmMatch = targetRetType.match(new RegExp(`rvm_${isa}_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t`));

    if (retRvdMatch) {
      const sub = retRvdMatch[1];
      neededScalarDts.add(sub);
      bridgeLines.push(`rvd_scalar_${sub}_m1_t sres = ${scalarFnName}(${scalarCallArgs.join(", ")});`);
      bridgeLines.push(`${targetRetType} res;`);
      bridgeLines.push(`memcpy(&res, &sres, sizeof(res));`);
      bridgeLines.push(`return res;`);
    } else if (retRvmMatch) {
      const sub = retRvmMatch[1];
      neededScalarDts.add(sub);
      neededScalarMasks.add(sub);
      bridgeLines.push(`rvm_scalar_${sub}_m1_t sres = ${scalarFnName}(${scalarCallArgs.join(", ")});`);
      bridgeLines.push(`${targetRetType} res;`);
      bridgeLines.push(`memcpy(&res, &sres, sizeof(res));`);
      bridgeLines.push(`return res;`);
    } else if (targetRetType === "void") {
      bridgeLines.push(`${scalarFnName}(${scalarCallArgs.join(", ")});`);
    } else {
      bridgeLines.push(`return ${scalarFnName}(${scalarCallArgs.join(", ")});`);
    }

    return fmtHelper(targetRetType, `${targetFnName}(${targetParamList})`, bridgeLines);
  }

  // Fully Generic Helper Function Generator (Extracted dynamically from apiData)
  function generateHelperDef(helperName) {
    const fnName = `mipp_${isa}_${helperName}_${dtMain}_m1`;
    const targetEntry = apiData.find((x) => x.name === helperName);
    if (!targetEntry) {
      const params = `const ${regTypeName} r0`;
      return {
        decl: `static inline\n${regTypeName} ${fnName}(${params});`,
        def: fmtHelper(regTypeName, `${fnName}(${params})`, [
          `${regTypeName} res = r0;`,
          `return res;`
        ])
      };
    }

    const tInfo = targetEntry.isa_support ? targetEntry.isa_support[isa] : null;
    const hFeatureOk = isFeatureSupported(tInfo, dtMain, isa, defines);
    const snip = hFeatureOk && tInfo && tInfo.code_snippets ? (tInfo.code_snippets[dtMain] || tInfo.code_snippets[dt]) : null;
    const emu = tInfo && tInfo.emulation_algorithms ? (tInfo.emulation_algorithms[dtMain] || tInfo.emulation_algorithms[dt]) : null;
    const ref = targetEntry.reference_algos && targetEntry.reference_algos["1"] && (targetEntry.reference_algos["1"][dtMain] || targetEntry.reference_algos["1"][dt])
      ? ((targetEntry.reference_algos["1"][dtMain] || targetEntry.reference_algos["1"][dt])["unmasked"] || (targetEntry.reference_algos["1"][dtMain] || targetEntry.reference_algos["1"][dt])["mask"])
      : null;

    let protoSamples = targetEntry.prototypes && targetEntry.prototypes.c99_samples && targetEntry.prototypes.c99_samples["1"]
      ? (targetEntry.prototypes.c99_samples["1"]["unmasked"] || Object.values(targetEntry.prototypes.c99_samples["1"])[0] || [])
      : [];
    if (!Array.isArray(protoSamples)) protoSamples = [protoSamples];
    let sampleProto = protoSamples.find((p) => p.includes(`_${dtMain}_`) || p.includes(`_${dtMain}(`)) ||
      protoSamples.find((p) => p.includes(dtMain)) ||
      protoSamples.find((p) => p.includes(dt)) ||
      protoSamples[0] || "";

    let params = "";
    const pMatch = sampleProto.match(/\(([^)]*)\)/);
    if (pMatch) {
      params = pMatch[1]
        .replace(/\brvd_[a-z0-9_]+_m1_t\b/g, regTypeName)
        .replace(/\brvm_[a-z0-9_]+_m1_t\b/g, maskTypeName)
        .replace(/\brvd_[a-z0-9_]+_t\b/g, regTypeName)
        .replace(/\brvm_[a-z0-9_]+_t\b/g, maskTypeName);
    } else {
      params = `const ${regTypeName} r0`;
    }

    let retType = regTypeName;
    if (sampleProto.startsWith("rvm_") || helperName.startsWith("cmp") || helperName.endsWith("_k")) {
      retType = maskTypeName;
    } else if (targetEntry.category === "reduction" || helperName === "getfirst" || helperName === "get" || sampleProto.startsWith("float") || sampleProto.startsWith("double") || sampleProto.startsWith("int") || sampleProto.startsWith("uint")) {
      const helperDti = (DT_INFO && DT_INFO[dtMain]) || { c_type: "float" };
      retType = helperDti.c_type || "float64_t";
    }

    if (snip) {
      const cleanSnip = cleanSnippetForC(snip);
      if (cleanSnip.includes("return ")) {
        return {
          decl: `static inline\n${retType} ${fnName}(${params});`,
          def: fmtHelper(retType, `${fnName}(${params})`, [cleanSnip])
        };
      }
      if (retType === "float" || retType === "double" || retType === "float32_t" || retType === "float64_t" || retType === "int32_t" || retType === "int64_t" || retType === "uint32_t" || retType === "uint64_t") {
        return {
          decl: `static inline\n${retType} ${fnName}(${params});`,
          def: fmtHelper(retType, `${fnName}(${params})`, [`return ${cleanSnip};`])
        };
      }
      const field = retType === maskTypeName ? "m" : "r";
      return {
        decl: `static inline\n${retType} ${fnName}(${params});`,
        def: fmtHelper(retType, `${fnName}(${params})`, [
          `${retType} res;`,
          `res.${field} = ${cleanSnip};`,
          `return res;`
        ])
      };
    }

    if (emu) {
      let converted = emu
        .replace(/mipp::reg/g, regTypeName)
        .replace(/mipp::msk/g, maskTypeName)
        .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dtMain}_m1()`)
        .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dtMain}_m1(`);

      let bodyLines = [];
      if (!converted.includes("return ")) {
        const cleanSnip = cleanSnippetForC(converted);
        if (retType === "float" || retType === "double" || retType === "float32_t" || retType === "float64_t" || retType === "int32_t" || retType === "int64_t" || retType === "uint32_t" || retType === "uint64_t") {
          bodyLines.push(`return ${cleanSnip};`);
        } else {
          const field = retType === maskTypeName ? "m" : "r";
          bodyLines.push(`${retType} res;`);
          bodyLines.push(`res.${field} = ${cleanSnip};`);
          bodyLines.push(`return res;`);
        }
      } else {
        bodyLines = converted.split("\n");
      }

      return {
        decl: `static inline\n${retType} ${fnName}(${params});`,
        def: fmtHelper(retType, `${fnName}(${params})`, bodyLines)
      };
    }

    if (ref) {
      if (isa !== "scalar") {
        const scalarFnName = `mipp_scalar_${helperName}_${dtMain}_m1`;
        const adaptedScalar = adaptScalarRef(ref, scalarFnName);
        const scalarDecl = extractDeclFromFunc(adaptedScalar);

        const bridgeDef = buildScalarBridge(fnName, retType, params, scalarFnName);
        const isaDecl = `static inline\n${retType} ${fnName}(${params});`;

        const decls = [];
        const defs = [];

        if (!emittedScalarFuncs.has(scalarFnName)) {
          emittedScalarFuncs.add(scalarFnName);
          if (scalarDecl) decls.push(scalarDecl);
          defs.push(adaptedScalar);
        }
        decls.push(isaDecl);
        defs.push(bridgeDef);

        return {
          decl: decls.join("\n"),
          def: defs.join("\n\n")
        };
      } else {
        return {
          decl: `static inline\n${retType} ${fnName}(${params});`,
          def: adaptScalarRef(ref, fnName)
        };
      }
    }

    return {
      decl: `static inline\n${retType} ${fnName}(${params});`,
      def: fmtHelper(retType, `${fnName}(${params})`, [
        `${retType} res;`,
        `return res;`
      ])
    };
  }

  // 1. Collect all helpers (transitive/recursive worklist)
  const neededHelpers = new Set();
  const helperQueue = [];

  function addHelper(name) {
    if (!name || neededHelpers.has(name) || name === entry.name) return;
    neededHelpers.add(name);
    helperQueue.push(name);
  }

  if (!nativeSnip && emuAlgo) {
    const matches = Array.from(emuAlgo.matchAll(/mipp::([a-zA-Z0-9_]+)\s*\(/g)).map((m) => m[1]);
    matches.forEach(addHelper);
  }
  if (needsMask && !isDedicatedMask) {
    addHelper("blend");
    if (mask === "maskz") addHelper("set0");
  } else if (isDedicatedMask) {
    if (mask === "maskz" || (maskedSnip && maskedSnip.includes("set0"))) {
      addHelper("set0");
    }
  }

  while (helperQueue.length > 0) {
    const hName = helperQueue.shift();
    if (hName === "abs" && dti.is_float) {
      addHelper("set1");
      addHelper("andnb");
    }
    const hEntry = apiData.find((x) => x.name === hName);
    if (!hEntry) continue;
    const hTInfo = hEntry.isa_support ? hEntry.isa_support[isa] : null;
    const hFeatureOk = isFeatureSupported(hTInfo, dtMain, isa, defines);
    const hSnip = hFeatureOk && hTInfo && hTInfo.code_snippets ? (hTInfo.code_snippets[dtMain] || hTInfo.code_snippets[dt]) : null;
    if (!hSnip) {
      const hEmu = hTInfo && hTInfo.emulation_algorithms ? (hTInfo.emulation_algorithms[dtMain] || hTInfo.emulation_algorithms[dt]) : null;
      if (hEmu) {
        const hMatches = Array.from(hEmu.matchAll(/mipp::([a-zA-Z0-9_]+)\s*\(/g)).map((m) => m[1]);
        hMatches.forEach(addHelper);
      }
    }
  }

  const order = Array.from(neededHelpers).sort((a, b) => {
    if (a === "set1" || a === "set0" || a === "andnb") return -1;
    if (b === "set1" || b === "set0" || b === "andnb") return 1;
    if (a === "abs") return 1;
    if (b === "abs") return -1;
    return 0;
  });

  const helperDefs = new Map();
  for (const h of order) {
    helperDefs.set(h, generateHelperDef(h));
  }

  const allGeneratedCode = [
    protoTemplate || "",
    emuAlgo || "",
    ...Array.from(helperDefs.values()).map((h) => `${h.decl}\n${h.def}`)
  ].join("\n");

  const isRvmReturn = protoTemplate.startsWith("rvm_") || entry.category === "comparison";
  const isReduction = entry.category === "reduction" || entry.name.startsWith("hadd") || entry.name.startsWith("hmax") || entry.name.startsWith("hmin") || entry.name.startsWith("hmul") || entry.name.startsWith("testz");

  const needsMaskType =
    (mask && mask !== "unmasked") ||
    isRvmReturn ||
    protoTemplate.includes("rvm_") ||
    (emuAlgo && (emuAlgo.includes("mipp::msk") || emuAlgo.includes("rvm_"))) ||
    allGeneratedCode.includes(maskTypeName) ||
    allGeneratedCode.includes(`rvm_${isa}_${dtMain}`) ||
    neededHelpers.has("blend") ||
    order.some((h) => h.startsWith("cmp") || h.endsWith("_k"));

  needsMask = mask && mask !== "unmasked";

  // Extra typedefs: scan all types referenced across prototype, emuAlgo and helpers
  const typeMatches = allGeneratedCode.matchAll(/\brv([dm])_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g);
  const extraDts = new Set();
  const extraMasks = new Set();

  for (const m of typeMatches) {
    const kind = m[1]; // 'd' or 'm'
    let sub = m[2];
    if (sub.startsWith(`${isa}_`)) {
      sub = sub.slice(isa.length + 1);
    } else if (sub.startsWith("scalar_") || sub.startsWith("sse_") || sub.startsWith("avx_") || sub.startsWith("avx512_") || sub.startsWith("neon_") || sub.startsWith("rvv_") || sub.startsWith("sve_")) {
      continue;
    }
    if (!sub) continue;
    if (sub !== dtMain) {
      extraDts.add(sub);
      if (kind === "m") {
        extraMasks.add(sub);
      }
    }
  }

  const isPrimaryLevel3 = !isScalar && !nativeSnip && !emuAlgo && (scalarRef || currentImplLvl === 3);
  if (isPrimaryLevel3) {
    neededScalarDts.add(dtMain);
    if (needsMask || isRvmReturn || protoTemplate.includes("rvm_")) {
      neededScalarMasks.add(dtMain);
    }
  }

  if (isScalar) {
    const alignExpr = currentLmulVal === -2 ? "((MIPP_SCALAR_RVD_SIZE_BYTE) / 2)" : "MIPP_SCALAR_RVD_SIZE_BYTE";
    lines.push(`typedef struct __attribute__((aligned(${alignExpr}))) {`);
    lines.push(`\t${dti.c_type} r[MIPP_SCALAR_N_${dtSuffix.toUpperCase()}_${lmulUpper}];`);
    lines.push(`} ${regTypeName};`);
    if (needsMaskType) {
      lines.push(`typedef struct __attribute__((aligned(${alignExpr}))) {`);
      lines.push(`\t${dti.uint_type} m[MIPP_SCALAR_N_${dtSuffix.toUpperCase()}_${lmulUpper}];`);
      lines.push(`} ${maskTypeName};`);
    }
    for (const subDt of extraDts) {
      const subDti = (DT_INFO && DT_INFO[subDt]) || { c_type: subDt, uint_type: "uint32_t" };
      lines.push(`typedef struct __attribute__((aligned(${alignExpr}))) {`);
      lines.push(`\t${subDti.c_type} r[MIPP_SCALAR_N_${subDt.toUpperCase()}_${lmulUpper}];`);
      lines.push(`} rvd_scalar_${subDt}${baseLmulSuffix}_t;`);
      if (extraMasks.has(subDt) || needsMaskType) {
        lines.push(`typedef struct __attribute__((aligned(${alignExpr}))) {`);
        lines.push(`\t${subDti.uint_type} m[MIPP_SCALAR_N_${subDt.toUpperCase()}_${lmulUpper}];`);
        lines.push(`} rvm_scalar_${subDt}${baseLmulSuffix}_t;`);
      }
    }
  } else if (isa === "rvv") {
    const emittedFixedAliases = new Set();
    const emitRvvReg = (dtName, lmulVal, typeName) => {
      const hwR = getHwRegType("rvv", dtName, defines, lmulVal);
      const lmulStr = lmulVal === -2 ? "d2" : (lmulVal === 1 ? "m1" : `m${lmulVal}`);
      const vlenExpr = lmulVal === -2 ? "__riscv_v_fixed_vlen/2" : (lmulVal === 1 ? "__riscv_v_fixed_vlen" : `__riscv_v_fixed_vlen*${lmulVal}`);
      const aliasName = `fixed_${lmulStr}_${dtName}_t`;
      if (!emittedFixedAliases.has(aliasName)) {
        lines.push(`typedef ${hwR} ${aliasName} __attribute__((riscv_rvv_vector_bits(${vlenExpr})));`);
        emittedFixedAliases.add(aliasName);
      }
      lines.push(`typedef struct { ${aliasName} r; } ${typeName};`);
    };

    const emitRvvMask = (dtName, lmulVal, typeName) => {
      const hwM = getHwMaskType("rvv", dtName, defines, lmulVal);
      const lmulStr = lmulVal === -2 ? "d2" : (lmulVal === 1 ? "m1" : `m${lmulVal}`);
      const dti = (DT_INFO && DT_INFO[dtName]) || { bits: 32, c_type: dtName.startsWith("float") ? `${dtName}_t` : `${dtName}_t` };
      const cType = dti.c_type || `${dtName}_t`;
      const maskVlenExpr = lmulVal === -2 ? `__riscv_v_fixed_vlen/2/(8*sizeof(${cType}))` : (lmulVal === 1 ? `__riscv_v_fixed_vlen/(8*sizeof(${cType}))` : `__riscv_v_fixed_vlen*${lmulVal}/(8*sizeof(${cType}))`);
      const aliasName = `fixed_${lmulStr}_bool${dti.bits}_t`;
      if (!emittedFixedAliases.has(aliasName)) {
        lines.push(`typedef ${hwM} ${aliasName} __attribute__((riscv_rvv_vector_bits(${maskVlenExpr})));`);
        emittedFixedAliases.add(aliasName);
      }
      lines.push(`typedef struct { ${aliasName} m; } ${typeName};`);
    };

    emitRvvReg(dtMain, currentLmulVal, regTypeName);
    if (needsMaskType) {
      emitRvvMask(dtMain, currentLmulVal, maskTypeName);
    }

    for (const subDt of extraDts) {
      const subLmulVal = isHwLmul ? currentLmulVal : 1;
      const subRegName = `rvd_rvv_${subDt}${lmulSuffix}_t`;
      emitRvvReg(subDt, subLmulVal, subRegName);
      if (extraMasks.has(subDt) || allGeneratedCode.includes(`rvm_rvv_${subDt}`)) {
        const subMaskName = `rvm_rvv_${subDt}${lmulSuffix}_t`;
        emitRvvMask(subDt, subLmulVal, subMaskName);
      }
    }
  } else if (isa === "sve") {
    const emittedSveAliases = new Set();
    const emitSveReg = (dtName, typeName) => {
      const hwR = getHwRegType("sve", dtName, defines, 1);
      const aliasName = `fixed_m1_${dtName}_t`;
      if (!emittedSveAliases.has(aliasName)) {
        lines.push(`typedef ${hwR} ${aliasName} __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));`);
        emittedSveAliases.add(aliasName);
      }
      lines.push(`typedef struct { ${aliasName} r; } ${typeName};`);
    };

    const emitSveMask = (dtName, typeName) => {
      const hwM = getHwMaskType("sve", dtName, defines, 1);
      const aliasName = `fixed_m1_bool_t`;
      if (!emittedSveAliases.has(aliasName)) {
        lines.push(`typedef ${hwM} ${aliasName} __attribute__((arm_sve_vector_bits(__ARM_FEATURE_SVE_BITS)));`);
        emittedSveAliases.add(aliasName);
      }
      lines.push(`typedef struct { ${aliasName} m; } ${typeName};`);
    };

    emitSveReg(dtMain, regTypeName);
    if (needsMaskType) {
      emitSveMask(dtMain, maskTypeName);
    }

    for (const subDt of extraDts) {
      const subRegName = `rvd_sve_${subDt}_m1_t`;
      emitSveReg(subDt, subRegName);
      if (extraMasks.has(subDt) || allGeneratedCode.includes(`rvm_sve_${subDt}`)) {
        const subMaskName = `rvm_sve_${subDt}_m1_t`;
        emitSveMask(subDt, subMaskName);
      }
    }
  } else {
    if (isa === "neon" && dtMain === "float64" && !(defines && defines.__aarch64__ !== false)) {
      lines.push(`typedef struct __attribute__((aligned(16))) { double r[2]; } ${regTypeName};`);
      if (needsMaskType) {
        lines.push(`typedef struct __attribute__((aligned(16))) { uint64_t m[2]; } ${maskTypeName};`);
      }
    } else {
      lines.push(`typedef struct { ${hwReg} r; } ${regTypeName};`);
      if (needsMaskType) {
        lines.push(`typedef struct { ${hwMask} m; } ${maskTypeName};`);
      }
    }

    for (const subDt of extraDts) {
      const hwR = getHwRegType(isa, subDt, defines, 1);
      const subRegName = `rvd_${isa}_${subDt}_m1_t`;
      lines.push(`typedef struct { ${hwR} r; } ${subRegName};`);
      if (extraMasks.has(subDt) || allGeneratedCode.includes(`rvm_${isa}_${subDt}`)) {
        const hwM = getHwMaskType(isa, subDt, defines, 1);
        const subMaskName = `rvm_${isa}_${subDt}_m1_t`;
        lines.push(`typedef struct { ${hwM} m; } ${subMaskName};`);
      }
    }
  }

  // Scalar Fallback Type Definitions
  if (!isScalar && neededScalarDts.size > 0) {
    for (const sDt of neededScalarDts) {
      const sDti = (DT_INFO && DT_INFO[sDt]) || { bits: 32, c_type: sDt, uint_type: "uint32_t" };
      lines.push(`typedef struct __attribute__((aligned(MIPP_SCALAR_RVD_SIZE_BYTE))) {`);
      lines.push(`\t${sDti.c_type} r[MIPP_SCALAR_N_${sDt.toUpperCase()}_M1];`);
      lines.push(`} rvd_scalar_${sDt}_m1_t;`);
      if (neededScalarMasks.has(sDt)) {
        lines.push(`typedef struct __attribute__((aligned(MIPP_SCALAR_RVD_SIZE_BYTE))) {`);
        lines.push(`\t${sDti.uint_type} m[MIPP_SCALAR_N_${sDt.toUpperCase()}_M1];`);
        lines.push(`} rvm_scalar_${sDt}_m1_t;`);
      }
    }
  }

  // LMUL Structs (Only for software emulated LMUL)
  if (!isHwLmul && numLmul > 1 && !isScalar) {
    const allDts = Array.from(new Set([dtMain, ...extraDts]));
    let prevLmul = 1;
    for (let cur = 2; cur <= numLmul; cur *= 2) {
      for (const curDt of allDts) {
        const prevName = `rvd_${isa}_${curDt}_m${prevLmul}_t`;
        const curName = `rvd_${isa}_${curDt}_m${cur}_t`;
        lines.push(`typedef struct { ${prevName} r1, r2; } ${curName};`);
        const curNeedsMask = curDt === dtMain ? needsMaskType : (extraMasks.has(curDt) || allGeneratedCode.includes(`rvm_${isa}_${curDt}`));
        if (curNeedsMask) {
          const prevMaskName = `rvm_${isa}_${curDt}_m${prevLmul}_t`;
          const curMaskName = `rvm_${isa}_${curDt}_m${cur}_t`;
          lines.push(`typedef struct { ${prevMaskName} m1, m2; } ${curMaskName};`);
        }
      }
      prevLmul = cur;
    }
  }
  lines.push("");

  // Emit helpers
  if (order.length > 0 && !isScalar) {
    lines.push("// -----------------------------------------------------------------------------");
    lines.push("// Inlined Primitive Helpers (Declarations)");
    lines.push("// -----------------------------------------------------------------------------");
    for (const h of order) {
      lines.push(helperDefs.get(h).decl);
    }
    lines.push("");
    lines.push("// -----------------------------------------------------------------------------");
    lines.push("// Inlined Primitive Helpers (Definitions)");
    lines.push("// -----------------------------------------------------------------------------");
    for (const h of order) {
      lines.push(helperDefs.get(h).def);
      lines.push("");
    }
  }

  lines.push("// -----------------------------------------------------------------------------");
  lines.push("// Specialized Function Implementation (Inlined by Compiler with -O3)");
  lines.push("// -----------------------------------------------------------------------------");

  let paramList = "";
  const parenMatch = protoTemplate.match(/\((.*)\);?$/s);
  if (parenMatch) {
    let p = parenMatch[1].trim();
    p = p.replace(/\brvd_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g, (m, sub) => {
      const cleanSub = sub.startsWith(`${isa}_`) ? sub.slice(isa.length + 1) : sub;
      return `rvd_${isa}_${cleanSub}${baseLmulSuffix}_t`;
    });
    p = p.replace(/\brvm_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g, (m, sub) => {
      const cleanSub = sub.startsWith(`${isa}_`) ? sub.slice(isa.length + 1) : sub;
      return `rvm_${isa}_${cleanSub}${baseLmulSuffix}_t`;
    });
    paramList = p;
  } else {
    if (needsMask) {
      paramList = `const ${maskTypeName} m0, const ${regTypeName} r0, const ${regTypeName} r1`;
    } else {
      paramList = `const ${regTypeName} r0, const ${regTypeName} r1`;
    }
  }

  const baseFuncNameNoLmul = `mipp_${isa}_${entry.name}_${dtSuffix}`;
  const specializedFuncNameNoLmul = needsMask ? `${baseFuncNameNoLmul}_${mask}` : baseFuncNameNoLmul;
  const specializedFuncName = `${specializedFuncNameNoLmul}${baseLmulSuffix}`;
  const baseFuncName = `${baseFuncNameNoLmul}${baseLmulSuffix}`;

  const isVoidReturn = protoTemplate.startsWith("void");
  let baseRetType = regTypeName;
  if (isVoidReturn) {
    baseRetType = "void";
  } else if (isRvmReturn) {
    baseRetType = maskTypeName;
  } else if (entry.category === "reduction") {
    baseRetType = (dti && dti.c_type) ? dti.c_type : "float64_t";
  }

  if (isScalar) {
    if (scalarRef) {
      let cleanCode = scalarRef
        .replace(/^static\s+inline\s+/gm, "")
        .replace(/^static\s+/gm, "")
        .replace(/mipp_scalar_/g, `mipp_${isa}_`);

      cleanCode = cleanCode.replace(
        /\bmipp_scalar_[a-zA-Z0-9_]+(?=\s*\()/g,
        specializedFuncName
      );

      cleanCode = cleanCode.replace(
        /\brvd_scalar_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g,
        `rvd_scalar_$1${baseLmulSuffix}_t`
      );
      cleanCode = cleanCode.replace(
        /\brvm_scalar_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\b/g,
        `rvm_scalar_$1${baseLmulSuffix}_t`
      );

      cleanCode = cleanCode.replace(
        /\bMIPP_SCALAR_N_([A-Z0-9]+)\b(?![_A-Z0-9])/g,
        (match, p1) => {
          if (p1.endsWith("_M1") || p1.endsWith("_M2") || p1.endsWith("_M4") || p1.endsWith("_M8") || p1.endsWith("_D2")) {
            return match;
          }
          return `MIPP_SCALAR_N_${p1}_${lmulUpper}`;
        }
      );

      lines.push("static inline\n" + cleanCode);
    } else {
      lines.push("static inline");
      lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t${baseRetType} res;`);
      lines.push(`\tfor (size_t i = 0; i < MIPP_SCALAR_N_${dtSuffix.toUpperCase()}_${lmulUpper}; i++) {`);
      lines.push(`\t\tres.r[i] = r0.r[i];`);
      lines.push(`\t}`);
      lines.push(`\treturn res;`);
      lines.push(`}`);
    }
  } else {
    if (!needsMask) {
      if (nativeSnip) {
        lines.push("static inline");
        lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
        lines.push(`\t// Level 0 (Native Hardware Intrinsic)`);
        if (nativeSnip.includes("return ")) {
          const cleanSnip = cleanSnippetForC(nativeSnip);
          const stmts = splitStatements(cleanSnip);
          for (const s of stmts) {
            lines.push(`\t${s}`);
          }
        } else if (protoTemplate.startsWith("void")) {
          lines.push(`\t${nativeSnip}`);
        } else {
          const cleanSnip = cleanSnippetForC(nativeSnip);
          const field = isRvmReturn ? "m" : "r";
          lines.push(`\t${baseRetType} res;`);
          lines.push(`\tres.${field} = ${cleanSnip};`);
          lines.push(`\treturn res;`);
        }
        lines.push(`}`);
      } else if (emuAlgo) {
        let converted = emuAlgo
          .replace(/mipp::reg/g, regTypeName)
          .replace(/mipp::msk/g, maskTypeName)
          .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dtMain}_m1()`)
          .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dtMain}_m1(`);

        lines.push("static inline");
        lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
        lines.push(`\t// Level 1/2 (Generic Emulated Algorithm)`);
        if (!converted.includes("return ")) {
          const cleanSnip = cleanSnippetForC(converted);
          const field = isRvmReturn ? "m" : "r";
          lines.push(`\t${baseRetType} res;`);
          lines.push(`\tres.${field} = ${cleanSnip};`);
          lines.push(`\treturn res;`);
        } else {
          lines.push(converted.split("\n").map((l) => "\t" + l).join("\n"));
        }
        lines.push(`}`);
      } else if (scalarRef) {
        if (!isScalar) {
          const scalarFnName = `mipp_scalar_${entry.name}_${dtSuffix}_m1`;
          const adaptedScalar = adaptScalarRef(scalarRef, scalarFnName);
          const scalarDecl = extractDeclFromFunc(adaptedScalar);
          const bridgeDef = buildScalarBridge(specializedFuncName, baseRetType, paramList, scalarFnName);

          if (!emittedScalarFuncs.has(scalarFnName)) {
            emittedScalarFuncs.add(scalarFnName);
            lines.push(scalarDecl);
            lines.push("");
            lines.push(adaptedScalar);
            lines.push("");
          }
          lines.push(bridgeDef);
        } else {
          let cleanCode = scalarRef
            .replace(/^static\s+inline\s+/gm, "")
            .replace(/^static\s+/gm, "")
            .replace(/mipp_scalar_/g, `mipp_${isa}_`);
          cleanCode = cleanCode.replace(
            new RegExp(`\\bmipp_${isa}_[a-zA-Z0-9_]+(?=\\s*\\()`, "g"),
            specializedFuncName
          );
          cleanCode = cleanCode.replace(
            new RegExp(`\\brvd_${isa}_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\\b`, "g"),
            `rvd_${isa}_$1${baseLmulSuffix}_t`
          );
          cleanCode = cleanCode.replace(
            new RegExp(`\\brvm_${isa}_([a-z0-9_]+?)(?:_m[0-9]+|_d[0-9]+)?_t\\b`, "g"),
            `rvm_${isa}_$1${baseLmulSuffix}_t`
          );
          cleanCode = cleanCode.replace(
            /\bMIPP_SCALAR_N_([A-Z0-9]+)\b(?![_A-Z0-9])/g,
            (match, p1) => {
              if (p1.endsWith("_M1") || p1.endsWith("_M2") || p1.endsWith("_M4") || p1.endsWith("_M8") || p1.endsWith("_D2")) {
                return match;
              }
              return `MIPP_SCALAR_N_${p1}_${lmulUpper}`;
            }
          );
          lines.push("static inline\n" + cleanCode);
        }
      } else {
        lines.push("static inline");
        lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
        lines.push(`\t${baseRetType} res = r0;`);
        lines.push(`\treturn res;`);
        lines.push(`}`);
      }
    } else if (isDedicatedMask) {
      lines.push("static inline");
      lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
      if (currentImplLvl === 0) {
        lines.push(`\t// Level 0 (Native Hardware Intrinsic Mapping)`);
      } else {
        lines.push(`\t// Level 1 (Dedicated Emulation)`);
      }
      let cleanSnip = cleanSnippetForC(maskedSnip);
      if (cleanSnip.includes("return ")) {
        lines.push(`\t${cleanSnip};`);
      } else {
        const field = isRvmReturn ? "m" : "r";
        lines.push(`\t${baseRetType} res;`);
        lines.push(`\tres.${field} = ${cleanSnip};`);
        lines.push(`\treturn res;`);
      }
      lines.push(`}`);
    } else if (needsMask) {
      const unmaskedParams = paramList
        .replace(/(?:const\s+)?rvm_[a-z0-9_]+_t\s+m0,?\s*/g, "")
        .replace(/(?:const\s+)?rvd_[a-z0-9_]+_t\s+rsrc,?\s*/g, "")
        .replace(/,\s*$/, "")
        .trim();
      const callArgs = unmaskedParams.split(",").map((p) => p.trim().split(/\s+/).pop()).join(", ");

      if (nativeSnip) {
        lines.push("static inline");
        lines.push(`${baseRetType} ${baseFuncName}(${unmaskedParams}) {`);
        if (nativeSnip.includes("return ")) {
          const cleanSnip = cleanSnippetForC(nativeSnip);
          const stmts = splitStatements(cleanSnip);
          for (const s of stmts) {
            lines.push(`\t${s}`);
          }
        }
        else {
          const cleanSnip = cleanSnippetForC(nativeSnip);
          lines.push(`\t${baseRetType} res;\n\tres.r = ${cleanSnip};\n\treturn res;`);
        }
        lines.push(`}`);
      } else if (emuAlgo) {
        lines.push("static inline");
        lines.push(`${baseRetType} ${baseFuncName}(${unmaskedParams}) {`);
        let converted = emuAlgo
          .replace(/mipp::reg/g, regTypeName)
          .replace(/mipp::msk/g, maskTypeName)
          .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dtMain}_m1()`)
          .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dtMain}_m1(`);
        if (!converted.includes("return ")) {
          const cleanSnip = cleanSnippetForC(converted);
          const field = isRvmReturn ? "m" : "r";
          lines.push(`\t${baseRetType} res;\n\tres.${field} = ${cleanSnip};\n\treturn res;`);
        } else {
          lines.push(converted.split("\n").map((l) => "\t" + l).join("\n"));
        }
        lines.push(`}`);
      } else if (scalarRef) {
        if (!isScalar) {
          const scalarFnName = `mipp_scalar_${entry.name}_${dtSuffix}_m1`;
          const adaptedScalar = adaptScalarRef(scalarRef, scalarFnName);
          const scalarDecl = extractDeclFromFunc(adaptedScalar);
          const bridgeDef = buildScalarBridge(baseFuncName, baseRetType, unmaskedParams, scalarFnName);
          if (!emittedScalarFuncs.has(scalarFnName)) {
            emittedScalarFuncs.add(scalarFnName);
            lines.push(scalarDecl);
            lines.push("");
            lines.push(adaptedScalar);
            lines.push("");
          }
          lines.push(bridgeDef);
        } else {
          lines.push("static inline");
          lines.push(`${baseRetType} ${baseFuncName}(${unmaskedParams}) {`);
          lines.push(`\t${baseRetType} res = r0;\n\treturn res;`);
          lines.push(`}`);
        }
      } else {
        lines.push("static inline");
        lines.push(`${baseRetType} ${baseFuncName}(${unmaskedParams}) {`);
        lines.push(`\t${baseRetType} res = r0;\n\treturn res;`);
        lines.push(`}`);
      }
      lines.push("");

      const mArgMatch = paramList.match(/const\s+(rvm_[a-z0-9_]+_t)\s+m0/);
      const mArgType = mArgMatch ? mArgMatch[1] : maskTypeName;
      const blendMaskArg = mArgType === maskTypeName ? "m0" : `*(const ${maskTypeName}*)&m0`;

      if (mask === "mask") {
        lines.push("static inline");
        lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
        lines.push(`\t// Level 2 (Generic Emulation with blend)`);
        lines.push(`\t${baseRetType} op = ${baseFuncName}(${callArgs});`);
        lines.push(`\treturn mipp_${isa}_blend_${dtMain}_m1(r0, op, ${blendMaskArg});`);
        lines.push(`}`);
      } else if (mask === "maskz") {
        lines.push("static inline");
        lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
        lines.push(`\t// Level 2 (Generic Emulation with zero blend)`);
        lines.push(`\t${baseRetType} op = ${baseFuncName}(${callArgs});`);
        lines.push(`\treturn mipp_${isa}_blend_${dtMain}_m1(mipp_${isa}_set0_${dtMain}_m1(), op, ${blendMaskArg});`);
        lines.push(`}`);
      } else if (mask === "masks") {
        lines.push("static inline");
        lines.push(`${baseRetType} ${specializedFuncName}(${paramList}) {`);
        lines.push(`\t// Level 2 (Generic Emulation with source blend)`);
        lines.push(`\t${baseRetType} op = ${baseFuncName}(${callArgs});`);
        lines.push(`\treturn mipp_${isa}_blend_${dtMain}_m1(rsrc, op, ${blendMaskArg});`);
        lines.push(`}`);
      }
    }

    if (isSoftwareLmulWrapper) {
      let prevLmul = 1;
      for (let cur = 2; cur <= numLmul; cur *= 2) {
        lines.push("");
        const curRetType = isReduction ? baseRetType : (isVoidReturn ? "void" : (isRvmReturn ? `rvm_${isa}_${dtMain}_m${cur}_t` : `rvd_${isa}_${dtMain}_m${cur}_t`));
        const curFuncName = `${specializedFuncNameNoLmul}_m${cur}`;
        const prevFuncName = `${specializedFuncNameNoLmul}_m${prevLmul}`;
        const parsed = parseCParams(paramList, isa, dtMain, cur);

        lines.push("static inline");
        lines.push(`${curRetType} ${curFuncName}(${parsed.lmulParamList}) {`);
        lines.push(`\t// Software Emulated LMUL=${cur}`);
        if (isReduction) {
          if (entry.name.startsWith("hadd")) {
            lines.push(`\treturn ${prevFuncName}(${parsed.call1}) + ${prevFuncName}(${parsed.call2});`);
          } else if (entry.name.startsWith("hmul")) {
            lines.push(`\treturn ${prevFuncName}(${parsed.call1}) * ${prevFuncName}(${parsed.call2});`);
          } else if (entry.name.startsWith("hmin")) {
            lines.push(`\t${curRetType} a = ${prevFuncName}(${parsed.call1});\n\t${curRetType} b = ${prevFuncName}(${parsed.call2});\n\treturn a < b ? a : b;`);
          } else if (entry.name.startsWith("hmax")) {
            lines.push(`\t${curRetType} a = ${prevFuncName}(${parsed.call1});\n\t${curRetType} b = ${prevFuncName}(${parsed.call2});\n\treturn a > b ? a : b;`);
          } else {
            lines.push(`\treturn ${prevFuncName}(${parsed.call1}) + ${prevFuncName}(${parsed.call2});`);
          }
        } else if (isVoidReturn) {
          lines.push(`\t${prevFuncName}(${parsed.call1});`);
          lines.push(`\t${prevFuncName}(${parsed.call2});`);
        } else if (isRvmReturn) {
          lines.push(`\t${curRetType} res;`);
          lines.push(`\tres.m1 = ${prevFuncName}(${parsed.call1});`);
          lines.push(`\tres.m2 = ${prevFuncName}(${parsed.call2});`);
          lines.push(`\treturn res;`);
        } else {
          lines.push(`\t${curRetType} res;`);
          lines.push(`\tres.r1 = ${prevFuncName}(${parsed.call1});`);
          lines.push(`\tres.r2 = ${prevFuncName}(${parsed.call2});`);
          lines.push(`\treturn res;`);
        }
        lines.push(`}`);
        prevLmul = cur;
      }
    }
  }

  let targetFuncName = specializedFuncName;
  let targetRetType = baseRetType;
  let targetParamList = paramList;

  if (isSoftwareLmulWrapper) {
    targetFuncName = `${specializedFuncNameNoLmul}_m${numLmul}`;
    targetRetType = isReduction ? baseRetType : (isVoidReturn ? "void" : (isRvmReturn ? `rvm_${isa}_${dtMain}_m${numLmul}_t` : `rvd_${isa}_${dtMain}_m${numLmul}_t`));
    const parsedTarget = parseCParams(paramList, isa, dtMain, numLmul);
    targetParamList = parsedTarget.lmulParamList;
  }

  lines.push("");
  lines.push(generateTestHarness(targetFuncName, targetRetType, targetParamList, entry, cfg));

  const initialCode = lines.join("\n");

  // Collect all needed defines
  const definesLines = [];

  // 1. Bit cast macros if referenced
  if (initialCode.includes("BIT_CAST_")) {
    definesLines.push("#ifndef BIT_CAST_1");
    definesLines.push("#define BIT_CAST_1(dst_ptr, src_ptr) memcpy((dst_ptr), (src_ptr), sizeof(*(dst_ptr)))");
    definesLines.push("#endif");
    definesLines.push("#ifndef BIT_CAST_N");
    definesLines.push("#define BIT_CAST_N(dst_ptr, src_ptr, n) memcpy((dst_ptr), (src_ptr), (n) * sizeof(*(dst_ptr)))");
    definesLines.push("#endif");
    definesLines.push("");
  }

  // 2. Helper macros from entry.scalar_macros if referenced
  const matchedHelperMacros = [];
  if (entry.scalar_macros && typeof entry.scalar_macros === "object") {
    for (const [mName, mObj] of Object.entries(entry.scalar_macros)) {
      if (new RegExp(`\\b${mName}\\b`).test(initialCode)) {
        matchedHelperMacros.push(mObj.definition);
      }
    }
  }
  if (matchedHelperMacros.length > 0) {
    definesLines.push("// Helper Macros");
    for (const def of matchedHelperMacros) {
      definesLines.push(def);
    }
    definesLines.push("");
  }

  // 3. Scalar buffer or fallback configuration
  const matchedScalarMacros = new Set(initialCode.match(/\bMIPP_SCALAR_N_[A-Z0-9_]+\b/g) || []);
  if (isScalar) {
    matchedScalarMacros.add(`MIPP_SCALAR_N_${dtSuffix.toUpperCase()}_${lmulUpper}`);
    for (const subDt of extraDts) {
      matchedScalarMacros.add(`MIPP_SCALAR_N_${subDt.toUpperCase()}_${lmulUpper}`);
    }
  } else if (neededScalarDts.size > 0) {
    for (const sDt of neededScalarDts) {
      matchedScalarMacros.add(`MIPP_SCALAR_N_${sDt.toUpperCase()}_M1`);
    }
  }

  const effectiveSimdWidth = (isa === "rvv" || isa === "sve" || isa === "scalar")
    ? (scalarSize || 256)
    : (isa === "avx512" ? 512 : (isa === "avx" ? 256 : 128));

  if (isScalar) {
    definesLines.push(`// Scalar buffer configuration (MIPP_SCALAR_SIZE=${effectiveSimdWidth} passed via -DMIPP_SCALAR_SIZE=${effectiveSimdWidth})`);
    definesLines.push("#define MIPP_SCALAR_RVD_SIZE_BYTE (MIPP_SCALAR_SIZE / 8)");
    for (const mName of Array.from(matchedScalarMacros).sort()) {
      const def = getScalarNMacroDef(mName);
      if (def) definesLines.push(def);
    }
    definesLines.push("");
  } else if (matchedScalarMacros.size > 0 || initialCode.includes("MIPP_SCALAR_")) {
    definesLines.push(`// Scalar fallback configuration (SIMD Width: ${effectiveSimdWidth} bits)`);
    definesLines.push(`#define MIPP_SCALAR_SIZE ${effectiveSimdWidth}`);
    definesLines.push("#define MIPP_SCALAR_RVD_SIZE_BYTE (MIPP_SCALAR_SIZE / 8)");
    for (const mName of Array.from(matchedScalarMacros).sort()) {
      const def = getScalarNMacroDef(mName);
      if (def) definesLines.push(def);
    }
    definesLines.push("");
  }

  const defsContent = definesLines.length > 0 ? definesLines.join("\n") + "\n" : "";
  const finalCode = initialCode
    .replace("/* __DEFINES_SECTION__ */\n\n", defsContent)
    .replace("/* __DEFINES_SECTION__ */\n", defsContent)
    .replace("/* __DEFINES_SECTION__ */", defsContent);

  return formatFunctionHeaders(finalCode);
}
