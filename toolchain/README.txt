                      ARM Microcontroller Toolchain Notes

   This toolchain includes binutils, gcc, newlib, and gdb. It may be built
   for Linux, MacOS (using [1]Fink or [2]MacPorts), OpenBSD, and Windows
   (using [3]Cygwin) development hosts. The toolchains produce identical
   results on every host operating system: This is the reason I created my
   own toolchain; I routinely flip back and forth among Linux, MacOS,
   OpenBSD, and Windows development environments. It is even possible to
   build the toolchain as a [4]Canadian Cross to run on a small Linux
   system such as the [5]Raspberry Pi or the [6]BeagleBone. See
   [7]Makefile.cross for details.

   My toolchain builds multilibs for the various Cortex-Mx devices,
   including hardware floating point for the Cortex-M4.

   Prebuilt toolchain packages are available at: [8]http://repo.munts.com.
   _______________________________________________________________________

   Questions or comments to Philip Munts [9]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. http://www.finkproject.org/
   2. http://www.macports.org/
   3. http://www.cygwin.com/
   4. http://en.wikipedia.org/wiki/Cross_compiler#Canadian_Cross
   5. http://www.raspberrypi.org/
   6. http://beagleboard.org/bone
   7. file:///home/pmunts/src/ARM/toolchain/Makefile.cross
   8. http://repo.munts.com/
   9. mailto:phil@munts.net
