/**
 * MIPP API Explorer - Sidebar Filter Component
 */
import { escapeHtml, ICON_ALL, ICON_CLEAR } from "../explorer.config.js";
import {
  ALL_CATEGORIES,
  ALL_DATATYPES,
  DATATYPE_GROUPS
} from "../data.js";
import { getDtBadgeClass } from "../syntax.js";
import { state, syncUrlHash } from "../state.js";

export function renderSidebar(catCounts, renderApp) {
  // Check state for All/Clear buttons
  const allCatsChecked = state.selectedCategories.length === ALL_CATEGORIES.length;
  const noCatsChecked = state.selectedCategories.length === 0;

  const allTypesChecked = state.selectedTypes.length === ALL_DATATYPES.length;
  const noTypesChecked = state.selectedTypes.length === 0;

  return `
    <aside class="mipp-sidebar">
      <!-- 1. Categories Filter -->
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

      <!-- 2. Datatypes Filter -->
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
    </aside>
  `;
}

export function updateSidebarUI(sidebarEl) {
  if (!sidebarEl) return;

  // 1. CATEGORIES
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

  // 2. DATATYPES
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
}

export function bindSidebarEvents(sidebarEl, onFilterChange) {
  if (!sidebarEl) return;

  // 1. CATEGORIES
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

  // 2. DATATYPES
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
}
