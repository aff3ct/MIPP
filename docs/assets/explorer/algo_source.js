/**
 * MIPP API Explorer - real source code of the "Algorithm" modal.
 *
 * The code shown in the modal is not rebuilt from templates: it is taken from the generated MIPP
 * headers, exported per ISA by generator/helpers_docs/algo_sources.py (assets/data/algo/<isa>.json):
 * every macro, type and function, with its preprocessor conditions and its dependencies.
 *
 * - buildFlatCode(): the self-contained C code of one function (the function and the transitive
 *   closure of what it uses, for the selected compiler flags) and a `test` function that calls it
 *   in a loop: its assembly shows that the MIPP calls compile to the bare instructions. With
 *   { verify: true }, a `main` runs it and compares with the scalar reference of MIPP.
 * - buildAbstractCode(): the same function written with the C++ Functional API (mipp::vd<T, LMUL>,
 *   mipp::add(...)), with the level of each MIPP function it calls.
 */

// Resolved from this module, whatever the base path of the site (URL is missing in some test runtimes)
const DATA_DIR = typeof URL !== "undefined" ? new URL("../data/algo/", import.meta.url).href : "";

// ---------------------------------------------------------------------------------------------
// Data loading
// ---------------------------------------------------------------------------------------------
let loader = async (file) => {
  const resp = await fetch(DATA_DIR + file, { cache: "no-cache" });
  if (!resp.ok) throw new Error(`Unable to load ${DATA_DIR + file}: HTTP ${resp.status}`);
  return resp.json();
};
/** Replaces the loader (tests outside the browser). */
export function setAlgoLoader(fn) { loader = fn; }

const tables = new Map(); // isa -> table (or Promise)
let indexData = null;

async function loadTable(isa) {
  if (!tables.has(isa)) tables.set(isa, loader(`${isa}.json`).then((t) => { tables.set(isa, t); return t; }));
  return tables.get(isa);
}

/** Loads the table of an ISA and of the ISAs it imports. Resolves to the ordered list of tables. */
export async function loadAlgoSources(isa) {
  if (!indexData) indexData = await loader("index.json");
  const order = [];
  const visit = async (name) => {
    if (order.some((t) => t.isa === name)) return;
    const t = await loadTable(name);
    order.push(t);
    for (const imp of t.imports || []) await visit(imp);
  };
  await visit(isa);
  return order;
}

/** The tables already loaded for an ISA, or null (synchronous access for the renderer). */
export function getLoadedSources(isa) {
  if (!indexData) return null;
  const order = [];
  const visit = (name) => {
    if (order.some((t) => t.isa === name)) return true;
    const t = tables.get(name);
    if (!t || t instanceof Promise) return false;
    order.push(t);
    return (t.imports || []).every(visit);
  };
  return visit(isa) ? order : null;
}

// ---------------------------------------------------------------------------------------------
// Preprocessor (conditions only: macros are not expanded in the shown code)
// ---------------------------------------------------------------------------------------------
function tokenize(expr) {
  const re = /\s*(defined|[A-Za-z_]\w*|0[xX][0-9a-fA-F]+|\d+[uUlL]*|&&|\|\||==|!=|>=|<=|<<|>>|[()!<>+\-*\/%])/y;
  const out = [];
  let m;
  re.lastIndex = 0;
  while (re.lastIndex < expr.length && (m = re.exec(expr))) out.push(m[1]);
  return out;
}

/** Evaluates a #if expression. `macros`: Map name -> value (string), undefined names are 0. */
export function evalCondition(expr, macros, depth = 0) {
  const toks = tokenize(String(expr));
  let i = 0;
  const peek = () => toks[i];
  const next = () => toks[i++];
  const valueOf = (name) => {
    if (!macros.has(name)) return 0;
    const v = String(macros.get(name)).trim();
    if (v === "") return 1;
    if (depth > 8) return 0;
    return evalCondition(v, macros, depth + 1);
  };
  const primary = () => {
    const t = next();
    if (t === "(") { const v = or(); next(); return v; }
    if (t === "!") return primary() ? 0 : 1;
    if (t === "-") return -primary();
    if (t === "defined") {
      let name = next();
      if (name === "(") { name = next(); next(); }
      return macros.has(name) ? 1 : 0;
    }
    if (t === undefined) return 0;
    if (/^\d/.test(t)) return parseInt(t, /^0[xX]/.test(t) ? 16 : 10);
    return valueOf(t);
  };
  const mul = () => { let v = primary(); while (["*", "/", "%"].includes(peek())) { const o = next(); const r = primary(); v = o === "*" ? v * r : o === "/" ? (r ? Math.trunc(v / r) : 0) : (r ? v % r : 0); } return v; };
  const add = () => { let v = mul(); while (["+", "-"].includes(peek())) { const o = next(); const r = mul(); v = o === "+" ? v + r : v - r; } return v; };
  const shift = () => { let v = add(); while (["<<", ">>"].includes(peek())) { const o = next(); const r = add(); v = o === "<<" ? v << r : v >> r; } return v; };
  const rel = () => { let v = shift(); while (["<", ">", "<=", ">="].includes(peek())) { const o = next(); const r = shift(); v = (o === "<" ? v < r : o === ">" ? v > r : o === "<=" ? v <= r : v >= r) ? 1 : 0; } return v; };
  const eq = () => { let v = rel(); while (["==", "!="].includes(peek())) { const o = next(); const r = rel(); v = (o === "==" ? v === r : v !== r) ? 1 : 0; } return v; };
  const and = () => { let v = eq(); while (peek() === "&&") { next(); const r = eq(); v = v && r ? 1 : 0; } return v; };
  const or = () => { let v = and(); while (peek() === "||") { next(); const r = and(); v = v || r ? 1 : 0; } return v; };
  return or();
}

/**
 * Keeps the lines of the active branches of `text` (#if / #ifdef / #ifndef / #elif / #else / #endif),
 * applies the #define / #undef of the active branches to `macros` and drops #error lines.
 */
