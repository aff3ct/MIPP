/**
 * MIPP API Explorer - "Dependencies" box of the Algorithm modal.
 * The call graph of a function (algo_source.js, callGraph) drawn in SVG, from left to right, colored
 * by effective level: as a DAG (one column per depth, the longest path from the function, each
 * function once) or as a tree (the DAG unfolded, one node per call). Drag to move, Ctrl + wheel or
 * pinch to zoom, hover a function to see what it uses, click it to open it in the modal.
 *
 * renderCallGraph returns the HTML of the box (layout computed here, no library); initCallGraphs
 * attaches the interactions once the HTML is in the page.
 */
import { escapeHtml } from "../explorer.config.js";

const FONT_PX = 11;          // labels (monospace)
const CHAR_PX = 6.7;         // width of a character of the labels
const NODE_H = 26;
const NODE_PAD = 10;         // inside a node, on each side of the label
const BADGE_W = 22;          // level, on the right of a node
const SLOT_GAP = 12;         // between two nodes of a column
const DUMMY_H = 10;          // slot of an edge that crosses a column
const COL_GAP = 64;
const MARGIN = 16;
const MIN_SCALE = 0.05;      // "Fit" shows the whole tree of an LMUL 8 wrapper
const MAX_SCALE = 2.5;

// ---------------------------------------------------------------------------------------------
// Layout: layers (longest path), order (barycenters), coordinates
// ---------------------------------------------------------------------------------------------

/**
 * { nodes: [{ id, x, y, w, h, layer, dummy }], edges: [{ from, to, points: [[x, y], ...] }],
 *   width, height }. `graph.nodes[0]` is the root; an edge that spans several columns goes
 * through one dummy node per column it crosses.
 */
