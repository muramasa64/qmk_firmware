/* Copyright 2018-2019 eswai <@eswai>
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

#pragma once

void naginata_type(void);
void naginata_clear(void);
void compress_buffer(int nt);
bool naginata_lookup(int nt, bool shifted);

bool process_modifier(uint16_t, keyrecord_t *);

void naginata_on(void);
void naginata_off(void);
bool naginata_state(void);
void naginata_use_toggle(void);

void mac_live_conversion_toggle(void);
void mac_live_conversion_on(void);
void mac_live_conversion_off(void);

bool process_naginata(uint16_t, keyrecord_t *);
void set_naginata(uint8_t);

typedef enum naginata_keycodes {
    KC_NG_Q = SAFE_RANGE,  // 薙刀式シフトキー
    KC_NG_W,
    KC_NG_E,
    KC_NG_R,
    KC_NG_T,
    KC_NG_Y,
    KC_NG_U,
    KC_NG_I,
    KC_NG_O,
    KC_NG_P,

    KC_NG_A,
    KC_NG_S,
    KC_NG_D,
    KC_NG_F,
    KC_NG_G,
    KC_NG_H,
    KC_NG_J,
    KC_NG_K,
    KC_NG_L,
    KC_NG_SCLN,

    KC_NG_Z,
    KC_NG_X,
    KC_NG_C,
    KC_NG_V,
    KC_NG_B,
    KC_NG_N,
    KC_NG_M,
    KC_NG_COMM,
    KC_NG_DOT,
    KC_NG_SLSH,

    KC_NG_SHFT,
} NGKEYS;

#define NG_SAFE_RANGE SAFE_RANGE + 31
