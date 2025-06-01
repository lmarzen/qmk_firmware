// Copyright 2024 emolitor (github.com/emolitor)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
    };
} confinfo_t;
confinfo_t confinfo;

void keyboard_post_init_kb(void) {
    confinfo.raw = eeconfig_read_kb();
    if (!confinfo.raw) {
        confinfo.flag = true;
        eeconfig_update_kb(confinfo.raw);
    }

    // Set GPIO as high input for battery charging state
    gpio_set_pin_input(BT_CABLE_PIN);
    gpio_set_pin_input_high(BT_CHARGE_PIN);

    gpio_set_pin_output(LED_POWER_EN_PIN);
    if (rgb_matrix_get_val() != 0) gpio_write_pin_low(LED_POWER_EN_PIN);

    gpio_set_pin_output(USB_POWER_EN_PIN);
    gpio_write_pin_low(USB_POWER_EN_PIN);

    keyboard_post_init_user();
}

void suspend_power_down_kb(void) {
    gpio_write_pin_high(LED_POWER_EN_PIN);

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    if (rgb_matrix_get_val() != 0) gpio_write_pin_low(LED_POWER_EN_PIN);

    suspend_wakeup_init_user();
}

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

    // When not in default layer set all mapped keys to yellow
    if (get_highest_layer(layer_state) > 0) {
        uint8_t layer = get_highest_layer(layer_state);

        for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
            for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
                uint8_t index = g_led_config.matrix_co[row][col];

                if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col,row}) > KC_TRNS) {
                    rgb_matrix_set_color(index, RGB_ADJ_YELLOW);
                }
            }
        }

        // Check if we are plugged in
        if (gpio_read_pin(BT_CABLE_PIN)) {
            // We are plugged in
            if (!gpio_read_pin(BT_CHARGE_PIN)) {
                // We are charging
                blink(ESCAPE_INDEX, RGB_ADJ_RED, blink_slow);
            } else {
                // We are fully charged
                rgb_matrix_set_color(ESCAPE_INDEX, RGB_ADJ_GREEN);
            }
        }
    }


    if (host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(CAPSLOCK_INDEX, RGB_ADJ_WHITE);
    }

    return true;
}