export function layoutCallGraph(graph, labelOf) {
  const n = graph.nodes.length;
  const index = new Map(graph.nodes.map((v, i) => [v.cName, i]));
  const succ = Array.from({ length: n }, () => []);
  const times = new Map(); // "i j" -> number of calls
  for (const [a, b, k] of graph.edges) {
    const i = index.get(a);
    const j = index.get(b);
    if (i !== undefined && j !== undefined && i !== j && !succ[i].includes(j)) succ[i].push(j);
    if (i !== undefined && j !== undefined) times.set(`${i} ${j}`, k || 1);
  }

  // topological order from the root (an edge back to a function on the current path is ignored)
  const order = [];
  const state = new Uint8Array(n); // 0: new, 1: on the path, 2: done
  const kept = Array.from({ length: n }, () => []);
  const dfs = (i) => {
    state[i] = 1;
    for (const j of succ[i]) {
      if (state[j] === 1) continue;
      kept[i].push(j);
      if (state[j] === 0) dfs(j);
    }
    state[i] = 2;
    order.push(i);
  };
  for (let i = 0; i < n; i++) if (state[i] === 0) dfs(i);
  order.reverse();

  // longest path: a function is one column after the deepest of its callers
  const layer = new Array(n).fill(0);
  for (const i of order) for (const j of kept[i]) layer[j] = Math.max(layer[j], layer[i] + 1);

  // nodes of the drawing: the functions, then the dummies of the long edges
  const nodes = graph.nodes.map((v, i) => ({ id: i, layer: layer[i], dummy: false, w: labelOf(v).w, h: NODE_H }));
  const pred = Array.from({ length: n }, () => []);
  const chains = []; // per edge of the graph: the drawing nodes it goes through
  for (let i = 0; i < n; i++) {
    for (const j of kept[i]) {
      const chain = [i];
      for (let l = layer[i] + 1; l < layer[j]; l++) {
        const d = nodes.length;
        nodes.push({ id: d, layer: l, dummy: true, w: 0, h: DUMMY_H });
        pred.push([]);
        chain.push(d);
      }
      chain.push(j);
      for (let k = 1; k < chain.length; k++) pred[chain[k]].push(chain[k - 1]);
      chains.push({ from: i, to: j, chain });
    }
  }
  const next = nodes.map(() => []);
  pred.forEach((ps, v) => ps.forEach((u) => next[u].push(v)));

  // order in each column: first seen first (DFS from the root), then barycenter sweeps
  const nLayers = Math.max(0, ...nodes.map((v) => v.layer)) + 1;
  const columns = Array.from({ length: nLayers }, () => []);
  const seen = new Set();
  const visit = (v) => {
    if (seen.has(v)) return;
    seen.add(v);
    columns[nodes[v].layer].push(v);
    next[v].forEach(visit);
  };
  for (const i of order) visit(i);
  nodes.forEach((v) => visit(v.id));
  const pos = new Array(nodes.length);
  const setPos = () => columns.forEach((col) => col.forEach((v, k) => { pos[v] = k; }));
  setPos();
  const sweep = (from, to, step, links) => {
    for (let l = from; l !== to; l += step) {
      const col = columns[l];
      const bary = new Map(col.map((v) => {
        const ls = links[v];
        return [v, ls.length ? ls.reduce((s, u) => s + pos[u], 0) / ls.length : pos[v]];
      }));
      col.sort((a, b) => bary.get(a) - bary.get(b) || pos[a] - pos[b]);
      col.forEach((v, k) => { pos[v] = k; });
    }
  };
  for (let it = 0; it < 4; it++) {
    sweep(1, nLayers, 1, pred);
    sweep(nLayers - 2, -1, -1, next);
  }

  // coordinates: columns side by side, each one centered vertically
  const colW = columns.map((col) => Math.max(0, ...col.map((v) => nodes[v].w)));
  const colH = columns.map((col) => col.reduce((s, v) => s + nodes[v].h, 0) + SLOT_GAP * Math.max(0, col.length - 1));
  const height = Math.max(NODE_H, ...colH) + 2 * MARGIN;
  let x = MARGIN;
  columns.forEach((col, l) => {
    let y = MARGIN + (height - 2 * MARGIN - colH[l]) / 2;
    for (const v of col) {
      const node = nodes[v];
      node.x = x + (node.dummy ? colW[l] / 2 : 0);
      node.y = y;
      node.colW = colW[l];
      y += node.h + SLOT_GAP;
    }
    x += colW[l] + COL_GAP;
  });
  const width = x - COL_GAP + MARGIN;

  const edges = chains.map(({ from, to, chain }) => ({
    from, to, times: times.get(`${from} ${to}`) || 1,
    points: chain.map((v, k) => {
      const node = nodes[v];
      const cy = node.y + node.h / 2;
      if (node.dummy) return [node.x, cy];
      return k === 0 ? [node.x + node.w, cy] : [node.x, cy];
    }),
  }));
  return { nodes, edges, width, height };
}

/**
 * Elbow from a parent to a child of the tree: horizontal, vertical in the middle of the gap before
 * the column of the child (the same line for all the children of a parent), horizontal again,
 * with rounded corners.
 */
function elbowPath([[x0, y0], [x1, y1]]) {
  const xm = x1 - COL_GAP / 2;
  const dy = y1 - y0;
  const r = Math.min(6, Math.abs(dy) / 2);
  const f = (v) => v.toFixed(1);
  if (r < 0.5) return `M${f(x0)},${f(y0)} H${f(x1)}`;
  const s = Math.sign(dy);
  return `M${f(x0)},${f(y0)} H${f(xm - r)} Q${f(xm)},${f(y0)} ${f(xm)},${f(y0 + s * r)} V${f(y1 - s * r)} Q${f(xm)},${f(y1)} ${f(xm + r)},${f(y1)} H${f(x1)}`;
}

/** Smooth path through the points (horizontal tangents at each point). */
function edgePath(points) {
  let d = `M${points[0][0].toFixed(1)},${points[0][1].toFixed(1)}`;
  for (let k = 1; k < points.length; k++) {
    const [x0, y0] = points[k - 1];
    const [x1, y1] = points[k];
    const dx = Math.max(16, (x1 - x0) / 2);
    d += ` C${(x0 + dx).toFixed(1)},${y0.toFixed(1)} ${(x1 - dx).toFixed(1)},${y1.toFixed(1)} ${x1.toFixed(1)},${y1.toFixed(1)}`;
  }
  return d;
}

// ---------------------------------------------------------------------------------------------
// Tree: the DAG unfolded from the root (one node per call)
// ---------------------------------------------------------------------------------------------
const TREE_MAX_NODES = 1000; // above, the Tree view is not offered (the unfolding can grow fast)

