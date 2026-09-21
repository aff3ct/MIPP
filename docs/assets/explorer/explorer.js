/**
 * MIPP API Explorer - Entrypoint Bridge
 * Dynamically loads the modular ES6 architecture.
 */
import("./main.js").catch((err) => {
  console.error("Failed to load MIPP Explorer ES modules:", err);
});
