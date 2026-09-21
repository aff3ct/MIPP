/**
 * MIPP API Explorer - Multi-Criteria Filter Engine
 */
import { allPrimitiveNamesDesc, INTRINSIC_INDEX, isIntrinsicPrefixTyped, matchesDatatype } from "./data.js";

function getPrimitiveFromQuery(rest) {
  for (const pName of allPrimitiveNamesDesc) {
    if (rest === pName || rest.startsWith(pName + "_")) {
      return pName;
    }
  }
  return null;
}

function matchesPrototypeQuery(entry, q) {
  if (!q) return true;

  // 1. C++ functional prototypes
  const cppSamples = (entry.prototypes && entry.prototypes.cpp_samples) || entry.cpp_samples;
  if (cppSamples && typeof cppSamples === "object") {
    for (const lmulKey of Object.keys(cppSamples)) {
      const maskMap = cppSamples[lmulKey];
      if (typeof maskMap === "object" && maskMap !== null) {
        for (const proto of Object.values(maskMap)) {
          if (typeof proto === "string" && proto.toLowerCase().includes(q)) return true;
        }
      } else if (typeof maskMap === "string") {
        if (maskMap.toLowerCase().includes(q)) return true;
      }
    }
  }

  // 2. C++ object prototypes
  const cppObjSamples = (entry.prototypes && entry.prototypes.cpp_obj_samples) || entry.cpp_obj_samples;
  if (cppObjSamples && typeof cppObjSamples === "object") {
    for (const proto of Object.values(cppObjSamples)) {
      if (typeof proto === "string" && proto.toLowerCase().includes(q)) return true;
    }
  }

  // 3. Generic & specialized C99 prototypes
  if (entry.prototypes && typeof entry.prototypes === "object") {
    if (entry.prototypes.c99 && entry.prototypes.c99.toLowerCase().includes(q)) return true;
    if (entry.prototypes.cpp && entry.prototypes.cpp.toLowerCase().includes(q)) return true;
    if (entry.prototypes.cpp_obj && entry.prototypes.cpp_obj.toLowerCase().includes(q)) return true;

    if (entry.prototypes.c99_samples && typeof entry.prototypes.c99_samples === "object") {
      for (const lmulKey of Object.keys(entry.prototypes.c99_samples)) {
        const maskMap = entry.prototypes.c99_samples[lmulKey];
        if (typeof maskMap === "object" && maskMap !== null) {
          for (const list of Object.values(maskMap)) {
            if (Array.isArray(list)) {
              for (const proto of list) {
                if (typeof proto === "string" && proto.toLowerCase().includes(q)) return true;
              }
            } else if (typeof list === "string") {
              if (list.toLowerCase().includes(q)) return true;
            }
          }
        }
      }
    }
  }

  return false;
}

export function matchesQuery(entry, qClean, field = "all") {
  if (!qClean || qClean === "mipp" || qClean === "mipp_" || qClean === "mipp::") {
    return { matches: true, matchedIntrinsic: null, matchedC99: null };
  }

  const nameLow = entry.name.toLowerCase();

  // Field: 'name'
  if (field === "name") {
    if (nameLow.includes(qClean)) return { matches: true, matchedIntrinsic: null, matchedC99: null };
    if (qClean.startsWith("mipp_") || qClean.startsWith("mipp::") || qClean.startsWith("mipp_scalar_")) {
      const rest = qClean.replace(/^(mipp_scalar_|mipp_|mipp::)/, "");
      if (nameLow === rest || nameLow.startsWith(rest)) {
        return { matches: true, matchedIntrinsic: null, matchedC99: null };
      }
    }
    return { matches: false, matchedIntrinsic: null, matchedC99: null };
  }

  // Field: 'desc'
  if (field === "desc") {
    const descLow = (entry.description || "").toLowerCase();
    return { matches: descLow.includes(qClean), matchedIntrinsic: null, matchedC99: null };
  }

  // Field: 'proto'
  if (field === "proto") {
    return { matches: matchesPrototypeQuery(entry, qClean), matchedIntrinsic: null, matchedC99: null };
  }

  // Field: 'hw'
  if (field === "hw") {
    if (entry.vendor_intrinsics_reverse_index) {
      for (const intr of entry.vendor_intrinsics_reverse_index) {
        if (intr.toLowerCase().includes(qClean)) {
          return { matches: true, matchedIntrinsic: intr, matchedC99: null };
        }
      }
    }
    if (entry.isa_support) {
      for (const [isa, s] of Object.entries(entry.isa_support)) {
        if (Array.isArray(s.intrinsics)) {
          for (const intr of s.intrinsics) {
            if (intr.toLowerCase().includes(qClean)) {
              return { matches: true, matchedIntrinsic: `${intr} (${isa.toUpperCase()})`, matchedC99: null };
            }
          }
        }
      }
    }
    return { matches: false, matchedIntrinsic: null, matchedC99: null };
  }

  // Field: 'all' (default)
  // 1. Query starts with MIPP namespace or prefix (mipp_, mipp::, mipp_scalar_)
  if (qClean.startsWith("mipp_scalar_") || qClean.startsWith("mipp_") || qClean.startsWith("mipp::")) {
    const rest = qClean.replace(/^(mipp_scalar_|mipp_|mipp::)/, "");

    const prim = getPrimitiveFromQuery(rest);
    if (prim && rest.startsWith(prim + "_")) {
      if (nameLow === prim) {
        const matchedC99 = entry._c99_names ? entry._c99_names.find((fn) => fn === qClean || fn.startsWith(qClean)) : null;
        return { matches: true, matchedIntrinsic: null, matchedC99: matchedC99 || qClean };
      }
      return { matches: false, matchedIntrinsic: null, matchedC99: null };
    }

    if (nameLow === rest || nameLow.startsWith(rest)) {
      return { matches: true, matchedIntrinsic: null, matchedC99: null };
    }

    if (entry._c99_names && entry._c99_names.length > 0) {
      const matched = entry._c99_names.find((fn) => fn === qClean || fn.startsWith(qClean));
      if (matched) {
        return { matches: true, matchedIntrinsic: null, matchedC99: matched };
      }
    }

    return { matches: false, matchedIntrinsic: null, matchedC99: null };
  }

  // 2. Standard search (no mipp_ prefix)
  // Check function name directly
  if (nameLow.includes(qClean)) {
    return { matches: true, matchedIntrinsic: null, matchedC99: null };
  }

  // If user searched for e.g. 'fmsub_float64_m2' or 'add_float64_m1' without 'mipp_'
  const primNoPrefix = getPrimitiveFromQuery(qClean);
  if (primNoPrefix && qClean.startsWith(primNoPrefix + "_")) {
    if (nameLow === primNoPrefix) {
      const matchedC99 = entry._c99_names ? entry._c99_names.find((fn) => fn.includes(qClean)) : null;
      return { matches: true, matchedIntrinsic: null, matchedC99: matchedC99 || qClean };
    }
  }

  // Reverse lookup in vendor intrinsics (only when an intrinsic prefix has been typed)
  if (isIntrinsicPrefixTyped(qClean) && entry.vendor_intrinsics_reverse_index) {
    for (const intr of entry.vendor_intrinsics_reverse_index) {
      if (intr.toLowerCase().startsWith(qClean) || intr.toLowerCase().includes(qClean)) {
        return { matches: true, matchedIntrinsic: intr, matchedC99: null };
      }
    }
  }

  // Category match
  if (entry.category && entry.category.toLowerCase().includes(qClean)) {
    return { matches: true, matchedIntrinsic: null, matchedC99: null };
  }

  // Description or math semantics
  if (entry.description && entry.description.toLowerCase().includes(qClean)) {
    return { matches: true, matchedIntrinsic: null, matchedC99: null };
  }
  if (entry.math_semantics && entry.math_semantics.toLowerCase().includes(qClean)) {
    return { matches: true, matchedIntrinsic: null, matchedC99: null };
  }

  // Prototypes match
  if (matchesPrototypeQuery(entry, qClean)) {
    return { matches: true, matchedIntrinsic: null, matchedC99: null };
  }

  return { matches: false, matchedIntrinsic: null, matchedC99: null };
}