/**
 * The call tree of the graph: the DAG unfolded from its root, one node per call (a function called
 * by three functions is three nodes; an LMUL wrapper that calls the function of the LMUL below on
 * the two halves has two children). { nodes: [{ fn (index in graph.nodes), depth }], children:
 * [[node, ...]] }, or { size } when it would have more than `maxNodes` nodes.
 */
export function unfoldCallGraph(graph, maxNodes = TREE_MAX_NODES) {
  const index = new Map(graph.nodes.map((v, i) => [v.cName, i]));
  const succ = graph.nodes.map(() => []);
  const times = graph.nodes.map(() => new Map()); // callee -> number of calls
  for (const [a, b, k] of graph.edges) {
    const i = index.get(a);
    const j = index.get(b);
    if (i === undefined || j === undefined || i === j) continue;
    if (!succ[i].includes(j)) succ[i].push(j);
    times[i].set(j, Math.max(times[i].get(j) || 0, k || 1));
  }
  // size first (number of paths, memoized): the unfolding is built only when it is small enough
  const memo = new Map();
  const onPath = new Set();
  const size = (i) => {
    if (memo.has(i)) return memo.get(i);
    onPath.add(i);
    let n = 1;
    for (const j of succ[i]) if (!onPath.has(j)) n += times[i].get(j) * size(j);
    onPath.delete(i);
    memo.set(i, n);
    return n;
  };
  const total = size(0);
  if (total > maxNodes) return { size: total };
  const nodes = [];
  const children = [];
  const visit = (i, depth, path) => {
    const id = nodes.length;
    nodes.push({ fn: i, depth });
    children.push([]);
    path.add(i);
    for (const j of succ[i]) {
      if (path.has(j)) continue;
      for (let c = 0; c < times[i].get(j); c++) children[id].push(visit(j, depth + 1, path));
    }
    path.delete(i);
    return id;
  };
  visit(0, 0, new Set());
  return { nodes, children };
}

/**
 * Tidy layout of a tree, from left to right: one column per depth, the leaves one below the
 * other in the order of the calls, a parent centered on its children.
 */
function layoutTree(tree, widthOf) {
  const nDepth = Math.max(...tree.nodes.map((t) => t.depth)) + 1;
  const colW = new Array(nDepth).fill(0);
  tree.nodes.forEach((t) => { colW[t.depth] = Math.max(colW[t.depth], widthOf(t.fn)); });
  const colX = [];
  let x = MARGIN;
  colW.forEach((w) => { colX.push(x); x += w + COL_GAP; });
  const nodes = tree.nodes.map((t) => ({ x: colX[t.depth], y: 0, w: widthOf(t.fn), h: NODE_H }));
  let nextY = MARGIN;
  const place = (id) => {
    const kids = tree.children[id];
    if (!kids.length) {
      nodes[id].y = nextY;
      nextY += NODE_H + SLOT_GAP;
    } else {
      kids.forEach(place);
      nodes[id].y = (nodes[kids[0]].y + nodes[kids[kids.length - 1]].y) / 2;
    }
  };
  place(0);
  const edges = [];
  tree.children.forEach((kids, id) => kids.forEach((k) => edges.push({
    from: id, to: k, elbow: true,
    points: [[nodes[id].x + nodes[id].w, nodes[id].y + NODE_H / 2], [nodes[k].x, nodes[k].y + NODE_H / 2]],
  })));
  return { nodes, edges, width: x - COL_GAP + MARGIN, height: nextY - SLOT_GAP + MARGIN };
}

// ---------------------------------------------------------------------------------------------
// Rendering
// ---------------------------------------------------------------------------------------------

