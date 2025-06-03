// Copyright 2025 emolitor (github.com/emolitor)
// Copyright 2024 Westberry Technology (ChangZhou) Corp., Ltd
// SPDX-License-Identifier: GPL-2.0-or-later*/

#include QMK_KEYBOARD_H
#include "wireless.h"

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
    };
} confinfo_t;
confinfo_t confinfo;

uint32_t post_init_timer = 0x00;
bool     pairing         = false;
uint8_t  blink_index     = 0;
bool     blink_fast      = true;
bool     blink_slow      = true;

// We use per-key tapping term to allow the wireless keys to have a much
// longer tapping term, therefore a longer hold, to match the default
// firmware behaviour.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(0, KC_BT1):
            return WIRELESS_TAPPING_TERM;
        case LT(0, KC_BT2):
            return WIRELESS_TAPPING_TERM;
        case LT(0, KC_BT3):
            return WIRELESS_TAPPING_TERM;
        case LT(0, KC_2G4):
            return WIRELESS_TAPPING_TERM;
        default:
            return TAPPING_TERM;
    }
}
void keyboard_post_init_kb(void) {
    confinfo.raw = eeconfig_read_kb();
    if (!confinfo.raw) {
        confinfo.flag = true;
        confinfo.devs = DEVS_USB;
        eeconfig_update_kb(confinfo.raw);
    }

    gpio_set_pin_output(ESCAPE_PIN);
    gpio_set_pin_output(DEVS_BT1_PIN);
    gpio_set_pin_output(DEVS_BT2_PIN);
    gpio_set_pin_output(DEVS_BT3_PIN);
    gpio_set_pin_output(DEVS_2G4_PIN);
    // writePin(LED_ESC_PIN, (pattern[led_blink_state[0]] & bit) != 0);

    // gpio_set_pin_output(LED_POWER_EN_PIN);
    // if (rgb_matrix_get_val() != 0) gpio_write_pin_low(LED_POWER_EN_PIN);

    // gpio_write_pin_low(USB_POWER_EN_PIN);
    // gpio_set_pin_output(USB_POWER_EN_PIN);

    // Set GPIO as high input for battery charging state
    // gpio_set_pin_input(BT_CABLE_PIN);
    // gpio_set_pin_input_high(BT_CHARGE_PIN);

    wireless_init();
    wireless_devs_change(!confinfo.devs, confinfo.devs, false);
    post_init_timer = timer_read32();

    keyboard_post_init_user();
}

// void usb_power_connect(void) {
//     gpio_write_pin_low(USB_POWER_EN_PIN);
// }

// void usb_power_disconnect(void) {
//     gpio_write_pin_high(USB_POWER_EN_PIN);
// }

// void suspend_power_down_kb(void) {
//     gpio_write_pin_high(LED_POWER_EN_PIN);
//
//     suspend_power_down_user();
// }

void suspend_wakeup_init_kb(void) {
    // if (rgb_matrix_get_val() != 0) gpio_write_pin_low(LED_POWER_EN_PIN);

    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    suspend_wakeup_init_user();
}

bool lpwr_is_allow_timeout_hook(void) {
    if (wireless_get_current_devs() == DEVS_USB) {
        return false;
    }

    return true;
}

void wireless_post_task(void) {
    if (post_init_timer && timer_elapsed32(post_init_timer) >= 100) {
        md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_2G4_EN); // timeout 30min to sleep in 2.4g mode, enable
        wireless_devs_change(!confinfo.devs, confinfo.devs, false);
        post_init_timer = 0x00;
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (process_record_user(keycode, record) != true) {
        return false;
    }

    switch (keycode) {
        // case KC_BATQ: {
        //     return false;
        // }
        case KC_USB: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
            return false;
        }
        case LT(0, KC_BT1): {
            if (record->tap.count && record->event.pressed) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, false);
            } else if (record->event.pressed && !pairing) {
                pairing = true;
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
            }
            return false;
        }
        case LT(0, KC_BT2): {
            if (record->tap.count && record->event.pressed) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, false);
            } else if (record->event.pressed && !pairing) {
                pairing = true;
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
            }
            return false;
        }
        case LT(0, KC_BT3): {
            if (record->tap.count && record->event.pressed) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, false);
            } else if (record->event.pressed && !pairing) {
                pairing = true;
                wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
            }
            return false;
        }
        case LT(0, KC_2G4): {
            if (record->tap.count && record->event.pressed) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, false);
            } else if (record->event.pressed && !pairing) {
                pairing = true;
                wireless_devs_change(wireless_get_current_devs(), DEVS_2G4, true);
            }
            return false;
        }
    }

    return true;
}

void wireless_devs_change_kb(uint8_t old_devs, uint8_t new_devs, bool reset) {
    pairing = reset;

    if (confinfo.devs != wireless_get_current_devs()) {
        confinfo.devs = wireless_get_current_devs();
        eeconfig_update_kb(confinfo.raw);
    }
}

void blink(long unsigned int key_index, bool blink) {
    if (blink) {
        // rgb_matrix_set_color(key_index, r, g, b);
    } else {
        // rgb_matrix_set_color(key_index, RGB_OFF);
    }
}

void wireless_indicators(void) {
    switch (confinfo.devs) {
        case DEVS_USB: {
            // rgb_matrix_set_color(DEVS_USB_INDEX, RGB_ADJ_WHITE);
        } break;
        case DEVS_BT1: {
            if (pairing) {
                blink(DEVS_BT1_PIN, blink_fast);
            } else if (*md_getp_state() != MD_STATE_CONNECTED) {
                blink(DEVS_BT1_PIN, blink_slow);
            } else {
                // rgb_matrix_set_color(DEVS_BT1_PIN, RGB_ADJ_WHITE);
            }
        } break;
        case DEVS_BT2: {
            if (pairing) {
                blink(DEVS_BT2_PIN, blink_fast);
            } else if (*md_getp_state() != MD_STATE_CONNECTED) {
                blink(DEVS_BT2_PIN, blink_slow);
            } else {
                // rgb_matrix_set_color(DEVS_BT2_PIN, RGB_ADJ_WHITE);
            }
        } break;
        case DEVS_BT3: {
            if (pairing) {
                blink(DEVS_BT3_PIN, blink_fast);
            } else if (*md_getp_state() != MD_STATE_CONNECTED) {
                blink(DEVS_BT3_PIN, blink_slow);
            } else {
                // rgb_matrix_set_color(DEVS_BT3_PIN, RGB_ADJ_WHITE);
            }
        } break;
        case DEVS_2G4: {
            if (pairing) {
                blink(DEVS_2G4_PIN, blink_fast);
            } else if (*md_getp_state() != MD_STATE_CONNECTED) {
                blink(DEVS_2G4_PIN, blink_slow);
            } else {
                // rgb_matrix_set_color(DEVS_2G4_PIN, RGB_ADJ_WHITE);
            }
        } break;
    }
}

/**
bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    blink_index = blink_index + 1;
    blink_fast = (blink_index % 64 == 0) ? !blink_fast : blink_fast;
    blink_slow = (blink_index % 128 == 0) ? !blink_slow : blink_slow;

    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }

    // When not in default layer show UX
    if (get_highest_layer(layer_state) > 0) {
        // Show active connection
        wireless_indicators();
    } else if (pairing || *md_getp_state() != MD_STATE_CONNECTED) {
        // Always show connections when pairing or when not connected
        wireless_indicators();
    }

    if (host_keyboard_led_state().caps_lock) {
        //rgb_matrix_set_color(CAPSLOCK_INDEX, RGB_ADJ_WHITE);
    }

    return true;
}
**/
