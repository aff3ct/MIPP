/**
 * MIPP API Explorer - Search Bar & Top Controls Component
 */
import { escapeHtml, ICON_SEARCH, copyToClipboard } from "../explorer.config.js";
import { state, syncUrlHash } from "../state.js";
import { ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES } from "../data.js";

function hasActiveFilters() {
  return (
    Boolean(state.query && state.query.trim().length > 0) ||
    state.selectedCategories.length < ALL_CATEGORIES.length ||
    state.selectedTypes.length < ALL_DATATYPES.length ||
    state.maskVariant !== "unmasked" ||
    state.selectedSimdExts.length < ALL_SIMD_EXTS.length ||
    state.lmul !== "1" ||
    state.flavor !== "cpp" ||
    state.expandedCards.size > 0 ||
    state.focusedCard !== null ||
    state.compareSet.size > 0 ||
    (typeof window !== "undefined" && Boolean(window.location.hash && window.location.hash.length > 1))
  );
}

export function renderSearchBar() {
  const isCppObj = state.flavor === "cpp_obj";

  return `
    <!-- Top Sticky Search & Dialect Controls with Integrated Brand Title -->
    <header class="mipp-explorer-header">
      <div class="mipp-search-row">
        <div class="mipp-header-brand">
          <h1 class="mipp-brand-title">
            <span class="mipp-brand-name">MIPP</span>
            <span class="mipp-brand-sub">API Explorer</span>
          </h1>
        </div>
        <div class="mipp-search-input-wrapper">
          ${ICON_SEARCH}
          <input
            id="mipp-search-input"
            type="text"
            class="mipp-search-input"
            placeholder='Search primitive (e.g. "fmadd", "blend") or vendor intrinsic (e.g. "_mm256_blendv_ps", "vbslq_f32")...'
            value="${escapeHtml(state.query)}"
            autocomplete="off"
            spellcheck="false"
          />
          <button id="mipp-search-clear-btn" class="mipp-search-clear" title="Clear search" style="${state.query ? "" : "display: none;"}">✕</button>
        </div>
      </div>

      <div class="mipp-controls-row">
        <!-- Dialect / Flavor Switcher -->
        <div class="mipp-controls-group">
          <span class="mipp-control-label">Dialect:</span>
          <div class="mipp-segmented-group" id="mipp-flavor-group">
            <button class="mipp-segment-btn ${state.flavor === "c99" ? "active" : ""}" data-flavor="c99">C99</button>
            <button class="mipp-segment-btn ${state.flavor === "cpp" ? "active" : ""}" data-flavor="cpp">
              <span class="mipp-dialect-full">C++ Functional</span><span class="mipp-dialect-sm">C++ Func</span>
            </button>
            <button class="mipp-segment-btn ${state.flavor === "cpp_obj" ? "active" : ""}" data-flavor="cpp_obj">
              <span class="mipp-dialect-full">C++ Object</span><span class="mipp-dialect-sm">C++ Obj</span>
            </button>
          </div>
        </div>

        <!-- Variant Selector -->
        <div class="mipp-controls-group">
          <span class="mipp-control-label">Variant:</span>
          <div class="mipp-segmented-group ${isCppObj ? "disabled" : ""}" id="mipp-mask-group" title="${isCppObj ? "Variants are not supported in C++ Object dialect (unmasked only)" : "Filter by variant"}">
            <button class="mipp-segment-btn ${isCppObj || state.maskVariant === "unmasked" ? "active" : ""}" data-mask-variant="unmasked" title="Unmasked">U</button>
            <button class="mipp-segment-btn ${!isCppObj && state.maskVariant === "mask" ? "active" : ""}" data-mask-variant="mask" ${isCppObj ? "disabled" : ""} title="Mask (merge)">M</button>
            <button class="mipp-segment-btn ${!isCppObj && state.maskVariant === "maskz" ? "active" : ""}" data-mask-variant="maskz" ${isCppObj ? "disabled" : ""} title="Maskz (zeroing)">Z</button>
            <button class="mipp-segment-btn ${!isCppObj && state.maskVariant === "masks" ? "active" : ""}" data-mask-variant="masks" ${isCppObj ? "disabled" : ""} title="Masks (sourcing)">S</button>
          </div>
        </div>

        <!-- LMUL Selector -->
        <div class="mipp-controls-group">
          <span class="mipp-control-label">LMUL:</span>
          <div class="mipp-segmented-group" id="mipp-lmul-group">
            <button class="mipp-segment-btn ${state.lmul === "1" ? "active" : ""}" data-lmul="1">1</button>
            <button class="mipp-segment-btn ${state.lmul === "2" ? "active" : ""}" data-lmul="2">2</button>
            <button class="mipp-segment-btn ${state.lmul === "4" ? "active" : ""}" data-lmul="4">4</button>
            <button class="mipp-segment-btn ${state.lmul === "8" ? "active" : ""}" data-lmul="8">8</button>
            <button class="mipp-segment-btn ${state.lmul === "-2" ? "active" : ""}" data-lmul="-2" title="Half vector (LMUL=1/2 / d2)">1/2</button>
          </div>
        </div>

        <!-- Utility Actions: Ultra-compact icon buttons -->
        <div class="mipp-controls-group mipp-actions-group">
          <span class="mipp-control-label mipp-actions-label">Actions:</span>
          <div class="mipp-actions-buttons">
            <div class="mipp-header-options-wrapper">
              <button id="mipp-options-btn" class="mipp-action-icon-btn mipp-options-btn" title="Explorer display settings (UI Size)" aria-label="Display settings" aria-expanded="false">
                ⚙️
              </button>
              <div id="mipp-options-popover" class="mipp-options-popover" style="display: none;">
                <div class="mipp-options-popover-title">Display Settings</div>
                <div class="mipp-options-popover-row">
                  <span class="mipp-control-label">UI Size:</span>
                  <div class="mipp-segmented-group" id="mipp-font-size-group">
                    <button class="mipp-segment-btn ${state.fontSize === "sm" ? "active" : ""}" data-font-size="sm" title="Small (compact)">S</button>
                    <button class="mipp-segment-btn ${state.fontSize === "md" ? "active" : ""}" data-font-size="md" title="Medium (standard)">M</button>
                    <button class="mipp-segment-btn ${state.fontSize === "lg" ? "active" : ""}" data-font-size="lg" title="Large (spacious)">L</button>
                  </div>
                </div>
              </div>
            </div>
            <button id="mipp-share-btn" class="mipp-action-icon-btn" title="Copy direct link to this view" aria-label="Share">
              🔗
            </button>
            <button
              id="mipp-reset-btn"
              class="mipp-action-icon-btn ${hasActiveFilters() ? "has-active" : ""}"
              ${hasActiveFilters() ? "" : "disabled"}
              title="${hasActiveFilters() ? "Reset all filters" : "No filters to reset"}"
              aria-label="Reset filters"
            >
              ↺
            </button>
          </div>
        </div>
      </div>
    </header>
  `;
}