/** Nodes and edges of a drawing in SVG. `fnOf(i)`: the index of the function of the node i. */
function drawScene(lay, n, fnOf, graph, info, labels) {
  const edgesSvg = lay.edges.map((e, k) => `<path class="mipp-dag-edge" data-dag-edge="${k}" data-from="${e.from}" data-to="${e.to}" d="${e.elbow ? elbowPath(e.points) : edgePath(e.points)}" marker-end="url(#mipp-dag-arrow)"></path>`).join("");
  // DAG: a function called several times by the same function, "×k" before the arrow
  const times = lay.edges.map((e) => {
    if (e.elbow || !(e.times > 1)) return "";
    const [x, y] = e.points[e.points.length - 1];
    return `<text class="mipp-dag-times" data-from="${e.from}" data-to="${e.to}" x="${(x - 12).toFixed(1)}" y="${(y - 5).toFixed(1)}" text-anchor="end">×${e.times}</text>`;
  }).join("");
  const out = Array.from({ length: n }, () => new Set());
  lay.edges.forEach((e) => out[e.from].add(e.to));
  const nodesSvg = Array.from({ length: n }, (_, i) => {
    const f = fnOf(i);
    const v = graph.nodes[f];
    const node = lay.nodes[i];
    const d = info[f];
    const lv = v.effective === null || v.effective === undefined ? "na" : v.effective;
    const nav = f > 0 && d.nav ? Object.entries(d.nav).map(([k, val]) => ` data-algo-nav-${k}="${escapeHtml(val)}"`).join("") : "";
    return `<g class="mipp-dag-node lvl-${lv}${i === 0 ? " mipp-dag-node--root" : ""}${nav ? " mipp-dag-node--link" : ""}" data-dag-node="${i}" data-fn="${f}" data-out="${[...out[i]].join(",")}" data-tip="${escapeHtml(JSON.stringify(d.tip))}"${nav}${nav ? ' tabindex="0" role="button"' : ""} aria-label="${escapeHtml(d.tip[0])}" transform="translate(${node.x.toFixed(1)},${node.y.toFixed(1)})">
        <rect class="mipp-dag-node-bg" width="${node.w}" height="${NODE_H}" rx="6"></rect>
        <rect width="${node.w}" height="${NODE_H}" rx="6"></rect>
        <text class="mipp-dag-label" x="${NODE_PAD}" y="${NODE_H / 2}" dominant-baseline="central">${escapeHtml(labels[f].text)}</text>
        <text class="mipp-dag-level" x="${node.w - BADGE_W / 2 - 4}" y="${NODE_H / 2}" dominant-baseline="central" text-anchor="middle">${lv === "na" ? "–" : `L${lv}`}</text>
      </g>`;
  }).join("");
  return edgesSvg + times + nodesSvg;
}

/**
 * HTML of the Dependencies box, with three views (`opts.view`): "dag" (the default: every
 * function once), "tree" (the DAG unfolded: one node per call) and "text" (`opts.treeList`, the
 * <li> of the call tree of the modal: each function with what its body is, recursively).
 * `describe(node)` gives { text (label), isa (ISA of another table, or ""), nav (data-algo-nav-*
 * attributes, or null), tip (lines of the tooltip) } for a node of the graph.
 */
