/**
 * MIPP Documentation - "Search in the API Explorer" link
 * Adds, at the top of the search results, a link that runs the same query in
 * the API Explorer (explorer/#q=...). The site search does not index the
 * vendor intrinsics (e.g. _mm256_fmadd_ps): the Explorer finds the MIPP
 * functions that use them.
 *
 * On the Explorer page itself, the link does not navigate (only the hash would
 * change): the search closes and the query goes to the search bar of the
 * Explorer, which gets the focus.
 */

(function () {
  const LINK_ID = "mipp-search-explorer-link";
  let currentQuery = "";

  function explorerUrl(query) {
    // The logo links to the home page, whatever the depth of the current page
    const home = document.querySelector(".md-header__button.md-logo");
    const url = new URL("explorer/", home ? home.href : window.location.href);
    url.hash = "q=" + encodeURIComponent(query);
    return url.href;
  }

  // Closes the search (Material #__search toggle)
  function closeSearch() {
    const toggle = document.getElementById("__search");
    if (toggle && toggle.checked) toggle.click();
    const input = document.querySelector(".md-search__input");
    if (input) input.blur();
  }

  function onLinkClick(e) {
    const explorerInput = document.getElementById("mipp-search-input");
    if (!explorerInput) return; // another page: regular navigation to the Explorer
    // Also keep the click from the instant navigation of Material (listener on
    // the document), which would reload the page and remount the Explorer
    e.preventDefault();
    e.stopPropagation();
    const query = currentQuery;
    closeSearch();
    explorerInput.value = query;
    // The Explorer filters on its "input" event (debounced), like when typing
    explorerInput.dispatchEvent(new Event("input", { bubbles: true }));
    explorerInput.focus();
    explorerInput.setSelectionRange(query.length, query.length);
  }

  function update() {
    const input = document.querySelector(".md-search__input");
    const meta = document.querySelector(".md-search-result__meta");
    if (!input || !meta) return;

    let link = document.getElementById(LINK_ID);
    currentQuery = input.value.trim();
    if (!currentQuery) {
      if (link) link.remove();
      return;
    }
    if (!link) {
      link = document.createElement("a");
      link.id = LINK_ID;
      link.className = "mipp-search-explorer-link";
      link.addEventListener("click", onLinkClick);
    }
    if (link.previousElementSibling !== meta) meta.insertAdjacentElement("afterend", link);
    link.href = explorerUrl(currentQuery);
    link.textContent = `Search “${currentQuery}” in the API Explorer (functions and vendor intrinsics) →`;
  }

  function init() {
    const input = document.querySelector(".md-search__input");
    const meta = document.querySelector(".md-search-result__meta");
    if (!input || !meta) return;
    input.addEventListener("input", update);
    // The result count is rewritten after each search: keep the link in sync
    new MutationObserver(update).observe(meta, { childList: true, characterData: true, subtree: true });
    update();
  }

  if (document.readyState === "loading") {
    document.addEventListener("DOMContentLoaded", init);
  } else {
    init();
  }
})();
