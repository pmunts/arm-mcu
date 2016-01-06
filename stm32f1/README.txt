       STMicroelectronics STM32F1 Cortex-M3 ARM Microcontroller Framework

Credits

   The C run time startup code stm32f1xxxx.S and linker scripts
   stm32f1xxxx.ld were written by myself based on various examples on the
   Internet and in [1]The Definitive Guide to the ARM Cortex-M3.

   The [2]CMSIS library came from [3]STMicroelectronics, extracted from
   the [4]STM32CubeF1 software package.

   Other files are original works by myself.

Memory Map (STM32F103RB)

   Code Flash: 0x00000000 to 0x0001FFFF 128 KB
   Data RAM:   0x20000000 to 0x20004FFF 20 KB

   The STM32F1 microcontrollers can have any of code flash at 0x08000000,
   system ROM (boot loader) at 0x1FFFF000, or data RAM at 0x20000000
   mapped to address 0x00000000, depending on the BOOT0 and BOOT1 pins.
   This framework assumes BOOT0 is strapped low, mapping code flash to
   0x00000000.

   This framework assumes a single stack for both thread and handler
   modes, using MSP (Main Stack Pointer) at the top of RAM. The C heap is
   placed at the end of BSS data.

Other Devices

   This framework may be used for other devices in the STM32F1 family,
   provided the following files are modified:

   stm32f1xxxx.ld         The RAM and ROM sizes must match the device.
   stm32f1xxxx.S          The interrupt vector table must match the device.
   stm32f1xxxx.debugjlink The memory regions reported to GDB must match
   the device.

Test Platform

   This framework is validated on the following STM32F1xx development
   boards:
     * [5]NUCLEO-F103RB
     * [6]Olimex STM32-P103
     * [7]Olimex STM32-P107

   Tested on 10 June 2015 with gcc 4.9.2.
     __________________________________________________________________

   Questions or comments to Philip Munts [8]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the STM32F1 or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php
   3. http://www.st.com/
   4. http://www.st.com/web/en/catalog/tools/PF260820
   5. http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/LN1847/PF259875
   6. http://www.olimex.com/dev/stm32-p103.html
   7. http://www.olimex.com/dev/stm32-p107.html
   8. mailto:phil@munts.net
