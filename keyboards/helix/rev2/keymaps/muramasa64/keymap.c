#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

#include <naginata.h>
NGKEYS naginata_keys;

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_number {
    _QWERTY = 0,
    _DVORAK,
    _NAGINATA,
    _KEYPAD,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = NG_SAFE_RANGE,
  DVORAK,
  NAGINATA,
  KEYPAD,
  KC_xEISU,
  KC_xKANA,
  RGBRST,
  LCTOGL,
  NAGINATA_USE,
};
enum combo_events {
  NAGINATA_ON_CMB,
  NAGINATA_OFF_CMB,
};

const uint16_t PROGMEM ngon_combo[] = {KC_H, KC_J, COMBO_END};
const uint16_t PROGMEM ngoff_combo[] = {KC_F, KC_G, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [NAGINATA_ON_CMB] = COMBO_ACTION(ngon_combo),
  [NAGINATA_OFF_CMB] = COMBO_ACTION(ngoff_combo),
};

// IME ONのcombo
void process_combo_event(uint8_t combo_index, bool pressed) {
  switch(combo_index) {
    case NAGINATA_ON_CMB:
      if (pressed) {
        naginata_on();
      }
      break;
    case NAGINATA_OFF_CMB:
      if (pressed) {
        naginata_off();
      }
      break;
  }
}

//Macros
#define KC_LOWER  MO(_LOWER)
#define KC_RAISE  MO(_RAISE)
#define KC_RABS   LT(_RAISE,KC_BSPC)
#define KC_RAEN   LT(_RAISE,KC_ENT)
#define KC_____   _______
#define KC_XXXX   XXXXXXX
#define KC_ADJ    MO(_ADJUST)
#define KC_LSMI   LSFT(KC_MINS)
#define KC_LSEQ   LSFT(KC_EQL)
#define KC_LSRB   LSFT(KC_RBRC)
#define KC_LSLB   LSFT(KC_LBRC)
#define KC_SNDS   SFT_T(KC_SPC)
#define KC_LTST   KC_LANG8
#define KC_RTST   KC_LANG9
#define KC_MKPD   MO(_KEYPAD)
#define KC_GLCB   LGUI(KC_LCBR)
#define KC_GRCB   LGUI(KC_RCBR)
#define KC_GLBR   LGUI(KC_LBRC)
#define KC_GRBR   LGUI(KC_RBRC)
#define KC_GPLS   LGUI(KC_PLUS)
#define KC_GMNS   LGUI(KC_MINS)
#define KC_MHME   LCTL(KC_A)
#define KC_MEND   LCTL(KC_E)
#define ___       _______
#define NGNTUSE   NAGINATA_USE

