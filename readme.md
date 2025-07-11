# Quantum Mechanical Keyboard Wireless Fork
This is a fork of the Quantum Mechanical Keyboard Firmware adding support
for Westberry based wireless keyboards. These keyboards are based on a
multichip solution coupling a WB32 MCU with a CH582F chip providing the
wireless connectivity. The chips communicate via UART and there are several
variations each with slightly different protocols. All of these variations
make it complicated to upstream a solution. The intent of this fork is to
provide a modern version of QMK for these keyboards as well as to experiment
consolidating the variations into a well formed and supportable code base
which can be upstreamed. This fork does not and will not contain any binary
blobs and is fully compliant with the upstream license used by QMK.

The following keyboards are currently supported by this repository.
* [Neo Studios Neo65](keyboards/neo/neo65_trimode/)
* [Neo Studios Neo70](keyboards/neo/neo70_trimode/)
* [Neo Studios Neo80](keyboards/neo/neo80_trimode/)
* [Neo Studios NeoErgo](keyboards/neo/neoergo_trimode/)
* [QwertyKeys QK65V2 Classic](keyboards/qwertykeys/qk65v2classic/)
* [Shortcut Studios Bridge75](keyboards/shortcut/bridge75/)

This is a community supported repository with special thanks to Kasper at 
[Monacokeys](https://monacokeys.de) who provided some spare boards and endless
time testing the initial port of the Bridge75. And to
[Shortcut Studio](https://shortcutofficial.com) for publishing the inital
source code for the Bridge75 and providing an ANSI Bridge75 PCB for
development as well testing and validating the initial Bridge75 port. And to
[Neo Studio](https://www.instagram.com/ne0_kb) for providing PCBs of their
boards as well as testing and validing the Neo keyboards.
[QwertyKeys](https://qwertykeys.com) for providing PCBs and validating and 
testing the QK65V2 Classic


# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/qmk)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the Clueboard product line.

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.
