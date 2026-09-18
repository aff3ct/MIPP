/**
 * MIPP API Explorer (explorer.js)
 * High-performance, client-side Single Page Application (SPA).
 * Zero server runtime, zero Node.js/npm dependencies, 100% offline capable.
 * Features:
 *  - Instant fuzzy search & vendor intrinsics reverse lookup
 *  - Multi-faceted filtering (ISAs, Guaranteed Levels, Categories, Types, Masking)
 *  - Dynamic hardware matrix filtering based on selected Target ISAs
 *  - API Flavor Switcher (C99, C++ Generic, C++ Object)
 *  - Tabbed accordion cards (Hardware Matrix, Prototypes, Scalar C Reference, Specs, Examples)
 *  - Interactive Datatype dropdown for Scalar C algorithms
 *  - Dedicated modal for Level 1 & Level 2 Emulation Algorithms
 *  - Lightweight client-side C/C++ regex syntax highlighter
 *  - Standalone Godbolt (Compiler Explorer) native compilation snippets
 *  - Side-by-side primitive comparator
 *  - URL hash deep-linking and state persistence
 *  - MkDocs Material light/dark theme integration
 */

(function () {
  "use strict";

  // Global State
  let apiData = [];
  let isInitialized = false;

  const state = {
    query: "",
    flavor: "cpp", // 'c99' | 'cpp' | 'cpp_obj'
    lmul: "1", // '1' | '2' | '4' | '8' | '-2'
    fontSize: localStorage.getItem("mipp_font_size") || (window.innerWidth <= 768 ? "sm" : "md"),
    selectedIsas: ["sse", "avx", "avx512", "neon", "sve", "rvv"],
    selectedLevels: [0, 1, 2, 3],
    intersectionMode: false,
    selectedCategories: [],
    selectedTypes: [],
    selectedMaskModes: ["unmasked", "mask", "maskz", "masks"],
    expandedCards: new Set(),
    openedCardsOrder: [], // Array tracking order in which cards were opened
    focusedCard: null, // Card name currently focused in URL
    compareSet: new Set(),
    compareModalOpen: false,
    cardTabs: {}, // cardName -> "hw" | "proto" | "scalar" | "specs" | "example"
    cardScalarTypes: {}, // cardName -> datatype string
    cardScalarVariants: {}, // cardName -> mask string
    cardTestVariants: {}, // cardName -> mask string for verification specs
    algoModal: {
      open: false,
      func: null,
      isa: null,
      level: null,
      dt: null,
    },
  };

  const ALL_ISAS = ["sse", "avx", "avx512", "neon", "sve", "rvv"];
  const ISA_DISPLAY_NAMES = {
    sse: "SSE",
    avx: "AVX",
    avx512: "AVX-512",
    neon: "NEON",
    sve: "SVE",
    rvv: "RVV",
  };

  const ALL_LEVELS = [0, 1, 2, 3];
  const LEVEL_DESCRIPTIONS = {
    0: "Native Hardware",
    1: "Dedicated Emulation",
    2: "Generic Emulation",
    3: "Scalar Fallback",
  };

  const ALL_DATATYPES = [
    { id: "float64", label: "float64", group: "floats" },
    { id: "float32", label: "float32", group: "floats" },
    { id: "int64", label: "int64", group: "signed" },
    { id: "int32", label: "int32", group: "signed" },
    { id: "int16", label: "int16", group: "signed" },
    { id: "int8", label: "int8", group: "signed" },
    { id: "uint64", label: "uint64", group: "unsigned" },
    { id: "uint32", label: "uint32", group: "unsigned" },
    { id: "uint16", label: "uint16", group: "unsigned" },
    { id: "uint8", label: "uint8", group: "unsigned" },
  ];

  const ICON_COPY = `<svg class="mipp-copy-icon" viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path></svg>`;
  const ICON_CHECK = `<svg class="mipp-copy-icon" viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="#10b981" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"></polyline></svg>`;
  const ICON_CHEVRON = `<svg class="mipp-chevron" viewBox="0 0 24 24" width="10" height="10" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="6 9 12 15 18 9"></polyline></svg>`;

  // ------------------------------------------------------------------------
  // Helper: Datatype Badge Class Resolver
  // ------------------------------------------------------------------------
  function getDtBadgeClass(dt) {
    if (!dt) return "";
    if (dt.includes(",")) {
      const parts = dt.split(",").map((p) => p.trim());
      if (parts.length >= 2 && parts.every((p) => p === parts[0])) {
        return `dt-${parts[0]}`;
      }
      return "dt-mixed";
    }
    return `dt-${dt}`;
  }

  // ------------------------------------------------------------------------
  // Helper: Clean Mathematical Semantics Typography
  // ------------------------------------------------------------------------
  function formatMathHtml(expr) {
    if (!expr) return "";
    let clean = String(expr)
      .replace(/\\mathrm\{([^}]+)\}/g, "$1")
      .replace(/\\text\{([^}]+)\}/g, "$1")
      .replace(/\\operatorname\{([^}]+)\}/g, "$1")
      .replace(/\ba_i\b/g, "r0<sub>i</sub>")
      .replace(/\bb_i\b/g, "r1<sub>i</sub>")
      .replace(/\bc_i\b/g, "r2<sub>i</sub>")
      .replace(/\\cdot/g, " · ")
      .replace(/\\times/g, " × ")
      .replace(/\\le/g, " ≤ ")
      .replace(/\\ge/g, " ≥ ")
      .replace(/\\neq/g, " ≠ ")
      .replace(/\\infty/g, "∞")
      .replace(/\\sqrt\{([^}]+)\}/g, "√($1)")
      .replace(/\\exp\b/g, "exp")
      .replace(/\\ln\b/g, "ln")
      .replace(/\\log\b/g, "log")
      .replace(/\\cos\b/g, "cos")
      .replace(/\\sin\b/g, "sin")
      .replace(/\\tan\b/g, "tan")
      .replace(/\\arccos\b/g, "arccos")
      .replace(/\\arcsin\b/g, "arcsin")
      .replace(/\\arctan\b/g, "arctan")
      .replace(/\\cosh\b/g, "cosh")
      .replace(/\\sinh\b/g, "sinh")
      .replace(/\\tanh\b/g, "tanh")
      .replace(/\\arcosh\b/g, "arcosh")
      .replace(/\\arsinh\b/g, "arsinh")
      .replace(/\\artanh\b/g, "artanh")
      .replace(/\\left\|/g, "|")
      .replace(/\\right\|/g, "|")
      .replace(/\\left/g, "")
      .replace(/\\right/g, "")
      .replace(/_\{([^}]+)\}/g, "<sub>$1</sub>")
      .replace(/_([a-zA-Z0-9])/g, "<sub>$1</sub>")
      .replace(/\^\{([^}]+)\}/g, "<sup>$1</sup>")
      .replace(/\^([a-zA-Z0-9])/g, "<sup>$1</sup>");
    return clean;
  }

  // ------------------------------------------------------------------------
  // Helper: Dynamic ISA Level Computation based on Datatypes & LMUL
  // ------------------------------------------------------------------------
  function getEffectiveIsaLevel(entry, isa, dt = null) {
    const isaInfo = entry.isa_support ? entry.isa_support[isa] : null;
    if (!isaInfo) return 3;

    let baseLevel = isaInfo.overall_level !== undefined ? isaInfo.overall_level : 3;
    if (dt && isaInfo.by_datatype && isaInfo.by_datatype[dt] !== undefined) {
      baseLevel = isaInfo.by_datatype[dt];
    } else if (!dt && isaInfo.by_datatype) {
      const activeDts = getActiveSelectedTypes(entry);
      if (activeDts.length > 0) {
        const levels = activeDts.map((d) => isaInfo.by_datatype[d]).filter((l) => l !== undefined);
        if (levels.length > 0) baseLevel = Math.min(...levels);
      }
    }

    // Dynamic LMUL impact:
    // Fixed-length vector ISAs (SSE, AVX, AVX-512, NEON) only feature hardware LMUL=1.
    // For LMUL > 1 or LMUL = 1/2, MIPP utilizes multi-register software loop emulation -> Level 2.
    // RVV hardware natively supports LMUL (1, 2, 4, 8, -2).
    const currentLmul = Number(state.lmul);
    const hwLmuls = isaInfo.hw_lmul || (isa === "rvv" ? [1, 2, 4, 8, -2] : [1]);
    if (currentLmul !== 1 && !hwLmuls.includes(currentLmul)) {
      if (baseLevel < 2) {
        baseLevel = 2; // Generic emulation loop
      }
    }

    return baseLevel;
  }

  // ------------------------------------------------------------------------
  // Lightweight C/C++ Syntax Highlighter (Linear Time Regex Tokenizer)
  // ------------------------------------------------------------------------
  function highlightCpp(code, scalarMacros = null) {
    if (!code) return "";
    const cleanCode = code.replace(/\binline\s+/g, "");

    const tokenPatterns = [
      // 1. Comments
      '(//[^\n]*|/\\*[\\s\\S]*?\\*/)',
      // 2. Preprocessor
      '(#[a-zA-Z_]+[^\n]*)',
      // 3. Strings
      '("(?:\\\\.|[^"\\\\])*")',
      // 4. Numbers
      '\\b(0x[0-9a-fA-F]+|\\d+(?:\\.\\d+)?(?:[eE][+-]?\\d+)?[fFulUL]*)\\b',
      // 5. Types (MIPP SIMD types, Rvd, rvd, Rvm, rvm, C/C++ primitives)
      '\\b(MKIND|rvd_[a-z0-9_]+_t|rvm_[a-z0-9_]+_t|Rvd|rvd|Rvm|rvm|__m128[a-z0-9_]*|__m256[a-z0-9_]*|__m512[a-z0-9_]*|float32x4_t|float32x8_t|sv[a-z0-9_]+_t|v[a-z0-9_]+_t|reg|msk|void|bool|bool_t|char|int|short|long|float|double|float32_t|float64_t|uint8_t|uint16_t|uint32_t|uint64_t|int8_t|int16_t|int32_t|int64_t|size_t)\\b',
      // 6. Keywords
      '\\b(const|static|return|if|else|for|while|do|switch|case|default|break|continue|struct|class|template|typename|auto|sizeof|typedef|namespace|using|constexpr|extern)\\b',
      // 7. Hardware Intrinsics
      '\\b(_mm256_[a-zA-Z0-9_]+|_mm512_[a-zA-Z0-9_]+|_mm_[a-zA-Z0-9_]+|v[a-z0-9_]+|sv[a-z0-9_]+|__riscv_[a-z0-9_]+)\\b',
      // 8. Template parameters (T, T1, T2, LMUL, LDIV, N, MK, M, Z, S, U)
      '\\b(T|T1|T2|LMUL|LDIV|N|MK|M|Z|S|U)\\b',
    ];

    if (scalarMacros && typeof scalarMacros === "object") {
      const macroNames = Object.keys(scalarMacros).filter((k) => /^[A-Z0-9_]+$/.test(k));
      if (macroNames.length > 0) {
        tokenPatterns.push('\\b(' + macroNames.join("|") + ')\\b');
      }
    }

    const tokenRegex = new RegExp(tokenPatterns.join("|"), "g");

    let lastIndex = 0;
    let html = "";
    let match;

    while ((match = tokenRegex.exec(cleanCode)) !== null) {
      if (match.index > lastIndex) {
        html += escapeHtml(cleanCode.slice(lastIndex, match.index));
      }
      const token = match[0];
      let cls = "";
      if (match[1]) cls = "mipp-hl-cmt";
      else if (match[2]) cls = "mipp-hl-pp";
      else if (match[3]) cls = "mipp-hl-str";
      else if (match[4]) cls = "mipp-hl-num";
      else if (match[5]) cls = "mipp-hl-type";
      else if (match[6]) cls = "mipp-hl-kw";
      else if (match[7]) cls = "mipp-hl-fn";
      else if (match[8]) cls = "mipp-hl-tmpl";

      if (scalarMacros && scalarMacros[token]) {
        const macroInfo = scalarMacros[token];
        const macroDef = typeof macroInfo === "object" ? (macroInfo.definition || macroInfo.body || "") : String(macroInfo);
        html += `<span class="mipp-hl-macro mipp-macro-ref" data-macro-name="${escapeHtml(token)}" data-macro-def="${escapeHtml(macroDef)}" tabindex="0" role="button">${escapeHtml(token)}</span>`;
      } else {
        html += `<span class="${cls}">${escapeHtml(token)}</span>`;
      }
      lastIndex = tokenRegex.lastIndex;
    }

    if (lastIndex < cleanCode.length) {
      html += escapeHtml(cleanCode.slice(lastIndex));
    }

    return html;
  }

  // ------------------------------------------------------------------------
  // Interactive Macro Definition Tooltip (Click/Tap Activated)
  // ------------------------------------------------------------------------
  function showMacroTooltip(macroEl) {
    if (!macroEl) return;
    const macroName = macroEl.getAttribute("data-macro-name") || macroEl.textContent.trim();
    const macroDef = macroEl.getAttribute("data-macro-def") || "";
    if (!macroDef) return;

    const existing = document.querySelector(".mipp-macro-tooltip");
    if (existing) {
      const wasSame = existing._targetMacro === macroEl;
      if (existing._targetMacro) {
        existing._targetMacro.classList.remove("active");
      }
      existing.remove();
      if (wasSame) return; // Toggle off on second click
    }

    macroEl.classList.add("active");

    const tooltip = document.createElement("div");
    tooltip.className = "mipp-macro-tooltip";
    tooltip._targetMacro = macroEl;
    tooltip.innerHTML = `
      <div class="mipp-macro-tooltip-header">
        <span class="mipp-macro-tooltip-title">Macro: <code>${escapeHtml(macroName)}</code></span>
        <div style="display: flex; align-items: center; gap: 0.35rem;">
          <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(macroDef)}" title="Copy macro definition">${ICON_COPY}</button>
          <button class="mipp-macro-tooltip-close" aria-label="Close" title="Close">✕</button>
        </div>
      </div>
      <pre class="mipp-macro-tooltip-code"><code>${escapeHtml(macroDef)}</code></pre>
    `;
    document.body.appendChild(tooltip);

    const copyBtn = tooltip.querySelector(".copy-proto-btn");
    if (copyBtn) {
      copyBtn.addEventListener("click", (e) => {
        e.stopPropagation();
        copyToClipboard(macroDef, "Macro definition copied!");
        flashCopySuccess(copyBtn);
      });
    }

    const rect = macroEl.getBoundingClientRect();
    const pad = 12;
    const maxW = Math.min(420, window.innerWidth - pad * 2);
    tooltip.style.maxWidth = `${maxW}px`;
    tooltip.style.boxSizing = "border-box";

    let top = rect.bottom + window.scrollY + 6;
    let left = rect.left + window.scrollX;

    const tooltipWidth = tooltip.offsetWidth || maxW;
    const viewportRight = window.scrollX + window.innerWidth - pad;

    if (left + tooltipWidth > viewportRight) {
      left = Math.max(window.scrollX + pad, viewportRight - tooltipWidth);
    }
    if (left < window.scrollX + pad) {
      left = window.scrollX + pad;
    }

    tooltip.style.top = `${top}px`;
    tooltip.style.left = `${left}px`;

    tooltip.querySelector(".mipp-macro-tooltip-close").addEventListener("click", (ev) => {
      ev.stopPropagation();
      macroEl.classList.remove("active");
      tooltip.remove();
    });
  }

  function hideMacroTooltip() {
    const existing = document.querySelector(".mipp-macro-tooltip");
    if (existing) {
      if (existing._targetMacro) {
        existing._targetMacro.classList.remove("active");
      }
      existing.remove();
    }
  }

  // ------------------------------------------------------------------------
  // Data Fetching with Resilient Candidate Paths & Streaming Progress
  // ------------------------------------------------------------------------
  async function loadApiData() {
    if (apiData.length > 0) return apiData;

    const candidatePaths = [
      "../../assets/data/mipp_api_index.json",
      "../assets/data/mipp_api_index.json",
      "assets/data/mipp_api_index.json",
      "/assets/data/mipp_api_index.json",
    ];

    for (const path of candidatePaths) {
      try {
        const fetchUrl = path + (path.includes("?") ? "&" : "?") + "v=" + Date.now();
        const resp = await fetch(fetchUrl, { cache: "no-cache" });
        if (resp.ok) {
          const contentLength = resp.headers.get("content-length");
          const totalBytes = contentLength ? parseInt(contentLength, 10) : 0;
          if (resp.body && window.ReadableStream && totalBytes > 0) {
            const reader = resp.body.getReader();
            let loadedBytes = 0;
            const chunks = [];
            while (true) {
              const { done, value } = await reader.read();
              if (done) break;
              chunks.push(value);
              loadedBytes += value.length;
              const pct = Math.min(100, Math.round((loadedBytes / totalBytes) * 100));
              const fillEl = document.getElementById("mipp-load-progress-fill");
              const textEl = document.getElementById("mipp-load-progress-text");
              if (fillEl) fillEl.style.width = `${pct}%`;
              if (textEl) {
                textEl.textContent = `${pct}% (${(loadedBytes / (1024 * 1024)).toFixed(1)} MB / ${(totalBytes / (1024 * 1024)).toFixed(1)} MB)`;
              }
            }
            const allChunks = new Uint8Array(loadedBytes);
            let pos = 0;
            for (const chunk of chunks) {
              allChunks.set(chunk, pos);
              pos += chunk.length;
            }
            const text = new TextDecoder("utf-8").decode(allChunks);
            apiData = JSON.parse(text);
            initApiDataIndexes(apiData);
            return apiData;
          } else {
            apiData = await resp.json();
            initApiDataIndexes(apiData);
            return apiData;
          }
        }
      } catch (err) {
        // Try next candidate
      }
    }
    throw new Error("Unable to load mipp_api_index.json from candidate paths.");
  }

  let allPrimitiveNamesDesc = [];

  function initApiDataIndexes(data) {
    if (!data || !Array.isArray(data)) return;
    allPrimitiveNamesDesc = data.map((e) => e.name.toLowerCase()).sort((a, b) => b.length - a.length);

    for (const entry of data) {
      if (entry._c99_names) continue;
      const set = new Set();
      if (entry.prototypes && entry.prototypes.c99) {
        const m = entry.prototypes.c99.match(/\b(mipp_[a-zA-Z0-9_]+)\(/);
        if (m) set.add(m[1].toLowerCase());
      }
      if (entry.prototypes && entry.prototypes.c99_samples) {
        for (const lmul in entry.prototypes.c99_samples) {
          const lmulObj = entry.prototypes.c99_samples[lmul];
          if (!lmulObj || typeof lmulObj !== "object") continue;
          for (const mask in lmulObj) {
            const protos = lmulObj[mask];
            if (!Array.isArray(protos)) continue;
            for (const p of protos) {
              const m = p.match(/\b(mipp_[a-zA-Z0-9_]+)\(/);
              if (m) set.add(m[1].toLowerCase());
            }
          }
        }
      }
      entry._c99_names = Array.from(set);
    }
  }

  // ------------------------------------------------------------------------
  // URL Hash State Synchronization
  // ------------------------------------------------------------------------
  const VALID_CARD_TABS = ["hw", "proto", "scalar", "specs", "example"];

  function setFocusedCard(cardName) {
    if (!cardName) return;
    state.openedCardsOrder = state.openedCardsOrder.filter((name) => name !== cardName);
    state.openedCardsOrder.push(cardName);
    state.focusedCard = cardName;
  }

  function removeOpenedCard(cardName) {
    state.openedCardsOrder = state.openedCardsOrder.filter((name) => name !== cardName);
    if (state.focusedCard === cardName) {
      let fallback = null;
      for (let i = state.openedCardsOrder.length - 1; i >= 0; i--) {
        if (state.expandedCards.has(state.openedCardsOrder[i])) {
          fallback = state.openedCardsOrder[i];
          break;
        }
      }
      if (!fallback && state.expandedCards.size > 0) {
        fallback = Array.from(state.expandedCards).pop();
      }
      state.focusedCard = fallback;
    }
  }

  function scrollToFocusedCard(cardName, smooth = false) {
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
      const gapMargin = 14; // professional breathing room between search bubble and card
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

  function getActiveCardScalarDt(cardName, entry) {
    if (!entry) entry = apiData.find((x) => x.name === cardName);
    if (!entry) return state.cardScalarTypes[cardName] || "float32";
    const activeDts = getActiveSelectedTypes(entry);
    const availableDts = activeDts.length > 0 ? activeDts : (entry.datatypes || ["float32"]);
    let selected = state.cardScalarTypes[cardName];
    if (!selected || !availableDts.includes(selected)) {
      selected = availableDts[0] || "float32";
      state.cardScalarTypes[cardName] = selected;
    }
    return selected;
  }

  function getActiveCardTestVariant(cardName, entry) {
    if (!entry) entry = apiData.find((x) => x.name === cardName);
    if (!entry) return (state.cardTestVariants && state.cardTestVariants[cardName]) || "unmasked";
    const variants = entry.test_specs && entry.test_specs.variants ? entry.test_specs.variants : null;
    const availableVariants = variants ? Object.keys(variants) : ["unmasked"];
    let selected = state.cardTestVariants && state.cardTestVariants[cardName];
    if (!selected || !availableVariants.includes(selected)) {
      selected = availableVariants[0] || "unmasked";
      if (!state.cardTestVariants) state.cardTestVariants = {};
      state.cardTestVariants[cardName] = selected;
    }
    return selected;
  }

  function parseUrlHash() {
    const hash = window.location.hash.substring(1);
    if (!hash) {
      state.expandedCards.clear();
      state.openedCardsOrder = [];
      state.focusedCard = null;
      return;
    }

    const params = new URLSearchParams(hash);
    if (params.has("q")) state.query = params.get("q");
    if (params.has("flavor")) state.flavor = params.get("flavor");
    if (params.has("lmul")) state.lmul = params.get("lmul");
    if (params.has("intersect")) state.intersectionMode = params.get("intersect") === "1";

    if (params.has("isa")) {
      const isas = params.get("isa").split(",").filter((x) => ALL_ISAS.includes(x));
      if (isas.length > 0) state.selectedIsas = isas;
    }
    if (params.has("l")) {
      const lvls = params.get("l").split(",").map(Number).filter((x) => !isNaN(x) && ALL_LEVELS.includes(x));
      if (lvls.length > 0) state.selectedLevels = lvls;
    }
    if (params.has("cat")) {
      state.selectedCategories = params.get("cat").split(",").filter(Boolean);
    }
    if (params.has("types")) {
      state.selectedTypes = params.get("types").split(",").filter(Boolean);
    }
    if (params.has("mask")) {
      const masks = params.get("mask").split(",").filter((x) => ["unmasked", "mask", "maskz", "masks"].includes(x));
      if (masks.length > 0) state.selectedMaskModes = masks;
    }
    if (params.has("focus")) {
      const focusName = params.get("focus");
      state.expandedCards.add(focusName);
      setFocusedCard(focusName);
      if (params.has("tab")) {
        const tab = params.get("tab");
        if (VALID_CARD_TABS.includes(tab)) {
          state.cardTabs[focusName] = tab;
        }
      }
      const scalarDt = params.get("scalar_dt") || params.get("sdt") || params.get("dt");
      if (scalarDt) {
        state.cardScalarTypes[focusName] = scalarDt;
      }
      const specMask = params.get("spec_mask") || params.get("vmask") || params.get("smask") || params.get("test_mask");
      if (specMask) {
        if (!state.cardTestVariants) state.cardTestVariants = {};
        state.cardTestVariants[focusName] = specMask;
      }
    }
  }

  function syncUrlHash(push = false) {
    const params = new URLSearchParams();
    if (state.query) params.set("q", state.query);
    if (state.flavor !== "cpp") params.set("flavor", state.flavor);
    if (state.lmul !== "1") params.set("lmul", state.lmul);
    if (state.intersectionMode) params.set("intersect", "1");

    if (state.selectedIsas.length !== ALL_ISAS.length) {
      params.set("isa", state.selectedIsas.join(","));
    }
    if (state.selectedLevels.length !== ALL_LEVELS.length) {
      params.set("l", state.selectedLevels.join(","));
    }
    if (state.selectedCategories.length > 0) {
      params.set("cat", state.selectedCategories.join(","));
    }
    if (state.selectedTypes.length > 0) {
      params.set("types", state.selectedTypes.join(","));
    }
    if (state.selectedMaskModes.length !== 4) {
      params.set("mask", state.selectedMaskModes.join(","));
    }

    const activeFocus = (state.focusedCard && state.expandedCards.has(state.focusedCard))
      ? state.focusedCard
      : (state.openedCardsOrder.slice().reverse().find((c) => state.expandedCards.has(c)) ||
         (state.expandedCards.size > 0 ? Array.from(state.expandedCards).pop() : null));

    if (activeFocus && state.expandedCards.has(activeFocus)) {
      params.set("focus", activeFocus);
      const activeTab = state.cardTabs[activeFocus] || "hw";
      params.set("tab", activeTab);

      if (activeTab === "scalar") {
        const scalarDt = getActiveCardScalarDt(activeFocus);
        if (scalarDt) {
          params.set("scalar_dt", scalarDt);
        }
      } else if (activeTab === "specs") {
        const specMask = getActiveCardTestVariant(activeFocus);
        if (specMask) {
          params.set("spec_mask", specMask);
        }
      }
    }

    const hashStr = params.toString() ? "#" + params.toString() : "";
    if (window.location.hash !== hashStr) {
      if (push) {
        history.pushState(null, "", window.location.pathname + window.location.search + hashStr);
      } else {
        history.replaceState(null, "", window.location.pathname + window.location.search + hashStr);
      }
    }
  }

  // ------------------------------------------------------------------------
  // Clipboard & Toast Feedback
  // ------------------------------------------------------------------------
  function showToast(message) {
    let toast = document.getElementById("mipp-toast");
    if (!toast) {
      toast = document.createElement("div");
      toast.id = "mipp-toast";
      toast.className = "mipp-toast";
      document.body.appendChild(toast);
    }
    const textMsg = typeof message === "string" && message.trim().length > 0 ? message : "Copied to clipboard!";
    toast.textContent = textMsg;
    toast.classList.add("visible");
    setTimeout(() => {
      toast.classList.remove("visible");
    }, 2200);
  }

  async function copyToClipboard(text, message = "Copied to clipboard!") {
    const textMsg = typeof message === "string" && message.trim().length > 0 ? message : "Copied to clipboard!";
    try {
      if (navigator.clipboard && window.isSecureContext) {
        await navigator.clipboard.writeText(text);
      } else {
        const textArea = document.createElement("textarea");
        textArea.value = text;
        textArea.style.position = "fixed";
        textArea.style.left = "-999999px";
        document.body.appendChild(textArea);
        textArea.focus();
        textArea.select();
        document.execCommand("copy");
        textArea.remove();
      }
      showToast(textMsg);
    } catch (err) {
      showToast("Unable to copy to clipboard.");
    }
  }

  function flashCopySuccess(btn) {
    if (!btn) return;
    const origHtml = btn.innerHTML;
    btn.innerHTML = ICON_CHECK;
    btn.classList.add("copied");
    setTimeout(() => {
      btn.innerHTML = origHtml;
      btn.classList.remove("copied");
    }, 1500);
  }

  // ------------------------------------------------------------------------
  // Filtering & Search Engine
  // ------------------------------------------------------------------------
  function getPrimitiveFromQuery(rest) {
    for (const pName of allPrimitiveNamesDesc) {
      if (rest === pName || rest.startsWith(pName + "_")) {
        return pName;
      }
    }
    return null;
  }

  function matchesQuery(entry, qClean) {
    if (!qClean || qClean === "mipp" || qClean === "mipp_" || qClean === "mipp::") {
      return { matches: true, matchedIntrinsic: null, matchedC99: null };
    }

    if (allPrimitiveNamesDesc.length === 0 && apiData.length > 0) {
      initApiDataIndexes(apiData);
    }

    const nameLow = entry.name.toLowerCase();

    // 1. Query starts with MIPP namespace or prefix (mipp_, mipp::, mipp_scalar_)
    if (qClean.startsWith("mipp_scalar_") || qClean.startsWith("mipp_") || qClean.startsWith("mipp::")) {
      const rest = qClean.replace(/^(mipp_scalar_|mipp_|mipp::)/, "");

      const prim = getPrimitiveFromQuery(rest);
      if (prim && rest.startsWith(prim + "_")) {
        if (nameLow === prim) {
          const matchedC99 = entry._c99_names ? entry._c99_names.find((fn) => fn === qClean || fn.startsWith(qClean)) : null;
          return { matches: true, matchedIntrinsic: null, matchedC99: matchedC99 || qClean };
        }
        return { matches: false, matchedIntrinsic: null, matchedC99: null };
      }

      if (nameLow === rest || nameLow.startsWith(rest)) {
        return { matches: true, matchedIntrinsic: null, matchedC99: null };
      }

      if (entry._c99_names && entry._c99_names.length > 0) {
        const matched = entry._c99_names.find((fn) => fn === qClean || fn.startsWith(qClean));
        if (matched) {
          return { matches: true, matchedIntrinsic: null, matchedC99: matched };
        }
      }

      return { matches: false, matchedIntrinsic: null, matchedC99: null };
    }

    // 2. Standard search (no mipp_ prefix)
    // Check function name directly
    if (nameLow.includes(qClean)) {
      return { matches: true, matchedIntrinsic: null, matchedC99: null };
    }

    // If user searched for e.g. 'add_float64_m1' without 'mipp_'
    const primNoPrefix = getPrimitiveFromQuery(qClean);
    if (primNoPrefix && qClean.startsWith(primNoPrefix + "_")) {
      if (nameLow === primNoPrefix) {
        const matchedC99 = entry._c99_names ? entry._c99_names.find((fn) => fn.includes(qClean)) : null;
        return { matches: true, matchedIntrinsic: null, matchedC99: matchedC99 || qClean };
      }
    }

    // Reverse lookup in vendor intrinsics
    if (entry.vendor_intrinsics_reverse_index) {
      for (const intr of entry.vendor_intrinsics_reverse_index) {
        if (intr.toLowerCase().includes(qClean)) {
          return { matches: true, matchedIntrinsic: intr, matchedC99: null };
        }
      }
    }

    // Category match
    if (entry.category.toLowerCase().includes(qClean)) {
      return { matches: true, matchedIntrinsic: null, matchedC99: null };
    }

    // Description or math semantics
    if (entry.description && entry.description.toLowerCase().includes(qClean)) {
      return { matches: true, matchedIntrinsic: null, matchedC99: null };
    }
    if (entry.math_semantics && entry.math_semantics.toLowerCase().includes(qClean)) {
      return { matches: true, matchedIntrinsic: null, matchedC99: null };
    }

    return { matches: false, matchedIntrinsic: null, matchedC99: null };
  }

  function matchesFilters(entry) {
    // 1. Category Filter
    if (state.selectedCategories.length > 0) {
      if (!state.selectedCategories.includes(entry.category)) {
        return false;
      }
    }

    // 2. Datatypes Filter
    if (state.selectedTypes.length > 0) {
      const hasType = state.selectedTypes.some((t) => {
        return entry.datatypes.some((edt) => edt === t || edt.startsWith(t + ",") || edt.endsWith("," + t));
      });
      if (!hasType) return false;
    }

    // 3. Masking Mode Filter
    if (state.selectedMaskModes.length > 0) {
      const hasMask = state.selectedMaskModes.some((m) => entry.mask_support && entry.mask_support[m]);
      if (!hasMask) return false;
    }

    // 4. Target ISAs & Guaranteed Acceleration Levels (Dynamic Levels based on LMUL & Datatype)
    if (state.selectedIsas.length > 0 && state.selectedLevels.length > 0) {
      if (state.intersectionMode) {
        const allSatisfy = state.selectedIsas.every((isa) => {
          const lvl = getEffectiveIsaLevel(entry, isa);
          return state.selectedLevels.includes(lvl);
        });
        if (!allSatisfy) return false;
      } else {
        const anySatisfies = state.selectedIsas.some((isa) => {
          const lvl = getEffectiveIsaLevel(entry, isa);
          return state.selectedLevels.includes(lvl);
        });
        if (!anySatisfies) return false;
      }
    }

    return true;
  }

  function getFilteredEntries() {
    let qClean = state.query.trim().toLowerCase();
    qClean = qClean.replace(/[\(\);]+$/, "").trim();
    const results = [];

    for (const entry of apiData) {
      const searchRes = matchesQuery(entry, qClean);
      if (!searchRes.matches) continue;

      if (!matchesFilters(entry)) continue;

      results.push({
        entry,
        matchedIntrinsic: searchRes.matchedIntrinsic,
        matchedC99: searchRes.matchedC99,
      });
    }

    return results;
  }

  // ------------------------------------------------------------------------
  // Helper: Active Selected Datatypes for Primitive
  // ------------------------------------------------------------------------
  function getActiveSelectedTypes(entry) {
    if (!state.selectedTypes || state.selectedTypes.length === 0) {
      return [];
    }
    return entry.datatypes.filter((edt) => {
      return state.selectedTypes.some((t) => edt === t || edt.startsWith(t + ",") || edt.endsWith("," + t));
    });
  }

  // ------------------------------------------------------------------------
  // Helper: Prototype Formatter (stripping redundant 'inline')
  // ------------------------------------------------------------------------
  function cleanProto(str) {
    if (!str) return "";
    return str.replace(/\binline\s+/g, "").trim();
  }

  function getActiveMaskVariantsForEntry(entry) {
    if (state.flavor === "cpp_obj") {
      return ["unmasked"];
    }
    const allVariants = ["unmasked", "mask", "maskz", "masks"];
    const supportedVariants = allVariants.filter(
      (m) => m === "unmasked" || (entry.mask_support && entry.mask_support[m])
    );
    if (state.selectedMaskModes.length > 0) {
      return supportedVariants.filter((m) => state.selectedMaskModes.includes(m));
    }
    return supportedVariants;
  }

  function getActivePrototype(entry) {
    const lmulKey = state.lmul;
    const protoData = entry.prototypes;
    const activeDts = getActiveSelectedTypes(entry);
    const activeMasks = getActiveMaskVariantsForEntry(entry);
    const preferredMask = activeMasks.length > 0 ? activeMasks[0] : "unmasked";

    if (state.flavor === "c99") {
      const samplesForLmul = protoData.c99_samples ? protoData.c99_samples[lmulKey] : null;
      let lines = [];
      if (samplesForLmul) {
        if (Array.isArray(samplesForLmul)) {
          lines = samplesForLmul;
        } else if (typeof samplesForLmul === "object") {
          lines = samplesForLmul[preferredMask] || samplesForLmul["unmasked"] || Object.values(samplesForLmul)[0] || [];
        }
      }
      if (lines && lines.length > 0) {
        if (activeDts.length > 0) {
          const match = lines.find((s) =>
            activeDts.some((dt) => s.includes(`_${dt}_`) || s.includes(`_${dt}(`) || s.includes(`_${dt};`) || s.includes(`_${dt}`))
          );
          if (match) return cleanProto(match);
        }
        return cleanProto(lines[0]);
      }
      return cleanProto(protoData.c99 || `mipp_${entry.name}(...)`);
    } else if (state.flavor === "cpp") {
      const cppSample = protoData.cpp_samples ? protoData.cpp_samples[lmulKey] : null;
      let baseProto = "";
      if (typeof cppSample === "object" && cppSample !== null) {
        baseProto = cleanProto(cppSample[preferredMask] || cppSample["unmasked"] || Object.values(cppSample)[0] || "");
      } else if (typeof cppSample === "string") {
        baseProto = cleanProto(cppSample);
      }
      if (!baseProto) {
        baseProto = cleanProto(protoData.cpp || `mipp::${entry.name}(...)`);
      }

      if (activeDts.length === 1) {
        const dt = activeDts[0];
        return baseProto.replace(/<typename\s+T>/g, "").replace(/<T>/g, `<${dt}>`).replace(/\bT\b/g, dt).trim();
      }
      return baseProto;
    } else {
      // C++ Object
      if (protoData.cpp_obj_samples && protoData.cpp_obj_samples[lmulKey]) {
        const baseProto = cleanProto(protoData.cpp_obj_samples[lmulKey]);
        if (activeDts.length === 1) {
          const dt = activeDts[0];
          return baseProto.replace(/<typename\s+T[^>]*>/g, "").replace(/<T>/g, `<${dt}>`).replace(/<T,/g, `<${dt},`).replace(/\bT\b/g, dt).trim();
        }
        return baseProto;
      }
      return cleanProto(protoData.cpp_obj || `r0.${entry.name}(...)`);
    }
  }

  function getAllPrototypesForFlavor(entry) {
    const lmulKey = state.lmul;
    const protoData = entry.prototypes;
    const activeDts = getActiveSelectedTypes(entry);

    if (state.flavor === "c99") {
      if (protoData.c99_samples && protoData.c99_samples[lmulKey] && protoData.c99_samples[lmulKey].length > 0) {
        let list = protoData.c99_samples[lmulKey].map(cleanProto);
        if (activeDts.length > 0) {
          const filtered = list.filter((sig) =>
            activeDts.some((dt) => sig.includes(`_${dt}_`) || sig.includes(`_${dt}(`) || sig.includes(`_${dt};`) || sig.includes(`_${dt}`))
          );
          if (filtered.length > 0) return filtered.join("\n");
        }
        return list.join("\n");
      }
      return cleanProto(protoData.c99 || `mipp_${entry.name}(...)`);
    } else if (state.flavor === "cpp") {
      let code = "";
      if (protoData.cpp_samples && protoData.cpp_samples[lmulKey]) {
        code = cleanProto(protoData.cpp_samples[lmulKey]);
      } else {
        code = cleanProto(protoData.cpp || `mipp::${entry.name}(...)`);
      }

      if (activeDts.length > 0) {
        const specializations = activeDts.map((dt) => {
          let spec = code
            .replace(/,\s*typename\s+T\b/g, "")
            .replace(/typename\s+T,\s*/g, "")
            .replace(/<typename\s+T>/g, "")
            .replace(/<T>/g, `<${dt}>`)
            .replace(/<T,/g, `<${dt},`)
            .replace(/\bT\b/g, dt)
            .replace(/template\s*<\s*>\s*/g, "")
            .trim();
          return `// Specialized for <${dt}>:\n${spec}`;
        }).join("\n\n");
        return `// C++ Functional Template:\n${code}\n\n${specializations}`;
      }
      return code;
    } else {
      let code = "";
      if (protoData.cpp_obj_samples && protoData.cpp_obj_samples[lmulKey]) {
        code = cleanProto(protoData.cpp_obj_samples[lmulKey]);
      } else {
        code = cleanProto(protoData.cpp_obj || `r0.${entry.name}(...)`);
      }

      if (activeDts.length > 0) {
        const specializations = activeDts.map((dt) => {
          const spec = code
            .replace(/<typename\s+T[^>]*>/g, "")
            .replace(/<T>/g, `<${dt}>`)
            .replace(/<T,/g, `<${dt},`)
            .replace(/\bT\b/g, dt)
            .trim();
          return `// Method on Rvd<${dt}>:\n${spec}`;
        }).join("\n\n");
        return `// C++ Object Template:\n${code}\n\n${specializations}`;
      }
      return code;
    }
  }

  // ------------------------------------------------------------------------
  // Dynamic Header Offset for Sticky Sidebar
  // ------------------------------------------------------------------------
  let headerObserver = null;
  function syncHeaderOffset() {
    const header = document.querySelector(".mipp-explorer-header");
    if (header) {
      const rect = header.getBoundingClientRect();
      const height = Math.ceil(rect.height);
      document.documentElement.style.setProperty("--mipp-header-height", `${height}px`);
    }
  }

  function observeHeader() {
    const header = document.querySelector(".mipp-explorer-header");
    if (header && window.ResizeObserver) {
      if (headerObserver) headerObserver.disconnect();
      headerObserver = new ResizeObserver(() => syncHeaderOffset());
      headerObserver.observe(header);
    }
  }

  // ------------------------------------------------------------------------
  // HTML Rendering
  // ------------------------------------------------------------------------
  function renderApp() {
    const appEl = document.getElementById("mipp-explorer-app");
    if (!appEl) return;

    appEl.className = `mipp-font-${state.fontSize}`;

    const prevSidebar = document.querySelector(".mipp-sidebar");
    const prevSidebarScrollTop = prevSidebar ? prevSidebar.scrollTop : 0;
    const prevWindowScrollY = window.scrollY;

    const isCppObj = state.flavor === "cpp_obj";
    if (isCppObj) {
      state.selectedMaskModes = state.selectedMaskModes.filter((m) => m === "unmasked");
    }

    // Collect Categories with Counts
    const catCounts = {};
    for (const item of apiData) {
      catCounts[item.category] = (catCounts[item.category] || 0) + 1;
    }

    const filtered = getFilteredEntries();

    appEl.innerHTML = `
      <!-- Top Sticky Search & Dialect Controls with Integrated Brand Title -->
      <header class="mipp-explorer-header">
        <div class="mipp-search-row">
          <div class="mipp-header-brand">
            <h1 class="mipp-brand-title">MIPP API Explorer</h1>
          </div>
          <div class="mipp-search-input-wrapper">
            <svg class="mipp-search-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
              <circle cx="11" cy="11" r="8"></circle>
              <line x1="21" y1="21" x2="16.65" y2="16.65"></line>
            </svg>
            <input 
              id="mipp-search-input" 
              type="text" 
              class="mipp-search-input" 
              placeholder='Search primitive (e.g. "fmadd", "blend") or vendor intrinsic (e.g. "_mm256_blendv_ps", "vbslq_f32")...' 
              value="${escapeHtml(state.query)}"
              autocomplete="off"
              spellcheck="false"
            />
            ${state.query
        ? `<button id="mipp-search-clear-btn" class="mipp-search-clear" title="Clear search">✕</button>`
        : ""
      }
          </div>
        </div>

        <div class="mipp-controls-row">
          <!-- Dialect Switcher -->
          <div class="mipp-controls-group">
            <span class="mipp-control-label">Dialect:</span>
            <div class="mipp-segmented-group" id="mipp-flavor-group">
              <button class="mipp-segment-btn ${state.flavor === "c99" ? "active" : ""}" data-flavor="c99">C99</button>
              <button class="mipp-segment-btn ${state.flavor === "cpp" ? "active" : ""}" data-flavor="cpp">C++ Functional</button>
              <button class="mipp-segment-btn ${state.flavor === "cpp_obj" ? "active" : ""}" data-flavor="cpp_obj">C++ Object</button>
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
              <button class="mipp-segment-btn ${state.lmul === "-2" ? "active" : ""}" data-lmul="-2">1/2</button>
            </div>
          </div>

          <!-- Font Size Selector -->
          <div class="mipp-controls-group">
            <span class="mipp-control-label">Size:</span>
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
            ${state.query ||
        state.selectedCategories.length > 0 ||
        state.selectedTypes.length > 0 ||
        state.selectedMaskModes.length > 0 ||
        state.selectedIsas.length !== ALL_ISAS.length ||
        state.selectedLevels.length !== ALL_LEVELS.length ||
        state.lmul !== "1" ||
        state.flavor !== "cpp"
        ? `<button id="mipp-reset-btn" class="mipp-action-btn" style="color: #ef4444;" title="Reset all filters">↺ Reset</button>`
        : ""
      }
          </div>
        </div>
      </header>

      <!-- Main Body: Sidebar Filters + Cards List -->
      <div class="mipp-explorer-body">
        <!-- Sidebar Filters -->
        <aside class="mipp-sidebar">
          <!-- Target ISAs Filter -->
          <div class="mipp-filter-section">
            <div class="mipp-filter-header">
              <h3 class="mipp-filter-title">Target ISAs</h3>
              <button id="mipp-select-all-isas" class="mipp-filter-quick-action">
                ${state.selectedIsas.length === ALL_ISAS.length ? "Clear" : "All"}
              </button>
            </div>
            <div class="mipp-filter-list">
              ${ALL_ISAS.map((isa) => `
                <label class="mipp-checkbox-item">
                  <input type="checkbox" data-isa="${isa}" ${state.selectedIsas.includes(isa) ? "checked" : ""}>
                  <span>${ISA_DISPLAY_NAMES[isa]}</span>
                </label>
              `).join("")}
            </div>
          </div>

          <!-- Guaranteed Level Filter -->
          <div class="mipp-filter-section">
            <div class="mipp-filter-header">
              <h3 class="mipp-filter-title">Guaranteed Level</h3>
              <button id="mipp-toggle-intersect" class="mipp-filter-quick-action" title="Toggle Union vs Intersection">
                ${state.intersectionMode ? "Intersection" : "Union (Any)"}
              </button>
            </div>
            <div class="mipp-filter-list">
              ${ALL_LEVELS.map((lvl) => `
                <label class="mipp-checkbox-item">
                  <input type="checkbox" data-level="${lvl}" ${state.selectedLevels.includes(lvl) ? "checked" : ""}>
                  <span class="mipp-isa-badge lvl-${lvl}">L${lvl}</span>
                  <span style="font-size: 0.8rem;">${LEVEL_DESCRIPTIONS[lvl]}</span>
                </label>
              `).join("")}
            </div>
          </div>

          <!-- Categories Filter -->
          <div class="mipp-filter-section">
            <div class="mipp-filter-header">
              <h3 class="mipp-filter-title">Categories</h3>
              ${state.selectedCategories.length > 0
        ? `<button id="mipp-clear-cats" class="mipp-filter-quick-action">Clear</button>`
        : ""
      }
            </div>
            <div class="mipp-filter-list">
              ${Object.keys(catCounts).sort().map((cat) => `
                <label class="mipp-checkbox-item">
                  <input type="checkbox" data-cat="${cat}" ${state.selectedCategories.includes(cat) ? "checked" : ""}>
                  <span style="text-transform: capitalize;">${cat}</span>
                  <span class="mipp-badge-count">${catCounts[cat]}</span>
                </label>
              `).join("")}
            </div>
          </div>

          <!-- Datatypes Filter (Consistent Badges) -->
          <div class="mipp-filter-section">
            <div class="mipp-filter-header">
              <h3 class="mipp-filter-title">Datatypes</h3>
              ${state.selectedTypes.length > 0
        ? `<button id="mipp-clear-types" class="mipp-filter-quick-action">Clear</button>`
        : ""
      }
            </div>
            <!-- Quick Group Chips -->
            <div class="mipp-filter-chips" style="margin-bottom: 0.4rem;">
              <button class="mipp-filter-chip" data-type-group="floats">Floats</button>
              <button class="mipp-filter-chip" data-type-group="signed">Signed</button>
              <button class="mipp-filter-chip" data-type-group="unsigned">Unsigned</button>
            </div>
            <div class="mipp-filter-chips">
              ${ALL_DATATYPES.map((dt) => {
        const isActive = state.selectedTypes.includes(dt.id);
        return `
                  <span class="mipp-filter-chip mipp-dt-badge ${getDtBadgeClass(dt.id)} ${isActive ? "active" : ""}" data-type="${dt.id}">
                    ${dt.label}
                  </span>
                `;
      }).join("")}
            </div>
          </div>

          <!-- Masking Variant Filter -->
          <div class="mipp-filter-section">
            <div class="mipp-filter-header">
              <h3 class="mipp-filter-title">Masking Modes</h3>
              ${state.selectedMaskModes.length > 0 && !isCppObj
        ? `<button id="mipp-clear-masks" class="mipp-filter-quick-action">Clear</button>`
        : ""
      }
            </div>
            <div class="mipp-filter-list">
              <label class="mipp-checkbox-item">
                <input type="checkbox" data-mask="unmasked" ${state.selectedMaskModes.includes("unmasked") ? "checked" : ""}>
                <span class="mipp-mask-badge mask-unmasked">unmasked</span>
              </label>
              <label class="mipp-checkbox-item ${isCppObj ? "disabled" : ""}" title="${isCppObj ? "Masking variants not supported in C++ Object dialect" : ""}">
                <input type="checkbox" data-mask="mask" ${!isCppObj && state.selectedMaskModes.includes("mask") ? "checked" : ""} ${isCppObj ? "disabled" : ""}>
                <span class="mipp-mask-badge mask-mask">mask</span>
              </label>
              <label class="mipp-checkbox-item ${isCppObj ? "disabled" : ""}" title="${isCppObj ? "Masking variants not supported in C++ Object dialect" : ""}">
                <input type="checkbox" data-mask="maskz" ${!isCppObj && state.selectedMaskModes.includes("maskz") ? "checked" : ""} ${isCppObj ? "disabled" : ""}>
                <span class="mipp-mask-badge mask-maskz">maskz</span>
              </label>
              <label class="mipp-checkbox-item ${isCppObj ? "disabled" : ""}" title="${isCppObj ? "Masking variants not supported in C++ Object dialect" : ""}">
                <input type="checkbox" data-mask="masks" ${!isCppObj && state.selectedMaskModes.includes("masks") ? "checked" : ""} ${isCppObj ? "disabled" : ""}>
                <span class="mipp-mask-badge mask-masks">masks</span>
              </label>
            </div>
          </div>
        </aside>

        <!-- Cards List -->
        <main class="mipp-cards-container">
          <div class="mipp-results-bar">
            <span>Showing <span class="mipp-results-count">${filtered.length}</span> of ${apiData.length} primitives</span>
            ${state.compareSet.size > 0
        ? `<span style="color: var(--mipp-accent); font-weight: 600;">${state.compareSet.size} selected for comparison</span>`
        : ""
      }
          </div>

          ${filtered.length === 0
        ? `
                <div style="text-align: center; padding: 3rem 1rem; background: var(--mipp-card-bg, #ffffff); border-radius: var(--mipp-border-radius-lg); border: 1px dashed var(--mipp-card-border, #cbd5e1);">
                  <div style="font-size: 2.5rem; margin-bottom: 0.5rem;">🔍</div>
                  <h3 style="margin: 0 0 0.5rem 0;">No matching MIPP primitives found</h3>
                  <p style="color: var(--md-default-fg-color--lighter, #94a3b8); margin: 0 0 1rem 0; font-size: 0.88rem;">
                    Try adjusting your search terms or clearing some of the filters in the sidebar.
                  </p>
                  <button id="mipp-reset-empty-btn" class="mipp-action-btn">Reset All Filters</button>
                </div>
              `
        : filtered.map(({ entry, matchedIntrinsic, matchedC99 }) => renderCard(entry, matchedIntrinsic, matchedC99)).join("")
      }
        </main>
      </div>

      <!-- Side-by-side Compare Floating Bar -->
      <div class="mipp-compare-bar ${state.compareSet.size >= 1 ? "visible" : ""}">
        <span style="font-weight: 600; font-size: 0.88rem;">
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

      <!-- Compare Modal -->
      <div id="mipp-compare-modal-backdrop" class="mipp-modal-backdrop ${state.compareModalOpen ? "visible" : ""}">
        <div class="mipp-modal-content mipp-compare-modal-content">
          <div class="mipp-modal-header">
            <h2 class="mipp-modal-title" style="margin: 0; font-size: 1.15rem; display: flex; align-items: center; gap: 0.5rem;">
              <span>⚖️ Side-by-Side Primitive Comparison</span>
            </h2>
            <button id="mipp-close-compare-btn" class="mipp-icon-btn mipp-modal-close-btn" style="font-size: 1.2rem;">✕</button>
          </div>
          <div class="mipp-compare-grid">
            ${Array.from(state.compareSet).map((name) => {
        const e = apiData.find((x) => x.name === name);
        return e ? renderCompareColumn(e) : "";
      }).join("")}
          </div>
        </div>
      </div>

      <!-- Emulation Algorithm Modal -->
      ${renderEmulationAlgoModal()}
    `;

    attachEventListeners();
    syncHeaderOffset();
    observeHeader();

    const nextSidebar = document.querySelector(".mipp-sidebar");
    if (nextSidebar) {
      nextSidebar.scrollTop = prevSidebarScrollTop;
    }
    window.scrollTo(0, prevWindowScrollY);
  }

  // ------------------------------------------------------------------------
  // Card Component Renderer
  // ------------------------------------------------------------------------
  function renderCard(entry, matchedIntrinsic, matchedC99) {
    const isExpanded = state.expandedCards.has(entry.name);
    const activeProto = getActivePrototype(entry);
    const isCheckedCompare = state.compareSet.has(entry.name);

    // Only show ISAs currently enabled in the sidebar filter
    const activeIsas = ALL_ISAS.filter((isa) => state.selectedIsas.includes(isa));

    return `
      <article class="mipp-card ${isExpanded ? "expanded" : ""}" id="card-${entry.name}">
        <div class="mipp-card-header" data-card-name="${entry.name}">
          <div class="mipp-card-top-row">
            <div class="mipp-card-title-group">
              <label class="mipp-checkbox-item" style="margin-right: 0.2rem;" onclick="event.stopPropagation();">
                <input type="checkbox" data-compare-name="${entry.name}" ${isCheckedCompare ? "checked" : ""} title="Add to comparison">
              </label>
              <span class="mipp-card-name">${escapeHtml(entry.name)}</span>
              <span class="mipp-cat-badge">${escapeHtml(entry.category)}</span>
              ${matchedIntrinsic
        ? `<span class="mipp-matched-chip" title="Matched vendor hardware intrinsic">Intrinsic: ${escapeHtml(matchedIntrinsic)}</span>`
        : matchedC99 && matchedC99 !== entry.name && matchedC99 !== `mipp_${entry.name}`
        ? `<span class="mipp-matched-chip" title="Matched C99 function">C99: ${escapeHtml(matchedC99)}</span>`
        : ""
      }
            </div>

            <!-- Dynamic ISA Badges Strip (filtered by selected ISAs and dynamic levels) -->
            <div class="mipp-isa-strip">
              ${activeIsas.map((isa) => {
        const lvl = getEffectiveIsaLevel(entry, isa);
        return `
                  <span class="mipp-isa-badge lvl-${lvl}" title="${ISA_DISPLAY_NAMES[isa]}: L${lvl} (${LEVEL_DESCRIPTIONS[lvl]})">
                    ${ISA_DISPLAY_NAMES[isa]}: L${lvl}
                  </span>
                `;
      }).join("")}
            </div>
          </div>

          <!-- Description -->
          <p class="mipp-card-desc">${escapeHtml(entry.description)}</p>

          <!-- Prototype Preview Container (Prototype code box + separate Details button) -->
          <div class="mipp-card-preview-container">
            <div class="mipp-card-proto-box">
              <div class="mipp-proto-code">${highlightCpp(activeProto)}</div>
              <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(activeProto)}" title="Copy prototype" onclick="event.stopPropagation();">
                ${ICON_COPY}
              </button>
            </div>
            <button class="mipp-toggle-details-btn ${isExpanded ? "is-expanded" : ""}" data-toggle-card="${entry.name}" title="Toggle expanded details">
              <span class="mipp-toggle-text">${isExpanded ? "Close" : "Details"}</span>
              ${ICON_CHEVRON}
            </button>
          </div>
        </div>

        <div class="mipp-card-expandable ${isExpanded ? "open" : ""}">
          <div class="mipp-card-expandable-inner">
            ${isExpanded ? renderCardExpandedDetails(entry) : ""}
          </div>
        </div>
      </article>
    `;
  }

  // ------------------------------------------------------------------------
  // Card Expanded Details View with Tabs
  // ------------------------------------------------------------------------
  function renderCardExpandedDetails(entry) {
    const activeTab = state.cardTabs[entry.name] || "hw";
    const selectedScalarDt = getActiveCardScalarDt(entry.name, entry);

    let tabContentHtml = "";
    if (activeTab === "hw") {
      tabContentHtml = renderHardwareTab(entry);
    } else if (activeTab === "proto") {
      tabContentHtml = renderPrototypesTab(entry);
    } else if (activeTab === "scalar") {
      tabContentHtml = renderScalarRefTab(entry, selectedScalarDt);
    } else if (activeTab === "specs") {
      tabContentHtml = renderTestSpecsTab(entry);
    } else if (activeTab === "example") {
      tabContentHtml = renderExamplesTab(entry);
    }

    return `
      <div class="mipp-card-body">
        <!-- Internal Tab Navigation -->
        <nav class="mipp-card-tabs" role="tablist">
          <button class="mipp-card-tab-btn ${activeTab === "hw" ? "active" : ""}" data-card-tab="hw" data-card="${entry.name}">
            ⚙️ Hardware Matrix
          </button>
          <button class="mipp-card-tab-btn ${activeTab === "proto" ? "active" : ""}" data-card-tab="proto" data-card="${entry.name}">
            📝 Prototypes
          </button>
          <button class="mipp-card-tab-btn ${activeTab === "scalar" ? "active" : ""}" data-card-tab="scalar" data-card="${entry.name}">
            📐 Scalar C Reference
          </button>
          <button class="mipp-card-tab-btn ${activeTab === "specs" ? "active" : ""}" data-card-tab="specs" data-card="${entry.name}">
            🧪 Verification Specs
          </button>
          <button class="mipp-card-tab-btn ${activeTab === "example" ? "active" : ""}" data-card-tab="example" data-card="${entry.name}">
            ⚡ Reproducible Example
          </button>
        </nav>

        <!-- Active Tab Pane -->
        <div class="mipp-tab-pane">
          ${tabContentHtml}
        </div>
      </div>
    `;
  }

  // Tab 1: Hardware Architecture Acceleration Matrix
  function renderHardwareTab(entry) {
    // Only display ISAs currently selected in sidebar
    const activeIsas = ALL_ISAS.filter((isa) => state.selectedIsas.includes(isa));
    const activeDts = getActiveSelectedTypes(entry);

    if (activeIsas.length === 0) {
      return `
        <div style="padding: 1.5rem; text-align: center; color: var(--md-default-fg-color--lighter);">
          <p style="margin: 0;">No target ISAs selected in the sidebar filter. Enable at least one ISA to view hardware mappings.</p>
        </div>
      `;
    }

    return `
      <div>
        ${activeDts.length > 0
        ? `<div style="font-size: 0.78rem; margin-bottom: 0.6rem; color: var(--md-default-fg-color--light);">
                 Filtered to selected datatypes: ${activeDts.map((dt) => `<span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${dt}</span>`).join(" ")}
               </div>`
        : ""
      }
        <div class="mipp-hw-table-wrapper">
          <table class="mipp-hw-table">
            <thead>
              <tr>
                <th style="width: 120px;">Architecture</th>
                <th style="width: 80px;">Tier</th>
                <th>Hardware Mapping & Emulation Logic</th>
              </tr>
            </thead>
            <tbody>
              ${activeIsas.map((isa) => {
        const info = entry.isa_support[isa];
        const lvl = getEffectiveIsaLevel(entry, isa);

        let instrs = info ? Object.entries(info.native_instructions || {}) : [];
        if (activeDts.length > 0) {
          instrs = instrs.filter(([dt]) => activeDts.includes(dt));
        }

        const sampleCode = info && info.code_snippets ? (
          activeDts.length > 0 && activeDts[0] in (info.code_snippets || {})
            ? info.code_snippets[activeDts[0]]
            : Object.values(info.code_snippets)[0]
        ) : null;

        const hasEmulationAlgos = info && info.emulation_algorithms && Object.keys(info.emulation_algorithms).length > 0;

        let mappingHtml = '<span style="color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">Scalar Fallback Loop (L3)</span>';

        if (lvl === 0 && instrs.length > 0) {
          mappingHtml = instrs.map(([dt, iname]) => `
                    <div style="display: flex; align-items: center; gap: 0.5rem; margin: 0.25rem 0;">
                      <span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${dt}</span>
                      <code class="mipp-hw-intrinsic-code">${escapeHtml(iname)}</code>
                    </div>
                  `).join("");
        } else if (lvl === 1 || lvl === 2) {
          const currentLmul = Number(state.lmul);
          const hwLmuls = info ? (info.hw_lmul || (isa === "rvv" ? [1, 2, 4, 8, -2] : [1])) : [1];
          const isLmulEmulated = currentLmul !== 1 && !hwLmuls.includes(currentLmul) && (info ? info.overall_level < 2 : false);
          const label = isLmulEmulated
            ? `LMUL=${state.lmul} software-emulated vector sequence`
            : (lvl === 1 ? "Target-specific multi-instruction emulation" : "Generic portable vector AST algorithm");

          if (hasEmulationAlgos) {
            const defaultAlgoDt = activeDts.find((dt) => info.emulation_algorithms && info.emulation_algorithms[dt]) || "";
            mappingHtml = `
                      <button class="mipp-algo-modal-btn lvl-${lvl}" data-algo-func="${entry.name}" data-algo-isa="${isa}" data-algo-level="${lvl}" data-algo-dt="${defaultAlgoDt}">
                        <span>${label}</span>
                        <span class="mipp-modal-open-icon">🔍 View Algorithm</span>
                      </button>
                    `;
          } else {
            mappingHtml = `<span style="color: ${lvl === 1 ? '#2563eb' : '#f59e0b'}; font-weight: 500;">${label}</span>`;
          }
        }

        return `
                  <tr>
                    <td style="font-weight: 700; font-family: var(--md-code-font, monospace);">${ISA_DISPLAY_NAMES[isa]}</td>
                    <td>
                      <span class="mipp-isa-badge lvl-${lvl}">L${lvl}</span>
                    </td>
                    <td>
                      ${mappingHtml}
                      ${sampleCode && lvl === 0
            ? `<div style="margin-top: 0.35rem; font-family: var(--md-code-font, monospace); font-size: 0.72rem; opacity: 0.75; overflow-x: auto;">↳ <code>${escapeHtml(sampleCode)}</code></div>`
            : ""
          }
                    </td>
                  </tr>
                `;
      }).join("")}
            </tbody>
          </table>
        </div>
      </div>
    `;
  }

  // Tab 2: Prototypes
  function renderPrototypesTab(entry) {
    const lmulKey = state.lmul;
    const protoData = entry.prototypes;
    const activeDts = getActiveSelectedTypes(entry);
    const activeMasks = getActiveMaskVariantsForEntry(entry);

    if (activeMasks.length === 0) {
      const availableList = Object.keys(entry.mask_support || {}).filter(k => entry.mask_support[k]).join(", ") || "unmasked";
      return `
        <div style="padding: 1rem; color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">
          ⚠️ No matching mask variant for this operation. Selected: <strong>${escapeHtml(state.selectedMaskModes.join(", "))}</strong> (Available for ${entry.name}: ${escapeHtml(availableList)})
        </div>
      `;
    }

    return `
      <div>
        <div class="mipp-card-sec-title">
          <span>${state.flavor === "c99" ? "C99 Declarations" : state.flavor === "cpp" ? "C++ Function Templates" : "C++ Object Methods"} (LMUL=${state.lmul})</span>
        </div>
        ${activeMasks.map((maskMode) => {
      let codeText = "";
      if (state.flavor === "c99") {
        const samplesForLmul = protoData.c99_samples ? protoData.c99_samples[lmulKey] : null;
        let lines = [];
        if (samplesForLmul) {
          if (Array.isArray(samplesForLmul)) {
            lines = samplesForLmul;
          } else if (typeof samplesForLmul === "object") {
            lines = samplesForLmul[maskMode] || samplesForLmul["unmasked"] || [];
          }
        }
        if (lines.length > 0) {
          let cleanLines = lines.map(cleanProto);
          if (activeDts.length > 0) {
            const filtered = cleanLines.filter((sig) =>
              activeDts.some((dt) => sig.includes(`_${dt}_`) || sig.includes(`_${dt}(`) || sig.includes(`_${dt};`) || sig.includes(`_${dt}`))
            );
            if (filtered.length > 0) cleanLines = filtered;
          }
          codeText = cleanLines.join("\n");
        } else {
          codeText = cleanProto(protoData.c99 || `mipp_${entry.name}(...)`);
        }
      } else if (state.flavor === "cpp") {
        const cppSample = protoData.cpp_samples ? protoData.cpp_samples[lmulKey] : null;
        let proto = "";
        if (typeof cppSample === "object" && cppSample !== null) {
          proto = cleanProto(cppSample[maskMode] || cppSample["unmasked"] || "");
        } else if (typeof cppSample === "string") {
          proto = cleanProto(cppSample);
        }
        if (!proto) {
          proto = cleanProto(protoData.cpp || `mipp::${entry.name}(...)`);
        }

        if (activeDts.length > 0) {
          const specializations = activeDts.map((dt) => {
            let spec = proto
              .replace(/,\s*typename\s+T\b/g, "")
              .replace(/typename\s+T,\s*/g, "")
              .replace(/<typename\s+T>/g, "")
              .replace(/<T>/g, `<${dt}>`)
              .replace(/<T,/g, `<${dt},`)
              .replace(/\bT\b/g, dt)
              .replace(/template\s*<\s*>\s*/g, "")
              .trim();
            return `// Specialized for <${dt}>:\n${spec}`;
          }).join("\n\n");
          codeText = `// C++ Functional Template:\n${proto}\n\n${specializations}`;
        } else {
          codeText = proto;
        }
      } else {
        // C++ Object
        let proto = "";
        if (protoData.cpp_obj_samples && protoData.cpp_obj_samples[lmulKey]) {
          proto = cleanProto(protoData.cpp_obj_samples[lmulKey]);
        } else {
          proto = cleanProto(protoData.cpp_obj || `r0.${entry.name}(...)`);
        }

        if (activeDts.length > 0) {
          const specializations = activeDts.map((dt) => {
            const spec = proto
              .replace(/<typename\s+T[^>]*>/g, "")
              .replace(/<T>/g, `<${dt}>`)
              .replace(/<T,/g, `<${dt},`)
              .replace(/\bT\b/g, dt)
              .trim();
            return `// Method on Rvd<${dt}>:\n${spec}`;
          }).join("\n\n");
          codeText = `// C++ Object Template:\n${proto}\n\n${specializations}`;
        } else {
          codeText = proto;
        }
      }

      return `
            <div class="mipp-proto-group">
              <div class="mipp-code-box">
                <div class="mipp-code-box-header">
                  <div class="mipp-code-box-header-left">
                    <span class="mipp-mask-badge mask-${maskMode}">${maskMode}</span>
                  </div>
                  <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(codeText)}" title="Copy prototype">
                    ${ICON_COPY}
                  </button>
                </div>
                <pre><code>${highlightCpp(codeText)}</code></pre>
              </div>
            </div>
          `;
    }).join("")}
      </div>
    `;
  }

  // Tab 3: Scalar C Reference Algorithm with Datatype Selector (Synced with Sidebar Masking Modes)
  function renderScalarRefTab(entry, selectedDt) {
    const lmulKey = state.lmul;
    const lmulAlgos = entry.reference_algos && entry.reference_algos[lmulKey] ? entry.reference_algos[lmulKey] : (entry.reference_algos || {});
    const dtAlgos = lmulAlgos[selectedDt] || {};
    const activeDts = getActiveSelectedTypes(entry);
    const dtsToDisplay = activeDts.length > 0 ? activeDts : entry.datatypes;

    const checkedMasks = state.flavor === "cpp_obj"
      ? ["unmasked"]
      : ["unmasked", "mask", "maskz", "masks"].filter((m) => state.selectedMaskModes.includes(m));

    if (checkedMasks.length === 0) {
      return `
        <div>
          ${entry.math_semantics
          ? `
                <div class="mipp-math-semantics" style="font-size: 0.88rem; padding: 0.5rem 0.8rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 6px; margin-bottom: 0.6rem;">
                  <strong>Mathematical Semantics:</strong>
                  <span class="mipp-math-formula">${formatMathHtml(entry.math_semantics)}</span>
                </div>
              `
          : ""
        }

          <div class="mipp-scalar-header">
            <div style="display: flex; align-items: center; gap: 0.75rem; flex-wrap: wrap;">
              <div style="display: flex; align-items: center; gap: 0.45rem;">
                <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
                  Datatype:
                </span>
                <select class="mipp-scalar-dt-select" data-card="${entry.name}">
                  ${dtsToDisplay.map((dt) => `
                    <option value="${dt}" ${dt === selectedDt ? "selected" : ""}>${dt}</option>
                  `).join("")}
                </select>
              </div>
            </div>
            <span style="font-size: 0.75rem; color: var(--md-default-fg-color--lighter);">
              LMUL=${state.lmul}
            </span>
          </div>

          <div style="padding: 1rem; color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">
            ⚠️ No masking mode selected in the left sidebar. Check at least one masking mode in the sidebar to view scalar reference implementations.
          </div>
        </div>
      `;
    }

    const supportedCheckedMasks = checkedMasks.filter(
      (m) => m === "unmasked" || (entry.mask_support && entry.mask_support[m])
    );

    return `
      <div>
        ${entry.math_semantics
        ? `
              <div class="mipp-math-semantics" style="font-size: 0.88rem; padding: 0.5rem 0.8rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 6px; margin-bottom: 0.6rem;">
                <strong>Mathematical Semantics:</strong>
                <span class="mipp-math-formula">${formatMathHtml(entry.math_semantics)}</span>
              </div>
            `
        : ""
      }

        <div class="mipp-scalar-header">
          <div style="display: flex; align-items: center; gap: 0.75rem; flex-wrap: wrap;">
            <div style="display: flex; align-items: center; gap: 0.45rem;">
              <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
                Datatype:
              </span>
              <select class="mipp-scalar-dt-select" data-card="${entry.name}">
                ${dtsToDisplay.map((dt) => `
                  <option value="${dt}" ${dt === selectedDt ? "selected" : ""}>${dt}</option>
                `).join("")}
              </select>
            </div>

            <div style="display: flex; align-items: center; gap: 0.35rem; margin-left: 0.4rem; flex-wrap: wrap;">
              <span style="font-size: 0.78rem; font-weight: 600; text-transform: uppercase; color: var(--md-default-fg-color--lighter, #94a3b8);">
                Variants:
              </span>
              ${checkedMasks.map((m) => {
        const isAvail = m === "unmasked" || (entry.mask_support && entry.mask_support[m]);
        if (isAvail) {
          return `<span class="mipp-mask-badge mask-${m}" title="${m} available">${m}</span>`;
        } else {
          return `<span class="mipp-mask-badge mask-${m} disabled" style="opacity: 0.45; filter: grayscale(1); cursor: not-allowed;" title="${m} not available for ${entry.name}">${m} (N/A)</span>`;
        }
      }).join("")}
            </div>
          </div>
          <span style="font-size: 0.75rem; color: var(--md-default-fg-color--lighter);">
            LMUL=${state.lmul}
          </span>
        </div>

        ${supportedCheckedMasks.length > 0
        ? supportedCheckedMasks.map((m) => {
          let code = "";
          if (typeof dtAlgos === "object" && dtAlgos !== null) {
            code = dtAlgos[m] || dtAlgos["unmasked"] || "// No scalar reference implementation for this variant";
          } else if (typeof dtAlgos === "string") {
            code = dtAlgos;
          } else {
            code = entry.reference_algo || "// No scalar reference code available";
          }
          code = code.replace(/^[ \t]*\/\/[ \t]*Level[ \t]+\d[^\n]*\r?\n?/gm, "").trim();

          return `
                  <div class="mipp-scalar-group">
                    <div class="mipp-code-box">
                      <div class="mipp-code-box-header">
                        <div class="mipp-code-box-header-left">
                          <span class="mipp-mask-badge mask-${m}" title="${m}">${m}</span>
                          <span style="font-size: 0.72rem; color: var(--md-default-fg-color--lighter);">Scalar C Reference</span>
                        </div>
                        <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(code)}" title="Copy scalar reference">
                          ${ICON_COPY}
                        </button>
                      </div>
                      <pre><code>${highlightCpp(code, entry.scalar_macros)}</code></pre>
                    </div>
                  </div>
                `;
        }).join("")
        : `
              <div style="padding: 1rem; color: var(--md-default-fg-color--lighter, #94a3b8); font-style: italic;">
                ⚠️ None of the selected masking modes (${checkedMasks.join(", ")}) are available for ${entry.name}.
              </div>
            `
      }
      </div>
    `;
  }

  // Tab 4: Test Verification Specifications
  function renderTestSpecsTab(entry) {
    const activeDts = getActiveSelectedTypes(entry);
    const variants = entry.test_specs && entry.test_specs.variants ? entry.test_specs.variants : null;
    const availableVariants = variants ? Object.keys(variants) : ["unmasked"];
    const selectedVariant = getActiveCardTestVariant(entry.name, entry);

    const variantSpec = variants ? (variants[selectedVariant] || variants["unmasked"] || Object.values(variants)[0]) : (entry.test_specs || {});

    let tableRows = variantSpec.table || [];
    if (activeDts.length > 0) {
      tableRows = tableRows.filter((row) => activeDts.includes(row.datatype));
    }

    return `
      <div>
        <!-- Available Test Variants Badges (Clickable per-card switcher) -->
        <div style="display: flex; align-items: center; gap: 0.5rem; margin-bottom: 0.75rem; flex-wrap: wrap;">
          <span style="font-size: 0.78rem; font-weight: 600; color: var(--md-default-fg-color--lighter);">Verification Variant:</span>
          ${availableVariants.map((v) => `
            <button class="mipp-mask-badge mask-${v} mipp-test-variant-btn ${v === selectedVariant ? "active" : ""}" data-card="${entry.name}" data-mask="${v}" title="Click to view specs for ${v}">
              ${v} ${v === selectedVariant ? "✓" : ""}
            </button>
          `).join("")}
        </div>

        <!-- General Spec Summary Cards -->
        <div style="display: flex; flex-wrap: wrap; gap: 0.5rem; margin-bottom: 0.75rem;">
          <div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;">
            <strong>Comparison Mode:</strong> <code>${escapeHtml(variantSpec.comparison || entry.test_specs?.comparison || "exact")}</code>
          </div>
          ${variantSpec.overflow_check
        ? `<div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;"><strong>Overflow Check:</strong> <code>${escapeHtml(variantSpec.overflow_check)}</code></div>`
        : ""
      }
          ${variantSpec.mask_pattern
        ? `<div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;"><strong>Mask Pattern:</strong> <code>${escapeHtml(variantSpec.mask_pattern)}</code></div>`
        : ""
      }
          <div style="font-size: 0.75rem; padding: 0.35rem 0.65rem; background: var(--md-default-bg-color--lighter, #f1f5f9); border-radius: 4px;">
            <strong>Test LMULs:</strong> <code>1, 2, 4, 8, 1/2</code>
          </div>
        </div>

        ${tableRows.length > 0
        ? `
              <div class="mipp-specs-table-wrapper">
                <table class="mipp-specs-table">
                  <thead>
                    <tr>
                      <th style="width: 120px;">Datatype</th>
                      <th>Input Domain Range</th>
                      <th>Tolerance</th>
                      <th style="width: 130px;">Verification Mode</th>
                    </tr>
                  </thead>
                  <tbody>
                    ${tableRows.map((row) => `
                      <tr>
                        <td><span class="mipp-dt-badge ${getDtBadgeClass(row.datatype)}">${escapeHtml(row.datatype)}</span></td>
                        <td><code>${escapeHtml(row.domain)}</code></td>
                        <td>${escapeHtml(row.tolerance)}</td>
                        <td><span class="mipp-cat-badge">${escapeHtml(row.comparison || variantSpec.comparison || "exact")}</span></td>
                      </tr>
                    `).join("")}
                  </tbody>
                </table>
              </div>
            `
        : `<p style="font-size: 0.82rem; color: var(--md-default-fg-color--lighter);">Bit-exact verification across all representable domains.</p>`
      }
      </div>
    `;
  }

  // Tab 5: Reproducible Example & Compiler Explorer
  function renderExamplesTab(entry) {
    const godboltNativeCode = (entry.snippets && entry.snippets.godbolt_native) || entry.snippets.cpp;
    const godboltUrl = buildGodboltUrl(godboltNativeCode, true);
    const cppCode = (entry.snippets && entry.snippets.cpp) || "";

    return `
      <div>
        <!-- Standalone Godbolt-Ready Native Intrinsic Example -->
        <div class="mipp-card-sec-title">
          <span>Standalone Hardware Intrinsic (Compiles out-of-the-box with &lt;immintrin.h&gt;)</span>
          <div style="display: flex; gap: 0.4rem;">
            <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(godboltNativeCode)}" title="Copy native C snippet">
              ${ICON_COPY}
            </button>
            <a href="${godboltUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-btn">
              ⚡ Open in Compiler Explorer (Godbolt) ↗
            </a>
          </div>
        </div>
        <div class="mipp-code-box" style="margin-bottom: 1rem;">
          <pre><code>${highlightCpp(godboltNativeCode)}</code></pre>
        </div>

        <!-- MIPP C++ Header Example -->
        <div class="mipp-card-sec-title">
          <span>Portable MIPP C++ Source</span>
          <div style="display: flex; gap: 0.4rem;">
            <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(cppCode)}" title="Copy MIPP C++ snippet">
              ${ICON_COPY}
            </button>
            <a href="${entry.doc_url}" class="mipp-action-btn" style="font-size: 0.75rem; padding: 0.25rem 0.6rem;">
              📖 Full Documentation Page ↗
            </a>
          </div>
        </div>
        <div class="mipp-code-box">
          <pre><code>${highlightCpp(cppCode)}</code></pre>
        </div>
      </div>
    `;
  }

  function cleanAlgoCode(code) {
    if (!code) return "";
    code = code.replace(/\t/g, "    ");
    const lines = code.split("\n");
    const nonEmpty = lines.slice(1).filter((l) => l.trim().length > 0);
    if (lines.length > 1 && lines[0].length - lines[0].trimStart().length === 0 && nonEmpty.length > 0) {
      let commonIndent = nonEmpty[0].length - nonEmpty[0].trimStart().length;
      for (const l of nonEmpty) {
        commonIndent = Math.min(commonIndent, l.length - l.trimStart().length);
      }
      if (commonIndent > 0) {
        const cleaned = [lines[0], ...lines.slice(1).map((l) => (l.trim().length ? l.slice(commonIndent) : ""))];
        return cleaned.join("\n").trim();
      }
    }
    return code.trim();
  }

  function renderEmulationAlgoModal() {
    if (!state.algoModal.open || !state.algoModal.func) {
      return `<div id="mipp-algo-modal-backdrop" class="mipp-modal-backdrop"></div>`;
    }

    const entry = apiData.find((x) => x.name === state.algoModal.func);
    if (!entry) return "";

    const isaInfo = entry.isa_support[state.algoModal.isa] || {};
    const algos = isaInfo.emulation_algorithms || {};
    const availableDts = Object.keys(algos);
    const activeDt = state.algoModal.dt || (availableDts.length > 0 ? availableDts[0] : null);
    const algoCode = activeDt ? cleanAlgoCode(algos[activeDt]) : "// No algorithm available";

    return `
      <div id="mipp-algo-modal-backdrop" class="mipp-modal-backdrop visible">
        <div class="mipp-modal-content">
          <div class="mipp-modal-header">
            <div>
              <h2 class="mipp-modal-title" style="margin: 0; font-size: 1.1rem; display: flex; align-items: center; gap: 0.5rem;">
                <span>🔍 Emulation Logic: <code style="color: var(--mipp-accent);">mipp::${entry.name}</code> on ${ISA_DISPLAY_NAMES[state.algoModal.isa]} (L${state.algoModal.level})</span>
              </h2>
              <div class="mipp-modal-subtitle" style="font-size: 0.8rem; color: var(--md-default-fg-color--lighter); margin-top: 0.2rem;">
                ${state.algoModal.level === 1 ? "Target-specific multi-instruction optimized sequence" : "Generic portable vector AST decomposed into MIPP primitives"}
              </div>
            </div>
            <button id="mipp-close-algo-modal-btn" class="mipp-icon-btn mipp-modal-close-btn" style="font-size: 1.2rem;">✕</button>
          </div>

          <div class="mipp-modal-body">
            <!-- Datatype Selector if multiple types exist -->
            ${availableDts.length > 1
        ? `
                  <div style="display: flex; align-items: center; gap: 0.5rem; flex-wrap: wrap;">
                    <span style="font-size: 0.8rem; font-weight: 600; color: var(--md-default-fg-color--lighter);">Available Datatypes:</span>
                    ${availableDts.map((dt) => `
                      <button class="mipp-filter-chip mipp-dt-badge ${getDtBadgeClass(dt)} ${dt === activeDt ? "active" : ""}" data-algo-dt="${dt}">
                        ${dt}
                      </button>
                    `).join("")}
                  </div>
                `
        : ""
      }

            <div class="mipp-code-box">
              <div class="mipp-code-box-header">
                <div class="mipp-code-box-header-left">
                  <span>C++ Portable Vector Implementation (${activeDt || "generic"})</span>
                </div>
                <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(algoCode)}" title="Copy algorithm code">
                  ${ICON_COPY}
                </button>
              </div>
              <pre><code>${highlightCpp(algoCode)}</code></pre>
            </div>
          </div>
        </div>
      </div>
    `;
  }

  // ------------------------------------------------------------------------
  // Compare Column Renderer
  // ------------------------------------------------------------------------
  function renderCompareColumn(entry) {
    const activeProto = getActivePrototype(entry);
    return `
      <div class="mipp-compare-col">
        <div style="display: flex; align-items: center; justify-content: space-between;">
          <h3 class="mipp-compare-col-name" style="margin: 0; font-family: var(--md-code-font, monospace); font-size: 1.1rem;">${escapeHtml(entry.name)}</h3>
          <span class="mipp-cat-badge">${escapeHtml(entry.category)}</span>
        </div>

        <p class="mipp-compare-col-desc" style="font-size: 0.82rem; margin: 0; color: var(--md-default-fg-color--light);">${escapeHtml(entry.description)}</p>

        <div>
          <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Mathematical Semantics</div>
          <div style="font-size: 0.82rem; background: var(--md-default-bg-color--lighter); padding: 0.4rem; border-radius: 4px;">
            ${entry.math_semantics ? `<span class="mipp-math-formula">${formatMathHtml(entry.math_semantics)}</span>` : "N/A"}
          </div>
        </div>

        <div>
          <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Architecture Support</div>
          <div class="mipp-isa-strip">
            ${ALL_ISAS.filter((isa) => state.selectedIsas.includes(isa)).map((isa) => {
      const lvl = getEffectiveIsaLevel(entry, isa);
      return `<span class="mipp-isa-badge lvl-${lvl}">${ISA_DISPLAY_NAMES[isa]}: L${lvl}</span>`;
    }).join("")}
          </div>
        </div>

        <div>
          <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Active Prototype (${state.flavor.toUpperCase()})</div>
          <div class="mipp-code-box">
            <pre style="padding: 0.5rem; font-size: 0.72rem;"><code>${highlightCpp(activeProto)}</code></pre>
          </div>
        </div>

        <div>
          <div class="mipp-control-label" style="margin-bottom: 0.3rem;">Supported Datatypes</div>
          <div style="display: flex; flex-wrap: wrap; gap: 0.35rem; margin-top: 0.25rem;">
            ${entry.datatypes.map((dt) => `<span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${dt}</span>`).join("")}
          </div>
        </div>
      </div>
    `;
  }

  // ------------------------------------------------------------------------
  // Helper Formatters
  // ------------------------------------------------------------------------
  function escapeHtml(str) {
    if (str === null || str === undefined) return "";
    return String(str)
      .replace(/&/g, "&amp;")
      .replace(/</g, "&lt;")
      .replace(/>/g, "&gt;")
      .replace(/"/g, "&quot;")
      .replace(/'/g, "&#039;");
  }

  function buildGodboltUrl(sourceCode, isC = true) {
    const lang = isC ? "c" : "c%2B%2B";
    const options = isC ? "-O3+-mavx2" : "-O3+-mavx2+-std=c%2B%2B20";
    return (
      "https://godbolt.org/#g:!((g:!((g:!((h:codeEditor,i:(filename:'1',fontScale:14,fontUseDefault:true,lang:'" +
      lang +
      "',source:'" +
      encodeURIComponent(sourceCode) +
      "'),l:'5',n:'0',o:'MIPP+Native+Sample',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0'),(g:!((h:compiler,i:(compiler:g142,filters:(b:'0',binary:'1',binaryObject:'1',commentOnly:'0',demangle:'0',directives:'0',execute:'1',intel:'0',libraryCode:'0',trim:'1'),flagsViewOpen:'1',fontScale:14,fontUseDefault:true,lang:'" +
      lang +
      "',options:'" +
      options +
      "'),l:'5',n:'0',o:'GCC+14.2+(-O3+-mavx2)',t:'0')),k:50,l:'4',m:100,n:'0',o:'',s:0,t:'0')),l:'2',n:'0',o:'',t:'0')),version:4"
    );
  }

  function updateCardInner(cardName) {
    const cardEl = document.getElementById(`card-${cardName}`);
    const entry = apiData.find((x) => x.name === cardName);
    if (cardEl && entry) {
      const inner = cardEl.querySelector(".mipp-card-expandable-inner");
      if (inner) {
        inner.innerHTML = renderCardExpandedDetails(entry);
        attachCardInternalListeners(cardEl, entry);
      }
    }
  }

  function attachCardInternalListeners(cardEl, entry) {
    cardEl.querySelectorAll(".mipp-card-tab-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const tab = btn.getAttribute("data-card-tab");
        state.cardTabs[entry.name] = tab;
        setFocusedCard(entry.name);
        updateCardInner(entry.name);
        syncUrlHash(true);
      });
    });

    cardEl.querySelectorAll(".mipp-scalar-dt-select").forEach((sel) => {
      sel.addEventListener("change", (e) => {
        e.stopPropagation();
        state.cardScalarTypes[entry.name] = sel.value;
        setFocusedCard(entry.name);
        updateCardInner(entry.name);
        syncUrlHash(true);
      });
    });

    cardEl.querySelectorAll(".mipp-algo-modal-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const func = btn.getAttribute("data-algo-func");
        const isa = btn.getAttribute("data-algo-isa");
        const lvl = Number(btn.getAttribute("data-algo-level"));
        const reqDt = btn.getAttribute("data-algo-dt");

        const targetEntry = apiData.find((x) => x.name === func) || entry;
        const isaInfo = targetEntry ? targetEntry.isa_support[isa] : null;
        const availableDts = isaInfo && isaInfo.emulation_algorithms ? Object.keys(isaInfo.emulation_algorithms) : [];

        state.algoModal = {
          open: true,
          func: func,
          isa: isa,
          level: lvl,
          dt: reqDt && availableDts.includes(reqDt) ? reqDt : (availableDts[0] || "float32")
        };
        renderApp();
      });
    });

    cardEl.querySelectorAll(".copy-proto-btn, .copy-code-btn, .mipp-code-copy-floating").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const text = btn.getAttribute("data-copy");
        copyToClipboard(text, "Copied to clipboard!");
        flashCopySuccess(btn);
      });
    });

    // Test Variant Switchers in Verification Specs Tab (Scoped strictly to this card's spec table)
    cardEl.querySelectorAll(".mipp-test-variant-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const mask = btn.getAttribute("data-mask");
        const cardName = btn.getAttribute("data-card");
        if (mask && cardName) {
          if (!state.cardTestVariants) state.cardTestVariants = {};
          state.cardTestVariants[cardName] = mask;
          setFocusedCard(cardName);
          updateCardInner(cardName);
          syncUrlHash(true);
        }
      });
    });
  }

  function toggleCard(cardName) {
    const cardEl = document.getElementById(`card-${cardName}`);
    const entry = apiData.find((x) => x.name === cardName);
    if (!cardEl || !entry) {
      if (state.expandedCards.has(cardName)) {
        state.expandedCards.delete(cardName);
        removeOpenedCard(cardName);
      } else {
        state.expandedCards.add(cardName);
        setFocusedCard(cardName);
      }
      syncUrlHash(true);
      renderApp();
      return;
    }

    const expandable = cardEl.querySelector(".mipp-card-expandable");
    const toggleBtn = cardEl.querySelector(".mipp-toggle-details-btn");
    const isNowExpanded = !state.expandedCards.has(cardName);

    if (isNowExpanded) {
      state.expandedCards.add(cardName);
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
          window.MathJax.typesetPromise([cardEl]).catch(() => { });
        }
      }
    } else {
      state.expandedCards.delete(cardName);
      removeOpenedCard(cardName);
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
  }

  // ------------------------------------------------------------------------
  // Event Listeners & Interactions
  // ------------------------------------------------------------------------
  function attachEventListeners() {
    const appEl = document.getElementById("mipp-explorer-app");
    if (!appEl) return;

    // 1. Search Input
    const searchInput = document.getElementById("mipp-search-input");
    if (searchInput) {
      searchInput.addEventListener("input", (e) => {
        state.query = e.target.value;
        syncUrlHash(false);
        renderApp();
        const updatedInput = document.getElementById("mipp-search-input");
        if (updatedInput) {
          updatedInput.focus();
          const len = updatedInput.value.length;
          updatedInput.setSelectionRange(len, len);
        }
      });
    }

    const clearBtn = document.getElementById("mipp-search-clear-btn");
    if (clearBtn) {
      clearBtn.addEventListener("click", () => {
        state.query = "";
        syncUrlHash(false);
        renderApp();
      });
    }

    // 2. Dialect Switcher
    const flavorGroup = document.getElementById("mipp-flavor-group");
    if (flavorGroup) {
      flavorGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
        btn.addEventListener("click", () => {
          const prevFlavor = state.flavor;
          state.flavor = btn.getAttribute("data-flavor");
          if (state.flavor === "cpp_obj") {
            state.selectedMaskModes = state.selectedMaskModes.filter((m) => m === "unmasked");
          } else if (prevFlavor === "cpp_obj" && state.selectedMaskModes.length <= 1) {
            state.selectedMaskModes = ["unmasked", "mask", "maskz", "masks"];
          }
          syncUrlHash(true);
          renderApp();
        });
      });
    }

    // 3. LMUL Switcher
    const lmulGroup = document.getElementById("mipp-lmul-group");
    if (lmulGroup) {
      lmulGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
        btn.addEventListener("click", () => {
          state.lmul = btn.getAttribute("data-lmul");
          syncUrlHash(true);
          renderApp();
        });
      });
    }

    // Font Size Switcher
    const fontSizeGroup = document.getElementById("mipp-font-size-group");
    if (fontSizeGroup) {
      fontSizeGroup.querySelectorAll(".mipp-segment-btn").forEach((btn) => {
        btn.addEventListener("click", () => {
          const size = btn.getAttribute("data-font-size");
          state.fontSize = size;
          localStorage.setItem("mipp_font_size", size);
          renderApp();
        });
      });
    }

    // 4. Share View
    const shareBtn = document.getElementById("mipp-share-btn");
    if (shareBtn) {
      shareBtn.addEventListener("click", () => {
        syncUrlHash(false);
        copyToClipboard(window.location.href, "Shareable URL copied to clipboard!");
      });
    }

    // 5. Reset Filters
    const resetBtn = document.getElementById("mipp-reset-btn");
    if (resetBtn) {
      resetBtn.addEventListener("click", resetAllFilters);
    }
    const resetEmptyBtn = document.getElementById("mipp-reset-empty-btn");
    if (resetEmptyBtn) {
      resetEmptyBtn.addEventListener("click", resetAllFilters);
    }

    // 6. ISA Checkboxes
    appEl.querySelectorAll("input[data-isa]").forEach((cb) => {
      cb.addEventListener("change", (e) => {
        const isa = e.target.getAttribute("data-isa");
        if (e.target.checked) {
          if (!state.selectedIsas.includes(isa)) state.selectedIsas.push(isa);
        } else {
          state.selectedIsas = state.selectedIsas.filter((x) => x !== isa);
        }
        syncUrlHash(true);
        renderApp();
      });
    });

    const selectAllIsas = document.getElementById("mipp-select-all-isas");
    if (selectAllIsas) {
      selectAllIsas.addEventListener("click", () => {
        if (state.selectedIsas.length === ALL_ISAS.length) {
          state.selectedIsas = [];
        } else {
          state.selectedIsas = [...ALL_ISAS];
        }
        syncUrlHash(true);
        renderApp();
      });
    }

    // 7. Level Checkboxes & Intersection Toggle
    appEl.querySelectorAll("input[data-level]").forEach((cb) => {
      cb.addEventListener("change", (e) => {
        const lvl = Number(e.target.getAttribute("data-level"));
        if (e.target.checked) {
          if (!state.selectedLevels.includes(lvl)) state.selectedLevels.push(lvl);
        } else {
          state.selectedLevels = state.selectedLevels.filter((x) => x !== lvl);
        }
        syncUrlHash(true);
        renderApp();
      });
    });

    const toggleIntersect = document.getElementById("mipp-toggle-intersect");
    if (toggleIntersect) {
      toggleIntersect.addEventListener("click", () => {
        state.intersectionMode = !state.intersectionMode;
        syncUrlHash(true);
        renderApp();
      });
    }

    // 8. Categories Filter
    appEl.querySelectorAll("input[data-cat]").forEach((cb) => {
      cb.addEventListener("change", (e) => {
        const cat = e.target.getAttribute("data-cat");
        if (e.target.checked) {
          if (!state.selectedCategories.includes(cat)) state.selectedCategories.push(cat);
        } else {
          state.selectedCategories = state.selectedCategories.filter((x) => x !== cat);
        }
        syncUrlHash(true);
        renderApp();
      });
    });

    const clearCats = document.getElementById("mipp-clear-cats");
    if (clearCats) {
      clearCats.addEventListener("click", () => {
        state.selectedCategories = [];
        syncUrlHash(true);
        renderApp();
      });
    }

    // 9. Datatype Chips & Groups
    appEl.querySelectorAll("[data-type]").forEach((chip) => {
      chip.addEventListener("click", () => {
        const dt = chip.getAttribute("data-type");
        if (state.selectedTypes.includes(dt)) {
          state.selectedTypes = state.selectedTypes.filter((x) => x !== dt);
        } else {
          state.selectedTypes.push(dt);
        }
        syncUrlHash(true);
        renderApp();
      });
    });

    appEl.querySelectorAll("[data-type-group]").forEach((btn) => {
      btn.addEventListener("click", () => {
        const grp = btn.getAttribute("data-type-group");
        const matching = ALL_DATATYPES.filter((d) => d.group === grp).map((d) => d.id);
        const allIncluded = matching.every((d) => state.selectedTypes.includes(d));
        if (allIncluded) {
          state.selectedTypes = state.selectedTypes.filter((d) => !matching.includes(d));
        } else {
          state.selectedTypes = Array.from(new Set([...state.selectedTypes, ...matching]));
        }
        syncUrlHash(true);
        renderApp();
      });
    });

    const clearTypes = document.getElementById("mipp-clear-types");
    if (clearTypes) {
      clearTypes.addEventListener("click", () => {
        state.selectedTypes = [];
        syncUrlHash(true);
        renderApp();
      });
    }

    // 10. Masking Checkboxes
    appEl.querySelectorAll("input[data-mask]").forEach((cb) => {
      cb.addEventListener("change", (e) => {
        const m = e.target.getAttribute("data-mask");
        if (e.target.checked) {
          if (!state.selectedMaskModes.includes(m)) state.selectedMaskModes.push(m);
        } else {
          state.selectedMaskModes = state.selectedMaskModes.filter((x) => x !== m);
        }
        syncUrlHash(true);
        renderApp();
      });
    });

    const clearMasks = document.getElementById("mipp-clear-masks");
    if (clearMasks) {
      clearMasks.addEventListener("click", () => {
        state.selectedMaskModes = [];
        syncUrlHash(true);
        renderApp();
      });
    }

    // 11. Accordion Card Header Click (Allows text selection in preview without toggling)
    appEl.querySelectorAll(".mipp-card-header").forEach((header) => {
      header.addEventListener("click", (e) => {
        if (
          e.target.closest("button") ||
          e.target.closest("input") ||
          e.target.closest("a") ||
          e.target.closest(".mipp-card-preview-container") ||
          e.target.closest(".mipp-card-preview-row")
        ) {
          return;
        }
        const sel = window.getSelection();
        if (sel && sel.toString().trim().length > 0) {
          return;
        }
        const cardName = header.getAttribute("data-card-name");
        toggleCard(cardName);
      });
    });

    // 12. Dedicated Details Toggle Button
    appEl.querySelectorAll(".mipp-toggle-details-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const cardName = btn.getAttribute("data-toggle-card");
        toggleCard(cardName);
      });
    });

    // 13. Internal Card Tab Switching & Scalar Dropdowns for Expanded Cards
    appEl.querySelectorAll(".mipp-card").forEach((cardEl) => {
      const cardName = cardEl.id.replace("card-", "");
      const entry = apiData.find((x) => x.name === cardName);
      if (entry && state.expandedCards.has(cardName)) {
        attachCardInternalListeners(cardEl, entry);
      }
    });

    // 15. Emulation Algorithm Modal Open
    appEl.querySelectorAll(".mipp-algo-modal-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const func = btn.getAttribute("data-algo-func");
        const isa = btn.getAttribute("data-algo-isa");
        const lvl = Number(btn.getAttribute("data-algo-level"));
        const reqDt = btn.getAttribute("data-algo-dt");

        const entry = apiData.find((x) => x.name === func);
        const isaInfo = entry ? entry.isa_support[isa] : null;
        const availableDts = isaInfo && isaInfo.emulation_algorithms ? Object.keys(isaInfo.emulation_algorithms) : [];

        state.algoModal = {
          open: true,
          func: func,
          isa: isa,
          level: lvl,
          dt: (reqDt && availableDts.includes(reqDt)) ? reqDt : (availableDts[0] || null),
        };
        renderApp();
      });
    });

    // Close Emulation Algorithm Modal
    const closeAlgoModalBtn = document.getElementById("mipp-close-algo-modal-btn");
    if (closeAlgoModalBtn) {
      closeAlgoModalBtn.addEventListener("click", () => {
        state.algoModal.open = false;
        renderApp();
      });
    }

    const algoModalBackdrop = document.getElementById("mipp-algo-modal-backdrop");
    if (algoModalBackdrop) {
      algoModalBackdrop.addEventListener("click", (e) => {
        if (e.target === algoModalBackdrop) {
          state.algoModal.open = false;
          renderApp();
        }
      });
    }

    // Switch Datatype in Emulation Algorithm Modal
    appEl.querySelectorAll("[data-algo-dt]").forEach((btn) => {
      btn.addEventListener("click", () => {
        state.algoModal.dt = btn.getAttribute("data-algo-dt");
        renderApp();
      });
    });

    // 16. Copy Buttons
    appEl.querySelectorAll(".copy-proto-btn").forEach((btn) => {
      btn.addEventListener("click", (e) => {
        e.stopPropagation();
        const textToCopy = btn.getAttribute("data-copy");
        copyToClipboard(textToCopy);
        flashCopySuccess(btn);
      });
    });

    // 17. Compare Checkboxes
    appEl.querySelectorAll("input[data-compare-name]").forEach((cb) => {
      cb.addEventListener("change", (e) => {
        e.stopPropagation();
        const name = e.target.getAttribute("data-compare-name");
        if (e.target.checked) {
          if (state.compareSet.size >= 3) {
            e.target.checked = false;
            showToast("Comparison limit is 3 primitives.");
            return;
          }
          state.compareSet.add(name);
        } else {
          state.compareSet.delete(name);
        }
        renderApp();
      });
    });

    // 18. Compare Modal Open/Close
    const openCompareBtn = document.getElementById("mipp-open-compare-btn");
    if (openCompareBtn) {
      openCompareBtn.addEventListener("click", () => {
        state.compareModalOpen = true;
        renderApp();
      });
    }

    const closeCompareBtn = document.getElementById("mipp-close-compare-btn");
    if (closeCompareBtn) {
      closeCompareBtn.addEventListener("click", () => {
        state.compareModalOpen = false;
        renderApp();
      });
    }

    const compareModalBackdrop = document.getElementById("mipp-compare-modal-backdrop");
    if (compareModalBackdrop) {
      compareModalBackdrop.addEventListener("click", (e) => {
        if (e.target === compareModalBackdrop) {
          state.compareModalOpen = false;
          renderApp();
        }
      });
    }

    const clearCompareBtn = document.getElementById("mipp-clear-compare-btn");
    if (clearCompareBtn) {
      clearCompareBtn.addEventListener("click", () => {
        state.compareSet.clear();
        state.compareModalOpen = false;
        renderApp();
      });
    }
  }

  function resetAllFilters() {
    state.query = "";
    state.searchField = "all";
    state.flavor = "cpp";
    state.lmul = "1";
    state.selectedIsas = [...ALL_ISAS];
    state.selectedLevels = [...ALL_LEVELS];
    state.intersectionMode = false;
    state.selectedCategories = [];
    state.selectedTypes = [];
    state.selectedMaskModes = ["unmasked", "mask", "maskz", "masks"];
    state.selectedExtensionTypes = [];
    state.expandedCards.clear();
    state.openedCardsOrder = [];
    state.focusedCard = null;
    state.compareSet.clear();
    state.cardTabs = {};
    state.cardScalarTypes = {};
    state.cardScalarVariants = {};
    state.cardTestVariants = {};
    syncUrlHash(true);
    renderApp();
  }

  // ------------------------------------------------------------------------
  // Entrypoint Lifecycle
  // ------------------------------------------------------------------------
  async function initExplorer() {
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
      parseUrlHash();
      renderApp();

      if (state.focusedCard) {
        scrollToFocusedCard(state.focusedCard, false);
      }

      const handleUrlNavigation = () => {
        const prevFocus = state.focusedCard;
        const prevTab = prevFocus ? state.cardTabs[prevFocus] : null;
        parseUrlHash();
        renderApp();
        if (state.focusedCard && (state.focusedCard !== prevFocus || state.cardTabs[state.focusedCard] !== prevTab)) {
          scrollToFocusedCard(state.focusedCard, true);
        }
      };

      window.addEventListener("hashchange", handleUrlNavigation);
      window.addEventListener("popstate", handleUrlNavigation);

      window.addEventListener("resize", syncHeaderOffset);
      window.addEventListener("scroll", syncHeaderOffset, { passive: true });

      // Global delegated macro click listener (works dynamically across all tabs and mobile)
      document.addEventListener("click", (e) => {
        const macroEl = e.target.closest(".mipp-macro-ref");
        if (macroEl) {
          e.stopPropagation();
          showMacroTooltip(macroEl);
          return;
        }
        if (!e.target.closest(".mipp-macro-tooltip")) {
          hideMacroTooltip();
        }
      });

      document.addEventListener("keydown", (e) => {
        if (e.key === "Escape") {
          hideMacroTooltip();
        } else if ((e.key === "Enter" || e.key === " ") && e.target && e.target.closest) {
          const macroEl = e.target.closest(".mipp-macro-ref");
          if (macroEl) {
            e.preventDefault();
            showMacroTooltip(macroEl);
          }
        }
      });
    } catch (err) {
      mountEl.innerHTML = `
        <div style="padding: 2rem; background: rgba(239, 68, 68, 0.1); border: 1px solid #ef4444; border-radius: 8px; color: #ef4444;">
          <h3 style="margin: 0 0 0.5rem 0;">Failed to load MIPP API Index data</h3>
          <p style="margin: 0;">Error: ${escapeHtml(err.message)}</p>
          <p style="margin: 0.5rem 0 0 0; font-size: 0.82rem;">Ensure <code>python3 generator/gen_mipp_docs.py</code> has been run to generate <code>docs/assets/data/mipp_api_index.json</code>.</p>
        </div>
      `;
    }
  }

  // MkDocs Material Instant Navigation Lifecycle Subscription
  if (typeof document$ !== "undefined") {
    document$.subscribe(initExplorer);
  } else {
    document.addEventListener("DOMContentLoaded", initExplorer);
  }
})();
