/**
 * MIPP API Explorer - tooltip of a vendor intrinsic in the code of the Algorithm modal.
 * Shows the ISA, the extension it needs (from the conditions of the MIPP functions that use it),
 * the MIPP functions that use it (they open in the modal) and a link to the official documentation.
 */
import { escapeHtml } from "../explorer.config.js";
import { SIMD_EXT_DISPLAY_NAMES, apiMetadata } from "../data.js";
import { getLoadedSources, parseCName } from "../algo_source.js";
import { tooltipWanted, openTooltip, hideTooltip } from "../syntax.js";

// RVV: no anchor per intrinsic in the official documentation, one page per family
const RVV_DOC = "https://github.com/riscv-non-isa/rvv-intrinsic-doc/blob/main/auto-generated/intrinsic_funcs/";
const RVV_FAMILIES = [
  [/^v(l|s)seg|^v(l|s)(s|ux|ox)seg/, "01_vector_loads_and_stores_segment_intrinsics.adoc"],
  [/^v(le|se|lse|sse|luxei|loxei|suxei|soxei|lm|sm)\d*/, "00_vector_loads_and_stores_intrinsics.adoc"],
  [/^v(sadd|ssub|aadd|asub|smul|ssrl|ssra|nclip)/, "03_vector_fixed-point_arithmetic_intrinsics.adoc"],
  [/^v(f|mf)/, "04_vector_floating-point_intrinsics.adoc"],
  [/^v(w?red|fred|fwred)/, "05_vector_reduction_operations.adoc"],
  [/^v(mand|mnand|mandn|mor|mnor|morn|mxor|mxnor|mnot|mmv|mclr|mset|cpop|first|msbf|msif|msof|iota|id_)/, "06_vector_mask_intrinsics.adoc"],
  [/^v(slide|rgather|compress|mv_x|mv_s)/, "07_vector_permutation_intrinsics.adoc"],
  [/^v(reinterpret|lmul_|undefined|set_|get_|create|setvl)/, "08_miscellaneous_vector_utility_intrinsics.adoc"],
  [/^v/, "02_vector_integer_arithmetic_intrinsics.adoc"],
];

/**
 * ACLE name of an SVE intrinsic as Arm's documentation indexes it: the suffixes that overloading
 * can drop are in brackets (svadd_f32_z -> svadd[_f32]_z, svdup_f32 -> svdup[_n]_f32,
 * svreinterpret_f32_u32 -> svreinterpret_f32[_u32]).
 */
function sveDocName(name) {
  if (/^sv(ptrue|ptest|cnt[bhwd]|pfirst|pnext)/.test(name)) return name;
  if (name === "svpfalse") return "svpfalse[_b]";
  const [base, ...tokens] = name.split("_");
  const pred = /^[zmx]$/.test(tokens[tokens.length - 1]) ? tokens.pop() : null;
  const isType = (t) => /^([suf]\d+|b\d*)$/.test(t);
  const hasN = tokens.includes("n");
  const types = tokens.filter(isType);
  const other = tokens.filter((t) => t !== "n" && !isType(t));
  let out = [base, ...other].join("_");
  if (base === "svdup" && types.length === 1) out += `[_n]_${types[0]}`;
  else if (base === "svwhilelt" || base === "svwhilele") out += types.length === 2 ? `_${types[0]}[_${types[1]}]` : types.map((t) => `_${t}`).join("");
  else if (hasN) out += `[_n${types.map((t) => `_${t}`).join("")}]`;
  else if (types.length === 2) out += `_${types[0]}[_${types[1]}]`;
  else if (types.length === 1) out += `[_${types[0]}]`;
  else if (pred) out += "[_b]"; // predicate logic: svand_z -> svand[_b]_z
  return out + (pred ? `_${pred}` : "");
}

/** Official documentation of an intrinsic: { url, label } or null. */
export function intrinsicDocLink(name, isa) {
  if (["sse", "avx", "avx512"].includes(isa)) {
    return { url: `https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=${encodeURIComponent(name)}`, label: "Intel Intrinsics Guide" };
  }
  if (isa === "neon" || isa === "sve") {
    const docName = isa === "sve" ? sveDocName(name) : name;
    return { url: `https://developer.arm.com/architectures/instruction-sets/intrinsics/${encodeURIComponent(docName)}`, label: "Arm Intrinsics" };
  }
  if (isa === "rvv") {
    const short = name.replace(/^__riscv_/, "");
    const fam = RVV_FAMILIES.find(([re]) => re.test(short));
    return { url: RVV_DOC + (fam ? fam[1] : ""), label: "RVV Intrinsics (family page)" };
  }
  return null;
}

/** Is this name a vendor intrinsic of this ISA? */
export function isIntrinsicName(name, isa) {
  if (["sse", "avx", "avx512"].includes(isa)) return /^_mm\d*_\w+$|^_(cvt|bit|pdep|pext|lzcnt|tzcnt)\w*$/.test(name);
  if (isa === "neon") return /^v[a-z0-9]+(q)?_[a-z0-9_]+$/.test(name);
  if (isa === "sve") return /^sv[a-z0-9_]+$/.test(name);
  if (isa === "rvv") return /^__riscv_\w+$/.test(name);
  return false;
}

const usageCache = new Map(); // isa -> Map(intrinsic -> [{cName, cond}])

