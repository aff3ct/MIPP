/**
 * MIPP API Explorer - Sidebar Filter Component
 */
import { escapeHtml, ICON_ALL, ICON_CLEAR, ICON_UNION, ICON_INTERSECT } from "../explorer.config.js";
import {
  ALL_SIMD_EXTS,
  SIMD_EXT_DISPLAY_NAMES,
  ALL_CATEGORIES,
  ALL_DATATYPES,
  DATATYPE_GROUPS,
  ALL_MASK_MODES,
  MASK_MODES_INFO,
  ALL_LEVELS,
  LEVEL_DESCRIPTIONS
} from "../data.js";
import { getDtBadgeClass } from "../syntax.js";
import { state, syncUrlHash } from "../state.js";

export function renderSidebar(catCounts, renderApp) {
  const isCppObj = state.flavor === "cpp_obj";

  // Check state for All/Clear buttons
  const extsList = ALL_SIMD_EXTS;
  const namesMap = SIMD_EXT_DISPLAY_NAMES;
  const selectedExts = state.selectedSimdExts || [];
  const allExtsChecked = selectedExts.length === extsList.length;
  const noExtsChecked = selectedExts.length === 0;

  const allLevelsChecked = state.selectedLevels.length === ALL_LEVELS.length;
  const noLevelsChecked = state.selectedLevels.length === 0;

  const allCatsChecked = state.selectedCategories.length === ALL_CATEGORIES.length;
  const noCatsChecked = state.selectedCategories.length === 0;

  const allTypesChecked = state.selectedTypes.length === ALL_DATATYPES.length;
  const noTypesChecked = state.selectedTypes.length === 0;

  const availableMaskModes = isCppObj
    ? ALL_MASK_MODES.filter((m) => MASK_MODES_INFO[m] && MASK_MODES_INFO[m].cpp_obj_support)
    : ALL_MASK_MODES;
  const allMasksChecked = availableMaskModes.length > 0 && availableMaskModes.every((m) => state.selectedMaskModes.includes(m));
  const noMasksChecked = state.selectedMaskModes.length === 0;

  return `
    <aside class="mipp-sidebar">
      <!-- 1. SIMD Extensions Filter -->
      <div class="mipp-filter-section">
        <div class="mipp-filter-header">
          <h3 class="mipp-filter-title">SIMD Extensions</h3>
          <div class="mipp-filter-actions">
            <button class="mipp-filter-action-icon ${allExtsChecked ? "active" : ""}" id="mipp-all-simd-exts" title="Select all SIMD extensions" ${allExtsChecked ? "disabled" : ""}>${ICON_ALL}</button>
            <button class="mipp-filter-action-icon ${noExtsChecked ? "active" : ""}" id="mipp-clear-simd-exts" title="Clear SIMD extensions" ${noExtsChecked ? "disabled" : ""}>${ICON_CLEAR}</button>
          </div>
        </div>
        <div class="mipp-filter-list">
          ${extsList.map((ext) => `
            <label class="mipp-checkbox-item">
              <input type="checkbox" data-simd-ext="${ext}" data-isa="${ext}" ${selectedExts.includes(ext) ? "checked" : ""}>
              <span>${namesMap[ext] || ext.toUpperCase()}</span>
            </label>
          `).join("")}
        </div>
      </div>

      <!-- 2. Levels Filter -->
      <div class="mipp-filter-section">
        <div class="mipp-filter-header">
          <h3 class="mipp-filter-title">Levels</h3>
          <div class="mipp-filter-actions">
            <button class="mipp-filter-action-icon ${allLevelsChecked ? "active" : ""}" id="mipp-all-levels" title="Select all levels" ${allLevelsChecked ? "disabled" : ""}>${ICON_ALL}</button>
            <button class="mipp-filter-action-icon ${noLevelsChecked ? "active" : ""}" id="mipp-clear-levels" title="Clear levels" ${noLevelsChecked ? "disabled" : ""}>${ICON_CLEAR}</button>
            <button class="mipp-filter-action-icon mipp-union-intersect-btn ${state.intersectionMode ? "active" : ""}" id="mipp-toggle-intersection"
                    title="${state.intersectionMode ? "Intersection (∩) : All selected SIMD extensions must support level" : "Union (∪) : At least one selected SIMD extension must support level"}">
              ${state.intersectionMode ? ICON_INTERSECT : ICON_UNION}
            </button>
          </div>
        </div>
        <div class="mipp-filter-list">
          ${ALL_LEVELS.map((lvl) => `
            <label class="mipp-checkbox-item">
              <input type="checkbox" data-level="${lvl}" ${state.selectedLevels.includes(lvl) ? "checked" : ""}>
              <span class="mipp-isa-badge lvl-${lvl}">L${lvl}</span>
              <span style="font-size: 0.82rem;">${LEVEL_DESCRIPTIONS[lvl] || `Level ${lvl}`}</span>
            </label>
          `).join("")}
        </div>
      </div>

      <!-- 3. Categories Filter -->
      <div class="mipp-filter-section">
        <div class="mipp-filter-header">
          <h3 class="mipp-filter-title">Categories</h3>
          <div class="mipp-filter-actions">
            <button class="mipp-filter-action-icon ${allCatsChecked ? "active" : ""}" id="mipp-all-cats" title="Select all categories" ${allCatsChecked ? "disabled" : ""}>${ICON_ALL}</button>
            <button class="mipp-filter-action-icon ${noCatsChecked ? "active" : ""}" id="mipp-clear-cats" title="Clear categories" ${noCatsChecked ? "disabled" : ""}>${ICON_CLEAR}</button>
          </div>
        </div>
        <div class="mipp-filter-list">
          ${ALL_CATEGORIES.map((cat) => `
            <label class="mipp-checkbox-item">
              <input type="checkbox" data-cat="${cat}" ${state.selectedCategories.includes(cat) ? "checked" : ""}>
              <span style="text-transform: capitalize;">${escapeHtml(cat)}</span>
              <span class="mipp-badge-count">${catCounts[cat] || 0}</span>
            </label>
          `).join("")}
        </div>
      </div>

      <!-- 4. Datatypes Filter -->
      <div class="mipp-filter-section">
        <div class="mipp-filter-header">
          <h3 class="mipp-filter-title">Datatypes</h3>
          <div class="mipp-filter-actions">
            <button class="mipp-filter-action-icon ${allTypesChecked ? "active" : ""}" id="mipp-all-types" title="Select all datatypes" ${allTypesChecked ? "disabled" : ""}>${ICON_ALL}</button>
            <button class="mipp-filter-action-icon ${noTypesChecked ? "active" : ""}" id="mipp-clear-types" title="Clear datatypes" ${noTypesChecked ? "disabled" : ""}>${ICON_CLEAR}</button>
          </div>
        </div>
        <!-- Quick Group Chips -->
        <div class="mipp-filter-chips" style="margin-bottom: 0.4rem;">
          ${Object.values(DATATYPE_GROUPS).map((grp) => `
            <button class="mipp-filter-chip" data-type-group="${escapeHtml(grp.id)}">${escapeHtml(grp.label)}</button>
          `).join("")}
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

      <!-- 5. Mask Variants Filter -->
      <div class="mipp-filter-section">
        <div class="mipp-filter-header">
          <h3 class="mipp-filter-title">Mask Variants</h3>
          <div class="mipp-filter-actions">
            <button class="mipp-filter-action-icon ${allMasksChecked ? "active" : ""}" id="mipp-all-masks" title="Select all mask variants" ${allMasksChecked ? "disabled" : ""}>${ICON_ALL}</button>
            <button class="mipp-filter-action-icon ${noMasksChecked ? "active" : ""}" id="mipp-clear-masks" title="Clear mask variants" ${noMasksChecked ? "disabled" : ""}>${ICON_CLEAR}</button>
          </div>
        </div>
        <div class="mipp-filter-list">
          ${ALL_MASK_MODES.map((mId) => {
    const minfo = MASK_MODES_INFO[mId] || { id: mId, label: mId, badge_class: `mask-${mId}`, cpp_obj_support: false };
    const isDisabled = isCppObj && !minfo.cpp_obj_support;
    const isChecked = !isDisabled && state.selectedMaskModes.includes(mId);
    const tooltip = isDisabled ? "Masking variants not supported in C++ Object dialect" : (minfo.description || "");
    return `
              <label class="mipp-checkbox-item ${isDisabled ? "disabled" : ""}" title="${escapeHtml(tooltip)}">
                <input type="checkbox" data-mask="${escapeHtml(mId)}" ${isChecked ? "checked" : ""} ${isDisabled ? "disabled" : ""}>
                <span class="mipp-mask-badge ${escapeHtml(minfo.badge_class || `mask-${mId}`)}">${escapeHtml(minfo.label || mId)}</span>
              </label>
            `;
  }).join("")}
        </div>
      </div>
    </aside>
  `;
}

