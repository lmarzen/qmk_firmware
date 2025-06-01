// Copyright 2025 emolitor (github.com/emolitor)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Specific tapping term for wireless configuration. If the key is held for
 * less than 3 seconds we select that device for the active connection. If
 * greater than 3 seconds we select that device and go into pairing mode.
 */
#define WIRELESS_TAPPING_TERM 3000

/* COLORS adjusted for RGB_MATRIX_MAXIMUM_BRIGHTNESS of 104 */
#define RGB_ADJ_WHITE   0x68, 0x68, 0x68
#define RGB_ADJ_BLUE    0x00, 0x68, 0x57
#define RGB_ADJ_RED     0x68, 0x00, 0x00
#define RGB_ADJ_YELLOW  0x68, 0x4b, 0x00
#define RGB_ADJ_GREEN   0x3d, 0x68, 0x00

/* KEYS */
#define ESCAPE_INDEX    0
#define CAPSLOCK_INDEX  43
#define DEVS_USB_INDEX  14
#define DEVS_BT1_INDEX  15
#define DEVS_BT2_INDEX  16
#define DEVS_BT3_INDEX  17
#define DEVS_2G4_INDEX  18

/* FLASH */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4
#define SPI_MOSI_PAL_MODE 5
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12

/* POWER */
#define USB_POWER_EN_PIN A14
#define LED_POWER_EN_PIN B7
#define BT_CABLE_PIN B8 // High when charging
#define BT_CHARGE_PIN B9 // Low when charging, high when fully charged

/* UART */
#define UART_TX_PIN A9
#define UART_TX_PAL_MODE 7
#define UART_RX_PIN A10
#define UART_RX_PAL_MODE 7

/* WIRELESS NAMES */
#define MD_BT1_NAME "Bridge75 BT1"
#define MD_BT2_NAME "Bridge75 BT2"
#define MD_BT3_NAME "Bridge75 BT3"
#define MD_DONGLE_PRODUCT "Bridge75 Dongle"

//#define LPWR_TIMEOUT RGB_MATRIX_TIMEOUT
//#define WLS_KEYBOARD_REPORT_KEYS 5
