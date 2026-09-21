/**
 * MIPP API Explorer - Card Component
 * Manages primitive card rendering and structural tab transitions.
 */
import { escapeHtml, ICON_COPY, ICON_CHEVRON } from "../explorer.config.js";
import { highlightCpp, getDtBadgeClass, formatCppObjProto } from "../syntax.js";
import { LEVEL_DESCRIPTIONS, ALL_MASK_MODES, ALL_SIMD_EXTS, SIMD_EXT_DISPLAY_NAMES } from "../data.js";
import { state, syncUrlHash, setFocusedCard } from "../state.js";
import { renderTabHw } from "./tab_hw.js";
import { renderTabProto } from "./tab_proto.js";
import { renderTabAlgos } from "./tab_algos.js";
import { renderTabSpecs } from "./tab_specs.js";
import { renderTabFlat } from "./tab_flat.js";

export function getActivePrototype(entry) {
  const lmulKey = state.lmul;
  const protoData = entry.prototypes;
  if (!protoData) return "";

  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  if (state.flavor === "c99") {
    if (entry.prototypes && entry.prototypes.c99_samples && entry.prototypes.c99_samples[lmulKey]) {
      const maskSamples = entry.prototypes.c99_samples[lmulKey];
      const selectedMask = state.selectedMaskModes[0] || "unmasked";
      const list = maskSamples[selectedMask] || maskSamples["unmasked"];
      if (Array.isArray(list)) {
        if (activeDts.length > 0) {
          const match = list.find((sig) => activeDts.some((dt) => sig.includes(`_${dt}`) || sig.includes(`<${dt}`)));
          if (match) return match;
        }
        return list[0] || "";
      }
    }
    return protoData.c99 || "";
  }

  const cppSamples = (entry.prototypes && entry.prototypes.cpp_samples) || entry.cpp_samples;
  if (state.flavor === "cpp" && cppSamples && cppSamples[lmulKey]) {
    const sample = cppSamples[lmulKey];
    if (typeof sample === "object" && sample !== null) {
      const selectedMask = state.selectedMaskModes[0] || "unmasked";
      return sample[selectedMask] || sample["unmasked"] || Object.values(sample)[0] || "";
    } else if (Array.isArray(sample)) {
      return sample[0] || "";
    }
    return String(sample);
  }

  const cppObjSamples = (entry.prototypes && entry.prototypes.cpp_obj_samples) || entry.cpp_obj_samples;
  if (state.flavor === "cpp_obj") {
    let sample = (cppObjSamples && (cppObjSamples[lmulKey] || cppObjSamples["1"])) || protoData.cpp_obj || "";
    if (typeof sample === "object" && sample !== null) {
      sample = sample["unmasked"] || Object.values(sample)[0] || "";
    } else if (Array.isArray(sample)) {
      sample = sample[0] || "";
    }
    return formatCppObjProto(String(sample), lmulKey);
  }

  return protoData[state.flavor] || protoData.cpp || protoData.c99 || "";
}

export function renderTabContent(entry, activeTab) {
  if (activeTab === "hw") return renderTabHw(entry);
  if (activeTab === "scalar") return renderTabAlgos(entry);
  if (activeTab === "specs") return renderTabSpecs(entry);
  if (activeTab === "flat" || activeTab === "example") return renderTabFlat(entry);
  return renderTabProto(entry);
}

export function renderCardExpandedDetails(entry) {
  const activeTab = state.cardTabs[entry.name] || "proto";

  return `
    <div class="mipp-card-body">
      <!-- Internal Tab Navigation: Prototypes before Hardware Matrix -->
      <nav class="mipp-card-tabs" role="tablist">
        <button class="mipp-card-tab-btn ${activeTab === "proto" ? "active" : ""}" data-tab="proto" data-card-tab="proto" data-target-card="${escapeHtml(entry.name)}" data-card="${escapeHtml(entry.name)}">
          📝 Prototypes
        </button>
        <button class="mipp-card-tab-btn ${activeTab === "hw" ? "active" : ""}" data-tab="hw" data-card-tab="hw" data-target-card="${escapeHtml(entry.name)}" data-card="${escapeHtml(entry.name)}">
          ⚙️ Hardware Matrix
        </button>
        <button class="mipp-card-tab-btn ${activeTab === "scalar" ? "active" : ""}" data-tab="scalar" data-card-tab="scalar" data-target-card="${escapeHtml(entry.name)}" data-card="${escapeHtml(entry.name)}">
          📐 Scalar C Reference
        </button>
        <button class="mipp-card-tab-btn ${activeTab === "specs" ? "active" : ""}" data-tab="specs" data-card-tab="specs" data-target-card="${escapeHtml(entry.name)}" data-card="${escapeHtml(entry.name)}">
          🧪 Verification Specs
        </button>
        <button class="mipp-card-tab-btn ${activeTab === "flat" ? "active" : ""}" data-tab="flat" data-card-tab="flat" data-target-card="${escapeHtml(entry.name)}" data-card="${escapeHtml(entry.name)}">
          💻 Flat Specialized Code
        </button>
      </nav>

      <div class="mipp-tab-pane" id="tab-content-${escapeHtml(entry.name)}">
        ${renderTabContent(entry, activeTab)}
      </div>
    </div>
  `;
}