export function updateSidebarUI(sidebarEl) {
  if (!sidebarEl) return;
  const isCppObj = state.flavor === "cpp_obj";

  // 1. SIMD Extensions
  const allExtsChecked = state.selectedSimdExts.length === ALL_SIMD_EXTS.length;
  const noExtsChecked = state.selectedSimdExts.length === 0;
  const allExtsBtn = sidebarEl.querySelector("#mipp-all-simd-exts");
  const clearExtsBtn = sidebarEl.querySelector("#mipp-clear-simd-exts");
  if (allExtsBtn) {
    allExtsBtn.classList.toggle("active", allExtsChecked);
    allExtsBtn.disabled = allExtsChecked;
  }
  if (clearExtsBtn) {
    clearExtsBtn.classList.toggle("active", noExtsChecked);
    clearExtsBtn.disabled = noExtsChecked;
  }
  sidebarEl.querySelectorAll("[data-simd-ext]").forEach((cb) => {
    const ext = cb.getAttribute("data-simd-ext");
    cb.checked = state.selectedSimdExts.includes(ext);
  });

  // 2. LEVELS
  const allLevelsChecked = state.selectedLevels.length === ALL_LEVELS.length;
  const noLevelsChecked = state.selectedLevels.length === 0;
  const allLevelsBtn = sidebarEl.querySelector("#mipp-all-levels");
  const clearLevelsBtn = sidebarEl.querySelector("#mipp-clear-levels");
  if (allLevelsBtn) {
    allLevelsBtn.classList.toggle("active", allLevelsChecked);
    allLevelsBtn.disabled = allLevelsChecked;
  }
  if (clearLevelsBtn) {
    clearLevelsBtn.classList.toggle("active", noLevelsChecked);
    clearLevelsBtn.disabled = noLevelsChecked;
  }
  const toggleIntersectBtn = sidebarEl.querySelector("#mipp-toggle-intersection");
  if (toggleIntersectBtn) {
    toggleIntersectBtn.classList.toggle("active", state.intersectionMode);
    toggleIntersectBtn.title = state.intersectionMode
      ? "Intersection (∩) : All selected SIMD extensions must support level"
      : "Union (∪) : At least one selected SIMD extension must support level";
    toggleIntersectBtn.innerHTML = state.intersectionMode ? ICON_INTERSECT : ICON_UNION;
  }
  sidebarEl.querySelectorAll("[data-level]").forEach((cb) => {
    const lvl = parseInt(cb.getAttribute("data-level"), 10);
    cb.checked = state.selectedLevels.includes(lvl);
  });

  // 3. CATEGORIES
  const allCatsChecked = state.selectedCategories.length === ALL_CATEGORIES.length;
  const noCatsChecked = state.selectedCategories.length === 0;
  const allCatsBtn = sidebarEl.querySelector("#mipp-all-cats");
  const clearCatsBtn = sidebarEl.querySelector("#mipp-clear-cats");
  if (allCatsBtn) {
    allCatsBtn.classList.toggle("active", allCatsChecked);
    allCatsBtn.disabled = allCatsChecked;
  }
  if (clearCatsBtn) {
    clearCatsBtn.classList.toggle("active", noCatsChecked);
    clearCatsBtn.disabled = noCatsChecked;
  }
  sidebarEl.querySelectorAll("[data-cat]").forEach((cb) => {
    const cat = cb.getAttribute("data-cat");
    cb.checked = state.selectedCategories.includes(cat);
  });

  // 4. DATATYPES
  const allTypesChecked = state.selectedTypes.length === ALL_DATATYPES.length;
  const noTypesChecked = state.selectedTypes.length === 0;
  const allTypesBtn = sidebarEl.querySelector("#mipp-all-types");
  const clearTypesBtn = sidebarEl.querySelector("#mipp-clear-types");
  if (allTypesBtn) {
    allTypesBtn.classList.toggle("active", allTypesChecked);
    allTypesBtn.disabled = allTypesChecked;
  }
  if (clearTypesBtn) {
    clearTypesBtn.classList.toggle("active", noTypesChecked);
    clearTypesBtn.disabled = noTypesChecked;
  }
  sidebarEl.querySelectorAll("[data-type]").forEach((chip) => {
    const dt = chip.getAttribute("data-type");
    chip.classList.toggle("active", state.selectedTypes.includes(dt));
  });

  // 5. MASKING
  const availableMaskModes = isCppObj
    ? ALL_MASK_MODES.filter((m) => MASK_MODES_INFO[m] && MASK_MODES_INFO[m].cpp_obj_support)
    : ALL_MASK_MODES;
  const allMasksChecked = availableMaskModes.length > 0 && availableMaskModes.every((m) => state.selectedMaskModes.includes(m));
  const noMasksChecked = state.selectedMaskModes.length === 0;
  const allMasksBtn = sidebarEl.querySelector("#mipp-all-masks");
  const clearMasksBtn = sidebarEl.querySelector("#mipp-clear-masks");
  if (allMasksBtn) {
    allMasksBtn.classList.toggle("active", allMasksChecked);
    allMasksBtn.disabled = allMasksChecked;
  }
  if (clearMasksBtn) {
    clearMasksBtn.classList.toggle("active", noMasksChecked);
    clearMasksBtn.disabled = noMasksChecked;
  }
  sidebarEl.querySelectorAll("[data-mask]").forEach((cb) => {
    const mId = cb.getAttribute("data-mask");
    const minfo = MASK_MODES_INFO[mId] || { id: mId, label: mId, badge_class: `mask-${mId}`, cpp_obj_support: false };
    const isDisabled = isCppObj && !minfo.cpp_obj_support;
    cb.disabled = isDisabled;
    cb.checked = !isDisabled && state.selectedMaskModes.includes(mId);
    const label = cb.closest(".mipp-checkbox-item");
    if (label) {
      label.classList.toggle("disabled", isDisabled);
    }
  });
}