export function updateSearchBarUI(headerEl) {
  if (!headerEl) return;
  const searchInput = headerEl.querySelector("#mipp-search-input");
  if (searchInput && document.activeElement !== searchInput) {
    searchInput.value = state.query || "";
  }
  const clearBtn = headerEl.querySelector("#mipp-search-clear-btn");
  if (clearBtn) {
    clearBtn.style.display = state.query ? "" : "none";
  }

  // Dialect
  headerEl.querySelectorAll("#mipp-flavor-group .mipp-segment-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.getAttribute("data-flavor") === state.flavor);
  });

  // Variant
  const isCppObj = state.flavor === "cpp_obj";
  if (isCppObj) {
    state.maskVariant = "unmasked";
  }
  const maskGroup = headerEl.querySelector("#mipp-mask-group");
  if (maskGroup) {
    maskGroup.classList.toggle("disabled", isCppObj);
    maskGroup.title = isCppObj ? "Variants are not supported in C++ Object dialect (unmasked only)" : "Filter by variant";
    maskGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
      const v = btn.getAttribute("data-mask-variant");
      if (isCppObj) {
        btn.disabled = (v !== "unmasked");
        btn.classList.toggle("active", v === "unmasked");
      } else {
        btn.disabled = false;
        btn.classList.toggle("active", v === state.maskVariant);
      }
    });
  }

  // LMUL
  headerEl.querySelectorAll("#mipp-lmul-group .mipp-segment-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.getAttribute("data-lmul") === state.lmul);
  });

  // UI Size
  headerEl.querySelectorAll("#mipp-font-size-group .mipp-segment-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.getAttribute("data-font-size") === state.fontSize);
  });

  // Reset button: ultra-compact icon button, disabled/grayed out if no active filters
  const resetBtn = headerEl.querySelector("#mipp-reset-btn");
  if (resetBtn) {
    const canReset = hasActiveFilters();
    resetBtn.disabled = !canReset;
    resetBtn.classList.toggle("has-active", canReset);
    resetBtn.title = canReset ? "Reset all filters" : "No filters to reset";
  }
}

