# microblaze-vga

This project connects a Microblaze MCS core to custom made block RAM (BRAM) and VGA controllers.
The code was developed and tested on a [Spartan3e starter board by Digilent] (https://reference.digilentinc.com/reference/programmable-logic/spartan-3e/start), using Xilinx ISE 13.4.

The VGA controller outputs a 60Hz, 640 x 480 signal, with at most 8 colors (due to limitations in
the dev. board).

A bank of BRAMs is used as a frame-buffer, and allows the microblaze to draw on screen, while the
pixel colors are read by the VGA controller.

TODO:
- [] upload Microblaze firmware.

