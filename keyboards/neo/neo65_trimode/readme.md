# Neo65 Tri-mode
The Neo65 Tri-mode is based on a Westberry Tech WB32FQ95 MCU in a LQFP64 
package and can be programmed with wb32-dfu. The keyboard uses a WCH CH582F 
chip running a proprietary firmware to provide wireless connectivity. This is 
a community port which was derived from a partial source originally released 
by the manufacturer.

## Status
Work on this board is currently in progress.
- [x] Document basic components
- [x] Probe and verify matrix
- [x] Basic wired functionality
- [ ] Add support for SPI Flash
- [ ] Backport Westberry Trimode Wireless
- [ ] Fix invalid USB VID/PID

## Flashing a new firmware
Hold ESCAPE [0,0] to enter bootloader mode while inserting the USB cable into
the keyboard. Then run the following to flash the firmware.
```shell
make neo/neo65_trimode:default:flash
```

## What wireless chip is the Neo65 using?
![WCH CH582F](documentation/wireless.jpg)
The Neo65 uses a WCH CH582F running a custom firmware to provide wireless
connectivity. The CH582F is attached to (I think UART1 but still researching).

## What flash is the WB32FQ95 using on the Neo65?
![Puya P25D80SH](documentation/flash.jpg)
The WB32FQ95 on the Neo65 is using a Puya P25D80SH serial flash.

## WB32FQ95 which UART is the Neo65 using?
The WB32FQ95 supports 3 UARTS since PA2 and PA3 are used by the matrix we can
rule UART2 out.
* UART1 (SD1)
   * UART1_TX is on PA9
   * UART1_RX is on PA10
* UART2 (SD2)
   * UART2_TX is on PA2
   * UART2_RX is on PA3
* UART3 (SD3)
   * UART3_TX is on PC10
   * UART3_RX is on PC11

## Reference Material
The following shouldn't be upstreamed but I've included documentation relevant
for porting in the repo to have everything in a single place.

* [WB32FQ95 Data Sheet](documentation/EN_DS1104041_WB32FQ95xC_V01.pdf)
* [WCH CH582F Data Sheet](documentation/CH583DS1.PDF)
* [Puya P25D80SH Data Sheet](documentation/PUYA-P25Q80H-SSH-IT_C194872.pdf)