/**
 * Preserve the viewport position of the current focal card across filtering re-renders (Scroll Anchoring - Cas A).
 */
export function preserveScrollAnchor(actionFn) {
  if (typeof window === "undefined" || typeof document === "undefined") {
    actionFn();
    return;
  }

  const headerEl = document.querySelector(".mipp-explorer-header");
  const headerBottom = headerEl ? Math.max(0, headerEl.getBoundingClientRect().bottom) : 0;
  const viewportHeight = window.innerHeight || document.documentElement.clientHeight || 800;

  let anchorEl = null;
  let anchorTop = 0;

  // 1. Prioritize any expanded card currently in viewport
  const expandedCards = Array.from(document.querySelectorAll(".mipp-card.expanded"));
  for (const card of expandedCards) {
    const rect = card.getBoundingClientRect();
    if (rect.bottom > headerBottom && rect.top < viewportHeight) {
      anchorEl = card;
      anchorTop = rect.top;
      break;
    }
  }

  // 2. Otherwise pick the card closest to top of viewport below header
  if (!anchorEl) {
    const allCards = Array.from(document.querySelectorAll(".mipp-card"));
    let closestDist = Infinity;
    for (const card of allCards) {
      const rect = card.getBoundingClientRect();
      if (rect.bottom > headerBottom) {
        const dist = Math.abs(rect.top - headerBottom);
        if (dist < closestDist) {
          closestDist = dist;
          anchorEl = card;
          anchorTop = rect.top;
        }
      }
    }
  }

  const anchorName = anchorEl ? anchorEl.getAttribute("data-card-name") : null;

  // Execute mutation
  actionFn();

  // Scroll compensation
  if (anchorName) {
    const performAdjustment = () => {
      const newAnchorEl = document.getElementById(`card-${anchorName}`)
        || document.querySelector(`.mipp-card[data-card-name="${anchorName}"]`);
      if (newAnchorEl) {
        const newTop = newAnchorEl.getBoundingClientRect().top;
        const deltaY = newTop - anchorTop;
        if (Math.abs(deltaY) > 1) {
          window.scrollBy({ top: deltaY, left: 0, behavior: "instant" });
        }
      }
    };

    requestAnimationFrame(performAdjustment);
    setTimeout(performAdjustment, 30);
  }
}

let searchDebounceTimer = null;

export function scrollToSearchResults(smooth = true) {
  const performScroll = () => {
    const appEl = document.getElementById("mipp-explorer-app");
    if (!appEl) return;
    const targetEl = appEl.querySelector(".mipp-card")
                  || appEl.querySelector(".mipp-results-bar")
                  || appEl.querySelector("#mipp-cards-container")
                  || appEl.querySelector(".mipp-cards-container")
                  || appEl.querySelector(".mipp-no-results");
    if (!targetEl) return;

    const headerEl = appEl.querySelector(".mipp-explorer-header");
    const headerBottom = headerEl ? Math.max(0, headerEl.getBoundingClientRect().bottom) : 0;
    const targetRect = targetEl.getBoundingClientRect();
    const gap = 12; // Espace d'aération esthétique sous le header
    const delta = targetRect.top - (headerBottom + gap);

    // Si les résultats sont déjà parfaitement visibles sous le header, éviter tout saut inutile
    if (Math.abs(delta) < 20) return;

    const targetY = Math.max(0, window.scrollY + delta);
    window.scrollTo({
      top: targetY,
      behavior: smooth ? "smooth" : "auto",
    });
  };

  // Si le clavier virtuel mobile est en train de se fermer, attendre l'adaptation du visualViewport
  if (window.visualViewport) {
    let executed = false;
    const onResize = () => {
      if (executed) return;
      executed = true;
      requestAnimationFrame(performScroll);
    };
    window.visualViewport.addEventListener("resize", onResize, { once: true });
    setTimeout(onResize, 180);
  } else {
    requestAnimationFrame(performScroll);
    setTimeout(performScroll, 100);
  }
}

export function bindSearchBarEvents(headerEl, onSearchChange) {
  if (!headerEl) return;
  const searchInput = headerEl.querySelector("#mipp-search-input");
  const clearSearchBtn = headerEl.querySelector("#mipp-search-clear-btn");

  if (searchInput) {
    searchInput.addEventListener("input", (e) => {
      clearTimeout(searchDebounceTimer);
      searchDebounceTimer = setTimeout(() => {
        state.query = e.target.value;
        if (clearSearchBtn) clearSearchBtn.style.display = state.query ? "" : "none";
        syncUrlHash(true);
        onSearchChange();
      }, 150);
    });

    // Validation sur touche Entrée : fermeture clavier virtuel et défilement dynamique vers les résultats
    searchInput.addEventListener("keydown", (e) => {
      if (e.key === "Enter") {
        e.preventDefault();
        searchInput.blur(); // Ferme le clavier virtuel sur mobile
        state.query = searchInput.value;
        if (clearSearchBtn) clearSearchBtn.style.display = state.query ? "" : "none";
        syncUrlHash(true);
        onSearchChange();

        scrollToSearchResults(true);
      }
    });
  }

  if (clearSearchBtn) {
    clearSearchBtn.addEventListener("click", () => {
      state.query = "";
      if (searchInput) searchInput.value = "";
      clearSearchBtn.style.display = "none";
      syncUrlHash(true);
      onSearchChange();
      if (searchInput) searchInput.focus();
    });
  }

  // Flavor Switcher
  const flavorGroup = headerEl.querySelector("#mipp-flavor-group");
  if (flavorGroup) {
    flavorGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
      btn.addEventListener("click", () => {
        const newFlavor = btn.getAttribute("data-flavor");
        if (state.flavor === newFlavor) return;
        preserveScrollAnchor(() => {
          state.flavor = newFlavor;
          if (state.flavor === "cpp_obj") {
            state.maskVariant = "unmasked";
          }
          syncUrlHash(true);
          onSearchChange();
        });
      });
    });
  }

  // Variant Switcher
  const maskGroup = headerEl.querySelector("#mipp-mask-group");
  if (maskGroup) {
    maskGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
      btn.addEventListener("click", () => {
        if (state.flavor === "cpp_obj") return;
        const newVariant = btn.getAttribute("data-mask-variant");
        if (state.maskVariant === newVariant) return;
        preserveScrollAnchor(() => {
          state.maskVariant = newVariant;
          syncUrlHash(true);
          onSearchChange();
        });
      });
    });
  }

  // LMUL Switcher
  const lmulGroup = headerEl.querySelector("#mipp-lmul-group");
  if (lmulGroup) {
    lmulGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
      btn.addEventListener("click", () => {
        const newLmul = btn.getAttribute("data-lmul");
        if (state.lmul === newLmul) return;
        preserveScrollAnchor(() => {
          state.lmul = newLmul;
          syncUrlHash(true);
          onSearchChange();
        });
      });
    });
  }

  // Options Popover Toggle (UI Size)
  const optionsBtn = headerEl.querySelector("#mipp-options-btn");
  const optionsPopover = headerEl.querySelector("#mipp-options-popover");
  if (optionsBtn && optionsPopover) {
    optionsBtn.addEventListener("click", (e) => {
      e.stopPropagation();
      const isVisible = optionsPopover.style.display !== "none";
      optionsPopover.style.display = isVisible ? "none" : "block";
      optionsBtn.setAttribute("aria-expanded", String(!isVisible));
    });

    document.addEventListener("click", (e) => {
      if (!optionsPopover.contains(e.target) && e.target !== optionsBtn) {
        optionsPopover.style.display = "none";
        optionsBtn.setAttribute("aria-expanded", "false");
      }
    });
  }

  // UI Size Switcher
  const fontSizeGroup = headerEl.querySelector("#mipp-font-size-group");
  if (fontSizeGroup) {
    fontSizeGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
      btn.addEventListener("click", () => {
        state.fontSize = btn.getAttribute("data-font-size");
        localStorage.setItem("mipp_font_size", state.fontSize);
        const appEl = document.getElementById("mipp-explorer-app");
        if (appEl) {
          appEl.classList.remove("mipp-font-sm", "mipp-font-md", "mipp-font-lg");
          appEl.classList.add(`mipp-font-${state.fontSize}`);
        }
        onSearchChange();
      });
    });
  }

  // Share View (Ultra-compact icon button)
  const shareBtn = headerEl.querySelector("#mipp-share-btn");
  if (shareBtn) {
    shareBtn.addEventListener("click", () => {
      syncUrlHash(false);
      copyToClipboard(window.location.href, "Shareable URL copied to clipboard!");
    });
  }

  // Reset Filters (Ultra-compact icon button)
  const resetBtn = headerEl.querySelector("#mipp-reset-btn");
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
      if (typeof window !== "undefined" && window.history && window.history.replaceState) {
        window.history.replaceState(null, "", window.location.pathname + window.location.search);
      }
      onSearchChange();
    });
  }
}
