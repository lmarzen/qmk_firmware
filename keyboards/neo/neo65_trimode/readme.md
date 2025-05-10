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

## Reference Material
The following shouldn't be upstreamed but I've included documentation relevant
for porting in the repo as it's not easy to find.

* [WB32FQ95 Data Sheet](EN_DS1104041_WB32FQ95xC_V01.pdf)