export function renderCallGraph(graph, describe, docsUrl, opts = {}) {
  if (!graph || !graph.nodes.length) return "";
  const tree = unfoldCallGraph(graph);
  const treeOk = Boolean(tree.nodes);
  let view = ["dag", "tree", "text"].includes(opts.view) ? opts.view : "dag";
  if ((view === "text" && !opts.treeList) || (view === "tree" && !treeOk)) view = "dag";

  const info = graph.nodes.map((v) => describe(v));
  const labels = info.map((d) => {
    const text = d.isa ? `${d.text} · ${d.isa}` : d.text;
    return { text, w: Math.ceil(text.length * CHAR_PX) + 2 * NODE_PAD + BADGE_W };
  });

  let body = "";
  if (view === "text") {
    body = `<ul>${opts.treeList}</ul>`;
  } else {
    const isTree = view === "tree";
    const lay = isTree
      ? layoutTree(tree, (f) => labels[f].w)
      : layoutCallGraph(graph, (v) => labels[graph.nodes.indexOf(v)]);
    const n = isTree ? tree.nodes.length : graph.nodes.length;
    const scene = drawScene(lay, n, isTree ? (i) => tree.nodes[i].fn : (i) => i, graph, info, labels);
    const what = isTree ? `Call tree: ${n} calls of ${graph.nodes.length} functions` : `Call graph: ${graph.nodes.length} functions, ${graph.edges.length} calls`;
    body = `
      <div class="mipp-dag-viewport" data-dag-viewport data-width="${lay.width.toFixed(0)}" data-height="${lay.height.toFixed(0)}" data-root-y="${(lay.nodes[0].y + NODE_H / 2).toFixed(0)}" style="height: ${Math.min(520, Math.max(120, Math.ceil(lay.height)))}px">
        <svg class="mipp-dag-svg" xmlns="http://www.w3.org/2000/svg" role="img" aria-label="${what}" style="font-size: ${FONT_PX}px">
          <defs>
            <marker id="mipp-dag-arrow" viewBox="0 0 10 10" refX="9" refY="5" markerWidth="7" markerHeight="7" orient="auto-start-reverse">
              <path d="M0,0 L10,5 L0,10 z" class="mipp-dag-arrow"></path>
            </marker>
          </defs>
          <g data-dag-scene>${scene}</g>
        </svg>
        <div class="mipp-dag-tip" data-dag-tip hidden></div>
      </div>`;
  }

  const legend = [0, 1, 2, 3].map((l) => `<span class="mipp-isa-badge lvl-${l}">L${l}</span>`).join("");
  const levels = `<a href="${docsUrl}implementation_levels/" target="_blank">implementation levels</a>`;
  const VIEWS = [
    ["dag", "DAG", "Directed acyclic graph: every function once, from left to right", true],
    ["tree", "Tree", treeOk ? "The graph unfolded: one node per call, a function used by several functions is drawn once per call"
      : `The graph unfolded would have ${tree.size} nodes: too many to draw, see the DAG or the text`, treeOk],
    ["text", "Text", "Each function with what its body is and its level, recursively", Boolean(opts.treeList)],
  ];
  const toggle = `
          <div class="mipp-segmented-group mipp-dag-views" role="group" aria-label="View of the dependencies">
            ${VIEWS.map(([id, label, title, ok]) => `<button type="button" class="mipp-segment-btn ${id === view ? "active" : ""}" data-deps-view="${id}" title="${escapeHtml(title)}" aria-pressed="${id === view}"${ok ? "" : " disabled"}>${label}</button>`).join("")}
          </div>`;
  const moves = "Drag to move, Ctrl + wheel or pinch to zoom, click a function to open it.";
  const own = {
    dag: `— every function it uses, once each, from left to right; the color is the effective level (${levels}). ${moves}`,
    tree: `— every call: a function used by several functions is drawn once per call (hover one to see the others); the color is the effective level (${levels}). ${moves}`,
    text: `— each function with what its body is and its level: the highest level of everything it uses (${levels})`,
  }[view];
  const zoom = view !== "text" ? `
          <button type="button" class="mipp-icon-btn" data-dag-zoom="out" title="Zoom out" aria-label="Zoom out">−</button>
          <button type="button" class="mipp-icon-btn" data-dag-zoom="in" title="Zoom in" aria-label="Zoom in">+</button>
          <button type="button" class="mipp-icon-btn mipp-dag-fit" data-dag-zoom="fit" title="Fit the whole graph" aria-label="Fit the whole graph">Fit</button>` : "";
  return `
    <div class="mipp-algo-tree mipp-dag">
      <div class="mipp-dag-head">
        <div class="mipp-algo-tree-title">Dependencies <span class="mipp-algo-tree-own">${own}</span></div>
        <div class="mipp-dag-tools">
          ${toggle}
          <span class="mipp-dag-legend">${legend}</span>${zoom}
        </div>
      </div>
      ${body}
    </div>`;
}

// ---------------------------------------------------------------------------------------------
// Interactions: pan, zoom, hover, click
// ---------------------------------------------------------------------------------------------

