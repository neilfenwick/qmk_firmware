# Lily58 QMK Customisation Checklist

This checklist will guide you through customising your Lily58 keyboard to closely match the home-row mod and layer-tap (LT) behaviour of your Ferris Sweep. The process covers config migration, tuning for heavier switches/slower typing, and resolving issues like missing spacebar key repeat.

---

## Pre-requisites

- [ ] task 1: Confirm a working QMK build environment (Python, QMK CLI, dependencies)
- [ ] task 2: Clone the [QMK firmware repository](https://github.com/qmk/qmk_firmware) if not already present

---

## Keymap and Config Migration

- [ ] task 3: Create a new keymap folder for your Lily58, e.g. `keyboards/mechboards/lily58/pro/keymaps/neil/`
- [ ] task 4: Export your current Lily58 layout from `lily58.layout.json` to a new `keymap.c` in that folder. (Tip: Use QMK’s `json2c` tool if needed)
- [ ] task 5: Transfer home-row mod logic and mapping from your Ferris Sweep keymap, adapting key positions for the Lily58

---

## Critical Behavioural Settings

- [ ] task 6: Create or edit a `config.h` file in your Mechboards Lily58 Pro keymap folder
- [ ] task 7: Set the tapping term: `#define TAPPING_TERM 225` (adjust to match your Sweep or taste)
- [ ] task 8: Add `#define IGNORE_MOD_TAP_INTERRUPT` to `config.h`
- [ ] task 9: Add `#define TAPPING_FORCE_HOLD` to `config.h`
- [ ] task 10: (Optional) Add `#define TAPPING_TERM_PER_KEY` for per-key tuning
- [ ] task 11: (Optional) In `keymap.c`, implement `get_tapping_term()` for specific mods (example below)

### Example `config.h`:
```c
#pragma once
#define TAPPING_TERM 225
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_FORCE_HOLD
// #define PERMISSIVE_HOLD  // (leave commented or omit)
#define TAPPING_TERM_PER_KEY  // (optional)
```

### Example `get_tapping_term()`:
```c
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MT(MOD_LALT, KC_S):
        case MT(MOD_LSFT, KC_D):
        case MT(MOD_LCTL, KC_F):
        case MT(MOD_LGUI, KC_G):
        case MT(MOD_LALT, KC_L):
        case MT(MOD_LSFT | MOD_RSFT, KC_K):
        case MT(MOD_LCTL | MOD_RCTL, KC_J):
        case MT(MOD_LGUI, KC_H):
            return 245; // or your preferred value
        default:
            return TAPPING_TERM;
    }
}
```

---

## Fixing LT (Space/Layer-Tap) Key Repeat

- [ ] task 12: Test if `LT(1, KC_SPC)` repeats as expected after applying above settings
- [ ] task 13: If not, update to the latest QMK firmware (`git pull` in your QMK repo)
- [ ] task 14: If still broken, implement a workaround (e.g., custom `process_record_user` handler or tap dance for space/layer tap)

---

## Compile and Flash (Mechboards Pro RP2040/Elite-Pi)

- [ ] task 15: Compile custom Lily58 firmware:
    ```
    qmk compile -kb mechboards/lily58/pro -km neil -e CONVERT_TO=elite_pi
    ```
    - The output file will be `.build/mechboards_lily58_pro_neil_elite_pi.uf2`.
- [ ] task 16: Flash both halves (one at a time via reset/bootloader):
    - Double-tap RESET on each half to enter UF2 bootloader mode
    - Copy the `.uf2` file to the RPI-RP2 drive that appears
- [ ] task 17: Confirm flashing is successful and all key behaviour is as intended

---

## Testing and Tuning

- [ ] task 18: Test home-row mod and LT behaviour at your usual typing speed
- [ ] task 19: Adjust `TAPPING_TERM` and per-key values further if accidental mods/holds persist
- [ ] task 20: Backup/document your final config

---

## Optional Advanced Tweaks

- [ ] task 21: (Optional) Add combo settings like `#define COMBO_TERM 35` if you use key combos
- [ ] task 22: (Optional) Enable or disable extra QMK features (RGB, power saving, etc.) as desired

---

## Notes

- QMK Configurator and VIA cannot change tap/hold timing or advanced settings—flashing custom firmware is required
- Flash both halves unless your wiring supports single-side flashing
