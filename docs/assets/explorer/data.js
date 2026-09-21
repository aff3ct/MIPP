/**
 * MIPP API Explorer - Data Fetching & Dynamic Indexing
 */

export let apiData = [];
export let apiMetadata = {
  isas: {},
  datatypes: {},
  datatype_groups: {},
  mask_modes: {},
  levels: {},
  categories: [],
  primitives: []
};

export let ALL_SIMD_EXTS = ["sse", "avx", "avx512", "neon", "sve", "rvv"];

export let SIMD_EXT_DISPLAY_NAMES = {
  sse: "SSE",
  avx: "AVX",
  avx512: "AVX-512",
  neon: "NEON",
  sve: "SVE",
  rvv: "RVV"
};

export let SIMD_EXT_FEATURE_DEFINES = {};

export let ALL_CATEGORIES = [
  "arithmetic",
  "comparison",
  "converts",
  "load",
  "logic",
  "math",
  "reduction",
  "reinterpret",
  "selection",
  "store"
];
export let ALL_LEVELS = [0, 1, 2, 3];
export let LEVEL_DESCRIPTIONS = {
  0: "Native Hardware",
  1: "Dedicated Emulation",
  2: "Generic Emulation",
  3: "Scalar Fallback",
};

export function matchesDatatype(dt, selectedTypes) {
  if (!dt || !selectedTypes || selectedTypes.length === 0) return false;
  if (selectedTypes.includes(dt)) return true;
  if (dt.includes(",")) {
    return dt.split(",").some((p) => selectedTypes.includes(p.trim()));
  }
  return false;
}

export let ALL_DATATYPES = [
  { id: "float64", label: "float64", group: "floats" },
  { id: "float32", label: "float32", group: "floats" },
  { id: "int64", label: "int64", group: "signed" },
  { id: "int32", label: "int32", group: "signed" },
  { id: "int16", label: "int16", group: "signed" },
  { id: "int8", label: "int8", group: "signed" },
  { id: "uint64", label: "uint64", group: "unsigned" },
  { id: "uint32", label: "uint32", group: "unsigned" },
  { id: "uint16", label: "uint16", group: "unsigned" },
  { id: "uint8", label: "uint8", group: "unsigned" },
];

export let DATATYPE_GROUPS = {
  floats:   { id: "floats",   label: "Floats",   types: ["float64", "float32"] },
  signed:   { id: "signed",   label: "Signed",   types: ["int64", "int32", "int16", "int8"] },
  unsigned: { id: "unsigned", label: "Unsigned", types: ["uint64", "uint32", "uint16", "uint8"] },
};

export let ALL_MASK_MODES = ["unmasked", "mask", "maskz", "masks"];
export let MASK_MODES_INFO = {
  unmasked: { id: "unmasked", label: "unmasked", badge_class: "mask-unmasked", description: "Unpredicated standard vector operation", cpp_obj_support: true },
  mask:     { id: "mask",     label: "mask",     badge_class: "mask-mask",     description: "Predicated execution with blend / merge preservation", cpp_obj_support: false },
  maskz:    { id: "maskz",    label: "maskz",    badge_class: "mask-maskz",    description: "Predicated execution with zeroing for false lanes", cpp_obj_support: false },
  masks:    { id: "masks",    label: "masks",    badge_class: "mask-masks",    description: "Predicated execution with explicit fallback source register", cpp_obj_support: false },
};

export let DT_INFO = {};
export let allPrimitiveNamesDesc = [];

// Dynamically extracted intrinsic prefixes from JSON
export let DYNAMIC_INTRINSIC_PREFIXES = [];

export function isIntrinsicPrefixTyped(q) {
  if (!q || q.length < 2) return false;
  const qLow = q.trim().toLowerCase();
  for (const p of DYNAMIC_INTRINSIC_PREFIXES) {
    if (p === "v") {
      // For single letter 'v', require at least 3 characters (e.g. vadd, vbsl, vneg, vfmsub)
      if (qLow.startsWith("v") && qLow.length >= 3) return true;
    } else {
      if (qLow.startsWith(p) || p.startsWith(qLow)) return true;
    }
  }
  return false;
}

// Reverse Intrinsic Index: intrinsic_name_lower -> Set of primitive names
export const INTRINSIC_INDEX = new Map();

