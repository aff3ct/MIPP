#!/usr/bin/env python3
import json
import sys

def check_json_key_order(file_path):
    with open(file_path, 'r', encoding='utf-8') as f:
        data = json.load(f)
    
    keys = list(data.keys())
    sorted_keys = sorted(keys)
    
    print(f"=== Audit Report for: {file_path} ===")
    
    misordered_keys = []
    for i, key in enumerate(keys):
        prev_key = keys[i-1] if i > 0 else ""
        if prev_key > key:
            misordered_keys.append((i, key, prev_key))
            
    if not misordered_keys:
        print("✓ All top-level keys are correctly sorted lexicographically!\n")
        return

    print(f"Found {len(misordered_keys)} key ordering violation(s):\n")
    for idx, key, prev in misordered_keys:
        expected_pos = sorted_keys.index(key)
        print(f"  • Key #{idx+1} '{key}' comes AFTER '{prev}'")
        print(f"    └─> Correct lexicographical position should be Index #{expected_pos+1} (near '{sorted_keys[max(0, expected_pos-1)]}')")
    print()

if __name__ == "__main__":
    target_files = sys.argv[1:] if len(sys.argv) > 1 else [
        "generator/helpers_headers/generic_emu_templates.json"
    ]
    for filepath in target_files:
        check_json_key_order(filepath)