export function bindSidebarEvents(sidebarEl, onFilterChange) {
  if (!sidebarEl) return;

  // 1. SIMD Extensions
  const allExtsBtn = sidebarEl.querySelector("#mipp-all-simd-exts");
  if (allExtsBtn) {
    allExtsBtn.addEventListener("click", () => {
      state.selectedSimdExts = [...ALL_SIMD_EXTS];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  const clearExtsBtn = sidebarEl.querySelector("#mipp-clear-simd-exts");
  if (clearExtsBtn) {
    clearExtsBtn.addEventListener("click", () => {
      state.selectedSimdExts = [];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  sidebarEl.querySelectorAll("[data-simd-ext]").forEach((cb) => {
    cb.addEventListener("change", (e) => {
      const ext = e.target.getAttribute("data-simd-ext");
      if (e.target.checked) {
        if (!state.selectedSimdExts.includes(ext)) state.selectedSimdExts.push(ext);
      } else {
        state.selectedSimdExts = state.selectedSimdExts.filter((x) => x !== ext);
      }
      syncUrlHash(true);
      onFilterChange();
    });
  });

  // 2. LEVELS
  const allLevelsBtn = sidebarEl.querySelector("#mipp-all-levels");
  if (allLevelsBtn) {
    allLevelsBtn.addEventListener("click", () => {
      state.selectedLevels = [...ALL_LEVELS];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  const clearLevelsBtn = sidebarEl.querySelector("#mipp-clear-levels");
  if (clearLevelsBtn) {
    clearLevelsBtn.addEventListener("click", () => {
      state.selectedLevels = [];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  const toggleIntersectBtn = sidebarEl.querySelector("#mipp-toggle-intersection");
  if (toggleIntersectBtn) {
    toggleIntersectBtn.addEventListener("click", () => {
      state.intersectionMode = !state.intersectionMode;
      syncUrlHash(true);
      onFilterChange();
    });
  }

  sidebarEl.querySelectorAll("[data-level]").forEach((cb) => {
    cb.addEventListener("change", (e) => {
      const lvl = parseInt(e.target.getAttribute("data-level"), 10);
      if (e.target.checked) {
        if (!state.selectedLevels.includes(lvl)) state.selectedLevels.push(lvl);
      } else {
        state.selectedLevels = state.selectedLevels.filter((x) => x !== lvl);
      }
      syncUrlHash(true);
      onFilterChange();
    });
  });

  // 3. CATEGORIES
  const allCatsBtn = sidebarEl.querySelector("#mipp-all-cats");
  if (allCatsBtn) {
    allCatsBtn.addEventListener("click", () => {
      state.selectedCategories = [...ALL_CATEGORIES];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  const clearCatsBtn = sidebarEl.querySelector("#mipp-clear-cats");
  if (clearCatsBtn) {
    clearCatsBtn.addEventListener("click", () => {
      state.selectedCategories = [];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  sidebarEl.querySelectorAll("[data-cat]").forEach((cb) => {
    cb.addEventListener("change", (e) => {
      const cat = e.target.getAttribute("data-cat");
      if (e.target.checked) {
        if (!state.selectedCategories.includes(cat)) state.selectedCategories.push(cat);
      } else {
        state.selectedCategories = state.selectedCategories.filter((x) => x !== cat);
      }
      syncUrlHash(true);
      onFilterChange();
    });
  });

  // 4. DATATYPES
  const allTypesBtn = sidebarEl.querySelector("#mipp-all-types");
  if (allTypesBtn) {
    allTypesBtn.addEventListener("click", () => {
      state.selectedTypes = ALL_DATATYPES.map((d) => d.id);
      syncUrlHash(true);
      onFilterChange();
    });
  }

  const clearTypesBtn = sidebarEl.querySelector("#mipp-clear-types");
  if (clearTypesBtn) {
    clearTypesBtn.addEventListener("click", () => {
      state.selectedTypes = [];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  sidebarEl.querySelectorAll("[data-type-group]").forEach((btn) => {
    btn.addEventListener("click", () => {
      const grp = btn.getAttribute("data-type-group");
      const matching = ALL_DATATYPES.filter((d) => d.group === grp).map((d) => d.id);
      const allActive = matching.every((d) => state.selectedTypes.includes(d));
      if (allActive) {
        state.selectedTypes = state.selectedTypes.filter((d) => !matching.includes(d));
      } else {
        state.selectedTypes = Array.from(new Set([...state.selectedTypes, ...matching]));
      }
      syncUrlHash(true);
      onFilterChange();
    });
  });

  sidebarEl.querySelectorAll("[data-type]").forEach((badge) => {
    badge.addEventListener("click", () => {
      const dt = badge.getAttribute("data-type");
      if (state.selectedTypes.includes(dt)) {
        state.selectedTypes = state.selectedTypes.filter((x) => x !== dt);
      } else {
        state.selectedTypes.push(dt);
      }
      syncUrlHash(true);
      onFilterChange();
    });
  });

  // 5. MASKING
  const allMasksBtn = sidebarEl.querySelector("#mipp-all-masks");
  if (allMasksBtn) {
    allMasksBtn.addEventListener("click", () => {
      if (state.flavor === "cpp_obj") {
        state.selectedMaskModes = ["unmasked"];
      } else {
        state.selectedMaskModes = [...ALL_MASK_MODES];
      }
      syncUrlHash(true);
      onFilterChange();
    });
  }

  const clearMasksBtn = sidebarEl.querySelector("#mipp-clear-masks");
  if (clearMasksBtn) {
    clearMasksBtn.addEventListener("click", () => {
      state.selectedMaskModes = [];
      syncUrlHash(true);
      onFilterChange();
    });
  }

  sidebarEl.querySelectorAll("[data-mask]").forEach((cb) => {
    cb.addEventListener("change", (e) => {
      const m = e.target.getAttribute("data-mask");
      if (e.target.checked) {
        if (!state.selectedMaskModes.includes(m)) state.selectedMaskModes.push(m);
      } else {
        state.selectedMaskModes = state.selectedMaskModes.filter((x) => x !== m);
      }
      syncUrlHash(true);
      onFilterChange();
    });
  });
}