export async function loadApiData() {
  if (apiData.length > 0) return apiData;

  const candidatePaths = [
    "../../assets/data/mipp_api_index.json",
    "../assets/data/mipp_api_index.json",
    "assets/data/mipp_api_index.json",
    "/assets/data/mipp_api_index.json",
  ];

  for (const path of candidatePaths) {
    try {
      const fetchUrl = path + (path.includes("?") ? "&" : "?") + "v=" + Date.now();
      const resp = await fetch(fetchUrl, { cache: "no-cache" });
      if (resp.ok) {
        const contentLength = resp.headers.get("content-length");
        const totalBytes = contentLength ? parseInt(contentLength, 10) : 0;
        if (resp.body && window.ReadableStream && totalBytes > 0) {
          const reader = resp.body.getReader();
          let loadedBytes = 0;
          const chunks = [];
          while (true) {
            const { done, value } = await reader.read();
            if (done) break;
            chunks.push(value);
            loadedBytes += value.length;
            const pct = Math.min(100, Math.round((loadedBytes / totalBytes) * 100));
            const fillEl = document.getElementById("mipp-load-progress-fill");
            const textEl = document.getElementById("mipp-load-progress-text");
            if (fillEl) fillEl.style.width = `${pct}%`;
            if (textEl) {
              textEl.textContent = `${pct}% (${(loadedBytes / (1024 * 1024)).toFixed(1)} MB / ${(totalBytes / (1024 * 1024)).toFixed(1)} MB)`;
            }
          }
          const allChunks = new Uint8Array(loadedBytes);
          let pos = 0;
          for (const chunk of chunks) {
            allChunks.set(chunk, pos);
            pos += chunk.length;
          }
          const text = new TextDecoder("utf-8").decode(allChunks);
          const rawObj = JSON.parse(text);
          if (Array.isArray(rawObj)) {
            apiData = rawObj;
            apiMetadata = { primitives: rawObj, isas: {}, datatypes: {}, levels: {} };
          } else {
            apiData = rawObj.primitives || [];
            apiMetadata = rawObj;
          }
          initApiDataIndexes(apiData, apiMetadata);
          return apiData;
        } else {
          const rawObj = await resp.json();
          if (Array.isArray(rawObj)) {
            apiData = rawObj;
            apiMetadata = { primitives: rawObj, isas: {}, datatypes: {}, levels: {} };
          } else {
            apiData = rawObj.primitives || [];
            apiMetadata = rawObj;
          }
          initApiDataIndexes(apiData, apiMetadata);
          return apiData;
        }
      }
    } catch (err) {
      // Try next candidate
    }
  }
  throw new Error("Unable to load mipp_api_index.json from candidate paths.");
}

