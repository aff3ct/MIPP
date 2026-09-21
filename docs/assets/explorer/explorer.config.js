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

export const SCALAR_BUFFER_SIZES = [64, 128, 256, 512, 1024, 2048];
export const VALID_CARD_TABS = ["hw", "proto", "scalar", "specs", "flat", "example"];

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
