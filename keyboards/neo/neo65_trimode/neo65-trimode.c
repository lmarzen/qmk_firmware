/* Copyright (C) 2022 jonylee@hfd
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

#ifdef WIRELESS_ENABLE
    include "wireless.h"
#endif

void keyboard_post_init_kb(void) {

//#ifdef CONSOLE_ENABLE
//    debug_enable = true;
//#endif

//eeconfig_confinfo_init();

//#ifdef LED_POWER_EN_PIN
//    gpio_set_pin_output(LED_POWER_EN_PIN);
//    gpio_write_pin_low(LED_POWER_EN_PIN);
//#endif

//#ifdef USB_POWER_EN_PIN
//    gpio_write_pin_low(USB_POWER_EN_PIN);
//    gpio_set_pin_output(USB_POWER_EN_PIN);
//#endif

#ifdef WIRELESS_ENABLE
    // For testing we are running without eeprom so always default to USB
    confinfo.flag = true;
    confinfo.devs = DEVS_USB;

    wireless_init();
    wireless_devs_change(!confinfo.devs, confinfo.devs, false);
    post_init_timer = timer_read32();
#endif

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {

    if (process_record_user(keycode, record) != true) {
        return false;
    }

#ifdef WIRELESS_ENABLE
    if (process_record_wls(keycode, record) != true) {
        return false;
    }
#endif

    switch (keycode) {
        default:
            return true;
    }

    return false;
}

#ifdef WIRELESS_ENABLE

typedef union {
    uint32_t raw;
    struct {
        uint8_t flag : 1;
        uint8_t devs : 3;
    };
} confinfo_t;
confinfo_t confinfo;

uint32_t post_init_timer = 0x00;

void usb_power_connect(void) {

//#    ifdef USB_POWER_EN_PIN
//    gpio_write_pin_low(USB_POWER_EN_PIN);
//#    endif
}

void usb_power_disconnect(void) {

//#    ifdef USB_POWER_EN_PIN
//    gpio_write_pin_high(USB_POWER_EN_PIN);
//#    endif
}

void suspend_power_down_kb(void) {

//#    ifdef LED_POWER_EN_PIN
//    gpio_write_pin_high(LED_POWER_EN_PIN);
//#    endif
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {

//#    ifdef LED_POWER_EN_PIN
//    gpio_write_pin_low(LED_POWER_EN_PIN);
//#    endif

    wireless_devs_change(wireless_get_current_devs(), wireless_get_current_devs(), false);
    suspend_wakeup_init_user();
}

void wireless_post_task(void) {

    // auto switching devs
    if (post_init_timer && timer_elapsed32(post_init_timer) >= 100) {
        md_send_devctrl(MD_SND_CMD_DEVCTRL_FW_VERSION);   // get the module fw version.
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_BT_EN);  // timeout 30min to sleep in bt mode, enable
        md_send_devctrl(MD_SND_CMD_DEVCTRL_SLEEP_24G_EN); // timeout 30min to sleep in 2.4g mode, enable
        wireless_devs_change(!confinfo.devs, confinfo.devs, false);
        post_init_timer = 0x00;
    }
}

uint32_t wls_process_long_press(uint32_t trigger_time, void *cb_arg) {
    uint16_t keycode = *((uint16_t *)cb_arg);

    switch (keycode) {
        case KC_BT1: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT1, true);
        } break;
        case KC_BT2: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT2, true);
        } break;
        case KC_BT3: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_BT3, true);
        } break;
        case KC_24G: {
            wireless_devs_change(wireless_get_current_devs(), DEVS_24G, true);
        } break;
        default:
            break;
    }

    return 0;
}

bool process_record_wls(uint16_t keycode, keyrecord_t *record) {
    static uint16_t keycode_shadow                     = 0x00;
    static deferred_token wls_process_long_press_token = INVALID_DEFERRED_TOKEN;

    keycode_shadow = keycode;

#    ifndef WLS_KEYCODE_PAIR_TIME
#        define WLS_KEYCODE_PAIR_TIME 3000
#    endif

#    define WLS_KEYCODE_EXEC(wls_dev)                                                                                          \
        do {                                                                                                                   \
            if (record->event.pressed) {                                                                                       \
                wireless_devs_change(wireless_get_current_devs(), wls_dev, false);                                             \
                if (wls_process_long_press_token == INVALID_DEFERRED_TOKEN) {                                                  \
                    wls_process_long_press_token = defer_exec(WLS_KEYCODE_PAIR_TIME, wls_process_long_press, &keycode_shadow); \
                }                                                                                                              \
            } else {                                                                                                           \
                cancel_deferred_exec(wls_process_long_press_token);                                                            \
                wls_process_long_press_token = INVALID_DEFERRED_TOKEN;                                                         \
            }                                                                                                                  \
        } while (false)

    switch (keycode) {
        case KC_BT1: {
            WLS_KEYCODE_EXEC(DEVS_BT1);
        } break;
        case KC_BT2: {
            WLS_KEYCODE_EXEC(DEVS_BT2);
        } break;
        case KC_BT3: {
            WLS_KEYCODE_EXEC(DEVS_BT3);
        } break;
        case KC_24G: {
            WLS_KEYCODE_EXEC(DEVS_24G);
        } break;
        case KC_USB: {
            if (record->event.pressed) {
                wireless_devs_change(wireless_get_current_devs(), DEVS_USB, false);
            }
        } break;
        //case KC_BATQ: {
        //} break;
        default:
            return true;
    }

    return false;
}

void wireless_send_nkro(report_nkro_t *report) {
    static report_keyboard_t temp_report_keyboard = {0};
    uint8_t wls_report_nkro[MD_SND_CMD_NKRO_LEN]  = {0};

#ifdef NKRO_ENABLE

    if (report != NULL) {
        report_nkro_t temp_report_nkro = *report;
        uint8_t key_count              = 0;

        temp_report_keyboard.mods = temp_report_nkro.mods;
        for (uint8_t i = 0; i < NKRO_REPORT_BITS; i++) {
            key_count += __builtin_popcount(temp_report_nkro.bits[i]);
        }

        /*
         * Use NKRO for sending when more than 6 keys are pressed
         * to solve the issue of the lack of a protocol flag in wireless mode.
         */

        for (uint8_t i = 0; i < key_count; i++) {
            uint8_t usageid;
            uint8_t idx, n = 0;

            for (n = 0; n < NKRO_REPORT_BITS && !temp_report_nkro.bits[n]; n++) {}
            usageid = (n << 3) | biton(temp_report_nkro.bits[n]);
            del_key_bit(&temp_report_nkro, usageid);

            for (idx = 0; idx < WLS_KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == usageid) {
                    goto next;
                }
            }

            for (idx = 0; idx < WLS_KEYBOARD_REPORT_KEYS; idx++) {
                if (temp_report_keyboard.keys[idx] == 0x00) {
                    temp_report_keyboard.keys[idx] = usageid;
                    break;
                }
            }
        next:
            if (idx == WLS_KEYBOARD_REPORT_KEYS && (usageid < (MD_SND_CMD_NKRO_LEN * 8))) {
                wls_report_nkro[usageid / 8] |= 0x01 << (usageid % 8);
            }
        }

        temp_report_nkro = *report;

         // find key up and del it.
        uint8_t nkro_keys = key_count;
        for (uint8_t i = 0; i < WLS_KEYBOARD_REPORT_KEYS; i++) {
            report_nkro_t found_report_nkro;
            uint8_t usageid = 0x00;
            uint8_t n;

            found_report_nkro = temp_report_nkro;

            for (uint8_t c = 0; c < nkro_keys; c++) {
                for (n = 0; n < NKRO_REPORT_BITS && !found_report_nkro.bits[n]; n++) {}
                usageid = (n << 3) | biton(found_report_nkro.bits[n]);
                del_key_bit(&found_report_nkro, usageid);
                if (usageid == temp_report_keyboard.keys[i]) {
                    del_key_bit(&temp_report_nkro, usageid);
                    nkro_keys--;
                    break;
                }
            }

            if (usageid != temp_report_keyboard.keys[i]) {
                temp_report_keyboard.keys[i] = 0x00;
            }
        }
    } else {
        memset(&temp_report_keyboard, 0, sizeof(temp_report_keyboard));
    }
#endif
    void wireless_task(void);
    bool smsg_is_busy(void);
    while(smsg_is_busy()) {
        wireless_task();
    }
    extern host_driver_t wireless_driver;
    wireless_driver.send_keyboard(&temp_report_keyboard);
    md_send_nkro(wls_report_nkro);
}
#endif
