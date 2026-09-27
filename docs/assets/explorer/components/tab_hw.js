/**
 * MIPP API Explorer - Tab 1: Hardware Matrix
 * Displays a streamlined support matrix per SIMD extension & datatype groups,
 * featuring intelligent family grouping and direct links to the View Algorithm modal.
 */
import { escapeHtml } from "../explorer.config.js";
import { ALL_SIMD_EXTS, SIMD_EXT_DISPLAY_NAMES, ALL_MASK_MODES } from "../data.js";
import { getDtBadgeClass } from "../syntax.js";
import { state } from "../state.js";

export function renderTabHw(entry) {
  const extsList = ALL_SIMD_EXTS;
  const namesMap = SIMD_EXT_DISPLAY_NAMES;
  const selectedExts = state.selectedSimdExts || [];
  const activeExts = extsList.filter((ext) => selectedExts.includes(ext));
  const activeDts = (entry.datatypes || []).filter((dt) => state.selectedTypes.includes(dt));
  const dtsToConsider = activeDts.length > 0 ? activeDts : (entry.datatypes || []);

  if (activeExts.length === 0) {
    return `
      <div style="padding: 1.5rem; text-align: center; color: var(--md-default-fg-color--lighter);">
        <p style="margin: 0;">No target SIMD extensions selected in the sidebar filter. Enable at least one SIMD extension to view hardware mappings.</p>
      </div>
    `;
  }

  const maskSupport = entry.mask_support || {};
  const effectiveMasks = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);

  const globalVariant = state.flavor === "cpp_obj" ? "unmasked" : (state.maskVariant || "unmasked");
  const currentMask = effectiveMasks.includes(globalVariant) ? globalVariant : "unmasked";

  const STANDARD_FLOATS = ["float64", "float32"];
  const STANDARD_INTS = ["int64", "int32", "int16", "int8"];
  const STANDARD_UINTS = ["uint64", "uint32", "uint16", "uint8"];
  const ALL_STANDARD_DTS = [...STANDARD_FLOATS, ...STANDARD_INTS, ...STANDARD_UINTS];

  function formatGroupBadges(groupDts, reqFeature) {
    // 1. If every standard datatype (all 10) is in this group
    if (ALL_STANDARD_DTS.every((d) => groupDts.includes(d))) {
      return `
        <div class="mipp-hw-dts-badges">
          <span class="mipp-dt-group-badge dt-group-all">all datatypes</span>
          ${reqFeature ? `<span class="mipp-req-feature-tag"><i>(req. ${escapeHtml(reqFeature)})</i></span>` : ""}
        </div>
      `;
    }

    // 2. Family groups & individual fallback
    const badges = [];
    const remaining = new Set(groupDts);

    if (STANDARD_FLOATS.every((d) => remaining.has(d))) {
      badges.push(`<span class="mipp-dt-group-badge dt-group-float">all float</span>`);
      STANDARD_FLOATS.forEach((d) => remaining.delete(d));
    }
    if (STANDARD_INTS.every((d) => remaining.has(d))) {
      badges.push(`<span class="mipp-dt-group-badge dt-group-int">all int</span>`);
      STANDARD_INTS.forEach((d) => remaining.delete(d));
    }
    if (STANDARD_UINTS.every((d) => remaining.has(d))) {
      badges.push(`<span class="mipp-dt-group-badge dt-group-uint">all uint</span>`);
      STANDARD_UINTS.forEach((d) => remaining.delete(d));
    }

    for (const dt of remaining) {
      badges.push(`<span class="mipp-dt-badge ${getDtBadgeClass(dt)}">${escapeHtml(dt)}</span>`);
    }

    return `
      <div class="mipp-hw-dts-badges">
        ${badges.join(" ")}
        ${reqFeature ? `<span class="mipp-req-feature-tag"><i>(req. ${escapeHtml(reqFeature)})</i></span>` : ""}
      </div>
    `;
  }

  return `
    <div>
      <div class="mipp-hw-table-wrapper">
        <table class="mipp-hw-table">
          <thead>
            <tr>
              <th class="mipp-hw-col-ext">
                <span class="mipp-hw-header-full">SIMD Extension</span>
                <span class="mipp-hw-header-short">Ext</span>
              </th>
              <th class="mipp-hw-col-dts">Datatypes</th>
              <th class="mipp-hw-col-tier">Tier</th>
              <th class="mipp-hw-col-action">Algorithm</th>
            </tr>
          </thead>
          <tbody>
            ${activeExts.map((isa) => {
              const info = entry.isa_support ? entry.isa_support[isa] : null;
              const isaLabel = namesMap[isa] || isa.toUpperCase();

              if (!info) {
                return `
                  <tr class="mipp-hw-row mipp-hw-group-first">
                    <td class="mipp-hw-col-ext">
                      <span class="mipp-hw-ext-name">${isaLabel}</span>
                    </td>
                    <td class="mipp-hw-col-dts">
                      ${formatGroupBadges(dtsToConsider)}
                    </td>
                    <td class="mipp-hw-col-tier">
                      <span class="mipp-isa-badge lvl-na">N/A</span>
                    </td>
                    <td class="mipp-hw-col-action">
                      <span class="mipp-hw-no-algo">—</span>
                    </td>
                  </tr>
                `;
              }

              const currentLmul = Number(state.lmul);
              const hwLmuls = info.hw_lmul || [1];
              const isLmulEmulated = currentLmul !== 1 && !hwLmuls.includes(currentLmul) && (info.overall_level < 2);
              const reqFeatures = info.required_features || {};

              const getDtLevel = (dt) => {
                let lvl;
                if (currentMask === "unmasked") {
                  lvl = info.by_datatype && info.by_datatype[dt] !== undefined
                    ? info.by_datatype[dt]
                    : (info.overall_level !== undefined ? info.overall_level : 3);
                } else {
                  const maskedDict = info.masked_by_datatype ? info.masked_by_datatype[currentMask] : null;
                  lvl = maskedDict && maskedDict[dt] !== undefined
                    ? maskedDict[dt]
                    : 2;
                }
                if (isLmulEmulated && lvl < 2) lvl = 2;
                return lvl;
              };

              // Group datatypes by (level, reqFeature)
              const groupsMap = new Map();
              for (const dt of dtsToConsider) {
                const lvl = getDtLevel(dt);
                const feat = (lvl === 0 && reqFeatures[dt]) ? reqFeatures[dt] : null;
                const groupKey = `${lvl}::${feat || ""}`;
                if (!groupsMap.has(groupKey)) {
                  groupsMap.set(groupKey, { level: lvl, reqFeature: feat, dts: [] });
                }
                groupsMap.get(groupKey).dts.push(dt);
              }

              const groups = Array.from(groupsMap.values()).sort((a, b) => a.level - b.level);
              if (groups.length === 0) {
                return `
                  <tr class="mipp-hw-row mipp-hw-group-first">
                    <td class="mipp-hw-col-ext"><span class="mipp-hw-ext-name">${isaLabel}</span></td>
                    <td class="mipp-hw-col-dts">${formatGroupBadges(dtsToConsider)}</td>
                    <td class="mipp-hw-col-tier"><span class="mipp-isa-badge lvl-na">N/A</span></td>
                    <td class="mipp-hw-col-action"><span class="mipp-hw-no-algo">—</span></td>
                  </tr>
                `;
              }

              return groups.map((group, idx) => {
                const isFirst = idx === 0;
                const defaultGroupDt = group.dts[0] || "float32";
                const reqFeatureAttr = group.reqFeature || "";

                const extCell = isFirst
                  ? `<td class="mipp-hw-col-ext" ${groups.length > 1 ? `rowspan="${groups.length}"` : ""}>
                       <span class="mipp-hw-ext-name">${isaLabel}</span>
                     </td>`
                  : "";

                const tierBadge = group.level > 3 || group.level === "na"
                  ? `<span class="mipp-isa-badge lvl-na">N/A</span>`
                  : `<span class="mipp-isa-badge lvl-${group.level}">L${group.level}</span>`;

                const algoBtn = `
                  <button type="button" class="mipp-icon-btn mipp-hw-algo-btn" data-algo-card="${escapeHtml(entry.name)}" data-algo-isa="${isa}" data-algo-dt="${defaultGroupDt}" data-algo-mask="${currentMask}" data-algo-feature="${escapeHtml(reqFeatureAttr)}" title="View algorithm for ${isaLabel} (${escapeHtml(group.dts.join(', '))})">
                    🔍
                  </button>
                `;

                return `
                  <tr class="mipp-hw-row ${isFirst ? "mipp-hw-group-first" : "mipp-hw-group-sub"}">
                    ${extCell}
                    <td class="mipp-hw-col-dts">${formatGroupBadges(group.dts, group.reqFeature)}</td>
                    <td class="mipp-hw-col-tier">${tierBadge}</td>
                    <td class="mipp-hw-col-action">${algoBtn}</td>
                  </tr>
                `;
              }).join("");
            }).join("")}
          </tbody>
        </table>
      </div>
    </div>
  `;
}