export function preprocess(text, macros, { keepDefines = true } = {}) {
  const out = [];
  const stack = []; // { active, taken, parentActive }
  const isActive = () => stack.every((s) => s.active);
  const lines = text.split("\n");
  for (let k = 0; k < lines.length; k++) {
    let line = lines[k];
    const m = line.match(/^\s*#\s*(\w+)\s*(.*)$/);
    if (!m) { if (isActive()) out.push(line); continue; }
    const [, kw, rest0] = m;
    const rest = rest0.replace(/\/\/.*$/, "").replace(/\/\*.*?\*\//g, "").trim();
    if (kw === "if" || kw === "ifdef" || kw === "ifndef") {
      const parent = isActive();
      const c = kw === "if" ? evalCondition(rest, macros) : (kw === "ifdef" ? macros.has(rest) : !macros.has(rest));
      stack.push({ active: parent && !!c, taken: !!c, parent });
    } else if (kw === "elif") {
      const s = stack[stack.length - 1];
      const c = !s.taken && evalCondition(rest, macros);
      s.active = s.parent && !!c;
      s.taken = s.taken || !!c;
    } else if (kw === "else") {
      const s = stack[stack.length - 1];
      s.active = s.parent && !s.taken;
      s.taken = true;
    } else if (kw === "endif") {
      stack.pop();
    } else if (!isActive()) {
      continue;
    } else if (kw === "define") {
      let full = line;
      while (full.endsWith("\\") && k + 1 < lines.length) full += "\n" + lines[++k];
      const d = full.match(/^\s*#\s*define\s+(\w+)(\([^)]*\))?\s*([\s\S]*)$/);
      if (d && !d[2]) macros.set(d[1], d[3].replace(/\\\n/g, " ").replace(/\/\/.*$/, "").trim());
      else if (d) macros.set(d[1], "1");
      if (keepDefines) out.push(full);
    } else if (kw === "undef") {
      macros.delete(rest);
    } else if (kw === "error" || kw === "warning") {
      continue;
    } else {
      out.push(line);
    }
  }
  return out.join("\n");
}

// ---------------------------------------------------------------------------------------------
// Predefined macros of a target (what the compiler defines for the selected flags)
// ---------------------------------------------------------------------------------------------
const X86_CHAIN = ["__SSE__", "__SSE2__", "__SSE3__", "__SSSE3__", "__SSE4_1__", "__SSE4_2__", "__AVX__", "__AVX2__"];
const X86_FLAGS = {
  "-msse": 0, "-msse2": 1, "-msse3": 2, "-mssse3": 3, "-msse4.1": 4, "-msse4.2": 5, "-mavx": 6, "-mavx2": 7,
};

/**
 * Macros defined by the compiler for `options` (e.g. "-O3 -mavx2 -mfma") and the MIPP macros
 * derived from them (MIPP_AVX, MIPP_BW, ...). `overrides`: {define: bool} for the features that
 * have no compiler flag (e.g. __ARM_FEATURE_DIRECTED_ROUNDING).
 */
export function targetMacros(isa, options, simdWidth = 256, overrides = {}) {
  const m = new Map();
  const toks = String(options || "").split(/\s+/).filter(Boolean);
  const arch = (toks.find((t) => t.startsWith("-march=")) || "").slice(7);
  const set = (k, v = "1") => m.set(k, String(v));
  if (["sse", "avx", "avx512"].includes(isa) || (isa === "scalar" && !arch.startsWith("arm") && !arch.startsWith("rv"))) {
    set("__x86_64__"); set("__SSE__"); set("__SSE2__");
    let level = 1;
    for (const t of toks) {
      if (X86_FLAGS[t] !== undefined) level = Math.max(level, X86_FLAGS[t]);
      if (t.startsWith("-mavx512")) level = Math.max(level, 7);
      if (t === "-mfma" || t.startsWith("-mavx512")) set("__FMA__");
      const a5 = t.match(/^-mavx512(\w+)$/);
      if (a5) { set("__AVX512F__"); set(`__AVX512${a5[1].toUpperCase()}__`); }
    }
    for (let k = 0; k <= level; k++) set(X86_CHAIN[k]);
  } else if (isa === "neon" || isa === "sve") {
    if (arch.startsWith("armv7")) {
      if (toks.some((t) => t.startsWith("-mfpu=neon"))) { set("__ARM_NEON"); set("__ARM_NEON__"); }
      if (toks.some((t) => t === "-mfpu=neon-vfpv4")) set("__ARM_FEATURE_FMA");
    } else {
      set("__aarch64__"); set("__ARM_NEON"); set("__ARM_FEATURE_FMA"); set("__ARM_FEATURE_DIRECTED_ROUNDING");
    }
    if (/\+sve/.test(arch)) {
      set("__ARM_FEATURE_SVE");
      const bits = toks.find((t) => t.startsWith("-msve-vector-bits="));
      set("__ARM_FEATURE_SVE_BITS", bits ? bits.split("=")[1] : simdWidth);
    }
    if (/\+sve2/.test(arch)) set("__ARM_FEATURE_SVE2");
  } else if (isa === "rvv") {
    set("__riscv"); set("__riscv_vector"); set("__riscv_v_intrinsic", "12000");
    const zvl = arch.match(/zvl(\d+)b/);
    set("__riscv_v_fixed_vlen", zvl ? zvl[1] : simdWidth);
    set("__riscv_v_elen", "64"); set("__riscv_v_elen_fp", "64");
  }
  for (const t of toks) {
    const d = t.match(/^-D(\w+)(?:=(.*))?$/);
    if (d) set(d[1], d[2] !== undefined ? d[2] : "1");
  }
  for (const [k, v] of Object.entries(overrides || {})) {
    if (!k.startsWith("__")) continue;
    if (v === false) m.delete(k);
  }
  // MIPP selection logic (public C interface): MIPP_AVX, MIPP_BW, MIPP_64BIT, ...
  if (indexData && indexData.selection) preprocess(indexData.selection, m, { keepDefines: false });
  return m;
}

// ---------------------------------------------------------------------------------------------
// Symbol resolution and closure
// ---------------------------------------------------------------------------------------------
function resolve(name, sources, macros) {
  for (const t of sources) {
    const variants = t.symbols[name];
    if (!variants) continue;
    for (const v of variants) {
      if (v.cond.every((c) => evalCondition(c, macros))) return { name, table: t.isa, ...v };
    }
  }
  return null;
}

/** Symbols needed by `roots`, dependencies first. Missing names are returned apart. */
export function closure(roots, sources, macros) {
  const order = [];
  const state = new Map(); // name -> 1 (visiting) | 2 (done)
  const missing = new Set();
  const cyclic = new Set();
  const visit = (name) => {
    const st = state.get(name);
    if (st === 2) return;
    if (st === 1) { cyclic.add(name); return; }
    const sym = resolve(name, sources, macros);
    if (!sym) {
      if (!macros.has(name)) missing.add(name); // e.g. MIPP_SCALAR_SIZE, given by -DMIPP_SCALAR_SIZE=...
      state.set(name, 2);
      return;
    }
    state.set(name, 1);
    let deps = sym.deps || [];
    if (sym.kind !== "macro" && /^\s*#/m.test(sym.code)) {
      // nested #if in a body: only the dependencies of the active branches
      sym.clean = cleanCode(sym, macros);
      const used = new Set(sym.clean.replace(/\/\/[^\n]*/g, "").match(/[A-Za-z_]\w*/g) || []);
      deps = deps.filter((d) => used.has(d));
    }
    for (const d of deps) visit(d);
    state.set(name, 2);
    order.push(sym);
  };
  roots.forEach(visit);
  return { order, missing: [...missing], cyclic: [...cyclic] };
}

const LEVEL_RE = /\/\/\s*Level\s+(\d)\s*\(([^)]*)\)/;
const LEVEL_NAMES = ["Level 0 (Native Hardware)", "Level 1 (Dedicated Emulation)", "Level 2 (Generic Emulation)", "Level 3 (Scalar Fallback)"];

export function levelOf(code) {
  const m = String(code || "").match(LEVEL_RE);
  return m ? { level: Number(m[1]), label: m[2] } : null;
}

/** Level of a body by its kind (sourceOf): the wrappers have none, they take the level of what they call. */
const KIND_LEVEL = { native: 0, dedicated: 1, composition: 2, fallback: 3, scalar: 0, lanewise: null, wrapper: null };

/**
 * Effective level of a function for the selected flags: the highest level among its own body and
 * the functions it calls (recursively), computed from the code that is really used. The `// Level N`
 * comments of the headers are not used for this: the generator writes there the worst level of all
 * the branches of the conditions (e.g. `fmadd` d2 on SSE says Level 3 because of the `!__SSE2__`
 * branch of the LMUL 1 function, while it is Level 2 when SSE2 is enabled).
 */
export function effectiveLevel(rootName, sources, macros, memo = new Map()) {
  if (memo.has(rootName)) return memo.get(rootName);
  memo.set(rootName, 0); // recursion guard
  const sym = resolve(rootName, sources, macros);
  if (!sym || sym.kind !== "func") { memo.set(rootName, 0); return 0; }
  const code = cleanCode(sym, macros);
  const p = String(rootName).match(/_(mask|maskz|masks)_(?:m\d|d2)$/);
  const own = KIND_LEVEL[sourceOf(code, sym.table, p ? p[1] : "unmasked").kind];
  let lv = own === null || own === undefined ? 0 : own;
  if (sym.table !== "scalar" || rootName.startsWith("mipp_scalar_")) {
    const body = code.split("{").slice(1).join("{").replace(/\/\/[^\n]*/g, "");
    for (const d of sym.deps || []) {
      if (!new RegExp(`\\b${d}\\s*\\(`).test(body)) continue;
      const ds = resolve(d, sources, macros);
      if (!ds || ds.kind !== "func") continue;
      // the scalar code called by a fallback does not lower or raise it: the fallback is Level 3
      if (ds.table === "scalar" && !rootName.startsWith("mipp_scalar_")) continue;
      lv = Math.max(lv, effectiveLevel(d, sources, macros, memo));
    }
  }
  memo.set(rootName, lv);
  return lv;
}

// ---------------------------------------------------------------------------------------------
// Names
// ---------------------------------------------------------------------------------------------
const VARIANT_SUFFIX = { unmasked: "", mask: "_mask", maskz: "_maskz", masks: "_masks" };
export function lmulSuffix(lmul) {
  const l = String(lmul);
  return l === "-2" || l === "0.5" ? "d2" : `m${Number(l) || 1}`;
}
/** C name of a function: mipp_<isa>_<func>_<dt(s)>[_<variant>]_<lmul>. */
export function cFunctionName(isa, func, dt, mask, lmul) {
  return `mipp_${isa}_${func}_${dt.replace(/\s*,\s*/g, "_")}${VARIANT_SUFFIX[mask] || ""}_${lmulSuffix(lmul)}`;
}

const C_TYPES = {
  float64: "float64_t", float32: "float32_t", int64: "int64_t", int32: "int32_t", int16: "int16_t", int8: "int8_t",
  uint64: "uint64_t", uint32: "uint32_t", uint16: "uint16_t", uint8: "uint8_t",
};
const REG_TYPE_RE = /^(vd|vm)_(\w+?)_(float64|float32|u?int64|u?int32|u?int16|u?int8)(?:_(m\d|d2))?_t$/;

/** {kind: vd|vm, isa, dt, lmul} of a register type name, following the typedef aliases. */
function regInfo(typeName) {
  const m = String(typeName).match(REG_TYPE_RE);
  if (!m) return null;
  return { kind: m[1], isa: m[2], dt: m[3], lsuf: m[4] || "m1" };
}

function parseSignature(code) {
  const head = code.split("{")[0].replace(/\/\/[^\n]*/g, "").replace(/\s+/g, " ").trim();
  const m = head.match(/^(?:static\s+)?(?:inline\s+)?(.+?)\s*\b(\w+)\s*\((.*)\)$/);
  if (!m) return null;
  const params = m[3].trim() && m[3].trim() !== "void" ? m[3].split(",").map((p) => {
    const s = p.trim();
    const arr = s.match(/^(.*?)(\w+)\s*\[([^\]]*)\]$/);
    if (arr) return { type: arr[1].replace(/\bconst\b/, "").trim(), name: arr[2], isConst: /\bconst\b/.test(s), isArray: true, arrayLen: arr[3], isPtr: true };
    const pm = s.match(/^(.*?)(\w+)$/);
    const type = pm[1].trim();
    return { type: type.replace(/\bconst\b/g, "").replace(/\s+/g, " ").trim(), name: pm[2], isConst: /\bconst\b/.test(type), isPtr: type.includes("*") };
  }) : [];
  return { ret: m[1].replace(/\bconst\b/, "").trim(), name: m[2], params };
}

// ---------------------------------------------------------------------------------------------
// Flat C code
// ---------------------------------------------------------------------------------------------
/**
 * Code of a symbol for the selected flags, with the `// Level N (...)` comment of a function set to
 * its effective level for these flags (the headers give the worst level of all the branches).
 */
function shownCode(sym, sources, macros, memo) {
  const code = cleanCode(sym, macros);
  if (sym.kind !== "func" || !LEVEL_RE.test(code)) return code;
  if (sym.table === "scalar" && !sym.name.startsWith("mipp_scalar_")) return code;
  const lv = effectiveLevel(sym.name, sources, macros, memo);
  return code.replace(/\/\/\s*Level\s+\d\s*\([^)]*\)/, `// ${LEVEL_NAMES[lv]}`);
}

