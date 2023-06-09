# voyager-lcd - Compose Voyager calculator display bitmaps

Copyright 2023 Eric Smith <spacewar@gmail.com>

SPDX-License-Identifier: GPL-3.0-only

voyager-lcd development is hosted at the
[voyager-lcd Github repository](https://github.com/brouhaha/voyager-lcd/).

## Introduction

The HP Voyasger series calculators (HP-10C, HP-11C, HP-12C, HP-15C, and
HP-16C) were introduced in 1981 to 1982. They used an LCD display with
ten seven-segment digits with right hand decimal and comma, and ten
annunciators, for a total of 100 display segments. (A 101st segment, a
battery low indicator, was present but not under firmware control.)

The display segments were individually controlled by 50 bits in each of
two hardware registers. The mapping of bits to segments was based on the
physical layout of the LCD, PCB wiring, and chip pinout. As a consequence,
the mapping seems quite arbitrary. It is tedious to manually compose display
bitmaps. This program presents an approximate graphical representation of
the LCD. Segments can be toggled with a mouse clock, and the corresponding
control register values are displayed in hexadecimal.

## Building from source on Linux

The program builds on Linux or Posix systems, and requires C++20 , Qt
6, Python 3, and SCons 4. It has been (only slightly) tested on Fedora
37 Linux with GCC 12.2.1, Qt 6.4.1, Python 3.11, and SCons 4.4.1.

To build:

- `scons`

or, after building any other target (e.g., win32):

- `scons target=posix`

The resulting executable will be `build/posix/voyager-lcd`.
The executable may be installed simply by copying it into any desired
directory.

## Cross-compiling for Windows on a Linux host

Cross-compiling for Windows requires a mingw32 cross-compilation toolchain,
cross-development Qt packages, and msitools. On Fedora 37, install the
required packages by:

- `sudo dnf install mingw32-g++ mingw32-qt6-qtbase msitools`

To build:

- `scons target=win32`

The resuling MSI installation package will be `build/win32/voyager-lcd.msi`.

## License

The voyager-lcd program is licensed under the Free Software Foundation
General Public License version 3. See `LICENSE/gpl-3.0.txt` for details.
