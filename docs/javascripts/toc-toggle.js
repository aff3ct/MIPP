/**
 * MIPP Documentation - Collapsible Table of Contents (TOC)
 * Allows users to toggle/hide the right TOC sidebar to expand reading area.
 */

(function () {
  const STORAGE_KEY = "mipp_toc_hidden";

  function isTocHidden() {
    return localStorage.getItem(STORAGE_KEY) === "true";
  }

  function isHomepage() {
    return !!document.querySelector(".mipp-hero");
  }

  function setTocHidden(hidden) {
    localStorage.setItem(STORAGE_KEY, hidden ? "true" : "false");
    if (hidden && !isHomepage()) {
      document.body.setAttribute("data-toc-hidden", "true");
    } else {
      document.body.removeAttribute("data-toc-hidden");
    }
    updateRestoreButton();
  }

  function updateRestoreButton() {
    let restoreBtn = document.getElementById("mipp-toc-restore-btn");

    // Strictly never show restore button on homepage
    if (isHomepage()) {
      if (restoreBtn) restoreBtn.style.display = "none";
      return;
    }

    const secondarySidebar = document.querySelector(".md-sidebar--secondary");
    const hasTocItems = secondarySidebar && secondarySidebar.querySelector(".md-nav__link");

    if (!hasTocItems) {
      if (restoreBtn) restoreBtn.style.display = "none";
      return;
    }

    if (isTocHidden()) {
      if (!restoreBtn) {
        restoreBtn = document.createElement("button");
        restoreBtn.id = "mipp-toc-restore-btn";
        restoreBtn.className = "mipp-toc-restore-btn";
        restoreBtn.setAttribute("title", "Afficher la table des matières (TOC)");
        restoreBtn.setAttribute("aria-label", "Afficher la table des matières");
        restoreBtn.innerHTML = `
          <svg viewBox="0 0 24 24" width="16" height="16" fill="currentColor">
            <path d="M3 9h14V7H3v2zm0 4h14v-2H3v2zm0 4h14v-2H3v2zm16 0h2v-2h-2v2zm0-10v2h2V7h-2zm0 6h2v-2h-2v2z"/>
          </svg>
          <span>TOC</span>
        `;
        restoreBtn.addEventListener("click", () => setTocHidden(false));
        document.body.appendChild(restoreBtn);
      }
      restoreBtn.style.display = "flex";
    } else if (restoreBtn) {
      restoreBtn.style.display = "none";
    }
  }

  function initTocToggle() {
    if (isHomepage()) {
      document.body.removeAttribute("data-toc-hidden");
      const restoreBtn = document.getElementById("mipp-toc-restore-btn");
      if (restoreBtn) restoreBtn.style.display = "none";
      return;
    }

    // 1. Restore saved preference
    if (isTocHidden()) {
      document.body.setAttribute("data-toc-hidden", "true");
    } else {
      document.body.removeAttribute("data-toc-hidden");
    }

    // 2. Inject collapse button into TOC header if not already present
    const tocTitle = document.querySelector(".md-sidebar--secondary .md-nav__title");
    if (tocTitle && !tocTitle.querySelector(".mipp-toc-collapse-btn")) {
      const collapseBtn = document.createElement("button");
      collapseBtn.type = "button";
      collapseBtn.className = "mipp-toc-collapse-btn";
      collapseBtn.setAttribute("title", "Masquer la table des matières");
      collapseBtn.setAttribute("aria-label", "Masquer la table des matières");
      collapseBtn.innerHTML = `
        <svg viewBox="0 0 24 24" width="14" height="14" fill="currentColor">
          <path d="M19 6.41L17.59 5 12 10.59 6.41 5 5 6.41 10.59 12 5 17.59 6.41 19 12 13.41 17.59 19 19 17.59 13.41 12 19 6.41z"/>
        </svg>
      `;
      collapseBtn.addEventListener("click", (e) => {
        e.preventDefault();
        e.stopPropagation();
        setTocHidden(true);
      });
      tocTitle.appendChild(collapseBtn);
    }

    updateRestoreButton();
  }

  // Subscribe to MkDocs Material instant navigation lifecycle
  if (typeof document$ !== "undefined") {
    document$.subscribe(initTocToggle);
  } else {
    document.addEventListener("DOMContentLoaded", initTocToggle);
  }
})();
