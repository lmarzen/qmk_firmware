// Copyright 2024 emolitor (github.com/emolitor)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

void blink(uint8_t key_index, uint8_t r, uint8_t g, uint8_t b, bool blink) {
    if (blink) {
        rgb_matrix_set_color(key_index, r, g, b);
    } else {
        rgb_matrix_set_color(key_index, RGB_OFF);
    }
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    static uint8_t blink_index = 0;
    static bool blink_fast = true;
    static bool blink_slow = true;

    blink_index = blink_index + 1;
    blink_fast = (blink_index % 64 == 0) ? !blink_fast : blink_fast;
    blink_slow = (blink_index % 128 == 0) ? !blink_slow : blink_slow;

    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    if (host_keyboard_led_state().caps_lock) {
        //blink(CAPSLOCK_INDEX, RGB_ADJ_WHITE, blink_fast);
        rgb_matrix_set_color(CAPSLOCK_INDEX, RGB_ADJ_WHITE);
    }

    return true;
}
