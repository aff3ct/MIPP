/**
 * MIPP API Explorer - Main Orchestrator & Lifecycle
 */
import { escapeHtml, ICON_CHECK, ICON_NO_RESULTS, VALID_CARD_TABS, copyToClipboard } from "./explorer.config.js";
import {
  apiData,
  apiMetadata,
  loadApiData,
  loadApiDetails,
  ALL_SIMD_EXTS,
  ALL_CATEGORIES,
  ALL_DATATYPES,
  ALL_MASK_MODES,
  getDefaultFeaturesForModal
} from "./data.js";
import { state, syncUrlHash, readUrlHash, setFocusedCard, closeCard } from "./state.js";
import { filterEntries } from "./filters.js";
import { renderSidebar, updateSidebarUI, bindSidebarEvents } from "./components/sidebar.js";
import { renderSearchBar, updateSearchBarUI, bindSearchBarEvents, scrollToSearchResults } from "./components/search_bar.js";
import { renderCard, switchCardTab, renderCardExpandedDetails } from "./components/card.js";
import { renderAlgoModal, algoModalIsa } from "./components/modal_algo.js";
import { getLoadedSources, loadAlgoSources } from "./algo_source.js";
import { renderCompareModal } from "./components/modal_compare.js";
import { showMacroTooltip, hideMacroTooltip, toggleMacroTooltip, typesetMath } from "./syntax.js";
import { toggleIntrinsicTooltip, hideIntrinsicTooltip, setIntrinsicNavigate } from "./components/intrinsic_tooltip.js";

let headerResizeObserver = null;

function updateHeaderHeight(headerEl) {
  if (!headerEl) return;
  const height = headerEl.getBoundingClientRect().height;
  if (height > 0) {
    document.documentElement.style.setProperty("--mipp-header-height", `${height}px`);
  }
}

function observeHeaderHeight(headerEl) {
  if (!headerEl) return;
  updateHeaderHeight(headerEl);

  if (typeof ResizeObserver !== "undefined") {
    if (headerResizeObserver) headerResizeObserver.disconnect();
    headerResizeObserver = new ResizeObserver((entries) => {
      for (const entry of entries) {
        const height = entry.borderBoxSize?.[0]?.blockSize ?? entry.target.getBoundingClientRect().height;
        if (height > 0) {
          document.documentElement.style.setProperty("--mipp-header-height", `${height}px`);
        }
      }
    });
    headerResizeObserver.observe(headerEl);
  }
}

export function renderApp() {
  const appEl = document.getElementById("mipp-explorer-app");
  if (!appEl) return;

  const sidebarEl = appEl.querySelector(".mipp-sidebar");
  const headerEl = appEl.querySelector(".mipp-explorer-header");
  const cardsContainerEl = appEl.querySelector(".mipp-cards-container");
  const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
  const compareBarEl = appEl.querySelector(".mipp-compare-bar");

  if (!sidebarEl || !headerEl || !cardsContainerEl || !modalsContainerEl || !compareBarEl) {
    mountAppShell(appEl);
    return;
  }

  updateHeaderHeight(headerEl);
  updateSidebarUI(sidebarEl);
  updateFiltersToggle(appEl);
  updateSearchBarUI(headerEl);
  renderCards(cardsContainerEl);
  updateCompareBar(compareBarEl);
  updateModals(modalsContainerEl);
}

// Number of restricted filter groups, shown on the (collapsed) filters toggle
function updateFiltersToggle(appEl) {
  const countEl = appEl.querySelector(".mipp-filters-toggle-count");
  if (!countEl) return;
  const restricted = [
    state.selectedCategories.length < ALL_CATEGORIES.length,
    state.selectedTypes.length < ALL_DATATYPES.length,
    state.selectedSimdExts.length < ALL_SIMD_EXTS.length,
    state.selectedLevels.length < 4,
  ].filter(Boolean).length;
  countEl.textContent = restricted ? `${restricted} active` : "";
  countEl.hidden = restricted === 0;
}

