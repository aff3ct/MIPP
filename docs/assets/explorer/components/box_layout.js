/**
 * MIPP API Explorer - boxes shown side by side that can be moved and resized (the columns of
 * the "Compare ISAs" view of the Algorithm modal).
 *
 * Markup, written by the view:
 *   <div class="mipp-box-row">                         the container, a wrapping flex row
 *     <div class="mipp-box-cell" data-box-key="sse">   one cell per box, in the order shown
 *       <div class="mipp-code-box">
 *         <div data-box-handle draggable="true">       header of the box: drag it to move the box
 *           <span data-box-grip tabindex="0">          keyboard handle (arrow keys)
 *       ${boxResizeHandles()}                          gutters right of and below the box
 *
 * The order belongs to the view (it is part of the URL): `onReorder` receives the new one and
 * renders again. The sizes are a display preference: `onResize` receives the size of a box in
 * pixels ({ w, h }, each optional), or null when it is back to its automatic size.
 */
import { escapeHtml } from "../explorer.config.js";

const MIN_WIDTH = 220;
const MIN_HEIGHT = 120;
const KEY_STEP = 24; // pixels per key press

/** Inline style of a cell: the size chosen by the user, nothing for an automatic size. */
export function boxSizeStyle(size) {
  if (!size) return "";
  return `${size.w ? `flex: 0 0 ${size.w}px;` : ""}${size.h ? `height: ${size.h}px;` : ""}`;
}

/** Resize handles of a cell: its right gutter (width), its bottom gutter (height), their corner (both). */
export function boxResizeHandles(label) {
  const title = (what) => escapeHtml(`Drag to change the ${what} of the ${label} box, double-click for the automatic ${what}`);
  return `
    <span class="mipp-box-resize mipp-box-resize-x" data-box-resize="x" title="${title("width")}"></span>
    <span class="mipp-box-resize mipp-box-resize-y" data-box-resize="y" title="${title("height")}"></span>
    <span class="mipp-box-resize mipp-box-resize-xy" data-box-resize="xy" title="${title("size")}"></span>`;
}

function applySize(cell, size) {
  cell.style.flex = size && size.w ? `0 0 ${size.w}px` : "";
  cell.style.height = size && size.h ? `${size.h}px` : "";
}

// Screen readers: what a key press did (the boxes are rendered again at each move)
let liveRegion = null;
function announce(text) {
  if (!liveRegion) {
    liveRegion = document.createElement("div");
    liveRegion.className = "mipp-sr-only";
    liveRegion.setAttribute("aria-live", "polite");
    document.body.appendChild(liveRegion);
  }
  liveRegion.textContent = text;
}

/**
 * Binds the boxes of `containerEl`.
 *   sizes:     { key: { w, h } }, the sizes chosen so far
 *   labels:    { key: name of the box }, for the announcements
 *   focusKey:  box whose keyboard handle takes the focus (the one moved with the keyboard before this render)
 *   onReorder: (keys in their new order, moved key, moved with the keyboard) => void
 *   onResize:  (key, { w, h } or null) => void
 */