function initOne(box) {
  const vp = box.querySelector("[data-dag-viewport]");
  const scene = box.querySelector("[data-dag-scene]");
  const tip = box.querySelector("[data-dag-tip]");
  if (!vp || !scene || vp.dataset.dagReady) return;
  vp.dataset.dagReady = "1";
  const W = Number(vp.dataset.width);
  const H = Number(vp.dataset.height);
  const view = { x: 0, y: 0, k: 1 };
  const apply = () => scene.setAttribute("transform", `translate(${view.x.toFixed(1)},${view.y.toFixed(1)}) scale(${view.k.toFixed(4)})`);
  const clampK = (k) => Math.min(MAX_SCALE, Math.max(MIN_SCALE, k));

  // first view: readable (the whole height down to 80%), the root on the left and centered vertically
  const initial = () => {
    const r = vp.getBoundingClientRect();
    view.k = clampK(Math.max(0.8, Math.min(1, r.height / H)));
    view.x = W * view.k < r.width ? (r.width - W * view.k) / 2 : 0;
    if (H * view.k <= r.height) {
      view.y = (r.height - H * view.k) / 2;
    } else {
      const rootY = Number(vp.dataset.rootY) * view.k;
      view.y = Math.min(0, Math.max(r.height - H * view.k, r.height / 2 - rootY));
    }
    apply();
  };
  const fit = () => {
    const r = vp.getBoundingClientRect();
    view.k = clampK(Math.min(r.width / W, r.height / H, 1));
    view.x = (r.width - W * view.k) / 2;
    view.y = (r.height - H * view.k) / 2;
    apply();
  };
  const zoomAt = (factor, cx, cy) => {
    const k = clampK(view.k * factor);
    view.x = cx - ((cx - view.x) * k) / view.k;
    view.y = cy - ((cy - view.y) * k) / view.k;
    view.k = k;
    apply();
  };
  initial();

  box.querySelectorAll("[data-dag-zoom]").forEach((btn) => btn.addEventListener("click", (e) => {
    e.stopPropagation();
    const r = vp.getBoundingClientRect();
    const what = btn.getAttribute("data-dag-zoom");
    if (what === "fit") fit();
    else zoomAt(what === "in" ? 1.25 : 0.8, r.width / 2, r.height / 2);
  }));

  // wheel: horizontal scroll moves the graph, Ctrl + wheel (and the pinch of a trackpad) zooms;
  // the vertical wheel alone scrolls the modal
  vp.addEventListener("wheel", (e) => {
    const r = vp.getBoundingClientRect();
    if (e.ctrlKey || e.metaKey) {
      e.preventDefault();
      zoomAt(Math.exp(-e.deltaY * 0.01), e.clientX - r.left, e.clientY - r.top);
    } else if (Math.abs(e.deltaX) > Math.abs(e.deltaY) || e.shiftKey) {
      e.preventDefault();
      view.x -= e.shiftKey && !e.deltaX ? e.deltaY : e.deltaX;
      apply();
    }
  }, { passive: false });

  // drag with one pointer, pinch with two
  const pointers = new Map();
  let moved = 0;
  let pinch = null;
  let suppressClick = false; // the click that ends a drag
  vp.addEventListener("pointerdown", (e) => {
    if (e.button !== 0) return;
    pointers.set(e.pointerId, { x: e.clientX, y: e.clientY });
    moved = 0;
    if (pointers.size === 2) {
      const [a, b] = [...pointers.values()];
      pinch = { d: Math.hypot(a.x - b.x, a.y - b.y), k: view.k };
    }
  });
  vp.addEventListener("pointermove", (e) => {
    const p = pointers.get(e.pointerId);
    if (!p) return;
    const dx = e.clientX - p.x;
    const dy = e.clientY - p.y;
    p.x = e.clientX;
    p.y = e.clientY;
    moved += Math.abs(dx) + Math.abs(dy);
    if (moved > 4 && !vp.hasPointerCapture(e.pointerId)) {
      vp.setPointerCapture(e.pointerId);
      vp.classList.add("mipp-dag-viewport--dragging");
      tip.hidden = true;
    }
    if (pointers.size === 2 && pinch) {
      const [a, b] = [...pointers.values()];
      const r = vp.getBoundingClientRect();
      const d = Math.hypot(a.x - b.x, a.y - b.y);
      zoomAt((pinch.k * (d / pinch.d)) / view.k, (a.x + b.x) / 2 - r.left, (a.y + b.y) / 2 - r.top);
    } else if (moved > 4) {
      view.x += dx;
      view.y += dy;
      apply();
    }
  });
  const release = (e) => {
    if (!pointers.has(e.pointerId)) return;
    pointers.delete(e.pointerId);
    if (moved > 4) {
      suppressClick = true;
      setTimeout(() => { suppressClick = false; }, 0); // no click follows a drag that ends outside
    }
    if (pointers.size < 2) pinch = null;
    if (!pointers.size) vp.classList.remove("mipp-dag-viewport--dragging");
  };
  vp.addEventListener("pointerup", release);
  vp.addEventListener("pointercancel", release);
  // a drag that ends on a function does not open it
  vp.addEventListener("click", (e) => {
    if (!suppressClick) return;
    suppressClick = false;
    e.stopPropagation();
    e.preventDefault();
  }, true);

  // hover: the function, everything it uses (and the calls between them) stand out
  const nodeEls = [...scene.querySelectorAll("[data-dag-node]")];
  const edgeEls = [...scene.querySelectorAll("[data-dag-edge], .mipp-dag-times")];
  const out = nodeEls.map((el) => (el.dataset.out ? el.dataset.out.split(",").map(Number) : []));
  const highlight = (i) => {
    if (i === null) {
      box.classList.remove("mipp-dag--focus");
      nodeEls.forEach((el) => el.classList.remove("is-on", "is-twin"));
      edgeEls.forEach((el) => el.classList.remove("is-on"));
      return;
    }
    const on = new Set([i]);
    const stack = [i];
    while (stack.length) for (const j of out[stack.pop()]) if (!on.has(j)) { on.add(j); stack.push(j); }
    box.classList.add("mipp-dag--focus");
    const fn = nodeEls[i].dataset.fn;
    nodeEls.forEach((el, k) => {
      el.classList.toggle("is-on", on.has(k));
      el.classList.toggle("is-twin", k !== i && el.dataset.fn === fn);
    });
    edgeEls.forEach((el) => el.classList.toggle("is-on", on.has(Number(el.dataset.from)) && on.has(Number(el.dataset.to))));
  };
  // The tooltip goes on the left of the function: what it uses is on its right. Without room on
  // the left, above the function, else below it (never over its dependencies).
  const showTip = (el) => {
    let lines = [];
    try { lines = JSON.parse(el.dataset.tip || "[]"); } catch (err) { lines = []; }
    tip.innerHTML = lines.map((l, k) => (k === 0 ? `<code>${escapeHtml(l)}</code>` : `<div>${escapeHtml(l)}</div>`)).join("");
    tip.hidden = false;
    const r = vp.getBoundingClientRect();
    const n = el.getBoundingClientRect();
    const tw = tip.offsetWidth;
    const th = tip.offsetHeight;
    const gap = 10;
    const clampY = (y) => Math.min(Math.max(4, y), Math.max(4, r.height - th - 4));
    const clampX = (x) => Math.min(Math.max(4, x), Math.max(4, r.width - tw - 4));
    let x;
    let y;
    if (n.left - r.left - gap - tw >= 4) {
      x = n.left - r.left - gap - tw;
      y = clampY(n.top - r.top + n.height / 2 - th / 2);
    } else if (n.top - r.top - gap - th >= 4) {
      x = clampX(n.left - r.left);
      y = n.top - r.top - gap - th;
    } else {
      x = clampX(n.left - r.left);
      y = clampY(n.bottom - r.top + gap);
    }
    tip.style.left = `${x}px`;
    tip.style.top = `${y}px`;
  };
  nodeEls.forEach((el, i) => {
    el.addEventListener("pointerenter", () => { if (!pointers.size) { highlight(i); showTip(el); } });
    el.addEventListener("pointerleave", () => { highlight(null); tip.hidden = true; });
    el.addEventListener("focus", () => { highlight(i); showTip(el); });
    el.addEventListener("blur", () => { highlight(null); tip.hidden = true; });
    el.addEventListener("keydown", (e) => {
      if (e.key === "Enter" || e.key === " ") { e.preventDefault(); el.dispatchEvent(new MouseEvent("click", { bubbles: true })); }
    });
  });
}

/** Attaches the interactions of the DAG boxes under `root` (after each render of the modal). */
export function initCallGraphs(root) {
  if (!root) return;
  root.querySelectorAll(".mipp-dag").forEach(initOne);
}