function mountAppShell(appEl) {
  // Compute category counts
  const catCounts = {};
  for (const c of ALL_CATEGORIES) catCounts[c] = 0;
  for (const e of apiData) {
    if (e.category && catCounts[e.category] !== undefined) {
      catCounts[e.category]++;
    }
  }

  appEl.innerHTML = `
    ${renderSearchBar()}

    <div class="mipp-explorer-body">
      <!-- Filters toggle (single-column layout only, see explorer.css) -->
      <button type="button" class="mipp-filters-toggle" aria-controls="mipp-sidebar-filters"
              aria-expanded="${appEl.classList.contains("mipp-filters-open") ? "true" : "false"}">
        <svg viewBox="0 0 24 24" width="16" height="16" fill="currentColor" aria-hidden="true">
          <path d="M14 12v7.88c.04.3-.06.62-.29.83a.996.996 0 0 1-1.41 0l-2.01-2.01a.989.989 0 0 1-.29-.83V12h-.03L4.21 4.62a1 1 0 0 1 .17-1.4c.19-.14.4-.22.62-.22h14c.22 0 .43.08.62.22a1 1 0 0 1 .17 1.4L14.03 12H14z"/>
        </svg>
        <span>Filters</span>
        <span class="mipp-filters-toggle-count" hidden></span>
        <svg class="mipp-filters-toggle-chevron" viewBox="0 0 24 24" width="18" height="18" fill="currentColor" aria-hidden="true">
          <path d="M7.41 8.58 12 13.17l4.59-4.59L18 10l-6 6-6-6 1.41-1.42z"/>
        </svg>
      </button>

      ${renderSidebar(catCounts, renderApp)}

      <!-- Cards Main Area -->
      <main class="mipp-cards-container" id="mipp-cards-container"></main>
    </div>

    <!-- Side-by-side Compare Floating Bar -->
    <div class="mipp-compare-bar ${state.compareSet.size >= 1 ? "visible" : ""}">
      <span class="mipp-compare-bar-text" style="font-weight: 600; font-size: var(--mipp-fs-md, 0.8rem);">
        Compare (${state.compareSet.size}/3): <span style="color: var(--mipp-accent);">${Array.from(state.compareSet).join(", ")}</span>
      </span>
      <div style="display: flex; gap: 0.5rem;">
        <button id="mipp-open-compare-btn" class="mipp-godbolt-btn" ${state.compareSet.size < 2 ? "disabled style='opacity:0.6;'" : ""}>
          View Side-by-Side
        </button>
        <button id="mipp-clear-compare-btn" class="mipp-action-btn">
          Clear
        </button>
      </div>
    </div>

    <!-- Modals Container -->
    <div id="mipp-modals-container"></div>
  `;

  const sidebarEl = appEl.querySelector(".mipp-sidebar");
  const headerEl = appEl.querySelector(".mipp-explorer-header");
  const cardsContainerEl = appEl.querySelector(".mipp-cards-container");
  const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
  const compareBarEl = appEl.querySelector(".mipp-compare-bar");

  // Dynamically observe header height for sticky positioning
  observeHeaderHeight(headerEl);

  // Filters toggle: the open state lives on the mount element, which survives
  // the re-renders of its content (closed again after a page navigation)
  const filtersToggleEl = appEl.querySelector(".mipp-filters-toggle");
  if (filtersToggleEl) {
    filtersToggleEl.addEventListener("click", () => {
      const open = appEl.classList.toggle("mipp-filters-open");
      filtersToggleEl.setAttribute("aria-expanded", open ? "true" : "false");
    });
  }

  // Bind shell events (once!)
  bindSidebarEvents(sidebarEl, renderApp);
  bindSearchBarEvents(headerEl, renderApp);
  bindCompareBarEvents(appEl);

  // Initial render of contents
  updateSidebarUI(sidebarEl);
  updateFiltersToggle(appEl);
  updateSearchBarUI(headerEl);
  renderCards(cardsContainerEl);
  updateCompareBar(compareBarEl);
  updateModals(modalsContainerEl);
}



function renderCards(cardsContainerEl) {
  if (!cardsContainerEl) return;
  const filtered = filterEntries(apiData, state);

  cardsContainerEl.innerHTML = `
    <div class="mipp-results-bar">
      <span>Showing <span class="mipp-results-count">${filtered.length}</span> of ${apiData.length} primitives</span>
      ${state.compareSet.size > 0
        ? `<span style="color: var(--mipp-accent); font-weight: 600;">${state.compareSet.size} selected for comparison</span>`
        : ""
      }
    </div>

    ${filtered.length === 0
      ? `
        <div class="mipp-no-results" style="text-align: center; padding: 3rem 1rem; background: var(--mipp-card-bg, #ffffff); border-radius: var(--mipp-border-radius-lg); border: 1px dashed var(--mipp-card-border, #cbd5e1);">
          <div style="margin-bottom: 0.5rem; color: var(--md-default-fg-color--lighter, #94a3b8);">${ICON_NO_RESULTS}</div>
          <h3 style="margin: 0 0 0.5rem 0;">No matching MIPP primitives found</h3>
          <p style="color: var(--md-default-fg-color--lighter, #94a3b8); margin: 0 0 1rem 0; font-size: var(--mipp-fs-md, 0.8rem);">
            Try adjusting your search terms or checking options in the sidebar filter.
          </p>
          <button id="mipp-reset-all-filters" class="mipp-filter-chip" style="background: var(--mipp-accent); color: white; border: none; padding: 0.45rem 1rem; cursor: pointer;">
            Reset All Filters
          </button>
        </div>
      `
      : filtered.map(({ entry, matchedIntrinsic, matchedC99 }) => renderCard(entry, matchedIntrinsic, matchedC99)).join("")
    }
  `;

  bindCardEvents(cardsContainerEl);
}

