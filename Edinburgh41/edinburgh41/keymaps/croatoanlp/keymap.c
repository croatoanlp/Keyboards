// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifdef THUMBSTICK_ENABLE
#    include "thumbstick.h"
#endif

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

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
    [ss]    = 0xDF   // scharf s
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_edinburgh41(
    KC_ESC,          KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,              KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    LT(1, KC_CAPS),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,              KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_ENTER,
    KC_LSFT,         KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,              KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                          LCTL_T(KC_LGUI),    KC_SPC,   KC_NO,   LOWER,    RAISE
  ),
  
  [_LOWER] = LAYOUT_edinburgh41(
    KC_TAB,   KC_1,      KC_2,     KC_3,     KC_4,      KC_5,               KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_BSPC,
    _______,  _______,   KC_NO,    KC_BTN2,  KC_BTN1,   KC_BTN2,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  _______,  KC_BSLS,
    KC_LSFT,  _______,   _______,  _______,  KC_MINS,   KC_EQL,             KC_LBRC,  KC_RBRC,  KC_QUOT,  _______,  _______,  KC_RSFT,
                                             KC_LGUI,   _______,  _______,  _______,  UC_MOD
  ),
  
  [_RAISE] = LAYOUT_edinburgh41(
    KC_GRAVE,  _______,       _______,    X(euro),     _______,     _______,            _______,    XP(ue, UE),    _______,    XP(oe, OE),    _______,   KC_DEL,
    _______,   XP(ae, AE),    X(ss),      _______,     _______,     _______,            _______,    _______,       _______,    _______,       _______,   _______,
    KC_LSFT,   KC_F1,         KC_F2,      KC_F3,       KC_F4,       KC_F5,              KC_F6,      KC_F7,         KC_F8,      KC_F9,         KC_F10,    KC_RSFT,
                                                       KC_F11,      KC_F12,  _______,   ADJUST,     _______
  ),
  
  [_ADJUST] = LAYOUT_edinburgh41(
    RGB_VAI,   RGB_SAI, RGB_HUI,  RGB_MOD,  XXXXXXX,   RGB_TOG,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    RGB_VAD,   RGB_SAD, RGB_HUD,  RGB_RMOD, XXXXXXX,   XXXXXXX,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   XXXXXXX,            RESET,    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                            _______,   _______,  XXXXXXX,  _______,  _______
  ),
};

// This function controls thumbstick functionality depending on active layer
uint32_t layer_state_set_user(uint32_t state) {
  
  
  switch (biton32(state)) {
    
    // For every layer you want the thumbstick to do something on, add a case. You have three choices for the behaviour on a layer.
    // Mouse behaviour: Copy the content of the case _BASE.
    // Keypress behaviour: Copy the content of the case _RAISE. Set input_keycodes.keycode_up = to the keycode you want to press when moving the thumbstick up etc.
    // Scroll behaviour: Copy the content of the case _LOWER.
    case _BASE:
      writePinHigh(LED1);
      writePinHigh(LED2);
      thumbstick_mode_set(THUMBSTICK_MODE_MOUSE);
      break;
    
    case _RAISE:
      writePinLow(LED1);
      writePinHigh(LED2);
      thumbstick_mode_set(THUMBSTICK_MODE_SCROLL);
      break;
      
    case _LOWER:
      writePinLow(LED2);
      writePinHigh(LED1);
      thumbstick_mode_set(THUMBSTICK_MODE_MOUSE);
      break;
  }
  return state;
}
