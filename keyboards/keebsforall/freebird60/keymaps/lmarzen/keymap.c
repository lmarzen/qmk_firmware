/* Copyright 2020 KnoblesseOblige
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [0] = LAYOUT(
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        MO(2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENTER,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLSH, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, MO(1), MO(1), MO(3), KC_RCTL
    ),
    [1] = LAYOUT( // function layer
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        _______, KC_HOME, KC_UP, KC_END, KC_PGUP, _______, _______, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_PAUS, KC_INS, KC_PSCR,
        KC_CAPS, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_SCRL, _______,
        KC_LSFT, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, _______, _______, KC_RCTL
    ),
    [2] = LAYOUT( // function layer for caps lock key
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_DEL,
        _______, KC_HOME, KC_UP, KC_END, KC_PGUP, _______, _______, KC_HOME, KC_UP, KC_END, KC_PGUP, KC_PAUS, KC_INS, KC_PSCR,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, KC_SCRL, _______,
        KC_LSFT, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, _______, _______, KC_RCTL
    ),
    [3] = LAYOUT( // alternative function layer
        QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_TAB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_LSFT, KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU, KC_BRID, KC_BRIU, KC_MUTE, KC_VOLD, KC_VOLU, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, _______, _______, KC_RCTL
    ),
};