function bindCardEvents(cardsContainerEl) {
  // 1. Reset all filters button in no-results box
  const resetBtn = cardsContainerEl.querySelector("#mipp-reset-all-filters");
  if (resetBtn) {
    resetBtn.addEventListener("click", () => {
      state.query = "";
      state.searchField = "all";
      state.flavor = "cpp";
      state.lmul = "1";
      state.selectedSimdExts = [...ALL_SIMD_EXTS];
      state.selectedCategories = [...ALL_CATEGORIES];
      state.selectedTypes = ALL_DATATYPES.map((d) => d.id);
      state.maskVariant = "unmasked";
      state.selectedLevels = [0, 1, 2, 3];
      state.intersectionMode = false;
      state.expandedCards.clear();
      state.openedCardsOrder = [];
      state.focusedCard = null;
      state.compareSet.clear();
      state.cardTabs = {};
      state.cardScalarTypes = {};
      state.cardScalarVariants = {};
      state.cardTestVariants = {};
      state.cardFlatState = {};
      state.cardHwMask = {};
      if (typeof window !== "undefined" && window.history && window.history.replaceState) {
        window.history.replaceState(null, "", window.location.pathname + window.location.search);
      }
      renderApp();
    });
  }

  // 2. Card Expansion Toggle
  cardsContainerEl.querySelectorAll("[data-toggle-card]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const cardName = btn.getAttribute("data-toggle-card");
      toggleCard(cardName);
    });
  });

  // Card Header Click to expand
  cardsContainerEl.querySelectorAll(".mipp-card-header").forEach((header) => {
    header.addEventListener("click", (e) => {
      if (e.target.closest("button") || e.target.closest("input") || e.target.closest(".copy-proto-btn") || e.target.closest("label")) return;
      const cardEl = header.closest(".mipp-card");
      if (!cardEl) return;
      const cardName = cardEl.getAttribute("data-card-name");
      toggleCard(cardName);
    });
  });

  // 3. Attach listeners to all already expanded cards
  cardsContainerEl.querySelectorAll(".mipp-card.expanded").forEach((cardEl) => {
    const cardName = cardEl.getAttribute("data-card-name");
    const entry = apiData.find((x) => x.name === cardName);
    if (entry) {
      attachCardInternalListeners(cardEl, entry);
      typesetMath(cardEl);
    }
  });

  // 4. Compare Checkboxes
  cardsContainerEl.querySelectorAll("input[data-compare], input[data-compare-name]").forEach((cb) => {
    cb.addEventListener("change", (e) => {
      const name = e.target.getAttribute("data-compare") || e.target.getAttribute("data-compare-name");
      if (e.target.checked) {
        state.compareSet.add(name);
      } else {
        state.compareSet.delete(name);
      }
      const compareBarEl = document.querySelector(".mipp-compare-bar");
      if (compareBarEl) updateCompareBar(compareBarEl);
    });
  });

  // 5. Macro Tooltip Clicks
  cardsContainerEl.querySelectorAll(".mipp-macro-ref").forEach((el) => {
    el.addEventListener("click", (e) => {
      e.stopPropagation();
      const mName = el.getAttribute("data-macro-name");
      const mDef = el.getAttribute("data-macro-def");
      toggleMacroTooltip(el, mName, mDef);
    });
  });

  // 6. Header Copy Buttons
  cardsContainerEl.querySelectorAll(".mipp-card-header .copy-proto-btn").forEach((btn) => {
    btn.addEventListener("click", async (e) => {
      e.stopPropagation();
      const textToCopy = btn.getAttribute("data-copy");
      if (textToCopy) {
        try {
          await copyToClipboard(textToCopy);
          const originalHtml = btn.innerHTML;
          btn.innerHTML = ICON_CHECK;
          setTimeout(() => {
            btn.innerHTML = originalHtml;
          }, 1500);
        } catch (err) {
          console.warn("Failed to copy:", err);
        }
      }
    });
  });
}

function toggleCard(cardName) {
  const cardEl = document.getElementById(`card-${cardName}`);
  const entry = apiData.find((x) => x.name === cardName);
  if (!cardEl || !entry) return;

  const expandable = cardEl.querySelector(".mipp-card-expandable");
  const toggleBtn = cardEl.querySelector(".mipp-toggle-details-btn");
  const isNowExpanded = !state.expandedCards.has(cardName);

  if (isNowExpanded) {
    setFocusedCard(cardName);
    cardEl.classList.add("expanded");
    if (toggleBtn) {
      toggleBtn.classList.add("is-expanded");
      const textSpan = toggleBtn.querySelector(".mipp-toggle-text") || toggleBtn.querySelector("span:first-child");
      if (textSpan) textSpan.textContent = "Close";
    }
    if (expandable) {
      const inner = expandable.querySelector(".mipp-card-expandable-inner");
      if (inner && !inner.innerHTML.trim()) {
        inner.innerHTML = renderCardExpandedDetails(entry);
        attachCardInternalListeners(cardEl, entry);
      }
      void expandable.offsetHeight;
      expandable.classList.add("open");
      typesetMath(cardEl);
    }
  } else {
    closeCard(cardName);
    cardEl.classList.remove("expanded");
    if (toggleBtn) {
      toggleBtn.classList.remove("is-expanded");
      const textSpan = toggleBtn.querySelector(".mipp-toggle-text") || toggleBtn.querySelector("span:first-child");
      if (textSpan) textSpan.textContent = "Details";
    }
    if (expandable) {
      expandable.classList.remove("open");
    }
  }
  syncUrlHash(true);
  const headerEl = document.querySelector(".mipp-explorer-header");
  if (headerEl) updateSearchBarUI(headerEl);
}

