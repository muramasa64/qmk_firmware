/* Copyright 2020 yushakobo
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H


// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY = 0,
  _DVORAK,
  _KEYPAD,
  _LOWER,
  _RAISE,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  EISU = SAFE_RANGE,
  KANA,
  ADJUST,
  RGBRST
};

#define QWERTY DF(_QWERTY)
#define DVORAK DF(_DVORAK)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define KEYPAD MO(_KEYPAD)
#define SNDS SFT_T(KC_SPC)
#define LTST KC_LANG8
#define RTST KC_LANG9
#define GLCB LGUI(KC_LCBR)
#define GRCB LGUI(KC_RCBR)
#define GLBR LGUI(KC_LBRC)
#define GRBR LGUI(KC_RBRC)
#define GPLS LGUI(KC_PLUS)
#define GMNS LGUI(KC_MINS)
#define MHME LCTL(KC_A)
#define MEND LCTL(KC_E)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | EISU | KANA |   N  |   M  |   ,  |   .  |   /  |  `   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust| Alt  | GUI  |Lower |TMBSFT|SandS |SandS |TMBSFT| Raise| GUI  | Alt  | Menu |Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS, \
      KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_MINS, \
      KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    EISU,    KANA,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_GRV, \
      KEYPAD, ADJUST, KC_LALT, KC_LGUI,  LOWER,    LTST,    SNDS,    SNDS,    RTST,   RAISE,    KC_RGUI, KC_RALT, KC_APP,  KC_ENT \
    ),
  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  | EISU | KANA |   B  |   M  |   W  |   V  |   Z  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust| Alt  | GUI  |Lower |TMBSFT|SandS |SandS |TMBSFT| Raise| GU I | Alt  | Menu |Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    EISU,    KANA,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_GRV, \
      KEYPAD, ADJUST, KC_LALT, KC_LGUI,  LOWER,    LTST,    SNDS,    SNDS,    RTST,   RAISE,    KC_RGUI, KC_RALT, KC_APP,  KC_ENT \
    ),
  /* KeyPad
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |   /  |   _  |   %  |   :  |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   *  |   7  |   8  |   9  |   E  |   F  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |   -  |   4  |   5  |   6  |   C  |   D  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |   +  |   1  |   2  |   3  |   A  |   B  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|      |      |      |      |      |      |      |      |   0  |   ,  |   .  |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_KEYPAD] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   KC_PSLS, KC_UNDS, KC_PERC, KC_COLN, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   KC_PAST, KC_7,    KC_8,    KC_9,    KC_E,    KC_F, \
      _______, _______, _______, _______, _______, _______,                   KC_PMNS, KC_4,    KC_5,    KC_6,    KC_C,    KC_D, \
      _______, _______, _______, _______, _______, _______, _______, _______, KC_PMNS, KC_1,    KC_2,    KC_3,    KC_A,    KC_B, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_0,    KC_COMM, KC_DOT,  _______, _______ \
    ),
  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |   _  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |GUI+{ |GUI+} |      |GUI++ |             |   {  |   }  |   +  |   /  |   \  |   =  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |GUI+[ |GUI+] |      |GUI+- |             |   [  |   ]  |   +  |   {  |   |  |   -  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   `  |   %  |   $  |   #  |   @  |   !  |   ~  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |Lower |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, KC_UNDS, \
      _______, _______, GLCB,    GRCB,    _______, GPLS,                      KC_LCBR, KC_RCBR, KC_PLUS, KC_SLSH, KC_BSLS, KC_EQL, \
      _______, _______, GLBR,    GLBR,    _______, GMNS,                      KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_PIPE, KC_MINS, \
      _______, _______, _______, _______, _______, _______, _______, KC_GRV,  KC_PERC, KC_DLR,  KC_HASH, KC_AT,   KC_EXLM, KC_TILD, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  | F10  | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |PageUp|Ctrl+A|  Up  |Ctrl+E| Lit+ | Vol+ |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      | Copy | Cut  | Paste|      |             |PageDn| Left | Down |Right | Lit- | Vol- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      | Mute |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |Raise |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12, \
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_PGUP, MHME,    KC_UP,   MEND,    KC_F15,  KC_VOLU, \
      _______, _______, KC_COPY, KC_CUT,  KC_PSTE, _______,                   KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_F14,  KC_VOLD, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, RAISE,   _______, _______, _______, _______, _______ \
      ),

  /* Adjust
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |Qwerty|Dvorak|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|      |EEPRST|      |      |             | Win  |Aud on|RGB on|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |Adjust|      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   QWERTY,  DVORAK,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
      XXXXXXX, RESET,   XXXXXXX, EEP_RST, XXXXXXX, XXXXXXX,                   AG_SWAP, AU_ON,   RGB_TOG, RGBRST,  XXXXXXX, XXXXXXX, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, AG_NORM,                   AG_NORM, AU_OFF,  RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, \
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, \
      XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
      )

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left side encoder */
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) { /* Right side encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case EISU:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LANG2);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if (is_mac_mode()) {
          register_code(KC_LANG1);
        }else{
          tap_code16(LALT(KC_GRAVE));
        }
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_LOWER);
        layer_on(_RAISE);
      } else {
        layer_off(_LOWER);
        layer_off(_RAISE);
      }
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