/** MIPP functions of the ISA that call an intrinsic, with the conditions of these definitions. */
function usageOf(name, isa) {
  if (!usageCache.has(isa)) {
    const sources = getLoadedSources(isa);
    if (!sources) return null;
    const index = new Map();
    const table = sources.find((t) => t.isa === isa);
    for (const [cName, variants] of Object.entries(table.symbols)) {
      for (const v of variants) {
        if (v.kind !== "func") continue;
        for (const m of v.code.matchAll(/\b([A-Za-z_]\w*)\s*\(/g)) {
          if (!isIntrinsicName(m[1], isa)) continue;
          if (!index.has(m[1])) index.set(m[1], []);
          const list = index.get(m[1]);
          if (!list.some((x) => x.cName === cName && x.cond.join() === v.cond.join())) list.push({ cName, cond: v.cond });
        }
      }
    }
    usageCache.set(isa, index);
  }
  return usageCache.get(isa).get(name) || [];
}

/**
 * Extensions the intrinsic needs (e.g. AVX2, BW): the feature macros tested positively by the
 * conditions of every definition that uses it. On a hierarchy (SSE), only the highest one.
 */
function requiredFeatures(uses, isa) {
  const fMeta = (apiMetadata.isas && apiMetadata.isas[isa] && apiMetadata.isas[isa].features) || {};
  const items = (fMeta.items || []).filter((it) => !it.locked);
  if (!uses.length || !items.length) return [];
  let common = null;
  for (const u of uses) {
    const found = new Set();
    for (const c of u.cond) {
      // positive macros of the condition only: defined(__AVX2__), not !defined(__AVX2__)
      for (const m of c.matchAll(/(!\s*)?defined\s*\(\s*(\w+)\s*\)/g)) if (!m[1]) found.add(m[2]);
    }
    common = common ? new Set([...common].filter((d) => found.has(d))) : found;
  }
  const req = items.filter((it) => common.has(it.define));
  if (fMeta.mode === "hierarchy" && req.length) return [req[req.length - 1].label];
  return req.map((it) => it.label);
}

let navigate = null;
/** Called with {func, isa, dt, mask, lmul} when a MIPP function of the tooltip is clicked. */
export function setIntrinsicNavigate(fn) { navigate = fn; }

/** Opens the tooltip of an intrinsic; `pinned`: kept open by a click. */
export function showIntrinsicTooltip(el, pinned = false) {
  if (!tooltipWanted(el, pinned)) return;
  const name = el.getAttribute("data-intrinsic");
  const isa = el.getAttribute("data-isa");
  const label = (SIMD_EXT_DISPLAY_NAMES[isa] || isa.toUpperCase());
  const uses = usageOf(name, isa) || [];
  const features = requiredFeatures(uses, isa);
  const doc = intrinsicDocLink(name, isa);

  // one line per MIPP function (all datatypes / LMULs / variants of this function together)
  const byFunc = new Map();
  for (const u of uses) {
    const p = parseCName(u.cName);
    if (!p) continue;
    const key = p.func + (p.mask === "unmasked" ? "" : `_${p.mask}`);
    if (!byFunc.has(key)) byFunc.set(key, { p, dts: new Set() });
    byFunc.get(key).dts.add(p.dt.replace(",", "→"));
  }
  const funcs = [...byFunc.entries()].sort((a, b) => a[0].localeCompare(b[0]));
  const shown = funcs.slice(0, 12);
  const usedBy = shown.map(([key, { p, dts }]) => `
    <button type="button" class="mipp-intrinsic-use" data-nav='${escapeHtml(JSON.stringify(p))}' title="Open mipp::${escapeHtml(p.func)} (${escapeHtml(p.dt)})">${escapeHtml(key)}</button><span class="mipp-intrinsic-dts">${escapeHtml([...dts].slice(0, 4).join(", "))}${dts.size > 4 ? "…" : ""}</span>`).join("");

  const t = document.createElement("div");
  t.className = "mipp-macro-tooltip mipp-intrinsic-tooltip";
  t.innerHTML = `
    <div class="mipp-macro-tooltip-header">
      <span class="mipp-macro-tooltip-title"><code>${escapeHtml(name)}</code> <span class="mipp-intrinsic-isa">${escapeHtml(label)}${features.length ? ` · requires ${escapeHtml(features.join(", "))}` : ""}</span></span>
      <button class="mipp-macro-tooltip-close" title="Close">×</button>
    </div>
    <div class="mipp-intrinsic-body">
      ${funcs.length ? `<div class="mipp-intrinsic-label">Used by ${funcs.length} MIPP function${funcs.length > 1 ? "s" : ""} on ${escapeHtml(label)}${funcs.length > shown.length ? ` (first ${shown.length})` : ""}:</div><div class="mipp-intrinsic-uses">${usedBy}</div>` : ""}
      ${doc ? `<a class="mipp-intrinsic-doc" href="${doc.url}" target="_blank" rel="noopener noreferrer">${escapeHtml(doc.label)} ↗</a>` : ""}
    </div>`;
  openTooltip(t, el, pinned, 560);

  t.querySelectorAll(".mipp-intrinsic-use").forEach((b) => b.addEventListener("click", (ev) => {
    ev.stopPropagation();
    const p = JSON.parse(b.getAttribute("data-nav"));
    hideTooltip();
    if (navigate) navigate(p);
  }));
}