export function scrollToFocusedCard(cardName, smooth = false) {
  if (!cardName) return;
  const performScroll = () => {
    const cardEl = document.getElementById(`card-${cardName}`);
    if (!cardEl) return;
    const headerEl = document.querySelector(".mipp-explorer-header");
    const headerBottom = headerEl ? Math.max(0, headerEl.getBoundingClientRect().bottom) : 0;
    const gap = 12;
    const cardRect = cardEl.getBoundingClientRect();
    const delta = cardRect.top - (headerBottom + gap);
    if (Math.abs(delta) < 15) return;

    const targetY = Math.max(0, window.scrollY + delta);
    window.scrollTo({
      top: targetY,
      behavior: smooth ? "smooth" : "auto",
    });
  };

  requestAnimationFrame(performScroll);
  setTimeout(performScroll, 80);
}

export { scrollToSearchResults };

function attachCardInternalListeners(cardEl, entry) {
  if (!cardEl || !entry) return;

  // 1. Tab buttons (bind once per card to prevent duplicate listeners)
  if (!cardEl._tabsBound) {
    cardEl._tabsBound = true;
    cardEl.querySelectorAll(".mipp-card-tab-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const targetTab = btn.getAttribute("data-tab") || btn.getAttribute("data-card-tab");
        switchCardTab(cardEl, entry, targetTab);
        attachCardInternalListeners(cardEl, entry);
      });
    });
  }

  const paneEl = cardEl.querySelector(`#tab-content-${entry.name}`);
  if (!paneEl) return;

  // 2. Scalar Reference Datatype Dropdown
  paneEl.querySelectorAll(".mipp-scalar-dt-select").forEach((sel) => {
    sel.addEventListener("change", (e) => {
      e.stopPropagation();
      state.cardScalarTypes[entry.name] = sel.value;
      setFocusedCard(entry.name);
      syncUrlHash(true);
      switchCardTab(cardEl, entry, "scalar");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  // 3. "View Algorithm" Modal Trigger
  paneEl.querySelectorAll("[data-algo-card]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const ext = btn.getAttribute("data-algo-simd-ext") || btn.getAttribute("data-algo-isa");
      const dt = btn.getAttribute("data-algo-dt");
      const mask = btn.getAttribute("data-algo-mask") || state.cardHwMask?.[entry.name] || "unmasked";
      const reqFeature = btn.getAttribute("data-algo-feature");
      state.algoModalOpen = true;
      state.algoModalData = {
        entry,
        isa: ext,
        simdExt: ext,
        dt,
        mask,
        lmul: state.lmul || "1",
        view: "abstract",
        scalarSize: 256,
        features: getDefaultFeaturesForModal(reqFeature, ext)
      };
      const appEl = document.getElementById("mipp-explorer-app");
      if (appEl) {
        const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
        if (modalsContainerEl) {
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      }
    });
  });

  // 6. Copy Buttons
  paneEl.querySelectorAll(".copy-proto-btn, .copy-code-btn, [data-copy]").forEach((btn) => {
    btn.addEventListener("click", async (e) => {
      e.stopPropagation();
      const textToCopy = btn.getAttribute("data-copy");
      if (textToCopy) {
        try {
          await copyToClipboard(textToCopy);
          const originalHtml = btn.innerHTML;
          btn.innerHTML = ICON_CHECK;
          setTimeout(() => {
            btn.innerHTML = originalHtml;
          }, 1500);
        } catch (err) {
          console.warn("Failed to copy:", err);
        }
      }
    });
  });
}

function updateCompareBar(compareBarEl) {
  syncUrlHash(true); // comparison selection (cmp), see updateModals
  if (!compareBarEl) return;
  const isVisible = state.compareSet.size >= 1;
  compareBarEl.classList.toggle("visible", isVisible);

  const textEl = compareBarEl.querySelector(".mipp-compare-bar-text");
  if (textEl) {
    textEl.innerHTML = `Compare (${state.compareSet.size}/3): <span style="color: var(--mipp-accent);">${Array.from(state.compareSet).join(", ")}</span>`;
  }

  const openBtn = compareBarEl.querySelector("#mipp-open-compare-btn");
  if (openBtn) {
    const canOpen = state.compareSet.size >= 2;
    openBtn.disabled = !canOpen;
    openBtn.style.opacity = canOpen ? "1" : "0.6";
  }
}

function bindCompareBarEvents(appEl) {
  const openCompareBtn = appEl.querySelector("#mipp-open-compare-btn");
  if (openCompareBtn) {
    openCompareBtn.addEventListener("click", () => {
      state.compareModalOpen = true;
      const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
      if (modalsContainerEl) updateModals(modalsContainerEl);
    });
  }

  const clearCompareBtn = appEl.querySelector("#mipp-clear-compare-btn");
  if (clearCompareBtn) {
    clearCompareBtn.addEventListener("click", () => {
      state.compareSet.clear();
      state.compareModalOpen = false;
      const compareBarEl = appEl.querySelector(".mipp-compare-bar");
      if (compareBarEl) updateCompareBar(compareBarEl);
      const cardsContainerEl = appEl.querySelector(".mipp-cards-container");
      if (cardsContainerEl) renderCards(cardsContainerEl);
      const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
      if (modalsContainerEl) updateModals(modalsContainerEl);
    });
  }
}

// Size of the Algorithm modal chosen by the user (desktop: CSS resize from the
// bottom right corner). The modal is rebuilt at each change (ISA, datatype,
// view...), so the size is kept here and applied again after each render; it
// is also remembered in the browser (a display preference, not part of the URL).
const ALGO_MODAL_SIZE_KEY = "mipp_algo_modal_size";
let algoModalSize = null;
try {
  algoModalSize = JSON.parse(localStorage.getItem(ALGO_MODAL_SIZE_KEY) || "null");
} catch (e) {
  algoModalSize = null;
}

function applyAlgoModalSize(modalsContainerEl) {
  const el = modalsContainerEl.querySelector(".mipp-algo-modal-content");
  if (!el || !algoModalSize || !window.matchMedia("(min-width: 769px)").matches) return;
  if (algoModalSize.width) el.style.width = algoModalSize.width;
  if (algoModalSize.height) el.style.height = algoModalSize.height;
}

// The browser writes the new size as an inline style at the end of a resize
function rememberAlgoModalSize() {
  const el = document.querySelector("#mipp-modals-container .mipp-algo-modal-content");
  if (!el || (!el.style.width && !el.style.height)) return;
  const size = { width: el.style.width || null, height: el.style.height || null };
  if (algoModalSize && size.width === algoModalSize.width && size.height === algoModalSize.height) return;
  algoModalSize = size;
  try {
    localStorage.setItem(ALGO_MODAL_SIZE_KEY, JSON.stringify(size));
  } catch (e) {
    /* private mode: kept for this visit only */
  }
}

function updateModals(modalsContainerEl) {
  if (!modalsContainerEl) return;

  modalsContainerEl.innerHTML = `
    ${state.algoModalOpen ? renderAlgoModal(state.algoModalData) : ""}
    ${state.compareModalOpen ? renderCompareModal(apiData) : ""}
  `;

  applyAlgoModalSize(modalsContainerEl);

  // The URL always encodes the current view (shareable link): every render of
  // the app ends here (renderApp), like every change of a modal
  syncUrlHash(true);

  // The code of the Algorithm modal comes from the header tables of the ISAs, loaded on demand
  if (state.algoModalOpen && state.algoModalData) {
    const md = state.algoModalData;
    const wanted = [algoModalIsa(md)];
    if (md.view === "compare") {
      const shown = modalsContainerEl.querySelectorAll("[data-modal-compare-isa].active");
      shown.forEach((b) => wanted.push(b.getAttribute("data-modal-compare-isa")));
    }
    for (const isa of new Set(wanted)) {
      if (!isa || getLoadedSources(isa) || md.loadError) continue;
      loadAlgoSources(isa)
        .then(() => {
          if (state.algoModalOpen && state.algoModalData === md) updateModals(modalsContainerEl);
        })
        .catch((err) => {
          if (state.algoModalOpen && state.algoModalData === md) {
            md.loadError = err.message;
            updateModals(modalsContainerEl);
          }
        });
    }
  }

  // Algo Modal Events
  if (state.algoModalOpen) {
    const algoCloseBtn = modalsContainerEl.querySelector("#mipp-algo-modal-close");
    if (algoCloseBtn) {
      algoCloseBtn.addEventListener("click", () => {
        state.algoModalOpen = false;
        state.algoModalData = null;
        updateModals(modalsContainerEl);
        syncUrlHash(true);
      });
    }

    // Open another function in the modal (with a way back): call tree and intrinsic tooltips
    const openInAlgoModal = ({ func, isa, dt, mask, lmul }) => {
      const md = state.algoModalData;
      const target = apiData.find((x) => x.name === func);
      if (!md || !target) return;
      const { history, ...current } = md;
      state.algoModalData = {
        ...md, entry: target, isa, simdExt: isa, dt, mask, lmul,
        view: "abstract", loadError: undefined, history: [...(history || []), current],
      };
      updateModals(modalsContainerEl);
      syncUrlHash(true);
    };
    setIntrinsicNavigate(openInAlgoModal);
    modalsContainerEl.querySelectorAll("[data-algo-nav-func]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        openInAlgoModal({
          func: btn.getAttribute("data-algo-nav-func"),
          isa: btn.getAttribute("data-algo-nav-isa"),
          dt: btn.getAttribute("data-algo-nav-dt"),
          mask: btn.getAttribute("data-algo-nav-mask"),
          lmul: btn.getAttribute("data-algo-nav-lmul"),
        });
      });
    });

    const algoBackBtn = modalsContainerEl.querySelector("#mipp-algo-modal-back");
    if (algoBackBtn) {
      algoBackBtn.addEventListener("click", (e) => {
        e.stopPropagation();
        const md = state.algoModalData;
        if (!md || !md.history || !md.history.length) return;
        const history = md.history.slice(0, -1);
        state.algoModalData = { ...md.history[md.history.length - 1], history };
        updateModals(modalsContainerEl);
        syncUrlHash(true);
      });
    }

    // Compare view: ISAs shown side by side
    modalsContainerEl.querySelectorAll("[data-modal-compare-isa]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const md = state.algoModalData;
        if (!md) return;
        const isa = btn.getAttribute("data-modal-compare-isa");
        const cur = [...modalsContainerEl.querySelectorAll("[data-modal-compare-isa].active")].map((b) => b.getAttribute("data-modal-compare-isa"));
        const next = cur.includes(isa) ? cur.filter((i) => i !== isa) : [...cur, isa];
        if (!next.length) return;
        md.compareIsas = next;
        updateModals(modalsContainerEl);
      });
    });

    const algoShareBtn = modalsContainerEl.querySelector("#mipp-algo-modal-share");
    if (algoShareBtn) {
      algoShareBtn.addEventListener("click", () => {
        syncUrlHash(true);
        copyToClipboard(window.location.href, "Direct link to algorithm copied to clipboard!");
        const originalHtml = algoShareBtn.innerHTML;
        algoShareBtn.innerHTML = "✓";
        setTimeout(() => {
          algoShareBtn.innerHTML = originalHtml;
        }, 1500);
      });
    }

    const algoBackdrop = modalsContainerEl.querySelector("#mipp-algo-modal-backdrop");
    if (algoBackdrop) {
      algoBackdrop.addEventListener("click", (e) => {
        if (e.target === algoBackdrop) {
          state.algoModalOpen = false;
          state.algoModalData = null;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    }

    // View Mode Switcher: Abstract C++ vs Flat C99 Code
    modalsContainerEl.querySelectorAll("[data-modal-view]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const v = btn.getAttribute("data-modal-view");
        if (state.algoModalData) {
          state.algoModalData.view = v;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });

    // ISA Switcher
    modalsContainerEl.querySelectorAll("[data-modal-isa]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const ext = btn.getAttribute("data-modal-isa");
        if (state.algoModalData) {
          state.algoModalData.isa = ext;
          state.algoModalData.simdExt = ext;
          state.algoModalData.loadError = undefined;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });

    // SIMD Width Switcher (Scalar, RVV, SVE)
    modalsContainerEl.querySelectorAll("[data-modal-scalarsize]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const sz = parseInt(btn.getAttribute("data-modal-scalarsize"), 10);
        if (state.algoModalData) {
          state.algoModalData.scalarSize = sz;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });

    const dtSelect = modalsContainerEl.querySelector("#mipp-algo-modal-dt-select");
    if (dtSelect) {
      dtSelect.addEventListener("change", (e) => {
        if (state.algoModalData) {
          state.algoModalData.dt = e.target.value;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    }

    modalsContainerEl.querySelectorAll("[data-modal-mask]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const m = btn.getAttribute("data-modal-mask");
        if (state.algoModalData) {
          state.algoModalData.mask = m;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });

    modalsContainerEl.querySelectorAll("[data-modal-lmul]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const l = btn.getAttribute("data-modal-lmul");
        if (state.algoModalData) {
          state.algoModalData.lmul = l;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });

    modalsContainerEl.querySelectorAll("[data-modal-toggle-feature]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        if (btn.hasAttribute("data-modal-locked") || btn.getAttribute("data-modal-locked") === "true") return;
        const feat = btn.getAttribute("data-modal-toggle-feature");
        if (state.algoModalData) {
          if (!state.algoModalData.features) {
            state.algoModalData.features = getDefaultFeaturesForModal();
          }
          const curVal = state.algoModalData.features[feat] !== false;
          state.algoModalData.features[feat] = !curVal;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });

    modalsContainerEl.querySelectorAll("[data-modal-tier]").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const target = btn.getAttribute("data-modal-tier");
        if (state.algoModalData) {
          if (!state.algoModalData.features) {
            state.algoModalData.features = getDefaultFeaturesForModal();
          }
          const currentIsa = state.algoModalData.simdExt || state.algoModalData.isa || Object.keys(apiMetadata.isas || {})[0] || "";
          state.algoModalData.features[currentIsa] = target;
          updateModals(modalsContainerEl);
          syncUrlHash(true);
        }
      });
    });
  }

  // Compare Modal Events
  if (state.compareModalOpen) {
    const closeCompareBtn = modalsContainerEl.querySelector("#mipp-close-compare-btn, #mipp-compare-modal-close");
    if (closeCompareBtn) {
      closeCompareBtn.addEventListener("click", () => {
        state.compareModalOpen = false;
        updateModals(modalsContainerEl);
      });
    }

    const compareBackdrop = modalsContainerEl.querySelector("#mipp-compare-modal-backdrop");
    if (compareBackdrop) {
      compareBackdrop.addEventListener("click", (e) => {
        if (e.target === compareBackdrop) {
          state.compareModalOpen = false;
          updateModals(modalsContainerEl);
        }
      });
    }

    const clearCompareBtn = modalsContainerEl.querySelector("#mipp-clear-compare-btn");
    if (clearCompareBtn) {
      clearCompareBtn.addEventListener("click", () => {
        state.compareSet.clear();
        state.compareModalOpen = false;
        const compareBarEl = document.querySelector(".mipp-compare-bar");
        if (compareBarEl) updateCompareBar(compareBarEl);
        const cardsContainerEl = document.querySelector(".mipp-cards-container");
        if (cardsContainerEl) renderCards(cardsContainerEl);
        updateModals(modalsContainerEl);
      });
    }

    modalsContainerEl.querySelectorAll("[data-remove-compare]").forEach((btn) => {
      btn.addEventListener("click", () => {
        const name = btn.getAttribute("data-remove-compare");
        state.compareSet.delete(name);
        const compareBarEl = document.querySelector(".mipp-compare-bar");
        if (compareBarEl) updateCompareBar(compareBarEl);
        const cardsContainerEl = document.querySelector(".mipp-cards-container");
        if (cardsContainerEl) renderCards(cardsContainerEl);
        updateModals(modalsContainerEl);
      });
    });

    typesetMath(modalsContainerEl);

    // Copy buttons inside modals
    modalsContainerEl.querySelectorAll(".copy-proto-btn, .copy-code-btn, [data-copy]").forEach((btn) => {
      btn.addEventListener("click", async (e) => {
        e.stopPropagation();
        const textToCopy = btn.getAttribute("data-copy");
        if (textToCopy) {
          try {
            await navigator.clipboard.writeText(textToCopy);
            const origHtml = btn.innerHTML;
            btn.innerHTML = `<span style="font-size: var(--mipp-fs-base, 0.72rem); color: #10b981;">✓</span>`;
            setTimeout(() => {
              btn.innerHTML = origHtml;
            }, 1500);
          } catch (err) {
            console.error("Failed to copy:", err);
          }
        }
      });
    });
  }
}

