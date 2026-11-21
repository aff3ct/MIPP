/**
 * MIPP Documentation - Previous / next links kept within a section
 * The footer navigation of Material follows the whole site order, so it jumps
 * between sections (e.g. "Previous: SVE (Masked)" on the Developer Guide).
 * A link to a page of another top-level tab is hidden; the footer navigation
 * is hidden when no link is left.
 */

(function () {
  // Directories of the same top-level tab (Specifications)
  const SECTION_ALIASES = { isas_support: "funcs_support" };

  function sectionOf(href, base) {
    const path = new URL(href, window.location.href).pathname;
    const rel = path.startsWith(base) ? path.slice(base.length) : path;
    const first = rel.split("/").filter(Boolean)[0] || "";
    return SECTION_ALIASES[first] || first;
  }

  function update() {
    const home = document.querySelector(".md-header__button.md-logo");
    const nav = document.querySelector(".md-footer__inner");
    if (!home || !nav) return;
    const base = new URL(home.href).pathname;
    const current = sectionOf(window.location.href, base);
    let visible = 0;
    for (const link of nav.querySelectorAll(".md-footer__link")) {
      const other = sectionOf(link.href, base) !== current;
      link.hidden = other;
      if (!other) visible++;
    }
    nav.hidden = visible === 0;
  }

  // Each page, including the instant navigations of Material
  if (typeof document$ !== "undefined") {
    document$.subscribe(update);
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", update);
  } else {
    update();
  }
})();
