/**
 * MIPP API Explorer - Reactive State & URL Synchronization
 */
import { VALID_CARD_TABS } from "./explorer.config.js";
import { ALL_SIMD_EXTS, ALL_CATEGORIES, ALL_DATATYPES, ALL_MASK_MODES, ALL_LEVELS } from "./data.js";

export const state = {
  query: "",
  searchField: "all", // 'all' | 'name' | 'desc' | 'proto' | 'hw'
  flavor: "cpp", // 'c99' | 'cpp' | 'cpp_obj'
  lmul: "1", // '1' | '2' | '4' | '8' | '-2'
  fontSize: (typeof localStorage !== "undefined" && typeof localStorage.getItem === "function" ? localStorage.getItem("mipp_font_size") : null) || (typeof window !== "undefined" && window.innerWidth <= 768 ? "sm" : "md"),
  selectedSimdExts: [],
  selectedLevels: [0, 1, 2, 3],
  intersectionMode: false, // false: Union (∪), true: Intersection (∩)
  selectedCategories: [],
  selectedTypes: [],
  selectedMaskModes: [],
  selectedExtensionTypes: [],
  expandedCards: new Set(),
  openedCardsOrder: [], // Array tracking order in which cards were opened
  focusedCard: null, // Card name currently focused in URL
  compareSet: new Set(),
  compareModalOpen: false,
  algoModalOpen: false,
  algoModalData: null, // { entry, simdExt, dt, mask, lmul }
  cardTabs: {}, // cardName -> "hw" | "proto" | "scalar" | "specs" | "flat"
  cardFlatState: {}, // cardName -> { simdExt, dt, mask, lmul, scalarSize, defines }
  cardHwMask: {}, // cardName -> "unmasked" | "mask" | "maskz" | "masks"
  cardScalarTypes: {},
  cardScalarVariants: {},
  cardTestVariants: {},
};

export function setFocusedCard(cardName) {
  if (cardName) {
    state.expandedCards.add(cardName);
    state.openedCardsOrder = [cardName, ...state.openedCardsOrder.filter((c) => c !== cardName)];
    state.focusedCard = cardName;
  } else {
    state.focusedCard = null;
  }
}

export function closeCard(cardName) {
  state.expandedCards.delete(cardName);
  state.openedCardsOrder = state.openedCardsOrder.filter((c) => c !== cardName);
  if (state.focusedCard === cardName) {
    const nextFocus = state.openedCardsOrder.find((c) => state.expandedCards.has(c)) || null;
    state.focusedCard = nextFocus;
  }
}

export function syncUrlHash(replace = false) {
  const params = new URLSearchParams();
  if (state.query && state.query.trim()) params.set("q", state.query.trim());
  if (state.searchField && state.searchField !== "all") params.set("field", state.searchField);
  if (state.flavor && state.flavor !== "cpp") params.set("flavor", state.flavor);
  if (state.lmul && state.lmul !== "1") params.set("lmul", state.lmul);

  const extsList = ALL_SIMD_EXTS;
  if (state.selectedSimdExts && state.selectedSimdExts.length < extsList.length) {
    params.set("simd_ext", state.selectedSimdExts.join(","));
  }
  if (state.selectedLevels && state.selectedLevels.length > 0 && state.selectedLevels.length < ALL_LEVELS.length) {
    params.set("lvl", state.selectedLevels.join(","));
  }
  if (state.intersectionMode) params.set("inter", "1");
  if (state.selectedCategories && state.selectedCategories.length < ALL_CATEGORIES.length) {
    params.set("cat", state.selectedCategories.join(","));
  }
  if (state.selectedTypes && state.selectedTypes.length < ALL_DATATYPES.length) {
    params.set("types", state.selectedTypes.join(","));
  }
  if (state.selectedMaskModes && state.selectedMaskModes.length < ALL_MASK_MODES.length) {
    params.set("mask", state.selectedMaskModes.join(","));
  }

  const activeFocus = (state.focusedCard && state.expandedCards.has(state.focusedCard))
    ? state.focusedCard
    : (state.openedCardsOrder.find((c) => state.expandedCards.has(c)) || null);

  if (activeFocus && state.expandedCards.has(activeFocus)) {
    params.set("focus", activeFocus);
    const activeTab = state.cardTabs[activeFocus] || "proto";
    params.set("tab", activeTab);

    if (activeTab === "scalar") {
      const dt = state.cardScalarTypes[activeFocus] || "float32";
      params.set("scalar_dt", dt);
    } else if (activeTab === "specs") {
      const mask = state.cardTestVariants[activeFocus] || "unmasked";
      params.set("spec_mask", mask);
    } else if (activeTab === "hw") {
      const hwMask = state.cardHwMask[activeFocus] || "unmasked";
      if (hwMask !== "unmasked") {
        params.set("hw_mask", hwMask);
      }
    }
  }

  const newHash = params.toString() ? `#${params.toString()}` : "";
  const newUrl = window.location.pathname + window.location.search + newHash;
  if (replace) {
    window.history.replaceState(null, "", newUrl);
  } else {
    window.history.pushState(null, "", newUrl);
  }
}

export function readUrlHash(allSimdExts, allCategories, allDatatypes, allMaskModes) {
  const hash = window.location.hash.slice(1);
  if (!hash) return;
  try {
    const params = new URLSearchParams(hash);
    if (params.has("q")) state.query = params.get("q");
    if (params.has("field")) state.searchField = params.get("field");
    if (params.has("flavor")) state.flavor = params.get("flavor");
    if (params.has("lmul")) state.lmul = params.get("lmul");

    if (params.has("simd_ext")) {
      const raw = params.get("simd_ext");
      const exts = raw.split(",").filter((x) => ALL_SIMD_EXTS.includes(x));
      state.selectedSimdExts = exts;
    }
    if (params.has("lvl")) {
      const lvls = params.get("lvl").split(",").map(Number).filter((n) => [0, 1, 2, 3].includes(n));
      state.selectedLevels = lvls;
    }
    if (params.has("inter")) {
      state.intersectionMode = params.get("inter") === "1";
    }
    if (params.has("cat")) {
      state.selectedCategories = params.get("cat").split(",").filter((c) => ALL_CATEGORIES.includes(c));
    }
    if (params.has("types")) {
      state.selectedTypes = params.get("types").split(",").filter((t) => ALL_DATATYPES.some((d) => d.id === t));
    }
    if (params.has("mask")) {
      state.selectedMaskModes = params.get("mask").split(",").filter((x) => ALL_MASK_MODES.includes(x));
    }
    if (params.has("focus")) {
      const focusName = params.get("focus");
      state.expandedCards.add(focusName);
      setFocusedCard(focusName);
      if (params.has("tab")) {
        const tab = params.get("tab");
        if (VALID_CARD_TABS.includes(tab)) {
          state.cardTabs[focusName] = (tab === "example" ? "flat" : tab);
        }
      }
      if (params.has("scalar_dt")) {
        state.cardScalarTypes[focusName] = params.get("scalar_dt");
      }
      if (params.has("spec_mask")) {
        state.cardTestVariants[focusName] = params.get("spec_mask");
      }
      if (params.has("hw_mask")) {
        const m = params.get("hw_mask");
        if (ALL_MASK_MODES.includes(m) || m === "unmasked") {
          state.cardHwMask[focusName] = m;
        }
      }
    }
  } catch (err) {
    console.warn("Failed to parse URL hash:", err);
  }
}