export function initApiDataIndexes(data, metadata = null) {
  const rawExts = metadata && (metadata.simd_exts || metadata.isas);
  if (rawExts && Object.keys(rawExts).length > 0) {
    // Exception for the explorer UI: do not display the "scalar" pseudo-extension
    ALL_SIMD_EXTS = Object.keys(rawExts).filter((id) => id.toLowerCase() !== "scalar");
    SIMD_EXT_DISPLAY_NAMES = {};
    SIMD_EXT_FEATURE_DEFINES = {};
    for (const [id, meta] of Object.entries(rawExts)) {
      if (id.toLowerCase() === "scalar") continue;
      SIMD_EXT_DISPLAY_NAMES[id] = meta.label || id.toUpperCase();
      SIMD_EXT_FEATURE_DEFINES[id] = meta.features || [];
    }
  }

  if (metadata && metadata.datatypes && Object.keys(metadata.datatypes).length > 0) {
    ALL_DATATYPES = Object.entries(metadata.datatypes).map(([id, info]) => ({
      id,
      label: info.label || id,
      group: info.group || "general"
    }));
    DT_INFO = metadata.datatypes;
  }

  if (metadata && metadata.datatype_groups && Object.keys(metadata.datatype_groups).length > 0) {
    DATATYPE_GROUPS = metadata.datatype_groups;
  }

  if (metadata && metadata.mask_modes && Object.keys(metadata.mask_modes).length > 0) {
    ALL_MASK_MODES = Object.keys(metadata.mask_modes);
    MASK_MODES_INFO = metadata.mask_modes;
  }

  if (metadata && metadata.levels && Object.keys(metadata.levels).length > 0) {
    LEVEL_DESCRIPTIONS = {};
    for (const [lvl, info] of Object.entries(metadata.levels)) {
      LEVEL_DESCRIPTIONS[lvl] = info.name;
    }
  }

  if (metadata && metadata.categories && Array.isArray(metadata.categories) && metadata.categories.length > 0) {
    ALL_CATEGORIES = [...metadata.categories];
  } else if (data && Array.isArray(data)) {
    ALL_CATEGORIES = Array.from(new Set(data.map((e) => e.category).filter(Boolean))).sort();
  }

  if (!data || !Array.isArray(data)) return;
  allPrimitiveNamesDesc = data.map((e) => e.name.toLowerCase()).sort((a, b) => b.length - a.length);

  // Dynamically extract intrinsic prefixes from metadata and all entry intrinsics
  const prefixSet = new Set();

  if (metadata && metadata.isas) {
    for (const [isa, meta] of Object.entries(metadata.isas)) {
      if (meta.datatypes) {
        for (const dt of Object.values(meta.datatypes)) {
          if (dt.reg) {
            const mX86 = dt.reg.match(/^__m(\d+)/);
            if (mX86) {
              const bits = mX86[1];
              if (bits === "128") {
                prefixSet.add("_mm_");
                prefixSet.add("_mm");
              } else {
                prefixSet.add(`_mm${bits}_`);
                prefixSet.add(`_mm${bits}`);
                prefixSet.add("_mm");
              }
            }
            if (dt.reg.startsWith("sv")) {
              prefixSet.add("sv_");
              prefixSet.add("sv");
            }
          }
        }
      }
      if (meta.define) {
        const mRiscv = meta.define.match(/__(riscv)_[a-z0-9_]+/);
        if (mRiscv) {
          prefixSet.add(`__${mRiscv[1]}_`);
          prefixSet.add(`__${mRiscv[1]}`);
        }
      }
    }
  }

  // Build Reverse Hardware Intrinsics & C99 Names Index
  INTRINSIC_INDEX.clear();
  for (const entry of data) {
    if (!entry._c99_names) {
      const set = new Set();
      if (entry.prototypes && entry.prototypes.c99) {
        const m = entry.prototypes.c99.match(/\b(mipp_[a-zA-Z0-9_]+)\(/);
        if (m) set.add(m[1].toLowerCase());
      }
      if (entry.prototypes && entry.prototypes.c99_samples) {
        for (const lmul in entry.prototypes.c99_samples) {
          const lmulObj = entry.prototypes.c99_samples[lmul];
          if (!lmulObj || typeof lmulObj !== "object") continue;
          for (const mask in lmulObj) {
            const protos = lmulObj[mask];
            if (!Array.isArray(protos)) continue;
            for (const p of protos) {
              const m = p.match(/\b(mipp_[a-zA-Z0-9_]+)\(/);
              if (m) set.add(m[1].toLowerCase());
            }
          }
        }
      }
      entry._c99_names = Array.from(set);
    }

    // Populate INTRINSIC_INDEX and dynamic prefixes from vendor_intrinsics_reverse_index
    if (Array.isArray(entry.vendor_intrinsics_reverse_index)) {
      for (const intr of entry.vendor_intrinsics_reverse_index) {
        const clean = intr.trim().toLowerCase();
        if (clean) {
          if (!INTRINSIC_INDEX.has(clean)) {
            INTRINSIC_INDEX.set(clean, new Set());
          }
          INTRINSIC_INDEX.get(clean).add(entry.name);

          // Extract prefix from intrinsic name dynamically
          if (clean.startsWith("__")) {
            const m = clean.match(/^(__[a-z0-9]+_)/);
            if (m) {
              prefixSet.add(m[1]);
              prefixSet.add(m[1].slice(0, -1));
            }
          } else if (clean.startsWith("_")) {
            const m = clean.match(/^(_[a-z0-9]+_)/);
            if (m) {
              prefixSet.add(m[1]);
              prefixSet.add(m[1].slice(0, -1));
              const base = m[1].match(/^(_[a-z]+)/);
              if (base) prefixSet.add(base[1]);
            }
          } else if (clean.startsWith("sv")) {
            prefixSet.add("sv");
            prefixSet.add("sv_");
          } else if (clean.startsWith("v")) {
            const m = clean.match(/^(v[a-z0-9]+?q_)/);
            if (m) prefixSet.add(m[1]);
            prefixSet.add("v");
          }
        }
      }
    }


    if (entry.isa_support) {
      for (const [isa, support] of Object.entries(entry.isa_support)) {
        if (support.intrinsics) {
          for (const intr of support.intrinsics) {
            const clean = intr.trim().toLowerCase();
            if (clean) {
              if (!INTRINSIC_INDEX.has(clean)) {
                INTRINSIC_INDEX.set(clean, new Set());
              }
              INTRINSIC_INDEX.get(clean).add(entry.name);
            }
          }
        }
      }
    }
  }

  DYNAMIC_INTRINSIC_PREFIXES = Array.from(prefixSet).sort((a, b) => b.length - a.length);
}