export function computeOptimisticLevel(entry, ext) {
  const sup = entry.isa_support ? entry.isa_support[ext] : null;
  if (!sup) return "na";

  const numLmul = Number(state.lmul) || 1;
  const isHalfLmul = state.lmul === "-2";
  const currentLmulVal = isHalfLmul ? -2 : numLmul;
  const hwLmuls = sup.hw_lmul || (ext === "rvv" ? [1, 2, 4, 8, -2] : [1]);
  const isLmulEmulated = currentLmulVal !== 1 && !hwLmuls.includes(currentLmulVal);

  // Active datatypes
  const allDts = entry.datatypes || [];
  const selectedDts = allDts.filter((dt) => (state.selectedTypes || []).includes(dt));
  const dtsToConsider = selectedDts.length > 0 ? selectedDts : allDts;

  // Active mask modes
  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const selectedMasks = allVariants.filter((m) => (state.selectedMaskModes || []).includes(m));
  const masksToConsider = selectedMasks.length > 0 ? selectedMasks : allVariants;

  if (dtsToConsider.length === 0 || masksToConsider.length === 0) {
    let lvl = sup.overall_level !== undefined ? sup.overall_level : "na";
    if (lvl !== "na" && isLmulEmulated && lvl < 2) lvl = 2;
    return lvl;
  }

  const levels = [];

  for (const mask of masksToConsider) {
    for (const dt of dtsToConsider) {
      let lvl;
      if (mask === "unmasked") {
        lvl = (sup.by_datatype && sup.by_datatype[dt] !== undefined)
          ? sup.by_datatype[dt]
          : (sup.overall_level !== undefined ? sup.overall_level : 3);
      } else {
        const maskedDict = sup.masked_by_datatype ? sup.masked_by_datatype[mask] : null;
        lvl = (maskedDict && maskedDict[dt] !== undefined)
          ? maskedDict[dt]
          : 2;
      }
      if (isLmulEmulated && lvl < 2) {
        lvl = 2;
      }
      levels.push(lvl);
    }
  }

  if (levels.length === 0) return "na";
  const bestLvl = Math.min(...levels);
  return bestLvl > 3 ? "na" : bestLvl;
}