// Loads mipp_api_details.json once the cards are displayed, then redraws the
// views that showed a loading note: expanded cards on the Scalar C Reference or
// Verification Specs tab, and the Algorithm modal (scalar macros, test domain
// of "Run in Godbolt")
function loadDetailsInBackground() {
  loadApiDetails()
    .then(() => {
      const appEl = document.getElementById("mipp-explorer-app");
      if (!appEl) return;
      const detailTabs = ["scalar", "specs"];
      const cardsNeedIt = [...state.expandedCards].some((name) => detailTabs.includes(state.cardTabs[name]));
      if (cardsNeedIt) {
        renderApp();
      } else if (state.algoModalOpen) {
        const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
        if (modalsContainerEl) updateModals(modalsContainerEl);
      }
    })
    .catch((err) => console.warn("[MIPP Explorer]", err.message));
}

// Default view of the Explorer (search, filters, opened cards, modals), before
// the URL hash is applied. Needed at each visit of the page, not only on a
// hash change: the state module survives the instant navigation of Material,
// so the search of a previous visit would still filter the cards targeted by a
// link such as "explorer/#focus=cast". The comparison selection is reset too:
// it is part of the URL (cmp), like the rest of the view.
function resetViewState() {
  state.selectedSimdExts = [...ALL_SIMD_EXTS];
  state.selectedCategories = [...ALL_CATEGORIES];
  state.selectedTypes = ALL_DATATYPES.map((d) => d.id);
  state.maskVariant = "unmasked";
  state.selectedLevels = [0, 1, 2, 3];
  state.query = "";
  state.searchField = "all";
  state.flavor = "cpp";
  state.lmul = "1";
  state.intersectionMode = false;
  state.focusedCard = null;
  state.expandedCards.clear();
  state.openedCardsOrder = [];
  state.cardTabs = {};
  state.cardScalarTypes = {};
  state.cardScalarVariants = {};
  state.cardTestVariants = {};
  state.cardFlatState = {};
  state.cardHwMask = {};
  state.algoModalOpen = false;
  state.algoModalData = null;
  state.compareModalOpen = false;
  state.compareSet.clear();
}