export function filterEntries(data, state) {
  if (!data || !Array.isArray(data)) return [];

  // 1. Strict Filter Rule: If any active filter section has 0 selections, return 0 results
  const selectedExts = state.selectedSimdExts || [];
  if (selectedExts.length === 0) return [];
  if (state.selectedCategories.length === 0) return [];
  if (state.selectedTypes.length === 0) return [];
  if (state.selectedMaskModes.length === 0) return [];
  if (state.selectedLevels.length === 0) return [];

  let qClean = (state.query || "").trim().toLowerCase();
  qClean = qClean.replace(/[\(\);]+$/, "").trim();
  const field = state.searchField || "all";

  const results = [];

  for (const entry of data) {
    // A. Category Filter
    if (!state.selectedCategories.includes(entry.category)) {
      continue;
    }

    // B. Datatypes Filter (At least one active selected datatype must match single or compound types)
    const entryDts = entry.datatypes || [];
    const hasMatchingType = entryDts.some((dt) => matchesDatatype(dt, state.selectedTypes));
    if (!hasMatchingType) {
      continue;
    }

    // C. Masking Modes Filter
    if (state.flavor === "cpp_obj") {
      if (!state.selectedMaskModes.includes("unmasked")) {
        continue;
      }
    } else {
      const maskSupport = entry.mask_support || {};
      const hasMatchingMask = state.selectedMaskModes.some(
        (m) => m === "unmasked" || maskSupport[m]
      );
      if (!hasMatchingMask) {
        continue;
      }
    }

    // D. SIMD Extensions & Guaranteed Acceleration Levels Filter (Union ∪ vs Intersection ∩)
    const effectiveTypes = entryDts.filter((dt) => matchesDatatype(dt, state.selectedTypes));
    const extMatches = selectedExts.map((ext) => {
      const sup = entry.isa_support ? entry.isa_support[ext] : null;
      if (!sup) return false;
      
      const byDt = sup.by_datatype || {};
      const levelsToCheck = effectiveTypes.length > 0
        ? effectiveTypes.map((dt) => byDt[dt] !== undefined ? byDt[dt] : sup.overall_level)
        : [sup.overall_level];
      
      return levelsToCheck.some((lvl) => state.selectedLevels.includes(lvl));
    });

    if (state.intersectionMode) {
      // Intersection Mode (∩): Every selected SIMD extension must support the operation at one of the selected levels
      if (!extMatches.every(Boolean)) continue;
    } else {
      // Union Mode (∪): At least one selected SIMD extension must support the operation at one of the selected levels
      if (!extMatches.some(Boolean)) continue;
    }

    // E. Search Query Filter
    const searchRes = matchesQuery(entry, qClean, field);
    if (!searchRes.matches) {
      continue;
    }

    results.push({
      entry,
      matchedIntrinsic: searchRes.matchedIntrinsic,
      matchedC99: searchRes.matchedC99,
    });
  }

  return results;
}