function cleanCode(sym, macros) {
  if (sym.kind === "macro") return sym.code.replace(/^\s+#/, "#");
  if (sym.clean !== undefined) return sym.clean;
  // nested conditions of the function bodies (e.g. #if defined(MIPP_AVX512) in a scalar fallback)
  return preprocess(sym.code, new Map(macros), { keepDefines: true });
}

function parseDomain(entry, dt, mask) {
  const specs = entry.test_specs && entry.test_specs.variants;
  const v = specs && (specs[mask] || specs.unmasked);
  const key = dt.replace(/\s+/g, "");
  const row = v && Array.isArray(v.rows)
    ? (v.rows.find((r) => String(r.datatype).replace(/\s+/g, "") === key)
      || v.rows.find((r) => String(r.datatype).startsWith(key.split(",")[0])))
    : null;
  // bounds of the first input in the test (default branch), null when the whole range of the type is used
  const range = row && Array.isArray(row.ranges) ? row.ranges[0] : null;
  let lo = range ? Number(range[0]) : null, hi = range ? Number(range[1]) : null;
  // a conversion to an unsigned type is undefined in C for negative values
  const [from, to] = key.split(",");
  if (to && to.startsWith("u") && from.startsWith("float")) { lo = Math.max(lo === null ? 0 : lo, 0); hi = hi === null ? 100 : hi; }
  return {
    lo, hi,
    exact: !row || row.exact !== false,
    maskPattern: (v && v.mask_pattern) || "uniform_bool",
  };
}

const IS_FLOAT = (dt) => dt.startsWith("float");
const BITS = (dt) => Number(dt.match(/\d+/)[0]);

function valueLiteral(dt, i, dom, salt) {
  // deterministic values in the test domain of the function
  const frac = ((i * 0.6180339887 + salt * 0.3819660113) % 1 + 1) % 1;
  if (IS_FLOAT(dt)) {
    const lo = dom.lo !== null ? dom.lo : -8, hi = dom.hi !== null ? dom.hi : 8;
    const v = Math.round((lo + (hi - lo) * frac) * 1000) / 1000;
    const s = String(v).includes(".") || String(v).includes("e") ? String(v) : `${v}.0`;
    return dt === "float32" ? `${s}f` : s;
  }
  const unsigned = dt.startsWith("u");
  const bits = BITS(dt);
  let lo = dom.lo !== null ? dom.lo : (unsigned ? 0 : -100), hi = dom.hi !== null ? dom.hi : 100;
  if (bits === 8) { lo = Math.max(lo, unsigned ? 0 : -100); hi = Math.min(hi, unsigned ? 200 : 100); }
  return String(Math.round(lo + (hi - lo) * frac));
}

function printfOf(dt) {
  if (IS_FLOAT(dt)) return { fmt: "%g", cast: "(double)" };
  if (dt.startsWith("u")) return { fmt: "%llu", cast: "(unsigned long long)" };
  return { fmt: "%lld", cast: "(long long)" };
}

/**
 * Self-contained C code of one function of MIPP: the function and everything it uses, then a
 * `test` function that calls it in a loop (its assembly shows the inlining).
 * cfg: { isa, func, dt, mask, lmul, options, simdWidth, overrides, compilerLabel }
 * opts.verify: also emit a `main` that runs `test` once and compares the result with the scalar
 * reference of MIPP (the "Run" link of the modal and the automatic checks).
 * Returns { code, missing, rootFound, level, effectiveLevel, rootName }.
 */
export function buildFlatCode(entry, sources, cfg, opts = {}) {
  const verify = Boolean(opts.verify);
  const { isa, func, dt, mask, lmul } = cfg;
  const macros = targetMacros(isa, cfg.options, cfg.simdWidth, cfg.overrides);
  const rootName = cFunctionName(isa, func, dt, mask, lmul);
  const root = resolve(rootName, sources, macros);
  if (!root) {
    return { code: `// ${rootName} is not defined for these compiler flags.\n`, missing: [rootName], rootFound: false };
  }
  const sig = parseSignature(root.code);
  const withRef = isa !== "scalar";
  const refName = withRef ? rootName.replace(`mipp_${isa}_`, "mipp_scalar_") : null;
  const refSym = refName ? resolve(refName, sources, macros) : null;

  // main() needs set_k for the mask parameters
  const helperRoots = [];
  for (const p of sig.params) {
    const ri = regInfo(p.type);
    if (ri && ri.kind === "vm") {
      helperRoots.push(`mipp_${ri.isa}_set_k_${ri.dt}_${ri.lsuf}`);
      if (refSym) helperRoots.push(`mipp_scalar_set_k_${ri.dt}_${ri.lsuf}`);
    }
  }
  const retInfo = regInfo(sig.ret);
  if (retInfo && retInfo.kind === "vm") {
    helperRoots.push(`mipp_${retInfo.isa}_get_k_${retInfo.dt}_${retInfo.lsuf}`);
    if (refSym) helperRoots.push(`mipp_scalar_get_k_${retInfo.dt}_${retInfo.lsuf}`);
  }
  const nMacro = (ri) => `MIPP_${ri.isa.toUpperCase()}_N_${ri.dt.toUpperCase()}_${ri.lsuf.toUpperCase()}`;
  for (const p of sig.params.concat([{ type: sig.ret }])) {
    const ri = regInfo(p.type);
    if (ri) helperRoots.push(nMacro(ri));
  }

  const lvMemo = new Map();
  const effective = effectiveLevel(rootName, sources, macros, lvMemo);
  // lane counts used by `test` to move the pointers of the memory functions
  const strideFor = (base) => {
    const reg = sig.params.concat([{ type: sig.ret }]).map((p) => regInfo(p.type)).find((ri) => ri && C_TYPES[ri.dt] === base);
    return reg ? nMacro(reg) : null;
  };
  const strideRoots = sig.params.filter((p) => p.isPtr && !p.isArray && !regInfo(p.type))
    .map((p) => strideFor(p.type.replace("*", "").trim())).filter(Boolean);
  const shown = closure([rootName, ...strideRoots], sources, macros);
  const shownNames = new Set(shown.order.map((x) => x.name));
  const extra = verify
    ? closure([...(refSym ? [refName] : []), ...helperRoots, "float32_t", "float64_t"], sources, macros)
    : { order: [], missing: [], cyclic: [] };
  extra.order = extra.order.filter((x) => !shownNames.has(x.name));
  const missing = [...new Set([...shown.missing, ...extra.missing])];

  const includesOf = (order, base) => {
    const out = [...base];
    for (const t of sources) {
      if (!order.some((x) => x.table === t.isa)) continue;
      for (const inc of t.includes || []) if (!inc.includes("mipp/") && !out.includes(inc)) out.push(inc);
    }
    return out;
  };
  const includes = includesOf(shown.order, []);
  if (!includes.includes("<stdint.h>")) includes.push("<stdint.h>");
  if (!includes.includes("<string.h>") && shown.order.some((x) => /\bmemcpy\s*\(/.test(x.code))) includes.push("<string.h>");

  const L = [];
  const lvl = levelOf(root.code);
  L.push("// =============================================================================");
  L.push(`// MIPP: ${rootName}`);
  L.push(`// ${isa.toUpperCase()} | ${dt} | ${mask} | LMUL ${lmul} | ${LEVEL_NAMES[effective]}`);
  if (cfg.compilerLabel) L.push(`// Compiler: ${cfg.compilerLabel}`);
  L.push("//");
  L.push("// The code of the MIPP headers for these flags: the function and everything it uses.");
  if (effective < 3) {
    L.push("// In the assembly of `test`, the MIPP calls are inlined: the loop only contains the");
    L.push("// instructions of the operation (MIPP has no run-time overhead).");
  } else {
    L.push("// This combination uses a scalar fallback (Level 3): a loop over the elements, that the");
    L.push("// compiler may keep as a function call in `test` instead of inlining it.");
  }
  L.push("// =============================================================================");
  L.push("");
  includes.forEach((inc) => L.push(`#include ${inc}`));
  L.push("");

  const emit = (order, titles) => {
    const groups = { macro: [], type: [], decl: [], func: [] };
    for (const x of order) (groups[x.kind] || groups.decl).push(x);
    const section = (title, syms) => {
      if (!syms.length) return;
      L.push(`// ---- ${title} ${"-".repeat(Math.max(4, 74 - title.length))}`);
      for (const x of syms) {
        L.push(shownCode(x, sources, macros, lvMemo));
        if (x.kind === "func" || x.code.includes("\n")) L.push("");
      }
      if (L[L.length - 1] !== "") L.push("");
    };
    section(titles.macro, groups.macro);
    section(titles.type, groups.type.concat(groups.decl));
    section(titles.scalar, groups.func.filter((x) => x.table === "scalar" && isa !== "scalar"));
    section(titles.func, groups.func.filter((x) => x.table !== "scalar" || isa === "scalar"));
  };
  if (shown.cyclic.length) {
    L.push("// ---- Declarations (mutually recursive functions) ------------------------");
    shown.order.filter((x) => x.kind === "func" && shown.cyclic.includes(x.name)).forEach((x) => L.push(x.code.split("{")[0].trim() + ";"));
    L.push("");
  }
  emit(shown.order, { macro: "Constants", type: "Types", scalar: "Scalar fallback (MIPP scalar target)", func: `${isa.toUpperCase()} implementation` });

  // ---- test: the function in a loop -----------------------------------------------------------
  const tparams = [];
  const targs = [];
  if (sig.ret !== "void") tparams.push(`${sig.ret}* res`);
  sig.params.forEach((p) => {
    const ri = regInfo(p.type);
    if (ri) { tparams.push(`const ${p.type}* ${p.name}`); targs.push(`${p.name}[i]`); return; }
    if (p.isPtr) {
      const base = p.type.replace("*", "").trim();
      const stride = p.isArray ? p.arrayLen : strideFor(base);
      tparams.push(`${p.isConst ? "const " : ""}${base}* ${p.name}`);
      targs.push(stride ? `${p.name} + i * ${stride}` : p.name);
      return;
    }
    tparams.push(`${p.isConst ? "const " : ""}${p.type} ${p.name}`);
    targs.push(p.name);
  });
  tparams.push("int n");
  const call = `${rootName}(${targs.join(", ")})`;
  L.push("// ---- Test function: look at its assembly ------------------------------------");
  const tsig = `void test(${tparams.join(", ")}) {`;
  L.push(tsig.length <= 100 ? tsig : `void test(${tparams.join(",\n          ")}) {`);
  L.push("\tfor (int i = 0; i < n; i++)");
  L.push(sig.ret === "void" ? `\t\t${call};` : `\t\tres[i] = ${call};`);
  L.push("}");

  if (!verify) {
    const code = L.join("\n") + "\n";
    return { code, missing, rootFound: true, level: lvl, effectiveLevel: effective, rootName, cyclic: shown.cyclic };
  }

  // ---- verification: scalar reference and main (not shown in the API Explorer) ----------------
  L.push("");
  L.push("// =============================================================================");
  L.push("// Verification: runs `test` once and compares with the scalar reference of MIPP");
  L.push("// =============================================================================");
  for (const inc of includesOf(extra.order, ["<stdio.h>", "<math.h>", "<string.h>"])) {
    if (!includes.includes(inc)) L.push(`#include ${inc}`);
  }
  L.push("");
  emit(extra.order, { macro: "Constants (verification)", type: "Types (verification)", scalar: "Scalar reference", func: `${isa.toUpperCase()} helpers (verification)` });

  // ---- main -----------------------------------------------------------------------------------
  const dom = parseDomain(entry, dt, mask);
  const M = [];
  const decls = [];
  const callArgs = [];
  const refArgs = [];
  const SHOW = 8;
  const show = (label, arr, ri, n) => {
    const { fmt, cast } = printfOf(ri.dt);
    M.push(`\tprintf("${label.padEnd(10)}=");`);
    M.push(`\tfor (int i = 0; i < ${n} && i < ${SHOW}; i++) printf(" ${fmt}", ${cast}${arr}[i]);`);
    M.push(`\tprintf("%s\\n", ${n} > ${SHOW} ? " ..." : "");`);
  };
  sig.params.forEach((p, idx) => {
    const ri = regInfo(p.type);
    if (ri && ri.kind === "vd") {
      const ct = C_TYPES[ri.dt], n = nMacro(ri);
      // sized as the register type: a half-vector by mask fills a whole register
      decls.push(`\t${ct} in_${p.name}[sizeof(${p.type}) / sizeof(${ct})] = {0};`);
      decls.push(`\tfor (int i = 0; i < ${n}; i++) in_${p.name}[i] = (${ct})vals_${ri.dt}[(i + ${idx * 3}) % 16];`);
      decls.push(`\t${p.type} ${p.name}; memcpy(&${p.name}, in_${p.name}, sizeof(${p.name}));`);
      if (refSym) {
        const rt = p.type.replace(`_${ri.isa}_`, "_scalar_");
        decls.push(`\t${rt} ref_${p.name}; memcpy(&ref_${p.name}, in_${p.name}, sizeof(ref_${p.name}));`);
        refArgs.push(`ref_${p.name}`);
      }
      callArgs.push(`&${p.name}`);
      show(p.name, `in_${p.name}`, ri, n);
    } else if (ri && ri.kind === "vm") {
      const n = nMacro(ri);
      decls.push(`\tint32_t bits_${p.name}[${n}];`);
      decls.push(`\tfor (int i = 0; i < ${n}; i++) bits_${p.name}[i] = (i % 3) != 1;`);
      decls.push(`\t${p.type} ${p.name} = mipp_${ri.isa}_set_k_${ri.dt}_${ri.lsuf}(bits_${p.name});`);
      if (refSym) {
        decls.push(`\t${p.type.replace(`_${ri.isa}_`, "_scalar_")} ref_${p.name} = mipp_scalar_set_k_${ri.dt}_${ri.lsuf}(bits_${p.name});`);
        refArgs.push(`ref_${p.name}`);
      }
      callArgs.push(`&${p.name}`);
      M.push(`\tprintf("${p.name.padEnd(10)}=");`);
      M.push(`\tfor (int i = 0; i < ${n} && i < ${SHOW}; i++) printf(" %d", (int)bits_${p.name}[i]);`);
      M.push(`\tprintf("%s\\n", ${n} > ${SHOW} ? " ..." : "");`);
    } else if (p.isPtr) {
      const base = p.type.replace("*", "").trim();
      const pdt = Object.keys(C_TYPES).find((k) => C_TYPES[k] === base) || "int32";
      const n = "4096";
      decls.push(`\tstatic ${base} buf_${p.name}[${n}];`);
      decls.push(`\tfor (int i = 0; i < ${n}; i++) buf_${p.name}[i] = (${base})vals_${pdt}[i % 16];`);
      if (refSym && !p.isConst) decls.push(`\tstatic ${base} refbuf_${p.name}[${n}]; memcpy(refbuf_${p.name}, buf_${p.name}, sizeof(refbuf_${p.name}));`);
      if (p.isArray && /idx|index/i.test(p.name) === false && pdt.startsWith("u")) { /* index arrays use the values below */ }
      callArgs.push(`buf_${p.name}`);
      refArgs.push(refSym && !p.isConst ? `refbuf_${p.name}` : `buf_${p.name}`);
    } else {
      // scalar parameter: a small value (shift amount, lane index, broadcast value)
      const base = p.type;
      const pdt = Object.keys(C_TYPES).find((k) => C_TYPES[k] === base);
      const reg = sig.params.map((q) => regInfo(q.type)).find(Boolean);
      const lit = pdt && IS_FLOAT(pdt) ? valueLiteral(pdt, 1, dom, 0)
        : (base === "uint32_t" && reg ? `(${nMacro(reg)} > 1 ? 1 : 0)` : "1"); // lane index: in the register
      decls.push(`\t${base} ${p.name} = ${lit};`);
      callArgs.push(p.name);
      refArgs.push(p.name);
    }
  });

  const valTables = [];
  const usedDts = new Set();
  sig.params.concat([{ type: sig.ret }]).forEach((p) => {
    const ri = regInfo(p.type);
    if (ri) usedDts.add(ri.dt);
    const base = String(p.type || "").replace("*", "").trim();
    const pdt = Object.keys(C_TYPES).find((k) => C_TYPES[k] === base);
    if (pdt) usedDts.add(pdt);
  });
  for (const d of usedDts) {
    const vals = Array.from({ length: 16 }, (_, i) => valueLiteral(d, i, d === dt.split(",")[0].trim() ? dom : { lo: null, hi: null }, BITS(d)));
    valTables.push(`\tstatic const ${C_TYPES[d]} vals_${d}[16] = {${vals.join(", ")}};`);
  }

  L.push("int main(void) {");
  valTables.forEach((l) => L.push(l));
  decls.forEach((l) => L.push(l));
  L.push(...M.splice(0)); // the inputs
  const tolerance = dom.exact ? "0" : (dt.startsWith("float64") ? "1e-9" : "1e-3");
  const cmp = (a, b, ri) => IS_FLOAT(ri.dt)
    ? `(fabs((double)${a} - (double)${b}) > ${tolerance} * (1.0 + fabs((double)${b})))`
    : `(${a} != ${b})`;
  if (sig.ret === "void") {
    L.push(`\ttest(${[...callArgs, "1"].join(", ")});`);
    const out = sig.params.find((p) => p.isPtr && !p.isConst && !regInfo(p.type));
    if (out) {
      const base = out.type.replace("*", "").trim();
      const pdt = Object.keys(C_TYPES).find((k) => C_TYPES[k] === base) || "int32";
      const ri = { dt: pdt };
      const regP = sig.params.find((p) => regInfo(p.type));
      const n = regP ? nMacro(regInfo(regP.type)) : "8";
      show(`${out.name} (out)`.slice(0, 10), `buf_${out.name}`, ri, n);
      if (refSym) {
        L.push(...M.splice(0));
        L.push(`\t${refName}(${refArgs.join(", ")});`);
        L.push(`\tint errors = 0;`);
        L.push(`\tfor (int i = 0; i < 4096; i++) errors += ${cmp(`buf_${out.name}[i]`, `refbuf_${out.name}[i]`, ri)};`);
        L.push(`\tprintf("%s\\n", errors ? "MISMATCH with the scalar reference" : "OK: same result as the scalar reference");`);
        L.push(`\treturn errors != 0;`);
      } else {
        L.push(...M.splice(0));
        L.push(`\treturn 0;`);
      }
    } else {
      L.push(...M.splice(0));
      L.push(`\treturn 0;`);
    }
  } else if (retInfo && retInfo.kind === "vd") {
    const ct = C_TYPES[retInfo.dt], n = nMacro(retInfo);
    L.push(`\t${sig.ret} res;`);
    L.push(`\ttest(${["&res", ...callArgs, "1"].join(", ")});`);
    L.push(`\t${ct} out[sizeof(${sig.ret}) / sizeof(${ct})]; memcpy(out, &res, sizeof(out));`);
    show("result", "out", retInfo, n);
    L.push(...M.splice(0));
    if (refSym) {
      L.push(`\t${sig.ret.replace(`_${retInfo.isa}_`, "_scalar_")} ref = ${refName}(${refArgs.join(", ")});`);
      L.push(`\t${ct} expected[${n}]; memcpy(expected, &ref, sizeof(expected));`);
      show("reference", "expected", retInfo, n);
      L.push(...M.splice(0));
      L.push(`\tint errors = 0;`);
      L.push(`\tfor (int i = 0; i < ${n}; i++) errors += ${cmp("out[i]", "expected[i]", retInfo)};`);
      L.push(`\tprintf("%s\\n", errors ? "MISMATCH with the scalar reference" : "OK: same result as the scalar reference");`);
      L.push(`\treturn errors != 0;`);
    } else {
      L.push(`\treturn 0;`);
    }
  } else if (retInfo && retInfo.kind === "vm") {
    const n = nMacro(retInfo);
    L.push(`\t${sig.ret} res;`);
    L.push(`\ttest(${["&res", ...callArgs, "1"].join(", ")});`);
    L.push(...M.splice(0));
    L.push(`\tint errors = 0;`);
    L.push(`\tprintf("result    =");`);
    if (refSym) L.push(`\t${sig.ret.replace(`_${retInfo.isa}_`, "_scalar_")} ref = ${refName}(${refArgs.join(", ")});`);
    L.push(`\tfor (int i = 0; i < ${n}; i++) {`);
    L.push(`\t\tint lane = mipp_${retInfo.isa}_get_k_${retInfo.dt}_${retInfo.lsuf}(res, i) != 0;`);
    if (refSym) L.push(`\t\terrors += lane != (mipp_scalar_get_k_${retInfo.dt}_${retInfo.lsuf}(ref, i) != 0);`);
    L.push(`\t\tif (i < ${SHOW}) printf(" %d", lane);`);
    L.push(`\t}`);
    L.push(`\tprintf("%s\\n", ${n} > ${SHOW} ? " ..." : "");`);
    if (refSym) {
      L.push(`\tprintf("%s\\n", errors ? "MISMATCH with the scalar reference" : "OK: same result as the scalar reference");`);
      L.push(`\treturn errors != 0;`);
    } else L.push(`\treturn 0;`);
  } else {
    const rdt = Object.keys(C_TYPES).find((k) => C_TYPES[k] === sig.ret) || "int32";
    const { fmt, cast } = printfOf(rdt);
    L.push(...M.splice(0));
    L.push(`\t${sig.ret} res;`);
    L.push(`\ttest(${["&res", ...callArgs, "1"].join(", ")});`);
    L.push(`\tprintf("result    = ${fmt}\\n", ${cast}res);`);
    if (refSym) {
      L.push(`\t${sig.ret} expected = ${refName}(${refArgs.join(", ")});`);
      L.push(`\tprintf("reference = ${fmt}\\n", ${cast}expected);`);
      L.push(`\tint errors = ${cmp("res", "expected", { dt: rdt })};`);
      L.push(`\tprintf("%s\\n", errors ? "MISMATCH with the scalar reference" : "OK: same result as the scalar reference");`);
      L.push(`\treturn errors != 0;`);
    } else L.push(`\treturn 0;`);
  }
  L.push("}");
  const code = L.join("\n") + "\n";
  return { code, missing, rootFound: true, level: lvl, effectiveLevel: effective, rootName, cyclic: shown.cyclic };
}

// ---------------------------------------------------------------------------------------------
// Abstract C++ view (C++ Functional API)
// ---------------------------------------------------------------------------------------------
function cppType(typeName, isa) {
  const ri = regInfo(typeName);
  if (!ri || ri.isa !== isa) return null; // other ISAs (scalar fallback, SSE half-vectors of AVX): C API
  const l = ri.lsuf === "d2" ? "-2" : ri.lsuf.slice(1);
  return `${ri.kind}<${C_TYPES[ri.dt]}, ${l}>`;
}

/** Replaces each call `name(args)` matched by `re` (global, on the name) by rename(name, args). */
function replaceCalls(code, re, rename) {
  let out = "";
  let last = 0;
  re.lastIndex = 0;
  let m;
  while ((m = re.exec(code))) {
    const name = m[0];
    let k = m.index + name.length;
    while (code[k] === " ") k++;
    if (code[k] !== "(") continue;
    let depth = 0, j = k;
    for (; j < code.length; j++) {
      if (code[j] === "(") depth++;
      else if (code[j] === ")" && --depth === 0) break;
    }
    const args = replaceCalls(code.slice(k + 1, j), new RegExp(re.source, "g"), rename);
    out += code.slice(last, m.index) + rename(name, args);
    last = j + 1;
    re.lastIndex = j + 1;
  }
  return out + code.slice(last);
}

/**
 * The function written with the C++ Functional API: types vd<T, LMUL> / vm<T, LMUL>, calls
 * mipp::<name>(...). The scalar fallbacks keep their C names (C API of the scalar target).
 * Returns { code, calls: [{cpp, cName, level}] }.
 */
export function buildAbstractCode(entry, sources, cfg) {
  const { isa, func, dt, mask, lmul } = cfg;
  const macros = targetMacros(isa, cfg.options, cfg.simdWidth, cfg.overrides);
  const rootName = cFunctionName(isa, func, dt, mask, lmul);
  const root = resolve(rootName, sources, macros);
  if (!root) return { code: `// ${rootName} is not defined for these compiler flags.`, calls: [], rootFound: false };
  const cppMap = Object.assign({}, ...sources.map((t) => t.cpp || {}));
  const body = shownCode(root, sources, macros, new Map());
  const calls = [];
  const seen = new Set();
  const isaFn = new RegExp(`\\bmipp_${isa}_\\w+\\b(?=\\s*\\()`, "g");

  let code = body.replace(/\b(rv[dm]_\w+?_t)\b/g, (t) => cppType(t, isa) || t);
  // signature: name of the C++ API without template arguments
  const head = cppMap[rootName] ? cppMap[rootName].replace(/<.*$/, "") : func;
  // on the scalar target the body calls the C math library (EXPD -> exp): do not shadow it
  const LIBM = /^(exp|exp2|log|log2|log10|pow|sqrt|cbrt|sin|cos|tan|asin|acos|atan|atan2|sinh|cosh|tanh|asinh|acosh|atanh|erf|round|trunc|floor|ceil|fmod|abs|fabs|min|max)$/;
  const base = isa === "scalar" && LIBM.test(head) ? `${head}_scalar` : head;
  const defName = mask === "unmasked" ? base : `${base}_${mask}`;
  code = code.replace(new RegExp(`\\b${rootName}\\b`), defName);
  code = code.replace(/^static\s+inline\s+/, "");
  // calls of the target ISA -> C++ Functional API. LMUL 1 is the default template argument; a call
  // whose template arguments keep a comma is parenthesized (it may be an argument of an intrinsic
  // that is a macro, e.g. _mm512_mask_i64gather_epi64).
  const cppCall = (name) => {
    let c = cppMap[name];
    if (!c) return null;
    c = c.replace(/,\s*1>$/, ">").replace(/<([^<>,]+)>$/, "<$1>");
    return `mipp::${c}`;
  };
  code = replaceCalls(code, isaFn, (name, args) => {
    if (name === rootName) return `${defName}(${args})`;
    const cpp = cppCall(name);
    if (!seen.has(name)) {
      seen.add(name);
      const sym = resolve(name, sources, macros);
      calls.push({ cName: name, cpp: cpp || name, level: sym ? effectiveLevel(name, sources, macros) : null });
    }
    if (!cpp) return `${name}(${args})`;
    return /<[^>]*,[^>]*>/.test(cpp) ? `(${cpp}(${args}))` : `${cpp}(${args})`;
  });
  // functions of the other ISAs (scalar fallback, SSE half-vectors of AVX) keep their C name
  for (const m of code.matchAll(/\bmipp_(\w+?)_\w+(?=\s*\()/g)) {
    if (seen.has(m[0]) || m[0] === defName) continue;
    seen.add(m[0]);
    const other = m[1];
    const sym = resolve(m[0], sources, macros);
    const lv = other === "scalar" ? 3 : (sym ? effectiveLevel(m[0], sources, macros) : null);
    calls.push({ cName: m[0], cpp: m[0], level: lv, scalar: other === "scalar", foreign: other });
  }
  return {
    code, calls, rootFound: true, level: levelOf(root.code), effectiveLevel: effectiveLevel(rootName, sources, macros), rootName,
    tree: callTree(rootName, sources, macros), source: sourceOf(cleanCode(root, macros), root.table, mask),
  };
}

// ---------------------------------------------------------------------------------------------
// Call tree, names and sources (navigation in the Algorithm modal)
// ---------------------------------------------------------------------------------------------
const C_NAME_RE = /^mipp_([a-z0-9]+)_(\w+?)_((?:float|u?int)\d+(?:_(?:float|u?int)\d+)?)(?:_(mask|maskz|masks))?_(m\d|d2)$/;

/** {isa, func, dt (Explorer format: "float32" or "float32,int32"), mask, lmul ("1", "2", "-2")} */
export function parseCName(name) {
  const m = String(name).match(C_NAME_RE);
  if (!m) return null;
  return {
    isa: m[1], func: m[2], dt: m[3].replace(/_(?=(?:float|u?int)\d)/, ","), mask: m[4] || "unmasked",
    lmul: m[5] === "d2" ? "-2" : m[5].slice(1),
  };
}

/**
 * Functions called by a function, recursively: { cName, table, own, ownLabel, effective, children,
 * repeated }. `own` is the level of the function itself (its `// Level N` comment, null for the
 * software LMUL wrappers), `effective` the highest level of everything it uses.
 */
export function callTree(rootName, sources, macros, maxDepth = 6) {
  const seen = new Set();
  const node = (name, depth) => {
    const sym = resolve(name, sources, macros);
    if (!sym || sym.kind !== "func") return null;
    const code = cleanCode(sym, macros);
    const own = levelOf(code);
    const isScalarRef = sym.table === "scalar" && !rootName.startsWith("mipp_scalar_");
    const p = parseCName(name);
    const n = {
      cName: name, table: sym.table, own: own ? own.level : null, ownLabel: own ? own.label : null,
      kind: sourceOf(code, sym.table, p ? p.mask : "unmasked").kind,
      effective: isScalarRef ? null : effectiveLevel(name, sources, macros), children: [], repeated: seen.has(name),
    };
    if (n.repeated || depth >= maxDepth) return n;
    seen.add(name);
    const body = code.replace(/\/\/[^\n]*/g, "");
    const calls = (sym.deps || [])
      .map((d) => ({ d, at: body.search(new RegExp(`\\b${d}\\s*\\(`)) }))
      .filter((x) => x.at >= 0)
      .sort((a, b) => a.at - b.at);
    for (const { d } of calls) {
      const c = node(d, depth + 1);
      if (c) n.children.push(c);
    }
    return n;
  };
  return node(rootName, 0);
}

/** The call tree of the function of a configuration (same cfg as buildFlatCode). */
export function buildCallTree(sources, cfg) {
  const macros = targetMacros(cfg.isa, cfg.options, cfg.simdWidth, cfg.overrides);
  return callTree(cFunctionName(cfg.isa, cfg.func, cfg.dt, cfg.mask, cfg.lmul), sources, macros);
}

const INTRINSIC_RE = /\b(_mm\d*_\w+|__riscv_\w+|sv[a-z0-9_]+|v[a-z0-9]+q?_[a-z0-9_]+|_cvt\w+|__builtin_\w+)\s*\(/;

/**
 * What the body of a function is, from its code (the `// Level N` comment of the headers gives the
 * effective level, not the kind of the body):
 * { kind: native | dedicated | composition | fallback | lanewise | wrapper | scalar, path, what }.
 * `path` is the generator file that produces it (from the root of the repository).
 */
export function sourceOf(code, table, mask) {
  const lv = levelOf(code);
  const text = (String(code).match(/\/\/\s*Level[^\n]*/) || [""])[0];
  const body = String(code).split("{").slice(1).join("{").replace(/\/\/[^\n]*/g, "");
  if (table === "scalar") return { kind: "scalar", path: "generator/helpers_headers/registry_scalar_implems.json", what: "scalar reference" };
  if (!lv) return { kind: "wrapper", path: "generator/helpers_headers/codegen/lmul_orchestrator.py", what: "software LMUL wrapper: one call per register of the LMUL below" };
  if (/lane-wise|half of the software LMUL|each half of the result/.test(text)) {
    return { kind: "lanewise", path: "generator/helpers_headers/codegen/ldiv_mask.py", what: "generated from the LMUL 1 function" };
  }
  if (/\bmipp_scalar_\w+\s*\(/.test(body) && /\bmemcpy\s*\(/.test(body)) {
    return { kind: "fallback", path: "generator/helpers_headers/codegen/emit_helpers.py", what: "scalar fallback: copies the registers and calls the scalar reference" };
  }
  const intrinsics = INTRINSIC_RE.test(body);
  if (/software LMUL specific/.test(text)) {
    return { kind: "dedicated", path: `generator/simd_ext/${table}/${table}_sw_lmul.json`, what: "software LMUL template of the ISA" };
  }
  if (/half-vector specific/.test(text)) {
    return intrinsics
      ? { kind: "dedicated", path: `generator/simd_ext/${table}/${table}_ldiv_mask.json`, what: "half-vector template of the ISA" }
      : { kind: "composition", path: "generator/helpers_headers/generic_ldiv_mask.json", what: "generic half-vector template" };
  }
  if (!intrinsics && /\bmipp_\w+\s*\(/.test(body)) {
    return mask && mask !== "unmasked"
      ? { kind: "composition", path: "generator/helpers_headers/generic_emu_implems_mask.json", what: "generic emulation of the masked variants (templates: generic_emu_templates_mask.json)" }
      : { kind: "composition", path: "generator/helpers_headers/generic_emu_implems.json", what: "generic emulation (templates: generic_emu_templates.json)" };
  }
  if (lv.level === 1 || /\bmipp_\w+\s*\(/.test(body)) {
    return { kind: "dedicated", path: `generator/simd_ext/${table}/${table}_emu_implems.json`, what: "dedicated emulation (templates: _emu_templates.json)" };
  }
  return { kind: "native", path: `generator/simd_ext/${table}/${table}_native_implems.json`, what: "native implementation (templates: _native_templates.json)" };
}
