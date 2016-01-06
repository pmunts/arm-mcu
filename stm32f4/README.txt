       STMicroelectronics STM32F4 Cortex-M4 ARM Microcontroller Framework

Credits

   The C run time startup code stm32f4xxxx.S and linker scripts
   stm32f4xxxx.ld were written by myself based on various examples on the
   Internet and in [1]The Definitive Guide to the ARM Cortex-M3.

   The [2]CMSIS library came from [3]STMicroelectronics, extracted from
   the [4]STM32CubeF4 software package.

   Other files are original works by myself.

Memory Map (STM32F407VG)

   Code Flash: 0x00000000 to 0x000FFFFF 1024 KB
   Data RAM:   0x20000000 to 0x2001FFFF 128 KB
   CCM RAM:    0x10000000 to 0x1000FFFF 64 KB

   The STM32F4 microcontrollers can have any of code flash at 0x08000000,
   system ROM (boot loader) at 0x1FFF0000, or data RAM at 0x20000000
   mapped to address 0x00000000, depending on the BOOT0 and BOOT1 pins.
   This framework assumes BOOT0 is strapped low, mapping code flash to
   0x00000000.

   This framework assumes a single stack for both thread and handler
   modes, using MSP (Main Stack Pointer) at the top of RAM. The C heap is
   placed at the end of BSS data.

   Note: CCM RAM is inaccessible to peripherals (DMA/Ethernet/USB).

Other Devices

   This framework may be used for other devices in the STM32F4 family,
   provided the following files are modified:

   stm32f4xxxx.ld         The RAM and ROM sizes must match the device.
   stm32f4xxxx.S          The interrupt vector table must match the device.
   stm32f4xxxx.debugjlink The memory regions reported to GDB must match
   the device.

Test Platform

   This framework is validated on the following STM32F4xx development
   boards:
     * [5]NUCLEO-F411RE
     * [6]FEZ Cerb40
     * [7]Netduino Plus 2
     * [8]MINI-M4 for STM32
     * [9]STM32 M4 Clicker
     * [10]STM32F4 Discovery

   Tested on 10 June 2015 with gcc 4.9.2.
     __________________________________________________________________

   Questions or comments to Philip Munts [11]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the STM32F4 or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php
   3. http://www.st.com/
   4. http://www.st.com/web/en/catalog/tools/PF259243
   5. http://www.st.com/web/catalog/tools/FM116/SC959/SS1532/LN1847/PF260320
   6. http://www.ghielectronics.com/catalog/product/353
   7. http://netduino.com/netduinoplus2/specs.htm
   8. http://www.mikroe.com/mini/stm32
   9. http://www.mikroe.com/stm32/clicker/
  10. http://www.st.com/internet/evalboard/product/252419.jsp
  11. mailto:phil@munts.net
