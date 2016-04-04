               ARM Microcontroller Firmware Development Framework

   Here is a framework for developing firmware for a number of [1]ARM
   (Advanced RISC Machine) architecture single chip microcontrollers.

   Each MCU directory includes startup code, linker script, [2]newlib
   syscall bindings, and [3]OpenOCD scripts for debugging and flashing.

News

     * 5 January 2015 -- Upgraded binutils to 2.25, gcc to 4.9.2, newlib
       to 2.2.0, and gdb to 7.8.1. With newlib 2.2.0, the INTEGER_STDIO
       and CONIO_STDIO options are no longer needed. CONIO_STDIO is still
       supported, mostly for other tool chains such as [4]GNU ARM
       Embedded. It is enabled by adding WITH_CONIO=yes to the make
       command line options.
     * 21 January 2015 -- Upgraded gdb to 7.8.2. Build gcc prequisites,
       including libiconv, from source. Added auxiliary makefile for
       building a Canadian Cross ARM microcontroller toolchain for the
       Raspberry Pi.
     * 13 April 2015 -- Renamed NETDUINO2 (which is STM32F2) to
       NETDUNIOPLUS2 (which is STM32F4). Added support for programming
       STM32 flash with [5]dfu-util.
     * 27 April 2015 -- Upgraded the STM32F4 Standard Peripheral Library
       to version 1.5.0. Added support for the [6]NUCLEO-F411RE board, and
       the corresponding STM32F411RE MCU.
     * 6 May 2015 -- Fixed a subtle bug in the linker scripts: (.data)
       should be (.data*) and (.bss) should be (.bss*). This was
       preventing successful use of the [7]GNU ARM Embedded toolchain,
       because some data sections were being discarded.
     * 7 May 2015 -- Define BOARDNAME C preprocessor macro. Eliminated the
       WITH_LIBSTDCPP make macro; always link with libstdc++. Added a C++
       iostream library test. The C++ iostream library now works, but adds
       over 200 kilobytes of code and will not fit in many of the smaller
       ARM microcontrollers. C++ container classes may or may not fit.
       Added system tick timer services, including millisleep() and
       sleep().
     * 8 May 2015 -- Fixed a bug in device_write(). Added code to device.c
       to honor O_RDONLY and O_WRONLY flags. Moved I/O syscall definitions
       from syscalls.c to device.c, where they are aliased to
       device_xxxx() functions. This eliminates an unnecessary function
       call for each syscall operation.
     * 12 May 2015 -- More improvements in device.c: Eliminated some calls
       to memset(). Switched to [8]texane/stlink even for Windows.
       Implemented interrupt driven serial I/O for the STM32F4 family.
     * 13 May 2015 -- Added even more error checking to device.c. Made the
       device table private to device.c. Added general support for
       fcntl(). The F_GETFL and F_SETFL operations are available for any
       file descriptor while other operations are delegated to the device
       specific fcntl() handler, if one was provided when the device was
       registered.
     * 25 May 2015 -- Stopped using the STM32F4 Standard Peripheral
       Library. Use [9]CMSIS instead. Eliminated USB serial port console
       support from most targets. It was just too unstable and hard to
       maintain. It is so much easier to use dedicated a dedicated USB
       serial port device like the [10]FT232R. Changed STM32F4 makefiles
       to always use the hardware FPU. With recent versions of newlib,
       there is no longer a code size penalty from enabling the FPU.
     * 10 June 2015 -- Another massive overhaul: Added support for the
       [11]STM32 M4 Clicker board. Dropped support for the [12]STM32 Value
       Line Discovery board. (Its ST-Link/V1 is obsolete.) Dropped support
       for the obsolete AT91SAM7S, LPC23xx, and STR91x MCU families.
       Dropped support for the obsolete [13]Wiznet W5200. Dropped support
       for the [14]BlueBoard LPC1768. Upgraded FreeRTOS to V8.2.1.
       Implemented interrupt driven serial I/O for the STM32F1 MCU family.
       Upgraded OpenOCD to 0.9.0. Added support for the [15]NUCLEO-F103RB
       board. Use a common LED test for all targets. Implemented A/D
       services for the STM32F4 MCU family. Use a common A/D test for all
       targets. Added button (momentary switch) services. Stopped using
       the STM32F1 Standard Peripheral Library. Use [16]CMSIS instead.
       Added code to each of the assembly language startup files to call
       _exit() if main() returns.
     * 6 August 2015 -- Upgraded GCC to 5.2.0. Upgraded GDB to 7.9.1.
     * 18 August 2015 -- Added support for systick callback function.
     * 17 September 2015 -- Upgraded GDB to 7.10. Resurrected and
       modernized support for the [17]Silicon Labs (formerly Energy Micro)
       EFM32 microcontroller family.
     * 18 September 2015 -- Upgraded FreeRTOS to 8.2.2.
     * 21 January 2016 -- Upgraded binutils to 2.25.1, gcc to 5.3.0,
       newlib to 2.3.0, and gdb to 0.7.1.
     * 4 April 2016 -- Upgraded binutils to 2.26, newlib to 2.4.0 and gdb
       to 7.11.

Git Repository

   The source code is available at: [18]http://git.munts.com

   Use the following command to clone it:

   git clone http://git.munts.com/arm-mcu.git

Copyright:

   Original works herein are copyrighted as follows:

Copyright (C)2013-2016, Philip Munts, President, Munts AM Corp.

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

   Questions or comments to Philip Munts [19]phil@munts.net

   I am available for custom system development (hardware and software) of
   products using these ARM microcontrollers.

References

   1. http://www.arm.com/
   2. http://sourceware.org/newlib
   3. http://openocd.sourceforge.net/
   4. http://launchpad.net/gcc-arm-embedded
   5. http://dfu-util.sourceforge.net/
   6. http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/LN1847/PF260320
   7. http://launchpad.net/gcc-arm-embedded
   8. https://github.com/texane/stlink
   9. http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php
  10. http://www.ftdichip.com/Products/ICs/FT232R.htm
  11. http://www.mikroe.com/stm32/clicker
  12. http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF250863
  13. http://www.wiznet.co.kr/product-item/w5200
  14. http://shop.ngxtechnologies.com/product_info.php?products_id=65
  15. http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/LN1847/PF259875
  16. http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php
  17. http://www.silabs.com/products/mcu/32-bit/Pages/32-bit-microcontrollers.aspx
  18. http://git.munts.com/
  19. mailto:phil@munts.net
