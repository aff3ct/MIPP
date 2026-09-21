/**
 * MIPP API Explorer - Main Orchestrator & Lifecycle
 */
import { escapeHtml, ICON_CHECK, VALID_CARD_TABS, copyToClipboard } from "./explorer.config.js";
import {
  apiData,
  apiMetadata,
  loadApiData,
  ALL_SIMD_EXTS,
  ALL_CATEGORIES,
  ALL_DATATYPES,
  ALL_MASK_MODES
} from "./data.js";
import { state, syncUrlHash, readUrlHash, setFocusedCard, closeCard } from "./state.js";
import { filterEntries } from "./filters.js";
import { renderSidebar, updateSidebarUI, bindSidebarEvents } from "./components/sidebar.js";
import { renderSearchBar, updateSearchBarUI, bindSearchBarEvents } from "./components/search_bar.js";
import { renderCard, switchCardTab, renderCardExpandedDetails } from "./components/card.js";
import { renderAlgoModal } from "./components/modal_algo.js";
import { renderCompareModal } from "./components/modal_compare.js";
import { showMacroTooltip, hideMacroTooltip, toggleMacroTooltip } from "./syntax.js";
import { getCardFlatState } from "./components/tab_flat.js";

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
  updateSearchBarUI(headerEl);
  renderCards(cardsContainerEl);
  updateCompareBar(compareBarEl);
  updateModals(modalsContainerEl);
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
      ${renderSidebar(catCounts, renderApp)}

      <!-- Cards Main Area -->
      <main class="mipp-cards-container"></main>
    </div>

    <!-- Side-by-side Compare Floating Bar -->
    <div class="mipp-compare-bar ${state.compareSet.size >= 1 ? "visible" : ""}">
      <span class="mipp-compare-bar-text" style="font-weight: 600; font-size: 0.88rem;">
        ⚖️ Compare (${state.compareSet.size}/3): <span style="color: var(--mipp-accent);">${Array.from(state.compareSet).join(", ")}</span>
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

  // Bind shell events (once!)
  bindSidebarEvents(sidebarEl, renderApp);
  bindSearchBarEvents(headerEl, renderApp);
  bindCompareBarEvents(appEl);

  // Initial render of contents
  updateSidebarUI(sidebarEl);
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
          <div style="font-size: 2.5rem; margin-bottom: 0.5rem;">🔍</div>
          <h3 style="margin: 0 0 0.5rem 0;">No matching MIPP primitives found</h3>
          <p style="color: var(--md-default-fg-color--lighter, #94a3b8); margin: 0 0 1rem 0; font-size: 0.88rem;">
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
      state.selectedMaskModes = [...ALL_MASK_MODES];
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
      if (window.MathJax && window.MathJax.typesetPromise) {
        window.MathJax.typesetPromise([cardEl]).catch(() => {});
      }
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
      if (window.MathJax && window.MathJax.typesetPromise) {
        window.MathJax.typesetPromise([cardEl]).catch(() => {});
      }
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
    let headerStickyTop = 11;
    let headerHeight = 135;
    if (headerEl) {
      headerHeight = headerEl.offsetHeight;
      const compStyle = window.getComputedStyle(headerEl);
      const topVal = parseFloat(compStyle.top);
      if (!isNaN(topVal)) {
        headerStickyTop = topVal;
      }
    }
    const gapMargin = 14;
    const totalOffset = headerStickyTop + headerHeight + gapMargin;
    const cardRect = cardEl.getBoundingClientRect();
    const targetY = window.scrollY + cardRect.top - totalOffset;
    window.scrollTo({
      top: Math.max(0, targetY),
      behavior: smooth ? "smooth" : "auto",
    });
  };

  setTimeout(performScroll, 60);
  setTimeout(performScroll, 220);
}

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

  // 3. Verification Specs Variant Buttons
  paneEl.querySelectorAll(".mipp-test-variant-btn, [data-test-variant]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const variant = btn.getAttribute("data-mask") || btn.getAttribute("data-test-variant");
      if (variant) {
        state.cardTestVariants[entry.name] = variant;
        setFocusedCard(entry.name);
        syncUrlHash(true);
        switchCardTab(cardEl, entry, "specs");
        attachCardInternalListeners(cardEl, entry);
      }
    });
  });

  // 4. Flat Code Tab Toolbar Buttons
  paneEl.querySelectorAll("[data-flat-isa], [data-flat-simd-ext]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const ext = btn.getAttribute("data-flat-simd-ext") || btn.getAttribute("data-flat-isa");
      const flatCfg = getCardFlatState(entry.name, entry);
      flatCfg.isa = ext;
      flatCfg.simdExt = ext;
      switchCardTab(cardEl, entry, "flat");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  paneEl.querySelectorAll("[data-flat-dt]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const dt = btn.getAttribute("data-flat-dt");
      const flatCfg = getCardFlatState(entry.name, entry);
      flatCfg.dt = dt;
      switchCardTab(cardEl, entry, "flat");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  paneEl.querySelectorAll("[data-flat-mask]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const m = btn.getAttribute("data-flat-mask");
      const flatCfg = getCardFlatState(entry.name, entry);
      flatCfg.mask = m;
      switchCardTab(cardEl, entry, "flat");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  paneEl.querySelectorAll("[data-flat-flag]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const flag = btn.getAttribute("data-flat-flag");
      const flatCfg = getCardFlatState(entry.name, entry);
      flatCfg.defines[flag] = flatCfg.defines[flag] === false ? true : false;
      switchCardTab(cardEl, entry, "flat");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  paneEl.querySelectorAll("[data-flat-scalarsize]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const sz = parseInt(btn.getAttribute("data-flat-scalarsize"), 10);
      const flatCfg = getCardFlatState(entry.name, entry);
      flatCfg.scalarSize = sz;
      switchCardTab(cardEl, entry, "flat");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  paneEl.querySelectorAll("[data-hw-mask]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const m = btn.getAttribute("data-hw-mask");
      if (!state.cardHwMask) state.cardHwMask = {};
      state.cardHwMask[entry.name] = m;
      switchCardTab(cardEl, entry, "hw");
      attachCardInternalListeners(cardEl, entry);
    });
  });

  // 5. "View Algorithm" Modal Trigger
  paneEl.querySelectorAll("[data-algo-card]").forEach((btn) => {
    btn.addEventListener("click", (e) => {
      e.stopPropagation();
      const ext = btn.getAttribute("data-algo-simd-ext") || btn.getAttribute("data-algo-isa");
      const dt = btn.getAttribute("data-algo-dt");
      const mask = btn.getAttribute("data-algo-mask") || state.cardHwMask?.[entry.name] || "unmasked";
      state.algoModalOpen = true;
      state.algoModalData = {
        entry,
        isa: ext,
        simdExt: ext,
        dt,
        mask,
        lmul: state.lmul || "1"
      };
      const appEl = document.getElementById("mipp-explorer-app");
      if (appEl) {
        const modalsContainerEl = appEl.querySelector("#mipp-modals-container");
        if (modalsContainerEl) updateModals(modalsContainerEl);
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
  if (!compareBarEl) return;
  const isVisible = state.compareSet.size >= 1;
  compareBarEl.classList.toggle("visible", isVisible);

  const textEl = compareBarEl.querySelector(".mipp-compare-bar-text");
  if (textEl) {
    textEl.innerHTML = `⚖️ Compare (${state.compareSet.size}/3): <span style="color: var(--mipp-accent);">${Array.from(state.compareSet).join(", ")}</span>`;
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

function updateModals(modalsContainerEl) {
  if (!modalsContainerEl) return;

  modalsContainerEl.innerHTML = `
    ${state.algoModalOpen ? renderAlgoModal(state.algoModalData) : ""}
    ${state.compareModalOpen ? renderCompareModal(apiData) : ""}
  `;

  // Algo Modal Events
  if (state.algoModalOpen) {
    const algoCloseBtn = modalsContainerEl.querySelector("#mipp-algo-modal-close");
    if (algoCloseBtn) {
      algoCloseBtn.addEventListener("click", () => {
        state.algoModalOpen = false;
        state.algoModalData = null;
        updateModals(modalsContainerEl);
      });
    }

    const algoBackdrop = modalsContainerEl.querySelector("#mipp-algo-modal-backdrop");
    if (algoBackdrop) {
      algoBackdrop.addEventListener("click", (e) => {
        if (e.target === algoBackdrop) {
          state.algoModalOpen = false;
          state.algoModalData = null;
          updateModals(modalsContainerEl);
        }
      });
    }

    const dtSelect = modalsContainerEl.querySelector("#mipp-algo-modal-dt-select");
    if (dtSelect) {
      dtSelect.addEventListener("change", (e) => {
        if (state.algoModalData) {
          state.algoModalData.dt = e.target.value;
          updateModals(modalsContainerEl);
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

    if (window.MathJax && window.MathJax.typesetPromise) {
      window.MathJax.typesetPromise([modalsContainerEl]).catch(() => {});
    }

    // Copy buttons inside modals
    modalsContainerEl.querySelectorAll(".copy-proto-btn, .copy-code-btn, [data-copy]").forEach((btn) => {
      btn.addEventListener("click", async (e) => {
        e.stopPropagation();
        const textToCopy = btn.getAttribute("data-copy");
        if (textToCopy) {
          try {
            await navigator.clipboard.writeText(textToCopy);
            const origHtml = btn.innerHTML;
            btn.innerHTML = `<span style="font-size: 0.75rem; color: #10b981;">✓</span>`;
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

export async function initExplorer() {
  const mountEl = document.getElementById("mipp-explorer-app");
  if (!mountEl) return;

  document.body.classList.add("mipp-has-explorer");

  mountEl.innerHTML = `
    <div style="text-align: center; padding: 4rem 1rem; color: var(--md-default-fg-color--lighter, #94a3b8); max-width: 480px; margin: 0 auto;">
      <div style="font-size: 2.2rem; margin-bottom: 0.75rem;">🔍</div>
      <div style="font-weight: 600; font-size: 1.15rem; color: var(--md-default-fg-color);">Loading MIPP API Explorer...</div>
      <p style="font-size: 0.85rem; margin: 0.4rem 0 1.2rem 0;">Preparing interactive catalog of SIMD primitives and hardware architectures</p>
      <div class="mipp-loading-bar-wrapper">
        <div class="mipp-loading-bar-fill" id="mipp-load-progress-fill" style="width: 0%;"></div>
      </div>
      <div id="mipp-load-progress-text" style="font-size: 0.78rem; margin-top: 0.5rem; font-family: var(--md-code-font, monospace);">
        Connecting...
      </div>
    </div>
  `;

  try {
    await loadApiData();

    // Initialize all filters as active by default
    state.selectedSimdExts = [...ALL_SIMD_EXTS];
    state.selectedCategories = [...ALL_CATEGORIES];
    state.selectedTypes = ALL_DATATYPES.map((d) => d.id);
    state.selectedMaskModes = [...ALL_MASK_MODES];
    state.selectedLevels = [0, 1, 2, 3];

    // Read URL hash overrides
    readUrlHash(ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES, ALL_MASK_MODES);
    syncUrlHash(true);

    // Apply UI Size class
    mountEl.classList.remove("mipp-font-sm", "mipp-font-md", "mipp-font-lg");
    mountEl.classList.add(`mipp-font-${state.fontSize}`);

    renderApp();

    if (state.focusedCard) {
      scrollToFocusedCard(state.focusedCard, false);
    }

    window.addEventListener("hashchange", () => {
      state.selectedSimdExts = [...ALL_SIMD_EXTS];
      state.selectedCategories = [...ALL_CATEGORIES];
      state.selectedTypes = ALL_DATATYPES.map((d) => d.id);
      state.selectedMaskModes = [...ALL_MASK_MODES];
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

      readUrlHash(ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES, ALL_MASK_MODES);
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
        const entry = apiData.find((x) => x.name === cardName);
        if (entry) {
          state.algoModalOpen = true;
          state.algoModalData = {
            entry,
            isa,
            dt,
            mask,
            lmul: state.lmul || "1"
          };
          const modalsContainerEl = document.getElementById("mipp-modals-container");
          if (modalsContainerEl) updateModals(modalsContainerEl);
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

      // 4. Macro tooltips toggle & outside dismissal
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
      }
    });
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
