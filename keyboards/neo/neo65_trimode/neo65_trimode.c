/* Copyright (C) 2025 emolitor@github.com/emolitor
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

#define LED_ESC 0
#define LED_ESC_PIN D2

#define LED_Q 1
#define LED_Q_PIN C11

#define LED_W 2
#define LED_W_PIN C10

#define LED_E 3
#define LED_E_PIN A15

#define LED_R 4
#define LED_R_PIN C0

#define NUM_LEDS_BLINK 5
#define LED_BLINK_FAST_PERIOD_MS 300

// Possible LED states.
enum { LED_OFF = 0, LED_ON = 1, LED_BLINK_SLOW = 2, LED_BLINK_FAST = 3 };
static uint8_t led_blink_state[NUM_LEDS_BLINK] = {0};

void keyboard_post_init_kb(void) {
    gpio_set_pin_output(LED_ESC_PIN);
    gpio_set_pin_output(LED_Q_PIN);
    gpio_set_pin_output(LED_W_PIN);
    gpio_set_pin_output(LED_E_PIN);
    //gpio_set_pin_output(LED_R_PIN);

    uint32_t led_blink_callback(uint32_t trigger_time, void* cb_arg) {
        static const uint8_t pattern[4] = {0x00, 0xff, 0x0f, 0xaa};
        static uint8_t phase = 0;
        phase = (phase + 1) % 8;

        uint8_t bit = 1 << phase;
        writePin(LED_ESC_PIN, (pattern[led_blink_state[0]] & bit) != 0);
        writePin(LED_Q_PIN, (pattern[led_blink_state[1]] & bit) != 0);
        writePin(LED_W_PIN, (pattern[led_blink_state[2]] & bit) != 0);
        writePin(LED_E_PIN, (pattern[led_blink_state[3]] & bit) != 0);

        return LED_BLINK_FAST_PERIOD_MS / 2;
    }

    //led_blink_state[LED_ESC] = LED_ON;
    //led_blink_state[LED_Q] = LED_BLINK_SLOW;
    //led_blink_state[LED_W] = LED_BLINK_FAST;

    defer_exec(1, led_blink_callback, NULL);

    keyboard_post_init_user();
}
