/**
 * MIPP API Explorer - "Algorithm" modal.
 * Shows the code of one function for one ISA, datatype, mask variant, LMUL and set of compiler
 * flags, taken from the generated headers (algo_source.js): the Abstract C++ view (C++ Functional
 * API) and the Flat C view (self-contained, runs on Compiler Explorer).
 */
import { escapeHtml, ICON_COPY, ICON_GRIP, ICON_GODBOLT, ICON_RUN, ICON_LINK, ICON_WARNING, ICON_INFO, ICON_CONTEXT, ICON_CLOCK } from "../explorer.config.js";
import { highlightCpp } from "../syntax.js";
import { SIMD_EXT_DISPLAY_NAMES, ALL_MASK_MODES, LEVEL_DESCRIPTIONS, apiMetadata, apiData, maskSupportOf, isLmulUndefined, undefinedLmulNotice, flagKey } from "../data.js";
import { state } from "../state.js";
import { renderFormSelector } from "./card.js";
import { boxSizeStyle, boxResizeHandles } from "./box_layout.js";
import { getCompilerConfigForFlat, buildGodboltUrlForFlat } from "../codegen.js";
import { renderCallGraph } from "./call_graph.js";
import { getLoadedSources, buildAbstractCode, buildFlatCode, parseCName, immChoices, algoLoadProgress } from "../algo_source.js";

export function getAllModalIsas() {
  return Object.keys(apiMetadata.isas || {});
}

/** ISA shown by the modal (the one of modalData, or the first ISA). */
export function algoModalIsa(modalData) {
  const all = getAllModalIsas();
  const raw = modalData && (modalData.isa || modalData.simdExt);
  return all.includes(raw) ? raw : (all[0] || "");
}

/**
 * ISAs of the Compare view, in the order of their boxes: the ones chosen by the user (picker,
 * drag and drop), else the ISA of the modal followed by two others.
 */
export function algoCompareIsas(modalData) {
  const all = getAllModalIsas();
  const chosen = [...new Set((modalData && modalData.compareIsas) || [])].filter((i) => all.includes(i));
  if (chosen.length) return chosen;
  const current = algoModalIsa(modalData);
  return [current, ...["sse", "neon", "rvv", "avx", "sve"].filter((i) => i !== current && all.includes(i))].slice(0, 3);
}