export function bindBoxLayout(containerEl, { sizes = {}, labels = {}, focusKey = null, onReorder, onResize }) {
  const cells = [...containerEl.querySelectorAll(":scope > [data-box-key]")];
  const keyOf = (cell) => cell.getAttribute("data-box-key");
  const order = cells.map(keyOf);
  const nameOf = (key) => labels[key] || key;

  const move = (key, to, keyboard = false) => {
    const from = order.indexOf(key);
    const target = Math.max(0, Math.min(order.length - 1, to));
    if (from < 0 || target === from) return;
    const next = order.filter((k) => k !== key);
    next.splice(target, 0, key);
    announce(`${nameOf(key)} moved to position ${target + 1} of ${order.length}`);
    onReorder(next, key, keyboard);
  };

  // ---- drag and drop: the header of a box is its handle -----------------------------------
  let dragged = null;
  const clearDrop = () => cells.forEach((c) => c.classList.remove("drop-before", "drop-after"));

  /** Where the dragged box would go: { index in the order without it, cell, after } or null when it would not move. */
  const dropTarget = (e) => {
    const others = cells.filter((c) => c !== dragged);
    if (!others.length) return null;
    const rects = new Map(others.map((c) => [c, c.getBoundingClientRect()]));
    const gap = (c) => {
      const r = rects.get(c);
      const dx = Math.max(r.left - e.clientX, 0, e.clientX - r.right);
      const dy = Math.max(r.top - e.clientY, 0, e.clientY - r.bottom);
      return dx * dx + dy * dy;
    };
    const cell = others.reduce((best, c) => (gap(c) < gap(best) ? c : best));
    const r = rects.get(cell);
    // boxes stacked in one column: the vertical half of the box decides
    const stacked = cells.every((c) => Math.abs(c.getBoundingClientRect().left - cells[0].getBoundingClientRect().left) < 2);
    const after = stacked ? e.clientY > r.top + r.height / 2 : e.clientX > r.left + r.width / 2;
    const index = others.indexOf(cell) + (after ? 1 : 0);
    return index === cells.indexOf(dragged) ? null : { index, cell, after };
  };

  cells.forEach((cell) => {
    const handle = cell.querySelector("[data-box-handle]");
    if (!handle) return;
    handle.addEventListener("dragstart", (e) => {
      dragged = cell;
      e.dataTransfer.effectAllowed = "move";
      e.dataTransfer.setData("text/plain", keyOf(cell));
      const r = cell.getBoundingClientRect();
      e.dataTransfer.setDragImage(cell, e.clientX - r.left, e.clientY - r.top);
      // after the browser took the picture of the box that follows the pointer
      requestAnimationFrame(() => cell.classList.add("is-dragging"));
    });
    handle.addEventListener("dragend", () => {
      cell.classList.remove("is-dragging");
      clearDrop();
      dragged = null;
    });
  });

  const onDragOver = (e) => {
    if (!dragged) return;
    e.preventDefault();
    e.dataTransfer.dropEffect = "move";
    const target = dropTarget(e);
    clearDrop();
    if (target) target.cell.classList.add(target.after ? "drop-after" : "drop-before");
  };
  containerEl.addEventListener("dragenter", onDragOver);
  containerEl.addEventListener("dragover", onDragOver);
  containerEl.addEventListener("drop", (e) => {
    if (!dragged) return;
    e.preventDefault();
    const target = dropTarget(e);
    const key = keyOf(dragged);
    dragged.classList.remove("is-dragging");
    clearDrop();
    dragged = null;
    if (target) move(key, target.index);
  });

  // ---- resize: the gutters right of and below a box ---------------------------------------
  const maxWidth = () => {
    const style = getComputedStyle(containerEl);
    return containerEl.clientWidth - parseFloat(style.paddingLeft) - parseFloat(style.paddingRight);
  };
  const resized = (cell, size) => {
    const kept = size && (size.w || size.h) ? size : null;
    applySize(cell, kept);
    onResize(keyOf(cell), kept);
  };

  cells.forEach((cell) => {
    const key = keyOf(cell);
    cell.querySelectorAll(":scope > [data-box-resize]").forEach((handle) => {
      const axis = handle.getAttribute("data-box-resize");
      handle.addEventListener("pointerdown", (e) => {
        if (e.button !== 0) return;
        e.preventDefault();
        handle.setPointerCapture(e.pointerId);
        const r = cell.getBoundingClientRect();
        const limit = maxWidth();
        let size = { ...(sizes[key] || {}) };
        document.documentElement.classList.add("mipp-box-resizing");
        handle.classList.add("active");
        const onMove = (ev) => {
          if (axis.includes("x")) size.w = Math.round(Math.max(MIN_WIDTH, Math.min(limit, r.width + ev.clientX - e.clientX)));
          if (axis.includes("y")) size.h = Math.round(Math.max(MIN_HEIGHT, r.height + ev.clientY - e.clientY));
          applySize(cell, size);
        };
        const onEnd = () => {
          handle.removeEventListener("pointermove", onMove);
          handle.removeEventListener("pointerup", onEnd);
          handle.removeEventListener("pointercancel", onEnd);
          document.documentElement.classList.remove("mipp-box-resizing");
          handle.classList.remove("active");
          resized(cell, size);
        };
        handle.addEventListener("pointermove", onMove);
        handle.addEventListener("pointerup", onEnd);
        handle.addEventListener("pointercancel", onEnd);
      });
      // back to the automatic size on this axis
      handle.addEventListener("dblclick", (e) => {
        e.preventDefault();
        const size = { ...(sizes[key] || {}) };
        if (axis.includes("x")) delete size.w;
        if (axis.includes("y")) delete size.h;
        resized(cell, size);
      });
    });
  });

  // ---- keyboard: arrow keys on the handle of a box move it, with Shift they resize it -----
  cells.forEach((cell) => {
    const key = keyOf(cell);
    const grip = cell.querySelector("[data-box-grip]");
    if (!grip) return;
    grip.addEventListener("keydown", (e) => {
      const arrows = { ArrowLeft: [-1, 0], ArrowRight: [1, 0], ArrowUp: [0, -1], ArrowDown: [0, 1] };
      const dir = arrows[e.key];
      if (e.altKey || e.ctrlKey || e.metaKey) return;
      if (dir && e.shiftKey) {
        e.preventDefault();
        const r = cell.getBoundingClientRect();
        const size = { ...(sizes[key] || {}) };
        if (dir[0]) size.w = Math.round(Math.max(MIN_WIDTH, Math.min(maxWidth(), r.width + dir[0] * KEY_STEP)));
        if (dir[1]) size.h = Math.round(Math.max(MIN_HEIGHT, r.height + dir[1] * KEY_STEP));
        resized(cell, size);
        announce(`${nameOf(key)}: ${dir[0] ? `${size.w} pixels wide` : `${size.h} pixels high`}`);
      } else if (dir) {
        e.preventDefault();
        move(key, order.indexOf(key) + (dir[0] || dir[1]), true);
      } else if (e.key === "Home" || e.key === "End") {
        e.preventDefault();
        move(key, e.key === "Home" ? 0 : order.length - 1, true);
      } else if ((e.key === "Delete" || e.key === "Backspace") && sizes[key]) {
        e.preventDefault();
        resized(cell, null);
        announce(`${nameOf(key)}: automatic size`);
      }
    });
    if (key === focusKey) grip.focus({ preventScroll: true });
  });
}
