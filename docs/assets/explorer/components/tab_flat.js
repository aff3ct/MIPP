/**
 * MIPP API Explorer - Tab 5: Flat Specialized Code
 */
import { escapeHtml, ICON_COPY, SCALAR_BUFFER_SIZES } from "../explorer.config.js";
import { highlightCpp, getDtBadgeClass } from "../syntax.js";
import {
  ALL_MASK_MODES,
  LEVEL_DESCRIPTIONS,
  ALL_SIMD_EXTS,
  SIMD_EXT_DISPLAY_NAMES,
  SIMD_EXT_FEATURE_DEFINES
} from "../data.js";
import { state } from "../state.js";
import { generateFlatSpecializedCode, buildGodboltUrlForFlat } from "../codegen.js";

export function getCardFlatState(cardName, entry) {
  if (!state.cardFlatState) state.cardFlatState = {};
  const cur = state.cardFlatState[cardName] || {};

  const activeExts = ALL_SIMD_EXTS.filter((ext) => state.selectedSimdExts.includes(ext));
  const effectiveExts = activeExts.length > 0 ? activeExts : [...ALL_SIMD_EXTS];
  let defaultIsa = cur.isa && effectiveExts.includes(cur.isa)
    ? cur.isa
    : effectiveExts[0];

  const defFlags = cur.defines || {};
  const flagsList = SIMD_EXT_FEATURE_DEFINES[defaultIsa] || [];
  for (const f of flagsList) {
    if (defFlags[f.name] === undefined) {
      defFlags[f.name] = f.default;
    }
  }

  const availableDts = entry.datatypes || [];
  const activeSidebarDts = availableDts.filter((dt) => state.selectedTypes.includes(dt));
  const effectiveDts = activeSidebarDts.length > 0 ? activeSidebarDts : availableDts;
  const defaultDt = cur.dt && effectiveDts.includes(cur.dt)
    ? cur.dt
    : (effectiveDts[0] || "float32");

  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const activeMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
  const effectiveMasks = activeMasks.length > 0 ? activeMasks : allVariants;
  const defaultMask = cur.mask && effectiveMasks.includes(cur.mask)
    ? cur.mask
    : (effectiveMasks[0] || "unmasked");

  state.cardFlatState[cardName] = {
    isa: defaultIsa,
    defines: defFlags,
    dt: defaultDt,
    mask: defaultMask,
    lmul: state.lmul || "1",
    scalarSize: cur.scalarSize || 256
  };
  return state.cardFlatState[cardName];
}

