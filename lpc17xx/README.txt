       NXP (nee Philips) LPC17xx ARM Cortex-M3 Microcontroller Framework

Credits

   The C run time startup code lpc17xx.S and linker script lpc17xx.ld were
   written by myself based on various examples on the Internet and in
   [1]The Definitive Guide to the ARM Cortex-M3.

   The [2]CMSIS library came from [3]NXP, with some minor customization by
   myself.

   Other files are original works by myself.

Memory Map (LPC1768)

   Code Flash: 0x00000000 to 0x0007FFFF 512 KB
   Data RAM:   0x10000000 to 0x10007FFF 32 KB

Other Devices

   This framework may be used for other devices in the NXP LPC17xx family,
   provided the following files are modified:

   lpc17xx.ld         The RAM and ROM sizes must match the device.
   lpc17xx.S          The interrupt vector table must match the device.
   lpc17xx.debugjlink The memory regions reported to GDB must match the
   device.

Test Platform

   This framework is validated on the following LPC17xx development
   boards:
     * [4]mbed LPC1768
     * [5]LPC1768-Mini-DK2

   Tested on 10 June 2015 with gcc 4.9.2.
     __________________________________________________________________

   Questions or comments to Philip Munts [6]phil@munts.net

   $Id$

   I am available for custom system development (hardware and software) of
   products using the LPC17xx or other microcontrollers.

References

   1. http://www.amazon.com/Definitive-Guide-Cortex-M3-Embedded-Technology/dp/0750685344
   2. http://www.arm.com/products/processors/cortex-m/cortex-microcontroller-software-interface-standard.php
   3. http://ics.nxp.com/support/lpcxpresso
   4. http://mbed.org/handbook/mbed-NXP-LPC1768
   5. http://www.hotmcu.com/lpc1768minidk2-development-board-p-55.html
   6. mailto:phil@munts.net