let globalListenersBound = false;

export async function initExplorer() {
  const mountEl = document.getElementById("mipp-explorer-app");
  if (!mountEl) {
    document.body.classList.remove("mipp-has-explorer");
    return;
  }

  document.body.classList.add("mipp-has-explorer");

  mountEl.innerHTML = `
    <div class="mipp-explorer-loading" role="status">
      <div class="mipp-explorer-loading-title">Loading the MIPP API Explorer…</div>
      <p>Preparing the catalog of SIMD primitives and hardware targets</p>
      <div class="mipp-loading-bar-wrapper">
        <div class="mipp-loading-bar-fill" id="mipp-load-progress-fill" style="width: 0%;"></div>
      </div>
      <div id="mipp-load-progress-text">Connecting...</div>
    </div>
  `;

  try {
    await loadApiData();

    // Default view, then the URL hash overrides
    resetViewState();
    readUrlHash(ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES, ALL_MASK_MODES);
    if (state.algoModalOpen && state.algoModalData && state.algoModalData.funcName) {
      const entry = apiData.find((x) => x.name === state.algoModalData.funcName);
      if (entry) {
        state.algoModalData.entry = entry;
        if (!state.algoModalData.dt) {
          state.algoModalData.dt = entry.datatypes?.[0] || "float32";
        }
      } else {
        state.algoModalOpen = false;
        state.algoModalData = null;
      }
    }
    syncUrlHash(true);

    // Apply UI Size class
    mountEl.classList.remove("mipp-font-sm", "mipp-font-md", "mipp-font-lg");
    mountEl.classList.add(`mipp-font-${state.fontSize}`);

    renderApp();

    if (state.focusedCard) {
      scrollToFocusedCard(state.focusedCard, false);
    }

    // Details (scalar reference, test specification): after the first display
    loadDetailsInBackground();

    // Global listeners: registered once. With the instant navigation of Material, initExplorer runs
    // again at each visit of the page; a second click listener would toggle the macro tooltips twice
    // (open, then close at once).
    if (!globalListenersBound) {
      globalListenersBound = true;

      // End of a resize of the Algorithm modal (see rememberAlgoModalSize)
      document.addEventListener("mouseup", rememberAlgoModalSize);

      // "/" on the Explorer page: focus the search bar of the Explorer instead of
      // opening the site search (Material listens on the document; "s" and "f"
      // still open the site search). Capture phase, to run before Material.
      window.addEventListener("keydown", (e) => {
        if (e.key !== "/" || e.ctrlKey || e.metaKey || e.altKey) return;
        const explorerInput = document.getElementById("mipp-search-input");
        if (!explorerInput) return; // not on the Explorer page
        const t = e.target;
        if (t && (t.isContentEditable || /^(INPUT|TEXTAREA|SELECT)$/.test(t.tagName))) return;
        const siteSearch = document.getElementById("__search");
        if (siteSearch && siteSearch.checked) return;
        e.preventDefault();
        e.stopPropagation();
        explorerInput.focus();
        explorerInput.select();
      }, true);
      window.addEventListener("hashchange", () => {
        if (!document.getElementById("mipp-explorer-app")) return;
        resetViewState();
        readUrlHash(ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES, ALL_MASK_MODES);
        if (state.algoModalOpen && state.algoModalData && state.algoModalData.funcName) {
          const entry = apiData.find((x) => x.name === state.algoModalData.funcName);
          if (entry) {
            state.algoModalData.entry = entry;
            if (!state.algoModalData.dt) {
              state.algoModalData.dt = entry.datatypes?.[0] || "float32";
            }
          } else {
            state.algoModalOpen = false;
            state.algoModalData = null;
          }
        }
        renderApp();

        if (state.focusedCard) {
          scrollToFocusedCard(state.focusedCard, true);
        }
      });

      document.addEventListener("click", (e) => {
        // 1. Algo Modal Trigger
        const algoBtn = e.target.closest("[data-algo-card]");
        if (algoBtn) {
          e.stopPropagation();
          const cardName = algoBtn.getAttribute("data-algo-card");
          const isa = algoBtn.getAttribute("data-algo-isa");
          const dt = algoBtn.getAttribute("data-algo-dt");
          const mask = algoBtn.getAttribute("data-algo-mask") || state.cardHwMask?.[cardName] || "unmasked";
          const reqFeature = algoBtn.getAttribute("data-algo-feature");
          const entry = apiData.find((x) => x.name === cardName);
          if (entry) {
            state.algoModalOpen = true;
            state.algoModalData = {
              entry,
              isa,
              dt,
              mask,
              lmul: state.lmul || "1",
              view: "abstract",
              scalarSize: 256,
              features: getDefaultFeaturesForModal(reqFeature, isa)
            };
            const modalsContainerEl = document.getElementById("mipp-modals-container");
            if (modalsContainerEl) {
              updateModals(modalsContainerEl);
              syncUrlHash(true);
            }
          }
          return;
        }

        // 2. Compare Modal Trigger
        const compareOpenBtn = e.target.closest("#mipp-open-compare-btn, [data-open-compare]");
        if (compareOpenBtn) {
          e.stopPropagation();
          state.compareModalOpen = true;
          const modalsContainerEl = document.getElementById("mipp-modals-container");
          if (modalsContainerEl) updateModals(modalsContainerEl);
          return;
        }

        // 3. Copy Code Buttons
        const copyBtn = e.target.closest(".copy-proto-btn, .copy-code-btn, [data-copy]");
        if (copyBtn) {
          e.stopPropagation();
          const code = copyBtn.getAttribute("data-copy");
          if (code) {
            copyToClipboard(code);
            const originalHtml = copyBtn.innerHTML;
            copyBtn.innerHTML = ICON_CHECK;
            setTimeout(() => {
              copyBtn.innerHTML = originalHtml;
            }, 1500);
          }
          return;
        }

        // 4. Macro and intrinsic tooltips toggle & outside dismissal
        const intrinsicEl = e.target.closest(".mipp-intrinsic-ref");
        if (intrinsicEl) {
          e.stopPropagation();
          toggleIntrinsicTooltip(intrinsicEl);
          return;
        }
        const macroEl = e.target.closest(".mipp-macro-ref");
        if (macroEl) {
          e.stopPropagation();
          toggleMacroTooltip(macroEl);
          return;
        }
        if (!e.target.closest(".mipp-macro-tooltip")) {
          hideMacroTooltip();
        }
      });

      document.addEventListener("keydown", (e) => {
        if (e.key === "Escape") {
          hideMacroTooltip();
          hideIntrinsicTooltip();
        }
        // Enter / Space on a focused macro or intrinsic opens its tooltip
        if ((e.key === "Enter" || e.key === " ") && e.target.closest && e.target.closest(".mipp-intrinsic-ref")) {
          e.preventDefault();
          toggleIntrinsicTooltip(e.target.closest(".mipp-intrinsic-ref"));
        }
      });
    }
  } catch (err) {
    mountEl.innerHTML = `
      <div style="text-align: center; padding: 3rem 1rem; color: #ef4444;">
        <h3>Failed to load MIPP API Index</h3>
        <p style="margin: 0;">Error: ${escapeHtml(err.message)}</p>
      </div>
    `;
  }
}

// Auto-boot if DOM is ready, or on DOMContentLoaded / MkDocs instant navigation
if (typeof document !== "undefined") {
  if (typeof document$ !== "undefined") {
    document$.subscribe(initExplorer);
  } else if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", initExplorer);
  } else {
    initExplorer();
  }
}
