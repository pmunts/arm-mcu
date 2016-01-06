                      ARM Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, newlib, and gdb. It may be built
   for Linux, MacOS (using [1]Fink), OpenBSD, and Windows (using
   [2]Cygwin) development hosts. The toolchains produce identical results
   on every host operating system: This is the reason I created my own
   toolchain; I routinely flip back and forth among Linux, MacOS, OpenBSD,
   and Windows development environments. It is even possible to build the
   toolchain as a [3]Canadian Cross to run on a small Linux system such as
   the [4]Raspberry Pi. See [5]Makefile.rpi for an example.

   My toolchain builds multilibs for the various Cortex-Mx devices,
   including hardware floating point for the Cortex-M4.
     __________________________________________________________________

   Questions or comments to Philip Munts [6]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. http://www.finkproject.org/
   2. http://www.cygwin.com/
   3. http://en.wikipedia.org/wiki/Cross_compiler#Canadian_Cross
   4. http://www.raspberrypi.org/
   5. http://tech.munts.com/MCU/Frameworks/ARM/toolchain/Makefile.rpi
   6. mailto:phil@munts.net
