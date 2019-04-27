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
    _KEYPAD,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  KEYPAD,
  EISU,
  KANA,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};


// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros
#define M_SAMPLE M(KC_SAMPLEMACRO)

#if HELIX_ROWS == 5
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | ESC  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  |  BS  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |  [   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  | EISU | KANA |   N  |   M  |   ,  |   .  |   /  |  `   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust| Alt  | GUI  |LANG8 |Lower |KeyPad|Space |Raise |LANG9 | GUI  | Alt  |GuiAlt|Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_QWERTY] = LAYOUT( \
      KC_ESC,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,              KC_6,    KC_7,   KC_8,    KC_9,   KC_0,    KC_BSPC, \
      KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,   KC_I,    KC_O,   KC_P,    KC_LBRC, \
      KC_LCTL,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  EISU, KANA, KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_GRV, \
      MO(_KEYPAD), MO(_ADJUST), KC_LALT, KC_LGUI, KC_LANG8, LT(_LOWER,KC_BSPC), MO(_KEYPAD), \
                                                   SFT_T(KC_SPC), LT(_RAISE,KC_ENT), KC_LANG9, KC_RGUI, KC_RALT, RGUI(KC_RALT), KC_ENT \
      ),

  /* Dvorak
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |      |      |      |      |      |             |      |      |      |      |      | Bksp |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   '  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  |  /   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Ctrl |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  -   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * | Shift|   ;  |   Q  |   J  |   K  |   X  | EISU | KANA |   B  |   M  |   W  |   V  |   Z  |  `   |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |KeyPad|Adjust| Alt  | GUI  | LANG8| Lower|KeyPad| Space| Raise| LANG9| GUI  | Alt  |GuiSft|Enter |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_DVORAK] = LAYOUT( \
      KC_ESC,  KC_1,    KC_2,    KC_3,   KC_4,    KC_5,             KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, \
      KC_TAB,  KC_QUOT, KC_COMM, KC_DOT, KC_P,    KC_Y,             KC_F, KC_G, KC_C, KC_R, KC_L, KC_SLSH, \
      KC_LCTL, KC_A,    KC_O,    KC_E,   KC_U,    KC_I,             KC_D, KC_H, KC_T, KC_N, KC_S, KC_MINS, \
      KC_LSFT, KC_SCLN, KC_Q,    KC_J,   KC_K,    KC_X, EISU, KANA, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_GRV, \
      MO(_KEYPAD), MO(_ADJUST), KC_LALT, KC_LGUI, KC_LANG8, LT(_LOWER,KC_BSPC), MO(_KEYPAD), \
                                                   SFT_T(KC_SPC), LT(_RAISE,KC_ENT), KC_LANG9, KC_RGUI, KC_RALT, RGUI(KC_RSFT), KC_ENT \
      ),

  /* KeyPad (Drovak)
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
      _______,  _______, _______, _______, _______, _______,                   KC_PSLS, KC_UNDS, KC_PERC, KC_COLN, _______, _______, \
      _______,  _______, _______, _______, _______, _______,                   KC_PAST, KC_P7,   KC_P8,   KC_P9,   KC_E,    KC_F, \
      _______,  _______, _______, _______, _______, _______,                   KC_PMNS, KC_P4,   KC_P5,   KC_P6,   KC_C,    KC_D, \
      _______,  _______, _______, _______, _______, _______, _______, _______, KC_PPLS, KC_P1,   KC_P2,   KC_P3,   KC_A,    KC_B, \
      _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_P0,   KC_COMM, KC_DOT,  _______, _______  \
      ),

  /* Lower (Dvorak)
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
  [_LOWER] = LAYOUT( \
      _______, _______, _______,       _______,       _______, _______,                   KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, KC_UNDS, \
      _______, _______, LGUI(KC_LCBR), LGUI(KC_RCBR), _______, LGUI(KC_PLUS),             KC_LCBR, KC_RCBR, KC_PLUS, KC_SLSH, KC_BSLS, KC_EQL, \
      _______, _______, LGUI(KC_LBRC), LGUI(KC_RBRC), _______, LGUI(KC_MINS),             KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_PIPE, KC_MINS, \
      _______, _______, _______,       _______,       _______, _______, _______, KC_GRV,  KC_PERC, KC_DLR,  KC_HASH, KC_AT,   KC_EXLM, KC_TILD, \
      _______, _______, _______,       _______,       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  | F10  | F11  | F12  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | Copy |      |      |             |PageUp|Ctr+A |  Up  |Ctr+E |      | Mute |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      | Cut  | Paste|      |             |PageDn| Left | Down |Right | Lit+ | Vol+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      | Lit- | Vol- |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |Raise |      |      |      |      |      |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_RAISE] = LAYOUT( \
      KC_F1,   KC_F2,   KC_F3,   KC_F4,      KC_F5,      KC_F6,                     KC_F7,   KC_F8,      KC_F9,   KC_F10,     KC_F11,  KC_F12, \
      _______, _______, _______, LGUI(KC_C), _______,    _______,                   KC_PGUP, LCTL(KC_A), KC_UP,   LCTL(KC_E), _______, KC__MUTE, \
      _______, _______, _______, LGUI(KC_X), LGUI(KC_V), _______,                   KC_PGDN, KC_LEFT,    KC_DOWN, KC_RGHT,    KC_F15,  KC__VOLUP, \
      _______, _______, _______, _______,    _______,    _______, _______, _______, _______, _______,    _______, _______,    KC_F14,  KC__VOLDOWN, \
      _______, _______, _______, _______,    _______,    _______, _______, _______, _______, _______,    _______, _______,    _______, _______ \
      ),

  /* Adjust
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      | Reset|RGBRST|      |      |      |             | Win  |Qwerty|      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff|      |             | Mac  |Dvorak|      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
   * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |Adjust|      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
   * `-------------------------------------------------------------------------------------------------'
   */
  [_ADJUST] =  LAYOUT( \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, RESET,   RGBRST,  _______, _______, _______,                   AG_NORM, QWERTY,  _______, _______, _______, _______, \
      _______, _______, _______, AU_ON,   AU_OFF,  _______,                   AG_SWAP, DVORAK,  _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RGB_MOD,RGB_HUD, RGB_SAD, RGB_VAD \
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
    // 1<<_COLEMAK - 1 == 2 - 1 == _COLEMAK (=1)
    current_default_layer = state - 1;
    // 1<<_DVORAK  - 2 == 4 - 2 == _DVORAK (=2)
    if ( current_default_layer == 3 ) current_default_layer -= 1;
    // 1<<_KEYPAD  - 5 == 8 - 5 == _KEYPAD (=3)
    if ( current_default_layer == 7 ) current_default_layer -= 4;
    return state;
}

void update_base_layer(int base)
{
    eeconfig_update_default_layer(1UL<<base);
    default_layer_set(1UL<<base);
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
    case EISU:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG2);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
      } else {
        unregister_code(KC_LANG2);
      }
      return false;
      break;
    case KANA:
      if (record->event.pressed) {
        if(keymap_config.swap_lalt_lgui==false){
          register_code(KC_LANG1);
        }else{
          SEND_STRING(SS_LALT("`"));
        }
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
#if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_ANIMATIONS)
  char buf[30];
  if(rgblight_config.enable) {
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
static const char Keypad_name[]  PROGMEM = " Keypad";

static const char Lower_name[]   PROGMEM = ":Lower";
static const char Raise_name[]   PROGMEM = ":Raise";
static const char Adjust_name[]  PROGMEM = ":Adjust";

static const char *layer_names[] = {
    [_QWERTY] = Qwerty_name,
    [_DVORAK] = Dvorak_name,
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
