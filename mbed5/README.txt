                      Arm Mbed OS 5 Application Framework

   This is a command line [1]make framework for building [2]Arm Mbed OS 5
   applications using the [3]Arm Mbed OS 5 Offline CLI libraries.

   Normally when you create Arm Mbed OS 5 CLI projects, you have to
   checkout the full Arm Mbed OS 5 CLI distribution (603 MB!) into each
   project directory. This seems insane to me, particularly if you are
   using your own source control system. So this framework relies on a
   single, shared Arm Mbed OS 5 CLI distribution installed at
   /usr/local/lib/mbed5.

   A Debian package (mbed5) that installs a copy of the Arm Mbed OS 5 CLI
   checkout to /usr/local/lib is available at:

   [4]http://repo.munts.com

   This framework relies on the [5]GNU ARM Embedded C/C++ toolchain, which
   is available at:

   [6]https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

   The GNU ARM Embedded toolchain tarball must be unpacked to
   /usr/local/gcc-arm-none-eabi/

   Each project Makefile must include include/mbed5.mk. The prepare.done
   target in mbed5.mk creates symbolic links to the necessary items under
   /usr/local/lib/mbed5/. After that the compile.done target issues the
   mbed compile command to build the project. Finally, the
   mbed5_mk_reallyclean target removes all working files and the symbolic
   links.
   ______________________________________________________________________

   Questions or comments to Philip Munts [7]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. https://www.gnu.org/software/make
   2. https://os.mbed.com/
   3. https://os.mbed.com/docs/mbed-os/v5.8/tutorials/quick-start-offline.html
   4. http://repo.munts.com/
   5. https://developer.arm.com/open-source/gnu-toolchain/gnu-rm
   6. https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
   7. mailto:phil@munts.net
