/**
 * MIPP Documentation - Header height CSS variable
 * Exposes the rendered height of the sticky header (title bar + tabs) as
 * --mipp-md-header-height on :root, so that the sticky sidebars stick right
 * under it. The height depends on the logo, the repository block and the
 * fonts, hence measured rather than hard-coded.
 * Not to be confused with --mipp-header-height, the height of the API
 * Explorer's own sticky search bar (assets/explorer/main.js).
 */

(function () {
  function update(header) {
    const height = header.getBoundingClientRect().height;
    if (height > 0) {
      document.documentElement.style.setProperty("--mipp-md-header-height", height + "px");
    }
  }

  function init() {
    const header = document.querySelector(".md-header");
    if (!header) return;
    update(header);
    // Header persists across instant navigations: one observer is enough
    if (typeof ResizeObserver !== "undefined") {
      new ResizeObserver(() => update(header)).observe(header);
    }
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", init);
  } else {
    init();
  }
})();
