/**
 * MIPP API Explorer - Code Generation & Compiler Explorer (Godbolt) Integration
 */
import { apiMetadata, DT_INFO, apiData } from "./data.js";

export function getHwRegType(isa, dt, defines) {
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

export function getHwMaskType(isa, dt, defines) {
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

export function buildGodboltUrlForFlat(sourceCode, isa, defines = {}, scalarSize = 256) {
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[isa] : null;
  const compilerMeta = (isaMeta && isaMeta.compiler) ? isaMeta.compiler : { id: "g142", arch: "x86", base_flags: "-O3", label: "x86-64 GCC" };

  let compiler = compilerMeta.id || "g142";
  let options = compilerMeta.base_flags || "-O3";
  let compilerLabel = compilerMeta.label || "GCC";

  if (isa === "scalar") {
    options = `-O3 -DMIPP_SCALAR_SIZE=${scalarSize}`;
    compilerLabel = `x86-64 GCC (-O3 -DMIPP_SCALAR_SIZE=${scalarSize})`;
  } else if (isa === "neon") {
    if (defines.__aarch64__ !== false) {
      compiler = compilerMeta.id || "aarch64-gcc-1420";
      const archExts = [];
      if (defines.__ARM_FEATURE_FMA !== false) archExts.push("+fma");
      options = `-O3 -march=armv8-a+simd${archExts.join("")}`;
      compilerLabel = `AArch64 GCC (${options})`;
    } else {
      compiler = compilerMeta.id_32 || "arm-gcc-1320";
      options = compilerMeta.flags_32 || "-O3 -march=armv7-a -mfpu=neon -mfloat-abi=hard";
      compilerLabel = `ARM32 GCC (${options})`;
    }
  } else if (isa === "sve") {
    options = defines.__ARM_FEATURE_SVE2 ? "-O3 -march=armv8.2-a+sve2" : "-O3 -march=armv8.2-a+sve";
    compilerLabel = `AArch64 SVE GCC (${options})`;
  } else if (isa === "rvv") {
    compiler = compilerMeta.id || "rv64-clang";
    options = compilerMeta.base_flags || "-O3 -march=rv64gcv";
    compilerLabel = `RISC-V 64 Clang (${options})`;
  } else if (isaMeta && isaMeta.features && isaMeta.features.length > 0) {
    const flags = ["-O3"];
    if (isa === "avx512") {
      for (const f of isaMeta.features) {
        if (defines[f.name] !== false && f.flag) flags.push(f.flag);
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

  const lang = "c";
  return (
    "https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUseDefault:true,lang:'" +
    lang +
    "',source:'" +
    encodeURIComponent(sourceCode) +
    "'),l:'5',n:'0',o:'MIPP+Specialized+C',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:" +
    compiler +
    ",filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1'),flagsViewOpen:'1',fontScale:14,fontUseDefault:true,lang:'" +
    lang +
    "',options:'" +
    encodeURIComponent(options) +
    "'),l:'5',n:'0',o:'" +
    encodeURIComponent(compilerLabel) +
    "',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"
  );
}

export function generateFlatSpecializedCode(entry, cfg) {
  const { isa, defines, dt, mask, lmul, scalarSize } = cfg;
  const dti = DT_INFO[dt] || DT_INFO.float32 || { c_type: "float", uint_type: "uint32_t", bits: 32 };
  const isScalar = isa === "scalar";
  const needsMask = mask && mask !== "unmasked";
  const numLmul = Number(lmul) || 1;
  const lines = [];

  const isaInfo = entry.isa_support ? entry.isa_support[isa] : null;
  const nativeSnip = isaInfo && isaInfo.code_snippets ? isaInfo.code_snippets[dt] : null;
  const emuAlgo = isaInfo && isaInfo.emulation_algorithms ? isaInfo.emulation_algorithms[dt] : null;
  const refAlgos = entry.reference_algos ? entry.reference_algos["1"] : null;
  const scalarRef = refAlgos && refAlgos[dt] ? (refAlgos[dt][mask] || refAlgos[dt]["unmasked"]) : null;

  // Scan for any helper macros from entry.scalar_macros used in code
  const neededMacros = [];
  const codeToScan = (scalarRef || "") + " " + (emuAlgo || "") + " " + (nativeSnip || "");
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
  lines.push("// =============================================================================");
  lines.push(`// MIPP Flat Specialized Code: ${entry.name} (${isa.toUpperCase()})`);
  lines.push(`// Datatype: ${dt} | Variant: ${mask} | LMUL: ${lmul}${isScalar ? ` | Buffer Size: ${scalarSize} bits` : ""}`);
  if (defines && Object.keys(defines).length > 0) {
    const defStr = Object.entries(defines).map(([k, v]) => `${k}=${v ? "1" : "0"}`).join(" ");
    lines.push(`// Feature switches: ${defStr}`);
  }
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
    if (hasMemcpy) lines.push("#include <string.h>");
    if (hasMath) lines.push("#include <math.h>");
  }
  lines.push("");

  // Common scalar typedefs for float32_t / float64_t
  lines.push("typedef float float32_t;");
  lines.push("typedef double float64_t;");
  lines.push("");

  // 2. Defines
  if (isScalar) {
    lines.push(`// Scalar buffer configuration (MIPP_SCALAR_SIZE=${scalarSize} bits)`);
    lines.push(`#define MIPP_SCALAR_SIZE ${scalarSize}`);
    lines.push(`#define MIPP_SCALAR_RVD_SIZE_BYTE (MIPP_SCALAR_SIZE / 8)`);
    lines.push(`#define MIPP_SCALAR_N_${dt.toUpperCase()} (MIPP_SCALAR_SIZE / ${dti.bits})`);
    lines.push("");
  }
  if (neededMacros.length > 0) {
    lines.push("// Helper Macros");
    for (const def of neededMacros) {
      lines.push(def);
    }
    lines.push("");
  }

  // 3. Typedefs
  lines.push("// -----------------------------------------------------------------------------");
  lines.push("// Minimal MIPP Type Definitions");
  lines.push("// -----------------------------------------------------------------------------");
  const regTypeName = `rvd_${isa}_${dt}_t`;
  const maskTypeName = `rvm_${isa}_${dt}_t`;
  const hwReg = getHwRegType(isa, dt, defines);
  const hwMask = getHwMaskType(isa, dt, defines);

  if (isScalar) {
    lines.push(`typedef struct __attribute__((aligned(MIPP_SCALAR_RVD_SIZE_BYTE))) {`);
    lines.push(`\t${dti.c_type} r[MIPP_SCALAR_N_${dt.toUpperCase()}];`);
    lines.push(`} ${regTypeName};`);
    if (needsMask) {
      lines.push(`typedef struct __attribute__((aligned(MIPP_SCALAR_RVD_SIZE_BYTE))) {`);
      lines.push(`\t${dti.uint_type} m[MIPP_SCALAR_N_${dt.toUpperCase()}];`);
      lines.push(`} ${maskTypeName};`);
    }
  } else {
    if (isa === "neon" && dt === "float64" && !(defines && defines.__aarch64__ !== false)) {
      lines.push(`typedef struct __attribute__((aligned(16))) { double r[2]; } ${regTypeName};`);
      if (needsMask) {
        lines.push(`typedef struct __attribute__((aligned(16))) { uint64_t m[2]; } ${maskTypeName};`);
      }
    } else {
      lines.push(`typedef struct { ${hwReg} r; } ${regTypeName};`);
      if (needsMask) {
        lines.push(`typedef struct { ${hwMask} m; } ${maskTypeName};`);
      }
    }
  }

  // LMUL Structs
  if (numLmul > 1) {
    let prevLmul = 1;
    for (let cur = 2; cur <= numLmul; cur *= 2) {
      const prevName = prevLmul === 1 ? regTypeName : `rvd_${isa}_${dt}_m${prevLmul}_t`;
      const curName = `rvd_${isa}_${dt}_m${cur}_t`;
      lines.push(`typedef struct { ${prevName} r1, r2; } ${curName};`);
      if (needsMask) {
        const prevMaskName = prevLmul === 1 ? maskTypeName : `rvm_${isa}_${dt}_m${prevLmul}_t`;
        const curMaskName = `rvm_${isa}_${dt}_m${cur}_t`;
        lines.push(`typedef struct { ${prevMaskName} m1, m2; } ${curMaskName};`);
      }
      prevLmul = cur;
    }
  }
  lines.push("");

  // 4. Inlined Helpers and Function Implementation
  function fmtHelper(retType, signature, bodyLines) {
    return [
      "static inline",
      `${retType} ${signature} {`,
      ...bodyLines.map((l) => `\t${l}`),
      "}"
    ].join("\n");
  }

  // Fully Generic Helper Function Generator (Extracted dynamically from apiData)
  function generateHelperDef(helperName) {
    const fnName = `mipp_${isa}_${helperName}_${dt}`;
    const targetEntry = apiData.find((x) => x.name === helperName);
    if (!targetEntry) {
      return fmtHelper(regTypeName, `${fnName}(const ${regTypeName} r0)`, [
        `${regTypeName} res = r0;`,
        `return res;`
      ]);
    }

    const tInfo = targetEntry.isa_support ? targetEntry.isa_support[isa] : null;
    const snip = tInfo && tInfo.code_snippets ? tInfo.code_snippets[dt] : null;
    const emu = tInfo && tInfo.emulation_algorithms ? tInfo.emulation_algorithms[dt] : null;
    const ref = targetEntry.reference_algos && targetEntry.reference_algos["1"] && targetEntry.reference_algos["1"][dt]
      ? (targetEntry.reference_algos["1"][dt]["unmasked"] || targetEntry.reference_algos["1"][dt]["mask"])
      : null;

    let protoSamples = targetEntry.prototypes && targetEntry.prototypes.c99_samples && targetEntry.prototypes.c99_samples["1"]
      ? (targetEntry.prototypes.c99_samples["1"]["unmasked"] || Object.values(targetEntry.prototypes.c99_samples["1"])[0] || [])
      : [];
    if (!Array.isArray(protoSamples)) protoSamples = [protoSamples];
    let sampleProto = protoSamples.find((p) => p.includes(dt)) || protoSamples[0] || "";

    let params = "";
    const pMatch = sampleProto.match(/\(([^)]*)\)/);
    if (pMatch) {
      params = pMatch[1]
        .replace(new RegExp(`rvd_${dt}_m1_t`, "g"), regTypeName)
        .replace(new RegExp(`rvm_${dt}_m1_t`, "g"), maskTypeName)
        .replace(/\brvd_[a-z0-9_]+_m1_t\b/g, regTypeName)
        .replace(/\brvm_[a-z0-9_]+_m1_t\b/g, maskTypeName);
    } else {
      params = `const ${regTypeName} r0`;
    }

    let retType = regTypeName;
    if (sampleProto.startsWith("rvm_") || helperName.startsWith("cmp") || helperName.endsWith("_k")) {
      retType = maskTypeName;
    }

    if (snip) {
      if (snip.includes("return ")) {
        return fmtHelper(retType, `${fnName}(${params})`, [snip]);
      }
      const cleanSnip = snip.replace(/;\s*$/, "");
      const field = retType === maskTypeName ? "m" : "r";
      return fmtHelper(retType, `${fnName}(${params})`, [
        `${retType} res;`,
        `res.${field} = ${cleanSnip};`,
        `return res;`
      ]);
    }

    if (emu) {
      let converted = emu
        .replace(/mipp::reg/g, regTypeName)
        .replace(/mipp::msk/g, maskTypeName)
        .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dt}()`)
        .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dt}(`);
      return fmtHelper(retType, `${fnName}(${params})`, converted.split("\n"));
    }

    if (ref) {
      let cleanRef = ref
        .replace(/^static\s+/gm, "static inline ")
        .replace(/mipp_scalar_/g, `mipp_${isa}_`);
      return cleanRef;
    }

    return fmtHelper(retType, `${fnName}(${params})`, [
      `${retType} res;`,
      `return res;`
    ]);
  }

  // Collect helper dependencies
  const neededHelpers = new Set();
  if (emuAlgo) {
    const matches = Array.from(emuAlgo.matchAll(/mipp::([a-zA-Z0-9_]+)\s*\(/g)).map((m) => m[1]);
    matches.forEach((m) => neededHelpers.add(m));
    if (neededHelpers.has("abs") && dti.is_float) {
      neededHelpers.add("set1");
      neededHelpers.add("andnb");
    }
  }
  if (needsMask) {
    neededHelpers.add("blend");
    if (mask === "maskz") neededHelpers.add("set0");
  }

  // Emit helpers
  if (neededHelpers.size > 0 && !isScalar) {
    lines.push("// -----------------------------------------------------------------------------");
    lines.push("// Inlined Primitive Helpers");
    lines.push("// -----------------------------------------------------------------------------");
    const order = Array.from(neededHelpers).sort((a, b) => {
      if (a === "set1" || a === "set0" || a === "andnb") return -1;
      if (b === "set1" || b === "set0" || b === "andnb") return 1;
      if (a === "abs") return 1;
      if (b === "abs") return -1;
      return 0;
    });
    for (const h of order) {
      lines.push(generateHelperDef(h));
      lines.push("");
    }
  }

  lines.push("// -----------------------------------------------------------------------------");
  lines.push("// Specialized Function Implementation (Inlined by Compiler with -O3)");
  lines.push("// -----------------------------------------------------------------------------");

  let protoTemplate = "";
  if (entry.prototypes && entry.prototypes.c99_samples && entry.prototypes.c99_samples["1"]) {
    const list = entry.prototypes.c99_samples["1"][mask] || entry.prototypes.c99_samples["1"]["unmasked"];
    if (Array.isArray(list) && list.length > 0) {
      protoTemplate = list.find((s) => s.includes(`_${dt}_`) || s.includes(`_${dt}(`)) || list[0];
    } else if (typeof list === "string") {
      protoTemplate = list;
    }
  }
  if (!protoTemplate && entry.prototypes && entry.prototypes.c99) {
    protoTemplate = entry.prototypes.c99;
  }

  let paramList = "";
  const parenMatch = protoTemplate.match(/\((.*)\);?$/s);
  if (parenMatch) {
    let p = parenMatch[1].trim();
    p = p.replace(new RegExp(`\\brvd_${dt}(?:_m1)?_t\\b`, "g"), regTypeName);
    p = p.replace(new RegExp(`\\brvm_${dt}(?:_m1)?_t\\b`, "g"), maskTypeName);
    paramList = p;
  } else {
    if (needsMask) {
      paramList = `const ${maskTypeName} m0, const ${regTypeName} r0, const ${regTypeName} r1`;
    } else {
      paramList = `const ${regTypeName} r0, const ${regTypeName} r1`;
    }
  }

  const baseFuncName = `mipp_${isa}_${entry.name}_${dt}`;
  const specializedFuncName = needsMask ? `${baseFuncName}_${mask}` : baseFuncName;

  const isAvxIntegerWithoutAvx2 = isa === "avx" && !dti.is_float && defines && defines.__AVX2__ === false;
  const isAvx512WithoutDq = isa === "avx512" && defines && defines.__AVX512DQ__ === false;
  const isAvx512WithoutBw = isa === "avx512" && defines && defines.__AVX512BW__ === false && (dti.bits === 8 || dti.bits === 16);

  if (isScalar) {
    if (scalarRef) {
      let cleanCode = scalarRef
        .replace(/^static\s+/gm, "")
        .replace(/mipp_scalar_/g, `mipp_${isa}_`);
      lines.push(cleanCode);
    } else {
      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t${regTypeName} res;`);
      lines.push(`\tfor (size_t i = 0; i < MIPP_SCALAR_N_${dt.toUpperCase()}; i++) {`);
      lines.push(`\t\tres.r[i] = r0.r[i];`);
      lines.push(`\t}`);
      lines.push(`\treturn res;`);
      lines.push(`}`);
    }
  } else if (isAvxIntegerWithoutAvx2) {
    lines.push(`// Note: __AVX2__ disabled -> Emulated via 128-bit SSE split execution`);
    lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
    lines.push(`\t__m128i r0_lo = _mm256_castsi256_si128(r0.r);`);
    lines.push(`\t__m128i r0_hi = _mm256_extractf128_si256(r0.r, 1);`);
    lines.push(`\t__m128i r1_lo = _mm256_castsi256_si128(r1.r);`);
    lines.push(`\t__m128i r1_hi = _mm256_extractf128_si256(r1.r, 1);`);
    lines.push(`\t__m128i res_lo = _mm_add_${dti.suffix}(r0_lo, r1_lo);`);
    lines.push(`\t__m128i res_hi = _mm_add_${dti.suffix}(r0_hi, r1_hi);`);
    lines.push(`\t${regTypeName} res;`);
    lines.push(`\tres.r = _mm256_insertf128_si256(_mm256_castsi128_si256(res_lo), res_hi, 1);`);
    lines.push(`\treturn res;`);
    lines.push(`}`);
  } else if (isAvx512WithoutBw || (isAvx512WithoutDq && !dti.is_float && dti.bits === 64)) {
    lines.push(`// Note: Feature flag disabled -> Emulated scalar fallback execution`);
    lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
    lines.push(`\t${regTypeName} res;`);
    lines.push(`\tfor (size_t i = 0; i < ${512 / dti.bits}; i++) {`);
    lines.push(`\t\tres.r[i] = r0.r[i];`);
    lines.push(`\t}`);
    lines.push(`\treturn res;`);
    lines.push(`}`);
  } else if (!needsMask && numLmul === 1) {
    if (nativeSnip) {
      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t// Level 0 (Native Hardware Intrinsic)`);
      if (nativeSnip.includes("return ")) {
        lines.push(`\t${nativeSnip}`);
      } else if (protoTemplate.startsWith("void")) {
        lines.push(`\t${nativeSnip}`);
      } else {
        const cleanSnip = nativeSnip.replace(/;\s*$/, "");
        lines.push(`\t${regTypeName} res;`);
        lines.push(`\tres.r = ${cleanSnip};`);
        lines.push(`\treturn res;`);
      }
      lines.push(`}`);
    } else if (emuAlgo) {
      let converted = emuAlgo
        .replace(/mipp::reg/g, regTypeName)
        .replace(/mipp::msk/g, maskTypeName)
        .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dt}()`)
        .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dt}(`);

      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t// Level 1/2 (Generic Emulated Algorithm)`);
      lines.push(converted.split("\n").map((l) => "\t" + l).join("\n"));
      lines.push(`}`);
    } else if (scalarRef) {
      lines.push(`// Level 3 (Auto Scalar Fallback)`);
      let cleanCode = scalarRef
        .replace(/^static\s+/gm, "")
        .replace(/mipp_scalar_/g, `mipp_${isa}_`);
      lines.push(cleanCode);
    } else {
      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t${regTypeName} res = r0;`);
      lines.push(`\treturn res;`);
      lines.push(`}`);
    }
  } else if (needsMask && numLmul === 1) {
    const unmaskedParams = paramList.replace(new RegExp(`(?:const\\s+)?${maskTypeName}\\s+m0,?\\s*`), "");
    const callArgs = unmaskedParams.split(",").map((p) => p.trim().split(/\s+/).pop()).join(", ");

    lines.push(`static inline ${regTypeName} ${baseFuncName}(${unmaskedParams}) {`);
    if (nativeSnip) {
      if (nativeSnip.includes("return ")) lines.push(`\t${nativeSnip}`);
      else {
        const cleanSnip = nativeSnip.replace(/;\s*$/, "");
        lines.push(`\t${regTypeName} res;\n\tres.r = ${cleanSnip};\n\treturn res;`);
      }
    } else if (emuAlgo) {
      let converted = emuAlgo
        .replace(/mipp::reg/g, regTypeName)
        .replace(/mipp::msk/g, maskTypeName)
        .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dt}()`)
        .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dt}(`);
      lines.push(converted.split("\n").map((l) => "\t" + l).join("\n"));
    } else {
      lines.push(`\t${regTypeName} res = r0;\n\treturn res;`);
    }
    lines.push(`}`);
    lines.push("");

    if (mask === "mask") {
      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t// Level 2 (Generic Emulation with blend)`);
      lines.push(`\t${regTypeName} op = ${baseFuncName}(${callArgs});`);
      lines.push(`\treturn mipp_${isa}_blend_${dt}(r0, op, m0);`);
      lines.push(`}`);
    } else if (mask === "maskz") {
      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t// Level 2 (Generic Emulation with zero blend)`);
      lines.push(`\t${regTypeName} op = ${baseFuncName}(${callArgs});`);
      lines.push(`\treturn mipp_${isa}_blend_${dt}(mipp_${isa}_set0_${dt}(), op, m0);`);
      lines.push(`}`);
    } else if (mask === "masks") {
      lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
      lines.push(`\t// Level 2 (Generic Emulation with source blend)`);
      lines.push(`\t${regTypeName} op = ${baseFuncName}(${callArgs});`);
      lines.push(`\treturn mipp_${isa}_blend_${dt}(rsrc, op, m0);`);
      lines.push(`}`);
    }
  } else if (numLmul > 1) {
    const unmaskedParams = paramList.replace(new RegExp(`(?:const\\s+)?${maskTypeName}\\s+m0,?\\s*`), "");
    lines.push(`static inline ${regTypeName} ${baseFuncName}(${unmaskedParams}) {`);
    if (nativeSnip) {
      const cleanSnip = nativeSnip.replace(/;\s*$/, "");
      lines.push(`\t${regTypeName} res;\n\tres.r = ${cleanSnip};\n\treturn res;`);
    } else if (emuAlgo) {
      let converted = emuAlgo
        .replace(/mipp::reg/g, regTypeName)
        .replace(/mipp::msk/g, maskTypeName)
        .replace(/mipp::set0\(\s*\)/g, `mipp_${isa}_set0_${dt}()`)
        .replace(/mipp::([a-zA-Z0-9_]+)\s*\(/g, `mipp_${isa}_$1_${dt}(`);
      lines.push(converted.split("\n").map((l) => "\t" + l).join("\n"));
    } else {
      lines.push(`\t${regTypeName} res = r0;\n\treturn res;`);
    }
    lines.push(`}`);
    lines.push("");

    const lmulTypeName = `rvd_${isa}_${dt}_m${numLmul}_t`;
    lines.push(`${lmulTypeName} ${baseFuncName}_m${numLmul}(const ${lmulTypeName} r0, const ${lmulTypeName} r1) {`);
    lines.push(`\t// Software Emulated LMUL=${numLmul}`);
    lines.push(`\t${lmulTypeName} res;`);
    lines.push(`\tres.r1 = ${baseFuncName}(r0.r1, r1.r1);`);
    lines.push(`\tres.r2 = ${baseFuncName}(r0.r2, r1.r2);`);
    lines.push(`\treturn res;`);
    lines.push(`}`);
  } else {
    lines.push(`${regTypeName} ${specializedFuncName}(${paramList}) {`);
    lines.push(`\t${regTypeName} res = r0;`);
    lines.push(`\treturn res;`);
    lines.push(`}`);
  }

  return lines.join("\n");
}
