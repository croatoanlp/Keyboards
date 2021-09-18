/* Copyright 2020 Paul James
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
 *
 * This Version was Last modified in 2021 by Aaron Müller
 *
 */

#include QMK_KEYBOARD_H

//Keyboard Layers
enum layers {
  _DEFAULT = 0,
  _LAY1,
  _LAY2
};

//Unicode input 
enum unicode_names { ae, AE, ue, UE, oe, OE, euro, ss };

const uint32_t PROGMEM unicode_map[] = {
    [ae]    = 0xE4,  // ae
    [AE]    = 0xC4,  // AE
    [ue]    = 0xFC,  // ue
    [UE]    = 0xDC,  // UE
    [oe]    = 0xF6,  // oe
    [OE]    = 0xD6,  // OE
    [euro]  = 0x20AC, // Euro 
    [ss]    = 0x00DF // scharf s
};



// Keymaps
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Baselayer
 * ,-----------------------------------------. ,-----------------------------------------.
 * | GESC |  1   |  2   |  3   |  4   |  5   | |  6   |  7   |  8   |  9   |  0   |  -   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Tab  |  Q   |  W   |  E   |  R   |  T   | |  Y   |  U   |  I   |  O   |  P   | Bksp |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | (1)  |  A   |  S   |  D   |  F   |  G   | |  H   |  J   |  K   |  L   | ;(1) | Entr |	(1) CAPS(press), LAY1(hold)		(2) ISO-DE: ö
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shft |  Z   |  X   |  C   |  V   |  B   | |  N   |  M   |  ,   |  .   |  /   | Shft |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Ctrl | Cmd  | Alt  |AltGr |       Space | |  LAY1       | Left | Down |  Up  | Rght |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_DEFAULT] = LAYOUT_ortho_5x12(
    KC_GESC,        KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,      KC_7,     KC_8,    KC_9,    KC_0,    KC_MINS,
    KC_TAB,         KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,      KC_U,     KC_I,    KC_O,    KC_P,    KC_BSPC,
    LT(1, KC_CAPS), KC_A,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,      KC_J,     KC_K,    KC_L,    KC_SCLN, KC_ENT,
    KC_LSFT,        KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,      KC_M,     KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_LCTL,        KC_LGUI,   KC_LALT, KC_RALT, KC_NO,   KC_SPC,  MO(_LAY1), KC_NO,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
),

/* Layer1 
 * ,-----------------------------------------. ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  | |  F6  |  F7  |  F8  |  F9  | F10  |  =   |
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | (1)  | F11  | F12  |  €   |      |      | |      |  ü   |      |  ö   |      | Del  | (1) UC_MOD: Cycle through Unicode modes: Windows (Wincompose), Windows (native), Linux
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |  ä   |  ß   |      |      |      | | Left | Down |  Up  | Rght | (2)  | \(3) | (2) ISO-DE: <>|  (3) ISO-DE: #'
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * | Shft |      |      |      |      |      | | [(4) | ](5) | '(6) |      |      | Shft | (4) ISO-DE: ü  (5) ISO-DE: +*~  (6) ISO-DE: ä
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      | LAY2 |      |      |             | |             | Home | Vol- | Vol+ | End  |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_LAY1] = LAYOUT_ortho_5x12(
    KC_GRV,  KC_F1,      KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,      KC_F8,   KC_F9,      KC_F10,  KC_EQL,
    UC_MOD,  KC_F11,     KC_F12,  X(euro), _______, _______, _______, XP(ue, UE), _______, XP(oe, OE), _______, KC_DEL,
    _______, XP(ae, AE), X(ss),   _______, _______, _______, KC_LEFT, KC_DOWN,    KC_UP,   KC_RGHT,    KC_NUBS, KC_BSLS,
    KC_LSFT, _______,    _______, _______, _______, _______, KC_LBRC, KC_RBRC,    KC_QUOT, _______,    _______, KC_RSFT,
    _______, MO(_LAY2),  _______, _______, KC_NO,   _______, _______, KC_NO,      KC_HOME, KC_VOLD,    KC_VOLU, KC_END
),

/* Layer2 to prevent accidential RESETs
 * ,-----------------------------------------. ,-----------------------------------------.
 * |      |      |      |      |      |      | |      |      |      |      |      |RESET | 
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      | 
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      | 
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |      |      | |      |      |      |      |      |      | 
 * |------+------+------+------+------+------| |------+------+------+------+------+------|
 * |      |      |      |      |             | |             |      |      |      |      |
 * `-----------------------------------------' `-----------------------------------------'
 */
[_LAY2] = LAYOUT_ortho_5x12(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  RESET,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KC_NO,   _______, _______, KC_NO,   _______, _______, _______, _______
   
)
};