export function renderTabFlat(entry) {
  const flatCfg = getCardFlatState(entry.name, entry);

  // 1. Filter SIMD Extensions to those checked in the left sidebar
  const availableExts = ALL_SIMD_EXTS.filter((ext) => state.selectedSimdExts.includes(ext));
  const effectiveExts = availableExts.length > 0 ? availableExts : [...ALL_SIMD_EXTS];
  if (!effectiveExts.includes(flatCfg.isa)) {
    flatCfg.isa = effectiveExts[0];
  }

  // 2. Filter Datatypes to those checked in the left sidebar
  const allDts = entry.datatypes || [];
  const activeSidebarDts = allDts.filter((dt) => state.selectedTypes.includes(dt));
  const availableDts = activeSidebarDts.length > 0 ? activeSidebarDts : allDts;
  if (!availableDts.includes(flatCfg.dt)) {
    flatCfg.dt = availableDts[0] || "float32";
  }

  // 3. Filter Mask variants to those checked in the left sidebar
  const maskSupport = entry.mask_support || {};
  const allVariants = ALL_MASK_MODES.filter((m) => m === "unmasked" || maskSupport[m]);
  const activeMasks = allVariants.filter((m) => state.selectedMaskModes.includes(m));
  const availableMasks = activeMasks.length > 0 ? activeMasks : allVariants;
  if (!availableMasks.includes(flatCfg.mask)) {
    flatCfg.mask = availableMasks[0] || "unmasked";
  }

  // 4. Bind LMUL directly from top search bar state
  flatCfg.lmul = state.lmul || "1";

  const standaloneCode = generateFlatSpecializedCode(entry, flatCfg);
  const godboltUrl = buildGodboltUrlForFlat(standaloneCode, flatCfg.isa, flatCfg.defines, flatCfg.scalarSize);

  let effectiveLvl = 1;
  let tierLabel = "L1 - Specialized Implementation";
  if (flatCfg.isa === "scalar") {
    effectiveLvl = 3;
    tierLabel = "L3 - Scalar Fallback";
  } else if (flatCfg.mask !== "unmasked" && flatCfg.isa !== "avx512") {
    effectiveLvl = 2;
    tierLabel = "L2 - Emulated with blend";
  } else if (Number(flatCfg.lmul) > 1) {
    effectiveLvl = 2;
    tierLabel = `L2 - Emulated LMUL=${flatCfg.lmul}`;
  } else if (entry.isa_support && entry.isa_support[flatCfg.isa]) {
    const byDt = entry.isa_support[flatCfg.isa].by_datatype || {};
    const dtLvl = byDt[flatCfg.dt] !== undefined ? byDt[flatCfg.dt] : entry.isa_support[flatCfg.isa].overall_level;
    effectiveLvl = dtLvl;
    tierLabel = dtLvl === 0 ? "L0 - Native Intrinsic" : `L${dtLvl} - Specialized Implementation`;
  }

  const lmulSuffix = (flatCfg.lmul && flatCfg.lmul !== "1") ? (flatCfg.lmul === "-2" ? "_m_half" : `_m${flatCfg.lmul}`) : "";
  const funcSig = `mipp_${flatCfg.isa}_${entry.name}_${flatCfg.dt}${flatCfg.mask !== "unmasked" ? `_${flatCfg.mask}` : ""}${lmulSuffix}`;

  return `
    <div class="mipp-flat-container">
      <!-- Specialization Toolbar -->
      <div class="mipp-flat-toolbar">
        <!-- Target SIMD Extension -->
        <div class="mipp-flat-row">
          <span class="mipp-flat-label">Target SIMD Ext:</span>
          <div class="mipp-flat-chips">
            ${effectiveExts.map((ext) => `
              <button class="mipp-flat-chip ${ext === flatCfg.isa ? "active" : ""}" data-flat-card="${entry.name}" data-flat-simd-ext="${ext}">
                ${(SIMD_EXT_DISPLAY_NAMES && SIMD_EXT_DISPLAY_NAMES[ext]) || ext.toUpperCase()}
              </button>
            `).join("")}
          </div>
        </div>

        <!-- Buffer Size or Features -->
        ${flatCfg.isa === "scalar"
          ? `
            <div class="mipp-flat-row">
              <span class="mipp-flat-label">Buffer Size:</span>
              <div class="mipp-flat-chips">
                ${SCALAR_BUFFER_SIZES.map((sz) => `
                  <button class="mipp-flat-chip ${sz === flatCfg.scalarSize ? "active" : ""}" data-flat-card="${entry.name}" data-flat-scalarsize="${sz}">
                    ${sz} bits
                  </button>
                `).join("")}
              </div>
            </div>
          `
          : (SIMD_EXT_FEATURE_DEFINES[flatCfg.isa] && SIMD_EXT_FEATURE_DEFINES[flatCfg.isa].length > 0
            ? `
              <div class="mipp-flat-row">
                <span class="mipp-flat-label">Features:</span>
                <div class="mipp-flat-chips">
                  ${SIMD_EXT_FEATURE_DEFINES[flatCfg.isa].map((flag) => {
                    const isLocked = flag.locked;
                    const isActive = isLocked || flatCfg.defines[flag.name] !== false;
                    return `
                      <button class="mipp-flag-chip ${isLocked ? "locked" : ""} ${isActive ? "active" : ""}"
                              data-flat-card="${entry.name}" data-flat-flag="${flag.name}"
                              title="${isLocked ? "Base architecture define (required)" : "Click to toggle feature define"}">
                        ${flag.name} ${isLocked ? "🔒" : (isActive ? "✓" : "✗")}
                      </button>
                    `;
                  }).join("")}
                </div>
              </div>
            `
            : ""
          )
        }

        <!-- Datatype -->
        <div class="mipp-flat-row">
          <span class="mipp-flat-label">Datatype:</span>
          <div class="mipp-flat-chips">
            ${availableDts.map((dt) => `
              <button class="mipp-flat-chip mipp-dt-badge ${getDtBadgeClass(dt)} ${dt === flatCfg.dt ? "active" : ""}" data-flat-card="${entry.name}" data-flat-dt="${dt}">
                ${dt}
              </button>
            `).join("")}
          </div>
        </div>

        <!-- Mask Variant -->
        <div class="mipp-flat-row">
          <span class="mipp-flat-label">Mask Variant:</span>
          <div class="mipp-flat-chips">
            ${availableMasks.map((m) => `
              <button class="mipp-mask-badge mask-${m} mipp-test-variant-btn ${m === flatCfg.mask ? "active" : ""}"
                      data-flat-card="${entry.name}" data-flat-mask="${m}" title="Click to view ${m} variant">
                ${m} ${m === flatCfg.mask ? "✓" : ""}
              </button>
            `).join("")}
          </div>
        </div>
      </div>

      <!-- Code Box with Integrated Header -->
      <div class="mipp-code-box">
        <div class="mipp-code-box-header">
          <div class="mipp-code-box-header-left" style="display: flex; gap: 0.5rem; align-items: center; flex-wrap: wrap;">
            <code style="font-size: 0.85rem; font-weight: 600; color: var(--md-default-fg-color);">${funcSig}</code>
            <span class="mipp-isa-badge lvl-${effectiveLvl}" title="Level ${effectiveLvl}: ${LEVEL_DESCRIPTIONS[effectiveLvl] || ""}">L${effectiveLvl}</span>
          </div>
          <div style="display: flex; gap: 0.5rem; align-items: center;">
            <a href="${godboltUrl}" target="_blank" rel="noopener noreferrer" class="mipp-godbolt-btn" title="Open and compile in Compiler Explorer">
              ⚡ Run in Compiler Explorer
            </a>
            <button class="mipp-icon-btn copy-proto-btn" data-copy="${escapeHtml(standaloneCode)}" title="Copy standalone C code">
              ${ICON_COPY}
            </button>
          </div>
        </div>
        <pre><code>${highlightCpp(standaloneCode, entry.scalar_macros || {})}</code></pre>
      </div>
    </div>
  `;
}
