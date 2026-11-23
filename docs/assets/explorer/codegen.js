/**
 * MIPP API Explorer - compiler configuration and Compiler Explorer (Godbolt) links of the
 * "Algorithm" modal. The code itself comes from the generated headers (algo_source.js).
 */
import { apiMetadata } from "./data.js";

export function isFeatureSupported(info, targetDt, targetIsa, targetDefines) {
  if (!info || !info.required_features || !targetDefines) return true;
  let req = info.required_features[targetDt];
  if (!req && targetDt.includes(",")) {
    const parts = targetDt.split(",").map((s) => s.trim());
    req = info.required_features[parts[0]] || info.required_features[parts[1]];
  }
  if (!req) return true;

  const isaMeta = apiMetadata.isas ? apiMetadata.isas[targetIsa] : null;
  const featuresMeta = isaMeta ? isaMeta.features : null;

  if (featuresMeta && Array.isArray(featuresMeta.items)) {
    const isHierarchy = featuresMeta.mode === "hierarchy";
    const isMixed = featuresMeta.mode === "mixed";
    const tierItems = featuresMeta.items.filter((it) => isHierarchy || (isMixed && it.type === "tier"));
    const flagItems = featuresMeta.items.filter((it) => it.type === "flag" || (!isHierarchy && !isMixed));

    // 1. Check if req is in tier items
    const reqTierIdx = tierItems.findIndex((it) => it.id === req);
    if (reqTierIdx !== -1) {
      let curIdx = tierItems.length - 1;
      const currentTier = targetDefines[targetIsa] || targetDefines.hierarchyTarget;
      if (currentTier) {
        const foundIdx = tierItems.findIndex((it) => it.id === currentTier);
        if (foundIdx !== -1) curIdx = foundIdx;
      } else {
        for (let i = tierItems.length - 1; i >= 0; i--) {
          const it = tierItems[i];
          if (targetDefines[it.define] !== false && targetDefines[it.id] !== false) {
            curIdx = i;
            break;
          }
        }
      }
      return curIdx >= reqTierIdx;
    }

    // 2. Check if req is in flag items
    const featItem = flagItems.find((it) => it.id === req);
    if (featItem) {
      if (targetDefines[featItem.define] === false || targetDefines[featItem.id] === false) {
        return false;
      }
      return true;
    }
  }

  // Fallback if metadata not loaded
  if (targetDefines[req] === false) return false;
  return true;
}

export function getCompilerConfigForFlat(isa, defines = {}, scalarSize = 256) {
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[isa] : null;
  const defaultCompiler = { id: "cg142", arch: "x86", base_flags: "-O3", label: "x86-64 GCC" };
  let compilerMeta = (isaMeta && isaMeta.compiler) ? isaMeta.compiler : defaultCompiler;

  // Handle 32-bit architecture override if requested (e.g. ARM32 NEON when __aarch64__ is false)
  if (defines.__aarch64__ === false && compilerMeta.compiler_32) {
    compilerMeta = compilerMeta.compiler_32;
  }

  const compiler = compilerMeta.id || "cg142";
  let baseFlags = (compilerMeta.base_flags || "-O3").replace(/\{simd_width\}/g, String(scalarSize || 256));
  const targetDesc = compilerMeta.label || "GCC / Clang";
  const flags = [baseFlags];

  // Adjust flags based on scalarSize/vectorSize if flags_by_size is provided by compiler metadata
  if (compilerMeta.flags_by_size) {
    const sizeKey = String(scalarSize || 256);
    const archFlags = compilerMeta.flags_by_size[sizeKey] || (scalarSize >= 512 ? compilerMeta.flags_by_size["512"] : "-march=native");
    if (archFlags) flags.push(archFlags);
  }

  // Append feature-specific compiler flags dynamically
  if (isaMeta && isaMeta.features) {
    const fMeta = isaMeta.features;
    const isHierarchy = fMeta.mode === "hierarchy";
    const isMixed = fMeta.mode === "mixed";
    const tierItems = (fMeta.items || []).filter((it) => isHierarchy || (isMixed && it.type === "tier"));
    const flagItems = (fMeta.items || []).filter((it) => it.type === "flag" || (!isHierarchy && !isMixed));

    if (tierItems.length > 0) {
      const currentTier = defines[isa] || defines.hierarchyTarget;
      let activeItem = null;
      if (currentTier) {
        activeItem = tierItems.find((it) => it.id === currentTier);
      }
      if (!activeItem) {
        for (let i = tierItems.length - 1; i >= 0; i--) {
          const it = tierItems[i];
          if (defines[it.define] !== false && defines[it.id] !== false) {
            activeItem = it;
            break;
          }
        }
      }
      if (activeItem && activeItem.flag) {
        flags.push(activeItem.flag);
      }
    }

    if (flagItems.length > 0) {
      for (const it of flagItems) {
        if (it.locked) continue;
        const isActive = (defines[it.define] !== undefined)
          ? Boolean(defines[it.define])
          : ((defines[it.id] !== undefined)
              ? Boolean(defines[it.id])
              : (it.default !== false));

        if (isActive && it.flag) {
          if (it.flag.startsWith("+")) {
            if (defines.__aarch64__ !== false) {
              flags[0] = flags[0] + it.flag;
            }
          } else if (it.flag.startsWith("-march=") && flags[0].includes("-march=")) {
            flags[0] = flags[0].replace(/-march=[^\s]+/, it.flag);
          } else {
            flags.push(it.flag);
          }
        }
      }
    }
  }

  // Handle ARM32 FMA FPU flag
  if (defines.__aarch64__ === false && isa === "neon") {
    const isFma = (defines.__ARM_FEATURE_FMA !== undefined) ? Boolean(defines.__ARM_FEATURE_FMA) : true;
    flags.push(isFma ? "-mfpu=neon-vfpv4" : "-mfpu=neon");
  }

  const options = flags.join(" ").replace(/\s+/g, " ").trim();
  const compilerLabel = `${compilerMeta.label || "Compiler"} (${options})`;

  // Compiler Explorer has no execution host for some targets (RISC-V, ARMv7)
  const canExecute = compilerMeta.execute !== false;

  return { compiler, options, compilerLabel, targetDesc, canExecute };
}


/**
 * Compiler Explorer link of a Flat C code. `execute`: build and run the program (the code must
 * have a `main`), otherwise only compile it (assembly view).
 */
export function buildGodboltUrlForFlat(sourceCode, isa, defines = {}, scalarSize = 256, { execute = false } = {}) {
  const { compiler, options, compilerLabel } = getCompilerConfigForFlat(isa, defines, scalarSize);

  // In Godbolt Rison strings delimited by '...', ! is the escape prefix character:
  // '!' -> '!!'
  // "'" -> "!'"
  const encodeRisonString = (str) => {
    const escaped = String(str).replace(/!/g, "!!").replace(/'/g, "!'");
    return encodeURIComponent(escaped);
  };

  // Compiler Explorer identifier of the C language (the compilers must be C compilers: cg142, ...)
  const lang = "___c";
  return (
    "https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUseDefault:true,lang:'" +
    lang +
    "',source:'" +
    encodeRisonString(sourceCode) +
    "'),l:'5',n:'0',o:'MIPP+Flat+C',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:" +
    compiler +
    ",filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'" + (execute ? "0" : "1") + "',intel:'0',libraryCode:'0',trim:'1'),flagsViewOpen:'1',fontScale:14,fontUseDefault:true,lang:'" +
    lang +
    "',options:'" +
    encodeRisonString(options) +
    "'),l:'5',n:'0',o:'" +
    encodeRisonString(compilerLabel) +
    "',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"
  );
}
