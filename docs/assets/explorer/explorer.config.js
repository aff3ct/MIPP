/**
 * MIPP API Explorer - Configuration & UI Assets
 */

export function escapeHtml(str) {
  if (str === null || str === undefined) return "";
  return String(str)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/"/g, "&quot;")
    .replace(/'/g, "&#039;");
}

export const ICON_SEARCH = `<svg class="mipp-search-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2"><circle cx="11" cy="11" r="8"></circle><line x1="21" y1="21" x2="16.65" y2="16.65"></line></svg>`;

export const ICON_ALL = `<svg class="mipp-action-icon" viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="3" width="18" height="18" rx="3" ry="3"></rect><polyline points="8 12 11 15 16 9"></polyline></svg>`;

export const ICON_CLEAR = `<svg class="mipp-action-icon" viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><rect x="3" y="3" width="18" height="18" rx="3" ry="3"></rect></svg>`;

export const ICON_UNION = `<svg class="mipp-action-icon mipp-union-icon" viewBox="0 0 24 24" width="15" height="15" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round"><path d="M6 5v8a6 6 0 0 0 12 0V5"></path></svg>`;

export const ICON_INTERSECT = `<svg class="mipp-action-icon mipp-intersect-icon" viewBox="0 0 24 24" width="15" height="15" fill="none" stroke="currentColor" stroke-width="2.4" stroke-linecap="round" stroke-linejoin="round"><path d="M6 19v-8a6 6 0 0 1 12 0v8"></path></svg>`;

export const ICON_COPY = `<svg class="mipp-copy-icon" viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round"><rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect><path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path></svg>`;

export const ICON_CHECK = `<svg class="mipp-copy-icon" viewBox="0 0 24 24" width="14" height="14" fill="none" stroke="#10b981" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="20 6 9 17 4 12"></polyline></svg>`;

export const ICON_CHEVRON = `<svg class="mipp-chevron" viewBox="0 0 24 24" width="10" height="10" fill="none" stroke="currentColor" stroke-width="2.2" stroke-linecap="round" stroke-linejoin="round"><polyline points="6 9 12 15 18 9"></polyline></svg>`;

// Monochrome line icons (same stroke style as above), in place of emojis:
// they follow the text color and the light / dark scheme
const lineIcon = (size, body, cls = "mipp-ui-icon") =>
  `<svg class="${cls}" viewBox="0 0 24 24" width="${size}" height="${size}" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round" aria-hidden="true">${body}</svg>`;

const SETTINGS_BODY = `<circle cx="12" cy="12" r="3"></circle><path d="M19.4 15a1.65 1.65 0 0 0 .33 1.82l.06.06a2 2 0 1 1-2.83 2.83l-.06-.06a1.65 1.65 0 0 0-1.82-.33 1.65 1.65 0 0 0-1 1.51V21a2 2 0 1 1-4 0v-.09A1.65 1.65 0 0 0 9 19.4a1.65 1.65 0 0 0-1.82.33l-.06.06a2 2 0 1 1-2.83-2.83l.06-.06A1.65 1.65 0 0 0 4.68 15a1.65 1.65 0 0 0-1.51-1H3a2 2 0 1 1 0-4h.09A1.65 1.65 0 0 0 4.6 9a1.65 1.65 0 0 0-.33-1.82l-.06-.06a2 2 0 1 1 2.83-2.83l.06.06A1.65 1.65 0 0 0 9 4.68a1.65 1.65 0 0 0 1-1.51V3a2 2 0 1 1 4 0v.09a1.65 1.65 0 0 0 1 1.51 1.65 1.65 0 0 0 1.82-.33l.06-.06a2 2 0 1 1 2.83 2.83l-.06.06A1.65 1.65 0 0 0 19.4 9a1.65 1.65 0 0 0 1.51 1H21a2 2 0 1 1 0 4h-.09a1.65 1.65 0 0 0-1.51 1z"></path>`;
const LINK_BODY = `<path d="M10 13a5 5 0 0 0 7.54.54l3-3a5 5 0 0 0-7.07-7.07l-1.72 1.71"></path><path d="M14 11a5 5 0 0 0-7.54-.54l-3 3a5 5 0 0 0 7.07 7.07l1.71-1.71"></path>`;
const MAGNIFIER_BODY = `<circle cx="11" cy="11" r="7"></circle><line x1="21" y1="21" x2="16" y2="16"></line>`;
const WARNING_BODY = `<path d="M10.29 3.86 1.82 18a2 2 0 0 0 1.71 3h16.94a2 2 0 0 0 1.71-3L13.71 3.86a2 2 0 0 0-3.42 0z"></path><line x1="12" y1="9" x2="12" y2="13"></line><line x1="12" y1="17" x2="12.01" y2="17"></line>`;
const INFO_BODY = `<circle cx="12" cy="12" r="10"></circle><line x1="12" y1="16" x2="12" y2="12"></line><line x1="12" y1="8" x2="12.01" y2="8"></line>`;
const SLIDERS_BODY = `<line x1="4" y1="21" x2="4" y2="14"></line><line x1="4" y1="10" x2="4" y2="3"></line><line x1="12" y1="21" x2="12" y2="12"></line><line x1="12" y1="8" x2="12" y2="3"></line><line x1="20" y1="21" x2="20" y2="16"></line><line x1="20" y1="12" x2="20" y2="3"></line><line x1="1" y1="14" x2="7" y2="14"></line><line x1="9" y1="8" x2="15" y2="8"></line><line x1="17" y1="16" x2="23" y2="16"></line>`;
const CLOCK_BODY = `<circle cx="12" cy="12" r="10"></circle><polyline points="12 6 12 12 16 14"></polyline>`;

const GRIP_BODY = `<circle cx="9" cy="5" r="1"></circle><circle cx="9" cy="12" r="1"></circle><circle cx="9" cy="19" r="1"></circle><circle cx="15" cy="5" r="1"></circle><circle cx="15" cy="12" r="1"></circle><circle cx="15" cy="19" r="1"></circle>`;

export const ICON_GRIP = lineIcon(14, GRIP_BODY);
export const ICON_SETTINGS = lineIcon(16, SETTINGS_BODY);
export const ICON_LINK = lineIcon(16, LINK_BODY);
export const ICON_INSPECT = lineIcon(14, MAGNIFIER_BODY);
export const ICON_NO_RESULTS = lineIcon(40, MAGNIFIER_BODY, "mipp-ui-icon mipp-no-results-icon");
export const ICON_WARNING = lineIcon(16, WARNING_BODY);
export const ICON_WARNING_SM = lineIcon(12, WARNING_BODY);
export const ICON_INFO = lineIcon(16, INFO_BODY);
export const ICON_CONTEXT = lineIcon(16, SLIDERS_BODY);
export const ICON_CLOCK = lineIcon(16, CLOCK_BODY);

// "Run in Godbolt" button: play triangle, green like the Godbolt logo
export const ICON_RUN = `<svg class="mipp-godbolt-icon mipp-run-icon" viewBox="0 0 24 24" width="14" height="14" fill="#16a34a" aria-hidden="true"><path d="M7 4.5v15a1 1 0 0 0 1.53.85l12-7.5a1 1 0 0 0 0-1.7l-12-7.5A1 1 0 0 0 7 4.5z"/></svg>`;

export const ICON_GODBOLT = `<svg class="mipp-godbolt-icon" viewBox="20 20 235 235" width="14" height="14" xmlns="http://www.w3.org/2000/svg"><path fill="#67c52a" d="M228.18 192.43c-1.1-2.1-1.1-4.6 0-6.6 1.4-2.5 2.6-5 3.8-7.6.8-1.9-.5-4-2.6-4h-22.5c-2.3 0-4.5 1.2-5.7 3.1-2.9 4.4-6.3 8.7-10.1 12.5-14.5 14.5-33.7 22.4-54.1 22.4-20.5 0-39.7-8-54.1-22.4-14.6-14.4-22.5-33.6-22.5-54.1s8-39.7 22.4-54.1c14.5-14.5 33.7-22.4 54.1-22.4 20.5 0 39.7 8 54.1 22.4 3.9 3.9 7.2 8.1 10.1 12.5 1.3 1.9 3.4 3.1 5.7 3.1h22.6c2.1 0 3.4-2.1 2.6-4-1.2-2.6-2.4-5.1-3.8-7.6-1.1-2.1-1.1-4.6 0-6.6l7.6-13.8c1.5-2.7 1-6-1.2-8.2l-19.1-19.1c-2.2-2.2-5.5-2.6-8.2-1.2l-13.9 7.7c-2.1 1.1-4.6 1.1-6.6 0-6.6-3.6-13.6-6.5-20.8-8.6-2.3-.7-4.1-2.4-4.7-4.7l-4.4-15.2c-.9-2.9-3.5-5-6.6-5h-27c-3.1 0-5.8 2-6.6 5l-4.4 15.2c-.7 2.3-2.4 4-4.7 4.7-7.2 2.1-14.2 5-20.8 8.6-2.1 1.1-4.6 1.2-6.6 0l-13.9-7.7c-2.7-1.5-6-1-8.2 1.2l-19.1 19.1c-2.2 2.2-2.6 5.5-1.2 8.2l7.7 13.9c1.1 2.1 1.1 4.6 0 6.6-3.6 6.6-6.5 13.6-8.6 20.8-.7 2.3-2.4 4.1-4.7 4.7l-15.2 4.4c-2.9.9-5 3.5-5 6.6v27c0 3.1 2 5.8 5 6.6l15.2 4.4c2.3.7 4 2.4 4.7 4.7 2.1 7.2 5 14.2 8.6 20.8 1.1 2.1 1.2 4.6 0 6.6l-7.7 13.9c-1.5 2.7-1 6 1.2 8.2l19.1 19.1c2.2 2.2 5.5 2.6 8.2 1.2l13.9-7.7c2.1-1.1 4.6-1.1 6.6 0 6.6 3.6 13.6 6.5 20.8 8.6 2.3.7 4.1 2.4 4.7 4.7l4.4 15.2c.9 2.9 3.5 5 6.6 5h27c3.1 0 5.8-2 6.6-5l4.4-15.2c.7-2.3 2.4-4 4.7-4.7 7.2-2.1 14.2-5 20.8-8.6 2.1-1.1 4.6-1.2 6.6 0l13.9 7.7c2.7 1.5 6 1 8.2-1.2l19.1-19.1c2.2-2.2 2.6-5.5 1.2-8.2z"/><path fill="currentColor" d="M91.08 96.83h92.7v17.2h-92.7zm0 30.6h76.4v17.2h-76.4zm0 30.6h92.7v17.2h-92.7z"/></svg>`;

export const SCALAR_BUFFER_SIZES = [64, 128, 256, 512, 1024, 2048];
export const VALID_CARD_TABS = ["hw", "proto", "scalar", "specs"];

export function showToast(message = "Copied to clipboard!") {
  if (typeof document === "undefined") return;
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

export async function copyToClipboard(text, message = null) {
  try {
    if (typeof navigator !== "undefined" && navigator.clipboard && window.isSecureContext) {
      await navigator.clipboard.writeText(text);
    } else if (typeof document !== "undefined") {
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
    if (message) {
      showToast(message);
    }
  } catch (err) {
    console.error("Failed to copy:", err);
  }
}
