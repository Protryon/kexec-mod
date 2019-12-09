# Kexec kernel module

## Purpose

Be able to run kexec within embedded x86 (and ARM later) systems that were not compiled with kexec support, where no direct kernel modification is possible due to secure boot.

## Building

Run `make all`.

## Requirements

This project requires:

* GCC 4.8
* Linux Kernel 3.12.17 (other versions may work, this is what was tested on) -- path is hardcoded to `../linux` in `Makefile`.
* Offsets of various non-exported symbols (details below)

## Integration with kexec-tools

This module adds in the proper `kexec_load` syscall as expected from the `kexec-tools` package, so `kexec` should work normally after this module is inserted.

## Notes on symbol exports

Due to the nature of kexec, it is required for this module to access many symbols that are not readily exported by the kernel.

If you can modify the kernel to export them, great, (point the various definitions in `./hardcode.c` to them). Otherwise, if you're lucky and have `System.map`, you can get the offsets out of there. I was not lucky, and statically analyzed the kernel this was designed for to get the present offsets in `./hardcode.c`.