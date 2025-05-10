# Neo65 Tri-mode
The Neo65 Tri-mode is based on a Westberry Tech WB32FQ95 MCU and can be
programmed with wb32-dfu. This is a community port which was derived from
partial source originally published by the manufacturer.

## Status
Work on this board is currently in progress.
- [x] Basic wired functionality
- [ ] Backport Westberry Trimode Wireless
- [ ] Fix invalid USB VID/PID

## Flashing a new firmware
Hold ESCAPE [0,0] to enter bootloader mode while inserting the USB cable into
the keyboard. Then run the following to flash the firmware.
```shell
make neo/neo65:default:flash
```

## WB32FQ95 which UART is the Neo65 using?
The WB32FQ95 supports 3 UARTS since PA2 and PA3 are used by the matrix we can
rule UART2 out.
* UART1 (SD1)
** UART1_TX is on PA9
** UART1_RX is on PA10
* UART2 (SD2)
** UART2_TX is on PA2
** UART2_RX is on PA3
* UART3 (SD3)
** UART3_TX is on PC10
** UART3_RX is on PC11

## Reference Material
The following shouldn't be upstreamed but I've included documentation relevant
for porting in the repo as it's not easy to find.

* [WB32FQ95 Data Sheet](EN_DS1104041_WB32FQ95xC_V01.pdf)
