// Copyright 2022 Lalit Mistry (@schwarzer-geiger)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "edinburgh41.h"

bool capslock_on = false;

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    return layer_state_set_user(state);
}