#if MATRIX_ROWS == 10 // HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  \   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  | Ctrl |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | EISU | KANA |   N  |   M  |   ,  |   .  |   /  | Shift|
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust|  Alt |  GUI | Lower|TMBSFT| SandS| SandS|TMBSFT| Raise| GUI  |  Alt | Menu |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT_kc( \
      ESC,    1,    2,    3,    4,    5,                  6,    7,    8,    9,    0,  BSPC, \
      TAB,    Q,    W,    E,    R,    T,                  Y,    U,    I,    O,    P,  BSLS, \
      LCTL,   A,    S,    D,    F,    G,                  H,    J,    K,    L, SCLN,  RCTL, \
      LSFT,   Z,    X,    C,    V,    B,  xEISU, xKANA,   N,    M, COMM,  DOT, SLSH,  RSFT, \
      MKPD, ADJ, LALT, LGUI, LOWER, LTST, SNDS,   SNDS, RTST, RAISE, RGUI, RALT, APP,  ENT \
      ),

  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  | EISU | KANA |   B  |   M  |   W  |   V  |   Z  |  `   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust|  Alt |  GUI | Lower|TMBSFT| SandS| SandS|TMBSFT| Raise| GUI  |  Alt | Menu |Lower |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT_kc( \
      ESC,     1,    2,    3,    4,    5,                  6,    7,    8,    9,    0, BSPC, \
      TAB,  QUOT, COMM,  DOT,    P,    Y,                  F,    G,    C,    R,    L, SLSH, \
      LCTL,    A,    O,    E,    U,    I,                  D,    H,    T,    N,    S, MINS, \
      LSFT, SCLN,    Q,    J,    K,    X, xEISU, xKANA,    B,    M,    W,    V,    Z,  GRV, \
      MKPD, ADJ, LALT, LGUI, LOWER, LTST, SNDS,   SNDS, RTST, RAISE, RGUI, RALT, APP,  ENT \
      ),

  /* Naginata
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | EISU | KANA |   N  |   M  |   ,  |   .  |   /  |  `   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust|  Alt |  GUI | Lower| SandS| SandS| SandS| SpSft| Raise| GUI  |  Alt | Menu |Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_NAGINATA] = LAYOUT_kc( \
      ESC,    1,    2,    3,    4,    5,                  6,    7,    8,    9,    0,  BSPC, \
      TAB, NG_Q, NG_W, NG_E, NG_R, NG_T,               NG_Y, NG_U, NG_I, NG_O, NG_P,  SLSH, \
      LCTL,NG_A, NG_S, NG_D, NG_F, NG_G,               NG_H, NG_J, NG_K, NG_L, NG_SCLN,  MINS, \
      LSFT,NG_Z, NG_X, NG_C, NG_V, NG_B, xEISU, xKANA, NG_N, NG_M, NG_COMM, NG_DOT, NG_SLSH, GRV, \
      MKPD, ADJ, LALT, LGUI, LOWER, NG_SHFT, SNDS, SNDS, NG_SHFT, RAISE, RGUI, RALT, APP,  ENT \
      ),
  /* Keypad
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

  [_KEYPAD] = LAYOUT_kc( \
      ____, ____, ____, ____, ____, ____,               PSLS, UNDS, PERC, COLN, ____, ____, \
      ____, ____, ____, ____, ____, ____,               PAST,    7,    8,    9,    E,    F, \
      ____, ____, ____, ____, ____, ____,               PMNS,    4,    5,    6,    C,    D, \
      ____, ____, ____, ____, ____, ____, ____, ____,   PPLS,    1,    2,    3,    A,    B, \
      ____, ____, ____, ____, ____, ____, ____, ____,   ____,    0, COMM,  DOT, ____, ____ \
      ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |   ^  |   &  |   *  |      |      |   _  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |GUI+{ |GUI+} |      |GUI++ |             |   {  |   }  |   +  |   /  |   \  |   =  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |GUI+[ |GUI+] |      |GUI+- |             |   [  |   ]  |   (  |   )  |   |  |   -  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |   `  |   %  |   $  |   #  |   @  |   !  |   ~  |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |Lower |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_LOWER] = LAYOUT_kc( \
      ____, ____, ____, ____, ____, ____,             CIRC, AMPR, ASTR, ____, ____, UNDS, \
      ____, ____, GLCB, GRCB, ____, GPLS,             LCBR, RCBR, PLUS, SLSH, BSLS,  EQL, \
      ____, ____, GLBR, GLBR,  DEL, GMNS,             LBRC, RBRC, LPRN, RPRN, PIPE, MINS, \
      ____, ____, ____, ____, ____, ____, ____,  GRV, PERC,  DLR, HASH,   AT, EXLM, TILD, \
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  | F10  | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |  !   |  @   |  #   |  $   |  %   |             |PageUp|Ctr+A |  Up  |Ctr+E | Lit+ | Vol+ |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      | Copy | Cut  | Paste|      |             |PageDn| Left | Down |Right | Lit- | Vol- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      | Mute |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |Raise |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT_kc( \
        F1,   F2,   F3,   F4,   F5,   F6,               F7,   F8,   F9,  F10,  F11,  F12, \
      TILD, EXLM,   AT, HASH,  DLR, PERC,             PGUP, MHME,   UP, MEND,  F15, _VOLUP, \
      ____, ____,  CUT, COPY, PSTE, ____,             PGDN, LEFT, DOWN, RGHT,  F14, _VOLDOWN, \
      ____, ____, ____, ____, ____, ____, ____, xKANA,xKANA,MNXT, VOLD, VOLU, ____, _MUTE, \
      ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____, ____ \
      ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |NGNTUS|Keypad|Dvorak|      |      |Qwerty|             |Qwerty|      |      |Dvorak|Keypad|NGNTUS|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|RGB ON|Aud on| Win  |             | Win  |Aud on|RGB ON|RGBRST|      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | HUE+ | SAT+ | VAL+ |RGB md|Audoff| Mac  |             | Mac  |Audoff|RGB md| VAL+ | SAT+ | HUE+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | HUE- | SAT- | VAL- |      |      |      |      |      |      |      |      | VAL- | SAT- | HUE- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      NGNTUSE, KEYPAD,  DVORAK,  XXXXXXX, XXXXXXX,  QWERTY,          QWERTY,  XXXXXXX, XXXXXXX,  DVORAK,  KEYPAD, NGNTUSE, \
      XXXXXXX, RESET,   RGBRST,  RGB_TOG,   AU_ON, AG_SWAP,          AG_SWAP,   AU_ON, RGB_TOG,  RGBRST, XXXXXXX, XXXXXXX, \
      RGB_HUI, RGB_SAI, RGB_VAI, RGB_MOD,  AU_OFF, AG_NORM,          AG_NORM,  AU_OFF, RGB_MOD, RGB_VAI, RGB_SAI, RGB_HUI, \
      RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, RGB_VAD, RGB_SAD, RGB_HUD, \
      _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, ___,___, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______ \
   )
};

#else
#error "undefined keymaps"
#endif


#ifdef AUDIO_ENABLE

float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

static int current_default_layer;

uint32_t default_layer_state_set_kb(uint32_t state) {
    // 1<<_QWERTY  - 1 == 1 - 1 == _QWERTY (=0)
    // 1<<_DVORAK - 1 == 2 - 1 == _DVORAK (=1)
    current_default_layer = state - 1;
    // 1<<_NAGINATA  - 2 == 4 - 2 == _NAGINATA (=2)
    if ( current_default_layer == 3 ) current_default_layer -= 1;
    // 1<<_KEYPAD - 5 == 8 - 5 == _KEYPAD (=3)
    if ( current_default_layer == 7 ) current_default_layer -= 4;
    return state;
}

void update_base_layer(int base)
{
    if( current_default_layer != base ) {
        eeconfig_update_default_layer(1UL<<base);
        default_layer_set(1UL<<base);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        update_base_layer(_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_DVORAK);
      }
      return false;
      break;
    case KEYPAD:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        update_base_layer(_KEYPAD);
      }
      return false;
      break;
    case KC_xEISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
        naginata_off();
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KC_xKANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
        naginata_on();
      } else {
        unregister_code(KC_LANG1);
      }
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
    case LCTOGL:
      if (record->event.pressed) {
        mac_live_conversion_toggle();
      }
      return false;
      break;
    case NAGINATA_USE:
      if (record->event.pressed) {
        naginata_use_toggle();
      }
      return false;
      break;
  }
  if (!process_naginata(keycode, record)) {
    return false;
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
    set_naginata(_NAGINATA);
    #ifdef NAGINATA_EDIT_MAC
    set_unicode_input_mode(UC_OSX);
    #endif
    #ifdef NAGINATA_EDIT_WIN
    set_unicode_input_mode(UC_WINC);
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

void matrix_scan_user(void) {
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
#ifdef RGBLIGHT_ENABLE
  char buf[30];
  if (RGBLIGHT_MODES > 1 && rgblight_config.enable) {
      snprintf(buf, sizeof(buf), " LED %2d: %d,%d,%d ",
               rgblight_config.mode,
               rgblight_config.hue/RGBLIGHT_HUE_STEP,
               rgblight_config.sat/RGBLIGHT_SAT_STEP,
               rgblight_config.val/RGBLIGHT_VAL_STEP);
      matrix_write(matrix, buf);
  }
#endif
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}

static const char Qwerty_name[]  PROGMEM = " Qwerty";
static const char Dvorak_name[]  PROGMEM = " Dvorak";
static const char Naginata_name[] PROGMEM = " Naginata";
static const char Keypad_name[]  PROGMEM = " Keypad";

static const char Lower_name[]   PROGMEM = ":Lower";
static const char Raise_name[]   PROGMEM = ":Raise";
static const char Adjust_name[]  PROGMEM = ":Adjust";

static const char *layer_names[] = {
    [_QWERTY] = Qwerty_name,
    [_DVORAK] = Dvorak_name,
    [_NAGINATA]= Naginata_name,
    [_KEYPAD] = Keypad_name,
    [_LOWER]  = Lower_name,
    [_RAISE]  = Raise_name,
    [_ADJUST] = Adjust_name
};

void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  int name_num;
  uint32_t lstate;
  matrix_write_P(matrix, layer_names[current_default_layer]);
  matrix_write_P(matrix, PSTR("\n"));
  for( lstate = layer_state, name_num = 0;
       lstate && name_num < sizeof(layer_names)/sizeof(char *);
       lstate >>=1, name_num++ ) {
      if( (lstate & 1) != 0 ) {
          if( layer_names[name_num] ) {
              matrix_write_P(matrix, layer_names[name_num]);
          }
      }
  }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
             (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
             (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
             (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif
