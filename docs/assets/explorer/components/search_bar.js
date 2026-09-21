/**
 * MIPP API Explorer - Search Bar & Top Controls Component
 */
import { escapeHtml, ICON_SEARCH, copyToClipboard } from "../explorer.config.js";
import { state, syncUrlHash } from "../state.js";
import { ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES, ALL_MASK_MODES, ALL_LEVELS } from "../data.js";

function hasActiveFilters() {
  return (
    Boolean(state.query && state.query.trim().length > 0) ||
    state.selectedCategories.length < ALL_CATEGORIES.length ||
    state.selectedTypes.length < ALL_DATATYPES.length ||
    state.selectedMaskModes.length < ALL_MASK_MODES.length ||
    state.selectedSimdExts.length < ALL_SIMD_EXTS.length ||
    state.selectedLevels.length < ALL_LEVELS.length ||
    state.lmul !== "1" ||
    state.flavor !== "cpp" ||
    state.expandedCards.size > 0 ||
    state.focusedCard !== null ||
    state.compareSet.size > 0 ||
    (typeof window !== "undefined" && Boolean(window.location.hash && window.location.hash.length > 1))
  );
}

export function renderSearchBar() {
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

        <!-- UI Size Selector -->
        <div class="mipp-controls-group">
          <span class="mipp-control-label">UI Size:</span>
          <div class="mipp-segmented-group" id="mipp-font-size-group">
            <button class="mipp-segment-btn ${state.fontSize === "sm" ? "active" : ""}" data-font-size="sm" title="Small font">S</button>
            <button class="mipp-segment-btn ${state.fontSize === "md" ? "active" : ""}" data-font-size="md" title="Medium font">M</button>
            <button class="mipp-segment-btn ${state.fontSize === "lg" ? "active" : ""}" data-font-size="lg" title="Large font">L</button>
          </div>
        </div>

        <!-- Utility Actions -->
        <div class="mipp-controls-group">
          <button id="mipp-share-btn" class="mipp-action-btn" title="Copy direct link to this view">
            🔗 Share
          </button>
          <button
            id="mipp-reset-btn"
            class="mipp-action-btn"
            ${hasActiveFilters() ? 'style="color: #ef4444;"' : "disabled"}
            title="${hasActiveFilters() ? "Reset all filters" : "No filters to reset"}"
          >
            ↺ Reset
          </button>
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

  // LMUL
  headerEl.querySelectorAll("#mipp-lmul-group .mipp-segment-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.getAttribute("data-lmul") === state.lmul);
  });

  // UI Size
  headerEl.querySelectorAll("#mipp-font-size-group .mipp-segment-btn").forEach((btn) => {
    btn.classList.toggle("active", btn.getAttribute("data-font-size") === state.fontSize);
  });

  // Reset button: always visible, disabled/grayed out if no active filters
  const resetBtn = headerEl.querySelector("#mipp-reset-btn");
  if (resetBtn) {
    const canReset = hasActiveFilters();
    resetBtn.disabled = !canReset;
    resetBtn.style.color = canReset ? "#ef4444" : "";
    resetBtn.title = canReset ? "Reset all filters" : "No filters to reset";
  }
}

let searchDebounceTimer = null;

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

    // Mobile Validation on Enter key: Close virtual keyboard (blur) & Smooth scroll to first result
    searchInput.addEventListener("keydown", (e) => {
      if (e.key === "Enter") {
        e.preventDefault();
        searchInput.blur(); // Dismiss virtual keyboard on mobile
        state.query = searchInput.value;
        if (clearSearchBtn) clearSearchBtn.style.display = state.query ? "" : "none";
        syncUrlHash(true);
        onSearchChange();

        requestAnimationFrame(() => {
          const appEl = document.getElementById("mipp-explorer-app");
          if (!appEl) return;
          const firstCard = appEl.querySelector(".mipp-card");
          if (firstCard) {
            firstCard.scrollIntoView({ behavior: "smooth", block: "start" });
          } else {
            const noResultsEl = appEl.querySelector(".mipp-no-results");
            if (noResultsEl) {
              noResultsEl.scrollIntoView({ behavior: "smooth", block: "start" });
            }
          }
        });
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
        const prevFlavor = state.flavor;
        state.flavor = btn.getAttribute("data-flavor");
        if (state.flavor === "cpp_obj") {
          state.selectedMaskModes = state.selectedMaskModes.filter((m) => m === "unmasked");
        } else if (prevFlavor === "cpp_obj" && state.selectedMaskModes.length <= 1) {
          state.selectedMaskModes = [...ALL_MASK_MODES];
        }
        syncUrlHash(true);
        onSearchChange();
      });
    });
  }

  // LMUL Switcher
  const lmulGroup = headerEl.querySelector("#mipp-lmul-group");
  if (lmulGroup) {
    lmulGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
      btn.addEventListener("click", () => {
        state.lmul = btn.getAttribute("data-lmul");
        if (state.algoModalData) {
          state.algoModalData.lmul = state.lmul;
        }
        syncUrlHash(true);
        onSearchChange();
      });
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

  // Share View
  const shareBtn = headerEl.querySelector("#mipp-share-btn");
  if (shareBtn) {
    shareBtn.addEventListener("click", () => {
      syncUrlHash(false);
      copyToClipboard(window.location.href, "Shareable URL copied to clipboard!");
    });
  }

  // Reset Filters
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
      if (typeof window !== "undefined" && window.history && window.history.replaceState) {
        window.history.replaceState(null, "", window.location.pathname + window.location.search);
      }
      onSearchChange();
    });
  }
}
