           Silicon Labs EFM32 ARM Cortex-M3 Microcontroller Framework

Credits

   The C run time startup code efm32xxxx.S and linker script efm32xxxx.ld
   were written by myself based on various examples on the Internet and in
   [1]The Definitive Guide to the ARM Cortex-M3.

   The files in the SDK/ subdirectory were extracted from the EFM32 SDK
   v4.0.0, which was itself extracted from [2]Simplicity Studio v3.1.

   Other files are original works by myself.

Memory Map (EFM32G890F128)

   Code Flash: 0x00000000 to 0x0001FFFF 128 KB
   Data RAM:   0x20000000 to 0x20003FFF 16 KB

Other Devices

   This framework may be used for other devices in the Silicon Labs EFM32
   family, provided the following files are modified:

   efm32xxxx.ld         The flash ROM and/or RAM sizes may need be changed.
   efm32xxxx.S          The interrupt vector table must match the device.
   efm32xxxx.debugjlink The memory regions reported to GDB must match the
                        device.

Test Platform

   This framework is validated on the [3]EFM32 Gecko Starter Kit
   development board.

   Tested on 17 September 2015 with gcc 5.2.0.
     __________________________________________________________________

   Questions or comments to Philip Munts [4]phil@munts.net

   $Id: README.txt 9382 2015-09-17 09:45:48Z svn $

   I am available for custom system development (hardware and software) of
   products using the EFM32G890F128 or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.silabs.com/products/mcu/Pages/simplicity-studio.aspx
   3. http://www.silabs.com/products/mcu/lowpower/Pages/efm32-g8xx-stk.aspx
   4. mailto:phil@munts.net
