// Copyright 2025 emolitor (github.com/emolitor)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* COLORS adjusted for RGB_MATRIX_MAXIMUM_BRIGHTNESS of 104 */
#define RGB_ADJ_WHITE  0x68, 0x68, 0x68
#define RGB_ADJ_BLUE   0x00, 0x68, 0x57
#define RGB_ADJ_RED    0x68, 0x00, 0x00
#define RGB_ADJ_YELLOW 0x68, 0x4b, 0x00
#define RGB_ADJ_GREEN  0x3d, 0x68, 0x00

/* KEYS */
#define CAPSLOCK_INDEX 43

/* FLASH */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4
#define SPI_MOSI_PAL_MODE 5
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
