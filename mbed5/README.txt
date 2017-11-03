                        Mbed OS 5 Application Framework

   This is a command line [1]make framework for building [2]Mbed OS 5
   applications using the [3]Mbed OS CLI (Command Line Interface).

   Normally when you create Mbed OS CLI projects, you have to checkout the
   full Mbed OS CLI distribution (603 MB!) into each project directory.
   This seems insane to me, particularly if you are using our own source
   control system. So this framework relies on a single, shared Mbed OS
   CLI distribution installed at /usr/local/lib/mbed5.

   Debian packages (munts-mbed-cli) that install a copy of the Mbed OS CLI
   to /usr/local/lib are available at:

   [4]http://repo.munts.com

   This framework relies on the [5]GNU ARM Embedded C/C++ toolchain, which
   is available at:

   [6]https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads

   The GNU ARM Embedded toolchain tarball must be unpacked to
   /usr/local/gcc-arm-none-eabi/

   Each project Makefile must include include/mbed5.mk. The prepare.done
   target in mbed5.mk creates symbolic links to the necessary items under
   mbed-cli/. After that the compile.done target issues the mbed compile
   command to build the project. Finally, the mbedos_mk_reallyclean target
   removes all working files and the symbolic links.

Git Repository

   The source code is available at:

   [7]http://git.munts.com

   Use the following command to clone it:

   git clone http://git.munts.com/arm-mcu.git

Copyright:

   Original works herein are copyrighted as follows:

Copyright (C)2017, Philip Munts, President, Munts AM Corp.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

   Redistributed works herein are copyrighted and/or licensed by their
   respective authors.
   ___________________________________________________________________

   Questions or comments to Philip Munts [8]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using ARM or other microcontrollers.

References

   1. https://www.gnu.org/software/make
   2. https://developer.mbed.org/
   3. https://docs.mbed.com/docs/mbed-os-handbook/en/latest/dev_tools/cli/
   4. http://repo.munts.com/
   5. https://developer.arm.com/open-source/gnu-toolchain/gnu-rm
   6. https://developer.arm.com/open-source/gnu-toolchain/gnu-rm/downloads
   7. http://git.munts.com/
   8. mailto:phil@munts.net