const DOCS = "../user/";
const ISA_LABEL = () => ({ ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" });
const levelBadge = (lvl, title) => `<span class="mipp-isa-badge lvl-${lvl === null || lvl === undefined ? "na" : lvl}" title="${escapeHtml(title || "")}">${lvl === null || lvl === undefined ? "–" : `L${lvl}`}</span>`;

/** One or two lines on the LMUL and the mask variant of the shown code, with links to the docs. */
function contextNotes(isa, lmul, mask, maskBySelect) {
  const notes = [];
  const l = String(lmul);
  const name = ISA_LABEL()[isa] || isa.toUpperCase();
  if (l === "-2") {
    const how = {
      avx: "a register of the narrower ISA (an SSE register for AVX)", avx512: "a register of the narrower ISA (an AVX register for AVX-512)",
      rvv: "a native fractional register group (mf2)", scalar: "an array of N/2 elements",
    }[isa] || "the lower half of a full register (the upper lanes are ignored)";
    notes.push(`<strong>LMUL 1/2</strong> (half-vector, <code>d2</code>): on ${escapeHtml(name)}, ${how}. <a href="${DOCS}vector_types_and_lmul/" target="_blank">Vector types &amp; LMUL</a>`);
  } else if (l !== "1") {
    notes.push(isa === "rvv"
      ? `<strong>LMUL ${l}</strong>: one group of ${l} hardware registers (RVV register grouping), handled by the instructions themselves. <a href="${DOCS}vector_types_and_lmul/" target="_blank">Vector types &amp; LMUL</a>`
      : `<strong>LMUL ${l}</strong>: two halves (<code>lo</code>, <code>hi</code>) processed one after the other by the LMUL ${Number(l) / 2} function. <a href="${DOCS}vector_types_and_lmul/" target="_blank">Vector types &amp; LMUL</a>`);
  }
  const maskText = {
    mask: "<strong>mask</strong> (merge): the inactive lanes keep the value of the first operand",
    maskz: "<strong>maskz</strong> (zeroing): the inactive lanes are set to zero",
    masks: "<strong>masks</strong> (source): the inactive lanes are taken from <code>src</code>",
  }[mask];
  if (maskText) {
    const how = maskBySelect
      ? "Here the operation is computed on all the lanes, then a <code>select</code> keeps the active ones"
      : "Here the target applies the mask itself (predicated instruction or masked memory access)";
    notes.push(`${maskText}. ${how}. <a href="${DOCS}masking_semantics/" target="_blank">Masking semantics</a>`);
  }
  return notes;
}

/** Navigation target of a function of the call tree (null when it is not a public function). */
function navTarget(cName) {
  const p = parseCName(cName);
  if (!p) return null;
  const entry = apiData.find((e) => e.name === p.func);
  if (!entry) return null;
  const dts = entry.datatypes || [];
  const dt = dts.includes(p.dt) ? p.dt : (dts.includes(p.dt.split(",")[0]) ? p.dt.split(",")[0] : null);
  return dt ? { ...p, dt } : null;
}

function treeLabel(cName) {
  const p = parseCName(cName);
  if (!p) return escapeHtml(cName);
  const lm = p.lmul === "1" ? "" : (p.lmul === "-2" ? " · d2" : ` · m${p.lmul}`);
  const v = p.mask === "unmasked" ? "" : `_${p.mask}`;
  return `${escapeHtml(p.func)}${v}&lt;${escapeHtml(p.dt.replace(",", ", "))}&gt;${lm}`;
}

// ---------------------------------------------------------------------------------------------
// Loading of the MIPP source code (the header tables of an ISA, 14 to 28 MB each)
// ---------------------------------------------------------------------------------------------
const MB = (n) => (n / (1024 * 1024)).toFixed(1);

function progressState(isa) {
  const p = algoLoadProgress(isa);
  if (!p || !p.total) return { pct: null, text: "" };
  const pct = Math.min(100, Math.floor((100 * p.loaded) / p.total));
  return { pct, text: `${pct}% (${MB(p.loaded)} MB / ${MB(p.total)} MB)` };
}

/** Loading note with a progress bar, updated in place by updateAlgoProgress. */
function loadingNote(isa, compact = false) {
  const names = { ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" };
  const label = (i) => (names[i] || i.toUpperCase()).replace("ARM ", "");
  const p = algoLoadProgress(isa);
  const others = p ? p.tables.filter((t) => t !== isa && t !== "interface").map(label) : [];
  const what = compact ? "Loading…" : `Loading the MIPP source code of ${label(isa)}${others.length ? ` (with the code of ${others.length > 1 ? `${others.slice(0, -1).join(", ")} and ${others[others.length - 1]}` : others[0]} that it includes)` : ""}…`;
  const { pct, text } = progressState(isa);
  return `<div class="mipp-algo-note mipp-algo-loading" data-algo-progress="${escapeHtml(isa)}">
      <span class="mipp-algo-note-icon">${ICON_CLOCK}</span>
      <div class="mipp-algo-loading-body">
        <span>${escapeHtml(what)}</span>
        <div class="mipp-loading-bar-wrapper" role="progressbar" aria-valuemin="0" aria-valuemax="100"${pct === null ? "" : ` aria-valuenow="${pct}"`}>
          <div class="mipp-loading-bar-fill${pct === null ? " mipp-loading-bar-fill--indeterminate" : ""}" data-algo-progress-fill${pct === null ? "" : ` style="width: ${pct}%"`}></div>
        </div>
        <span class="mipp-algo-loading-text" data-algo-progress-text>${escapeHtml(text)}</span>
      </div>
    </div>`;
}

/** Updates the progress bars of the modal (called when bytes of a table arrive). */
export function updateAlgoProgress(root) {
  if (!root) return;
  root.querySelectorAll("[data-algo-progress]").forEach((el) => {
    const { pct, text } = progressState(el.getAttribute("data-algo-progress"));
    const fill = el.querySelector("[data-algo-progress-fill]");
    const bar = el.querySelector('[role="progressbar"]');
    const label = el.querySelector("[data-algo-progress-text]");
    if (pct === null) return;
    if (fill) {
      fill.classList.remove("mipp-loading-bar-fill--indeterminate");
      fill.style.width = `${pct}%`;
    }
    if (bar) bar.setAttribute("aria-valuenow", String(pct));
    if (label) label.textContent = text;
  });
}

// ---------------------------------------------------------------------------------------------
// Path of the functions opened from one another (history), as a breadcrumb
// ---------------------------------------------------------------------------------------------
const MASK_WORDS = { unmasked: "unmasked", mask: "merge-masked", maskz: "zero-masked", masks: "source-masked" };
const lmulWord = (l) => (String(l) === "-2" ? "1/2" : String(l));

/**
 * Title of the modal: the path of the functions opened from one another, the current one last
 * (`mipp::name`), each step with the settings that differ from the step before (ISA, datatype,
 * mask variant, LMUL), all of them in its title. A long path keeps the first step and the last
 * three. Without history: the name of the function only.
 */
function renderTitlePath(modalData) {
  const history = modalData.history || [];
  const current = `<code>mipp::${escapeHtml(modalData.entry.form_of || modalData.entry.name)}</code>`;
  if (!history.length) return current;
  const names = { ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" };
  const isaWord = (i) => (names[i] || String(i).toUpperCase()).replace("ARM ", "");
  const steps = [...history, modalData];
  let prev = null;
  const items = steps.map((md, i) => {
    const r = md.resolved || { isa: md.isa || md.simdExt, dt: md.dt, mask: md.mask || "unmasked", lmul: md.lmul || "1" };
    const name = md.entry.form_of || md.entry.name;
    const changed = [];
    if (prev) {
      if (r.isa !== prev.isa) changed.push(isaWord(r.isa));
      if (r.dt !== prev.dt) changed.push(String(r.dt).replace(",", " → "));
      if (r.mask !== prev.mask) changed.push(MASK_WORDS[r.mask] || r.mask);
      if (String(r.lmul) !== String(prev.lmul)) changed.push(`LMUL ${lmulWord(r.lmul)}`);
    }
    prev = r;
    const title = `mipp::${name}<${r.dt}> · ${isaWord(r.isa)} · ${MASK_WORDS[r.mask] || r.mask} · LMUL ${lmulWord(r.lmul)}`;
    const tags = changed.length ? `<span class="mipp-algo-crumb-tags">${escapeHtml(changed.join(" · "))}</span>` : "";
    if (i === steps.length - 1) {
      return { name, html: `<span class="mipp-algo-crumb-current" title="${escapeHtml(title)}">${current}${tags}</span>` };
    }
    return { name, html: `<button type="button" class="mipp-algo-crumb" data-algo-crumb="${i}" title="Back to ${escapeHtml(title)}">${escapeHtml(name)}${tags}</button>` };
  });
  const shown = items.length > 5
    ? [items[0], { html: `<span class="mipp-algo-crumb-more" title="${escapeHtml(items.slice(1, -3).map((it) => it.name).join(" › "))}">…</span>` }, ...items.slice(-3)]
    : items;
  return shown.map((it) => it.html).join('<span class="mipp-algo-crumb-sep" aria-hidden="true">›</span>');
}

// What the body of a function of the call tree / graph is: [label, explanation]
const KINDS = {
  native: ["native", "Instructions of the ISA"],
  dedicated: ["dedicated emulation", "A sequence of instructions written for this ISA"],
  composition: ["composition", "Calls other MIPP functions"],
  fallback: ["scalar fallback", "Copies the registers to arrays and calls the scalar reference"],
  immediate: ["immediate", "Instructions with an immediate, selected because the argument is a constant"],
  lanewise: ["from LMUL 1", "Generated from the LMUL 1 function on the same register"],
  wrapper: ["LMUL wrapper", "One call per register of the LMUL below"],
  scalar: ["scalar code", "Plain C loop of the MIPP scalar target"],
};

/** A node of the call graph for the Dependencies box (call_graph.js). */
function describeGraphNode(graph, currentIsa) {
  const callers = new Map();
  const callees = new Map();
  for (const [a, b] of graph.edges) {
    callees.set(a, (callees.get(a) || 0) + 1);
    callers.set(b, (callers.get(b) || 0) + 1);
  }
  return (node) => {
    const p = parseCName(node.cName);
    const nav = navTarget(node.cName);
    const k = KINDS[node.kind] || [node.kind, ""];
    const isa = node.table !== currentIsa ? (ISA_LABEL()[node.table] || node.table) : "";
    const lmul = p ? (p.lmul === "1" ? "" : (p.lmul === "-2" ? " · d2" : ` · m${p.lmul}`)) : "";
    const text = p ? `${p.func}${p.mask === "unmasked" ? "" : `_${p.mask}`}<${p.dt.replace(",", ", ")}>${lmul}` : node.cName;
    const lv = node.effective === null || node.effective === undefined ? null : node.effective;
    const nIn = callers.get(node.cName) || 0;
    const nOut = callees.get(node.cName) || 0;
    const tip = [
      node.cName,
      `${k[0]}: ${k[1]}`,
      lv === null ? "Effective level: none (code of the scalar target)" : `Effective level: L${lv} (${LEVEL_DESCRIPTIONS[lv] || ""})`,
      isa ? `From the headers of ${isa}` : "",
      `Uses ${nOut} function${nOut === 1 ? "" : "s"}, used by ${nIn}`,
    ].filter(Boolean);
    return {
      text, isa, tip,
      nav: nav ? { func: nav.func, isa: nav.isa, dt: nav.dt, mask: nav.mask, lmul: nav.lmul } : null,
    };
  };
}

/** Call tree: each function with its own level and its effective level, clickable. */
function renderTree(node, currentIsa, depth = 0) {
  if (!node) return "";
  const nav = navTarget(node.cName);
  const isaTag = node.table !== currentIsa ? `<span class="mipp-algo-tree-isa">${escapeHtml(ISA_LABEL()[node.table] || node.table)}</span>` : "";
  const k = KINDS[node.kind] || [node.kind, ""];
  const own = `<span class="mipp-algo-tree-own" title="${escapeHtml(k[1])}">${escapeHtml(k[0])}</span>`;
  const label = nav && depth > 0
    ? `<button type="button" class="mipp-algo-tree-link" data-algo-nav-func="${escapeHtml(nav.func)}" data-algo-nav-isa="${escapeHtml(nav.isa)}" data-algo-nav-dt="${escapeHtml(nav.dt)}" data-algo-nav-mask="${escapeHtml(nav.mask)}" data-algo-nav-lmul="${escapeHtml(nav.lmul)}" title="Open ${escapeHtml(node.cName)}">${treeLabel(node.cName)}</button>`
    : `<span class="mipp-algo-tree-name" title="${escapeHtml(node.cName)}">${treeLabel(node.cName)}</span>`;
  const kids = node.repeated ? "" : node.children.map((c) => renderTree(c, currentIsa, depth + 1)).join("");
  const times = node.calls > 1 ? ` <span class="mipp-algo-tree-times" title="Called ${node.calls} times">×${node.calls}</span>` : "";
  return `<li>${label}${times}${isaTag} ${levelBadge(node.effective, "Effective level: the highest level of everything this function uses")} ${own}${node.repeated ? ' <span class="mipp-algo-tree-own">(see above)</span>' : ""}${kids ? `<ul>${kids}</ul>` : ""}</li>`;
}

export function renderAlgoModal(modalData) {
  if (!modalData) return "";
  const { entry } = modalData;
  const allModalIsas = getAllModalIsas();
  const defaultIsa = allModalIsas[0] || "";
  const rawIsa = modalData.isa || modalData.simdExt || defaultIsa;
  const currentIsa = allModalIsas.includes(rawIsa) ? rawIsa : defaultIsa;
  const currentView = ["flat", "compare"].includes(modalData.view) ? modalData.view : "abstract";
  const currentScalarSize = Number(modalData.scalarSize) || 256;
  const namesMap = { ...SIMD_EXT_DISPLAY_NAMES, scalar: "Scalar" };

  const allDts = entry.datatypes || [];
  const activeDts = allDts.filter((d) => state.selectedTypes.includes(d));
  const selectableDts = (state.selectedTypes.length > 0 && activeDts.length > 0) ? activeDts : allDts;
  const defaultDt = selectableDts[0] || "float32";
  const currentDt = (modalData.dt && selectableDts.includes(modalData.dt)) ? modalData.dt : defaultDt;

  const maskSupport = maskSupportOf(entry);
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const defaultMask = (state.maskVariant && allVariants.includes(state.maskVariant))
    ? state.maskVariant
    : (allVariants[0] || "unmasked");
  const currentMask = (modalData.mask && allVariants.includes(modalData.mask)) ? modalData.mask : defaultMask;

  const effectiveLmul = (modalData.lmul !== undefined && modalData.lmul !== null) ? String(modalData.lmul) : (state.lmul || "1");
  // the settings shown, kept with the step when another function is opened (breadcrumb)
  modalData.resolved = { isa: currentIsa, dt: currentDt, mask: currentMask, lmul: effectiveLmul };
  // functions that change the LMUL (lo, hi, combine, wcvt, ncvt) are not defined for every LMUL
  const lmulUndefined = isLmulUndefined(entry, effectiveLmul);

  const isHalfLmul = effectiveLmul === "-2";

  // Features resolution (contextual per ISA)
  const features = modalData.features || {};
  const isaMeta = apiMetadata.isas ? apiMetadata.isas[currentIsa] : null;
  const featuresMeta = (isaMeta && isaMeta.features) ? isaMeta.features : { mode: "none", items: [] };

  // Features of an ISA as {define: bool, id: bool}: its tiers up to the selected one, and its
  // flags. Per ISA: the same macro can be a feature of several ISAs (__FMA__, __AVX2__), with
  // a state of its own on each.
  const definesOf = (isaName) => {
    const defines = {};
    const fMeta = apiMetadata.isas && apiMetadata.isas[isaName] ? apiMetadata.isas[isaName].features : null;
    if (!fMeta || !Array.isArray(fMeta.items)) return defines;
    const hierarchy = fMeta.mode === "hierarchy";
    const mixed = fMeta.mode === "mixed";
    const tiers = fMeta.items.filter((it) => hierarchy || (mixed && it.type === "tier"));
    const flags = fMeta.items.filter((it) => it.type === "flag" || (!hierarchy && !mixed));
    if (tiers.length > 0) {
      const selectedTier = features[isaName] || fMeta.default || tiers[tiers.length - 1].id;
      const targetIdx = tiers.findIndex((it) => it.id === selectedTier);
      const effectiveIdx = targetIdx !== -1 ? targetIdx : (tiers.length - 1);
      tiers.forEach((it, idx) => {
        defines[it.define] = idx <= effectiveIdx;
        defines[it.id] = idx <= effectiveIdx;
      });
    }
    for (const it of flags) {
      const chosen = features[flagKey(isaName, it.id)];
      const val = it.locked ? true : (chosen !== undefined ? Boolean(chosen) : (it.default !== false));
      defines[it.define] = val;
      defines[it.id] = val;
    }
    return defines;
  };
  const flatDefines = definesOf(currentIsa);

  // Effective level of the shown code (set from the real code once the tables are loaded)
  let currentImplLvl = "na";

  // Code of the two views: taken from the generated MIPP headers (algo_source.js)
  const sources = getLoadedSources(currentIsa);
  const compilerCfg = getCompilerConfigForFlat(currentIsa, flatDefines, currentScalarSize);
  const algoCfg = {
    isa: currentIsa, func: entry.name, dt: currentDt, mask: currentMask, lmul: effectiveLmul,
    options: compilerCfg.options, simdWidth: currentScalarSize, overrides: flatDefines,
    compilerLabel: compilerCfg.compilerLabel,
  };

  // View of the parameter that can be an immediate (functions with an "imm"): the dynamic
  // body ("var"), the body selected for an immediate, or the whole dispatch of the headers.
  // `immAvailable`: the function has a body of its own for an immediate with these settings;
  // otherwise the same code runs in both cases, and the modal shows nothing about it (no
  // selector, the parameter is not boxed in the code)
  let immMode = "var";
  let immValues = [];
  let immAvailable = false;
  if (entry.imm) {
    algoCfg.imm = { arg: entry.imm.arg, mode: "var" };
    const choice = sources ? immChoices(sources, algoCfg) : undefined;
    immAvailable = Boolean(choice);
    if (choice) {
      if (choice.values) {
        immValues = choice.values;
      } else {
        // every value of the range: the lanes of the register (or of a block), the bits of an element
        const bits = Number((currentDt.match(/\d+/) || ["32"])[0]);
        const width = isaMeta && typeof isaMeta.vector_size_bits === "number" ? isaMeta.vector_size_bits : currentScalarSize;
        const l = Number(effectiveLmul);
        const lanes = Math.max(1, Math.round((width / bits) * (l < 0 ? 0.5 : (l || 1))));
        const block = Math.min(lanes, 128 / bits);
        const last = { lt_n: lanes - 1, le_n: lanes, lt_nb: block - 1, le_nb: block, lt_bits: bits - 1 }[entry.imm.range];
        immValues = Array.from({ length: Math.max(1, (last === undefined ? lanes : last) + 1) }, (_, i) => i);
      }
      const asked = modalData.imm;
      if (asked === "dispatch") {
        immMode = "dispatch";
      } else if (asked !== undefined && asked !== null && asked !== "var" && /^-?\d+$/.test(String(asked))) {
        immMode = "const";
      }
      const value = immValues.includes(Number(asked)) ? Number(asked) : (immValues.includes(1) ? 1 : immValues[0]);
      algoCfg.imm = { arg: entry.imm.arg, mode: immMode, value };
    }
  }
  const isaLabel = namesMap[currentIsa] || currentIsa.toUpperCase();
  const tName = (d) => (d.includes(",") ? d.split(",").map((x) => `${x.trim()}_t`).join(" -> ") : `${d}_t`);
  let fullCode = "";
  let flatStandaloneCode = "";
  let godboltUrl = "";
  let godboltRunUrl = "";
  let abstractCalls = [];
  let callTreeRoot = null;
  let callGraph = null;
  let loadingHtml = "";
  if (modalData.loadError) {
    loadingHtml = `<div class="mipp-algo-note"><span class="mipp-algo-note-icon">${ICON_WARNING}</span><span>Unable to load the MIPP source code: ${escapeHtml(modalData.loadError)}</span></div>`;
  } else if (!sources) {
    loadingHtml = loadingNote(currentIsa);
  } else if (!lmulUndefined) {
    const abs = buildAbstractCode(entry, sources, algoCfg);
    abstractCalls = abs.calls || [];
    callTreeRoot = abs.tree || null;
    callGraph = abs.graph || null;
    if (abs.rootFound) {
      currentImplLvl = abs.effectiveLevel;
    } else {
      currentImplLvl = "na";
    }
    const uses = abstractCalls.filter((c) => !c.scalar).map((c) => `${c.cpp.replace(/<.*$/, "")} (L${c.level === null ? "?" : c.level})`);
    const head = [
      "// =============================================================================",
      `// mipp::${entry.name} | ${isaLabel} | ${tName(currentDt)} | ${currentMask} | LMUL ${isHalfLmul ? "1/2 (-2)" : effectiveLmul}`,
      `// Compiler flags: ${compilerCfg.options}`,
      abs.rootFound ? `// Effective level: ${currentImplLvl} (${LEVEL_DESCRIPTIONS[currentImplLvl] || ""})` : "// Not defined for these compiler flags",
    ];
    if (uses.length) head.push(`// Calls: ${uses.join(", ")}`);
    if (abstractCalls.some((c) => c.scalar)) head.push("// The scalar fallback calls the C API of the scalar target (mipp_scalar_*).");
    head.push("// C++ Functional API (#include <mipp.hpp>): vd<T, LMUL> = data register, vm<T, LMUL> = mask.");
    head.push("// =============================================================================", "");
    fullCode = head.join("\n") + "\n" + abs.code;
    if (currentView === "flat") {
      flatStandaloneCode = buildFlatCode(entry, sources, algoCfg).code;
      godboltUrl = buildGodboltUrlForFlat(flatStandaloneCode, currentIsa, flatDefines, currentScalarSize);
      // the same code with a main() that runs it and compares with the scalar reference
      // (no link when Compiler Explorer cannot run the programs of the target)
      if (compilerCfg.canExecute) {
        const runCode = buildFlatCode(entry, sources, algoCfg, { verify: true }).code;
        godboltRunUrl = buildGodboltUrlForFlat(runCode, currentIsa, flatDefines, currentScalarSize, { execute: true });
      }
    }
  }
  // Compare view: the same function on several ISAs, side by side
  const compareIsas = algoCompareIsas(modalData);
  let compareHtml = "";
  if (currentView === "compare" && !lmulUndefined) {
    const cols = compareIsas.map((isa) => {
      const src = getLoadedSources(isa);
      const label = namesMap[isa] || isa.toUpperCase();
      // a box that can be moved (its header, or the arrow keys on its grip) and resized (its gutters)
      const cell = (box) => `<div class="mipp-box-cell" data-box-key="${isa}" style="${boxSizeStyle(state.compareBoxSizes[isa])}">${box}${boxResizeHandles(label)}</div>`;
      const grip = `<span class="mipp-box-grip" data-box-grip role="button" tabindex="0" aria-label="Move or resize the ${escapeHtml(label)} box: arrow keys to move, Shift and arrow keys to resize, Delete for the automatic size" title="Drag the header to move this box. Keyboard: arrow keys to move, Shift + arrow keys to resize.">${ICON_GRIP}</span>`;
      if (!src) return cell(`<div class="mipp-code-box"><div class="mipp-code-box-header" data-box-handle draggable="true"><div class="mipp-code-box-header-left">${grip}<span class="mipp-code-lang">${escapeHtml(label)}</span></div></div>${loadingNote(isa, true)}</div>`);
      const isaDefines = definesOf(isa);
      const cc = getCompilerConfigForFlat(isa, isaDefines, currentScalarSize);
      const r = buildAbstractCode(entry, src, { ...algoCfg, isa, options: cc.options, compilerLabel: cc.compilerLabel, overrides: isaDefines });
      const lv = r.rootFound ? r.effectiveLevel : null;
      return cell(`<div class="mipp-code-box">
        <div class="mipp-code-box-header" data-box-handle draggable="true">
          <div class="mipp-code-box-header-left">
            ${grip}
            <span class="mipp-code-lang">${escapeHtml(label)}</span>
            ${levelBadge(lv, lv === null ? "Not defined" : `Effective level ${lv}`)}
            <span class="mipp-algo-tree-own mipp-algo-compare-flags" title="${escapeHtml(cc.options)}">${escapeHtml(cc.options)}</span>
          </div>
          <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(r.code)}" title="Copy ${escapeHtml(label)} code">${ICON_COPY}</button>
        </div>
        <pre><code>${highlightCpp(r.code, {}, { isa, imm: entry.imm && immChoices(src, { ...algoCfg, isa, options: cc.options, overrides: isaDefines }) ? entry.imm : null, immFunc: [entry.name, entry.form_of] })}</code></pre>
      </div>`);
    }).join("");
    compareHtml = `
      <div class="mipp-modal-ctrl-group mipp-compare-picker">
        <span class="mipp-control-label">Compare:</span>
        <div class="mipp-segmented-group">
          ${allModalIsas.map((isa) => `<button type="button" class="mipp-segment-btn ${compareIsas.includes(isa) ? "active" : ""}" data-modal-compare-isa="${isa}">${escapeHtml((namesMap[isa] || isa.toUpperCase()).replace("ARM ", ""))}</button>`).join("")}
        </div>
      </div>
      <div class="mipp-algo-compare mipp-box-row">${cols}</div>`;
  }
  const treeHas = (n, f) => Boolean(n) && (f(n) || n.children.some((c) => treeHas(c, f)));
  const maskBySelect = treeHas(callTreeRoot, (n) => { const p = parseCName(n.cName); return Boolean(p) && p.func === "select"; });
  const notes = contextNotes(currentIsa, effectiveLmul, currentMask, maskBySelect);
  const notesHtml = notes.length ? `<div class="mipp-algo-note mipp-algo-context"><span class="mipp-algo-note-icon">${ICON_CONTEXT}</span><span>${notes.join("<br>")}</span></div>` : "";
  // Dependencies: DAG, tree or text; by default the DAG, the text on phones (a graph is hard to
  // move around on a small touch screen)
  const narrow = typeof window !== "undefined" && window.matchMedia && window.matchMedia("(max-width: 768px)").matches;
  const dagHtml = callGraph ? renderCallGraph(callGraph, describeGraphNode(callGraph, currentIsa), DOCS, {
    view: modalData.depsView || (narrow ? "text" : "dag"), treeList: callTreeRoot ? renderTree(callTreeRoot, currentIsa) : "",
  }) : "";
  const lvlDescFinal = LEVEL_DESCRIPTIONS[currentImplLvl] || (currentImplLvl === "na" ? "Not Supported" : `Level ${currentImplLvl}`);

  const VARIANT_LETTERS = { unmasked: "U", mask: "M", maskz: "Z", masks: "S" };
  const VARIANT_TITLES = {
    unmasked: "Unmasked (U)",
    mask: "Merge-Masked (M)",
    maskz: "Zero-Masked (Z)",
    masks: "Source-Masked (S)"
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

  // Parameter that can be an immediate: variable / immediate (with its value) / dispatch. Only
  // when the function has a body of its own for an immediate with these settings: otherwise
  // the same code runs in both cases, and there is nothing to choose
  let immControlsHtml = "";
  if (entry.imm && immAvailable) {
    const arg = escapeHtml(entry.imm.arg);
    const btn = (mode, label, title) => `<button type="button" class="mipp-segment-btn ${immMode === mode ? "active" : ""}" data-modal-imm="${mode}" title="${title}">${label}</button>`;
    immControlsHtml = `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">Parameter <span class="mipp-imm-ref" data-imm="${escapeHtml(JSON.stringify(entry.imm))}" data-imm-kind="param" tabindex="0" role="button">${arg}</span>:</span>
        <div class="mipp-segmented-group" id="mipp-modal-imm-group" data-modal-imm-default="${immValues.includes(1) ? 1 : (immValues[0] || 0)}">
          ${btn("var", "variable", `${arg} is a variable: the dynamic body`)}
          ${btn("const", "immediate", `${arg} is an immediate (a value known at compile time): the body selected for it`)}
          ${btn("dispatch", "dispatch", `The code of the headers: the selection between the immediates, then the dynamic body`)}
        </div>
        ${immMode === "const" ? `
          <select class="mipp-modal-imm-select" data-modal-imm-value title="Value of ${arg}" aria-label="Value of ${arg}">
            ${immValues.map((v) => `<option value="${v}" ${v === algoCfg.imm.value ? "selected" : ""}>${arg} = ${v}</option>`).join("")}
          </select>` : ""}
      </div>
    `;
  }

  const isHierarchy = featuresMeta.mode === "hierarchy";
  const isMixed = featuresMeta.mode === "mixed";
  const tierItems = (featuresMeta.items || []).filter((it) => isHierarchy || (isMixed && it.type === "tier"));
  const flagItems = (featuresMeta.items || []).filter((it) => it.type === "flag" || (!isHierarchy && !isMixed));

  if (tierItems.length > 0 || flagItems.length > 0) {
    let tierGroupHtml = "";
    if (tierItems.length > 0) {
      const activeTier = features[currentIsa] || featuresMeta.default || (tierItems.length ? tierItems[tierItems.length - 1].id : "");
      const selectableItems = tierItems.filter((it) => !it.locked);
      tierGroupHtml = `
        <div class="mipp-segmented-group" id="mipp-modal-tier-group">
          ${selectableItems.map((it) => `
            <button type="button" class="mipp-segment-btn ${activeTier === it.id ? "active" : ""}" data-modal-tier="${it.id}" data-feature-isa="${currentIsa}" data-feature-id="${escapeHtml(it.id)}">${escapeHtml(it.label)}</button>
          `).join("")}
        </div>
      `;
    }

    let flagGroupHtml = "";
    if (flagItems.length > 0) {
      flagGroupHtml = `
        <div class="mipp-segmented-group" id="mipp-modal-features-group">
          ${flagItems.map((it) => {
            const isActive = flatDefines[it.define] !== false;
            const isLocked = Boolean(it.locked);
            // a locked feature cannot be switched (main.js ignores the click), but it has its tooltip
            const style = isLocked ? 'style="cursor: default; opacity: 0.85;" aria-disabled="true"' : '';
            return `
              <button type="button" class="mipp-segment-btn ${isActive ? "active" : ""}" data-modal-toggle-feature="${it.id}" ${isLocked ? 'data-modal-locked="true"' : ""} data-feature-isa="${currentIsa}" data-feature-id="${escapeHtml(it.id)}" ${style}>
                ${escapeHtml(it.label)}
              </button>
            `;
          }).join("")}
        </div>
      `;
    }

    featureControlsHtml += `
      <div class="mipp-modal-ctrl-group">
        <span class="mipp-control-label">HW Features:</span>
        ${tierGroupHtml}
        ${flagGroupHtml}
      </div>
    `;
  }

  if (isaMeta && (isaMeta.is_scalar || isaMeta.vector_size_bits === "scalable")) {
    featureControlsHtml += simdWidthHtml;
  }

  return `
    <div class="mipp-modal-backdrop visible active" id="mipp-algo-modal-backdrop">
      <div class="mipp-modal-container mipp-modal-content mipp-algo-modal-content">
        <!-- Header -->
        <div class="mipp-modal-header">
          <div style="display: flex; gap: 0.65rem; align-items: center; flex-wrap: wrap;">
            <h3 class="mipp-modal-title mipp-algo-title" style="margin: 0;">Algorithm: ${renderTitlePath(modalData)}</h3>
          </div>
          <div style="display: flex; gap: 0.45rem; align-items: center;">
            ${(modalData.history && modalData.history.length) ? `<button class="mipp-modal-share-btn" id="mipp-algo-modal-back" title="Back to ${escapeHtml(modalData.history[modalData.history.length - 1].entry.name)}" aria-label="Back">←</button>` : ""}
            <button class="mipp-modal-share-btn" id="mipp-algo-modal-share" title="Copy direct link to this algorithm" aria-label="Share direct link">${ICON_LINK}</button>
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
                ${allModalIsas.map((ext) => `
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
            ${(entry.forms || []).length > 1 ? `
              <div class="mipp-modal-ctrl-group">
                <span class="mipp-control-label">Form:</span>
                ${renderFormSelector(entry, "data-modal-form")}
              </div>` : ""}
            ${immControlsHtml}
          </div>

          <!-- Modal View Tabs: Abstract C++ Implementation vs Flat C Code -->
          <div class="mipp-modal-tabs" role="tablist">
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'abstract' ? 'active' : ''}" data-modal-view="abstract" role="tab" aria-selected="${currentView === 'abstract'}">
              Abstract C++ Implementation
            </button>
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'flat' ? 'active' : ''}" data-modal-view="flat" role="tab" aria-selected="${currentView === 'flat'}">
              Flat C Code
            </button>
            <button type="button" class="mipp-modal-tab-btn ${currentView === 'compare' ? 'active' : ''}" data-modal-view="compare" role="tab" aria-selected="${currentView === 'compare'}">
              Compare ISAs
            </button>
          </div>

          <!-- Active View Content -->
          ${lmulUndefined ? undefinedLmulNotice(entry, effectiveLmul) : currentView === 'compare' ? `${notesHtml}${compareHtml}` : loadingHtml ? loadingHtml : currentView === 'abstract' ? `
            ${notesHtml}
            <div class="mipp-algo-note">
              <span class="mipp-algo-note-icon">${ICON_INFO}</span>
              <span>The code of the MIPP headers for these flags, written with the C++ Functional API: <code>vd&lt;T, LMUL&gt;</code> is a <strong>data</strong> register, <code>vm&lt;T, LMUL&gt;</code> a <strong>mask</strong> register. Each <code>mipp::</code> call is another MIPP function, with its own level.</span>
            </div>

            <!-- Abstract C++ Code Box -->
            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left" style="display: flex; gap: 0.55rem; align-items: center; flex-wrap: wrap;">
                  <span class="mipp-code-lang">Abstract C++ Implementation</span>
                  <span class="mipp-isa-badge lvl-${currentImplLvl}" title="Effective implementation level: Level ${currentImplLvl} (${escapeHtml(lvlDescFinal)})">${currentImplLvl === "na" ? "N/A" : `L${currentImplLvl}`}</span>
                </div>
                <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(fullCode)}" title="Copy algorithm code">
                  ${ICON_COPY}
                </button>
              </div>
              <pre><code>${highlightCpp(fullCode, {}, { isa: currentIsa, imm: immAvailable ? entry.imm : null, immFunc: [entry.name, entry.form_of] })}</code></pre>
            </div>
            ${dagHtml}
          ` : `
            <div class="mipp-algo-note">
              <span class="mipp-algo-note-icon">${ICON_INFO}</span>
              <span>Self-contained C: the function and everything it uses, as in the MIPP headers. Open it in Godbolt and look at the assembly of <code>test</code>: the MIPP calls are inlined, only the instructions of the operation remain in the loop.</span>
            </div>
            ${notesHtml}
            <!-- Flat C99 Code Box -->
            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left" style="display: flex; gap: 0.55rem; align-items: center; flex-wrap: wrap;">
                  <span class="mipp-code-lang">Flat C Code</span>
                  <span class="mipp-isa-badge lvl-${currentImplLvl}" title="Effective implementation level: Level ${currentImplLvl} (${escapeHtml(lvlDescFinal)})">${currentImplLvl === "na" ? "N/A" : `L${currentImplLvl}`}</span>
                </div>
                <div style="display: flex; gap: 0.5rem; align-items: center;">
                  ${godboltRunUrl ? `
                  <a href="${godboltRunUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-btn" title="Open in Godbolt with a main() that runs test() once and compares the result with the scalar reference of MIPP">
                    ${ICON_RUN}
                    <span>Run in Godbolt</span>
                  </a>` : ""}
                  <a href="${godboltUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-btn" title="Open in Godbolt and look at the assembly of test()">
                    ${ICON_GODBOLT}
                    <span>Open in Godbolt</span>
                  </a>
                  <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(flatStandaloneCode)}" title="Copy standalone C code">
                    ${ICON_COPY}
                  </button>
                </div>
              </div>
              <pre><code>${highlightCpp(flatStandaloneCode, entry.scalar_macros || {}, { isa: currentIsa, imm: immAvailable ? entry.imm : null, immFunc: [entry.name, entry.form_of] })}</code></pre>
            </div>
          `}
        </div>
      </div>
    </div>
  `;
}