export function renderCard(entry, matchedIntrinsic = null, matchedC99 = null) {
  const isExpanded = state.expandedCards.has(entry.name);
  const activeProto = getActivePrototype(entry);
  const isCompared = state.compareSet.has(entry.name);

  const extsList = ALL_SIMD_EXTS;
  const selectedExts = state.selectedSimdExts || [];
  const extsToDisplay = selectedExts.length > 0 ? selectedExts : extsList;
  const namesMap = SIMD_EXT_DISPLAY_NAMES;

  return `
    <article class="mipp-card ${isExpanded ? "expanded" : ""}" data-card-name="${escapeHtml(entry.name)}" id="card-${escapeHtml(entry.name)}">
      <!-- Card Header -->
      <div class="mipp-card-header" data-card-name="${escapeHtml(entry.name)}">
        <div class="mipp-card-top-row">
          <div class="mipp-card-title-group">
            <label class="mipp-checkbox-item" style="margin-right: 0.2rem;" onclick="event.stopPropagation();">
              <input type="checkbox" data-compare="${escapeHtml(entry.name)}" data-compare-name="${escapeHtml(entry.name)}" ${isCompared ? "checked" : ""} title="Add to comparison">
            </label>
            <span class="mipp-card-name">${escapeHtml(entry.name)}</span>
            <span class="mipp-cat-badge">${escapeHtml(entry.category)}</span>
            ${matchedIntrinsic
              ? `<span class="mipp-matched-chip" title="Matched vendor hardware intrinsic">Intrinsic: ${escapeHtml(matchedIntrinsic)}</span>`
              : ""
            }
            ${matchedC99 && matchedC99 !== entry.name && matchedC99 !== `mipp_${entry.name}`
              ? `<span class="mipp-matched-chip" title="Matched C99 function">C99: ${escapeHtml(matchedC99)}</span>`
              : ""
            }
          </div>

          <!-- SIMD Extensions Strip -->
          <div class="mipp-isa-strip mipp-simd-ext-strip">
            ${extsToDisplay.map((ext) => {
              const lvl = computeOptimisticLevel(entry, ext);
              return `
                <span class="mipp-isa-badge lvl-${lvl}"
                      title="${namesMap[ext] || ext.toUpperCase()}: ${lvl === "na" ? "Not Supported" : `Level ${lvl} (${LEVEL_DESCRIPTIONS[lvl] || ""})`}">
                  ${namesMap[ext] || ext.toUpperCase()}${lvl !== "na" ? `: L${lvl}` : ""}
                </span>
              `;
            }).join("")}
          </div>
        </div>

        <p class="mipp-card-desc">${escapeHtml(entry.description)}</p>

        <!-- Prototype Preview Container (Prototype code box + separate Details button) -->
        <div class="mipp-card-preview-container">
          <div class="mipp-card-proto-box">
            <div class="mipp-proto-code">${highlightCpp(activeProto)}</div>
            <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(activeProto)}" title="Copy prototype" onclick="event.stopPropagation();">
              ${ICON_COPY}
            </button>
          </div>
          <button class="mipp-toggle-details-btn ${isExpanded ? "is-expanded" : ""}" data-toggle-card="${escapeHtml(entry.name)}" title="Toggle expanded details">
            <span class="mipp-toggle-text">${isExpanded ? "Close" : "Details"}</span>
            ${ICON_CHEVRON}
          </button>
        </div>
      </div>

      <!-- Card Body (Tabs with smooth slide transition) -->
      <div class="mipp-card-expandable ${isExpanded ? "open" : ""}">
        <div class="mipp-card-expandable-inner">
          ${isExpanded ? renderCardExpandedDetails(entry) : ""}
        </div>
      </div>
    </article>
  `;
}

export function switchCardTab(cardEl, entry, targetTab) {
  state.cardTabs[entry.name] = targetTab;
  setFocusedCard(entry.name);

  if (targetTab === "scalar" && !state.cardScalarTypes[entry.name]) {
    const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
    const dtsToDisplay = activeDts.length > 0 ? activeDts : (entry.datatypes || []);
    state.cardScalarTypes[entry.name] = dtsToDisplay[0] || "float32";
  }
  if (targetTab === "specs" && !state.cardTestVariants[entry.name]) {
    const maskSupport = entry.mask_support || {};
    const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
    const activeMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
    const availableVariants = activeMasks.length > 0 ? activeMasks : allVariants;
    state.cardTestVariants[entry.name] = availableVariants[0] || "unmasked";
  }
  if (targetTab === "hw" && !state.cardHwMask[entry.name]) {
    const maskSupport = entry.mask_support || {};
    const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
    const activeMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
    const availableVariants = activeMasks.length > 0 ? activeMasks : allVariants;
    state.cardHwMask[entry.name] = availableVariants[0] || "unmasked";
  }

  syncUrlHash(true);

  // 1. Update active class on tab buttons without destroying the tabs nav container
  const tabsNav = cardEl.querySelector(".mipp-card-tabs");
  if (tabsNav) {
    tabsNav.querySelectorAll(".mipp-card-tab-btn").forEach((btn) => {
      const tab = btn.getAttribute("data-tab") || btn.getAttribute("data-card-tab");
      if (tab === targetTab) {
        btn.classList.add("active");
      } else {
        btn.classList.remove("active");
      }
    });
  }

  // 2. Replace only the tab pane content
  const tabContent = cardEl.querySelector(`#tab-content-${entry.name}`);
  if (tabContent) {
    tabContent.innerHTML = renderTabContent(entry, targetTab);
    if (targetTab === "scalar" && window.MathJax && window.MathJax.typesetPromise) {
      const mathEl = tabContent.querySelector(".arithmatex");
      if (mathEl) {
        window.MathJax.typesetPromise([mathEl]).catch(() => {});
      }
    }
  }
}
