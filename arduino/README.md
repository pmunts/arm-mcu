# Arduino Framework for ARM MCU Platforms

In order to use this framework, you will need to clone the
[arm-mcu](https://github.com/pmunts/arm-mcu) **`git`** repository with
the following command:

    git clone https://github.com/pmunts/arm-mcu.git

## GNU Make Projects

## Arduino IDE 2

This framework works well with [Arduino IDE
2](https://docs.arduino.cc/software/ide/#ide-v2). To use this framework
within the Arduino IDE 2, all you need to do is:

- Start Arduino IDE 2.
- Select your **target platform** from **`Tools → Board`**.
- Select the **communication port** from **`Tools → Port`**.
- Set the **sketchbook directory** to your **Arduino Framework for ARM
  MCU Platforms** checkout directory (*e.g.* **`~/arm-mcu/arduino/`**)
  from **`File → Preferences → Sketchbook location`**.

Your project does ***not*** need to be within the **Arduino Framework
for ARM MCU Platforms** checkout directory.

The Arduino IDE 2 does not use anything from the GNU make project except
for the sketch source file(s).

An Arduino IDE 2 Debian package for Linux x86-64 *aka* amd64 machines is
available at the [Munts Technologies Debian Package
Repository](https://repo.munts.com/debian13/). It is packaged from the
official Arduino release. Unfortunately there is no official Arduino IDE
2 release for ARMv8 *aka* arm64 machines.

## Visual Studio Code

## [FreeRTOS](https://www.freertos.org)

FreeRTOS is an [open source](https://en.wikipedia.org/wiki/Open_source)
lightweight [Real Time Operating
System](https://en.wikipedia.org/wiki/Real-time_operating_system) that
has been ported to many microcontrollers, including ARM 32-bit
microcontrollers. FreeRTOS was originally published in 2003 by Richard
Barry. [Amazon Web Services](https://aws.amazon.com) acquired ownership
or a least stewardship of the FreeRTOS project in 2017, apparently to
facilitate the creation of microcontroller [Internet of
Things](https://en.wikipedia.org/wiki/Internet_of_things) nodes to feed
AWS backend applications. FreeRTOS has been very widely used throughout
the world by developers across industries ranging from hobbyists to
[Fortune 500](https://us500.com/fortune-500-companies) companies.

To enable FreeRTOS, just add **`#define ENABLE_FREERTOS`** before
**`#include <Arduino_ARM.h>`**.

### RP2040/RP2350

The [Arduino-Pico](https://github.com/earlephilhower/arduino-pico) core
package for RP2040 and RP2350 microcontrollers includes a tightly
integrated implementation of [FreeRTOS
SMP](https://www.freertos.org/Documentation/02-Kernel/02-Kernel-features/13-Symmetric-multiprocessing-introduction)
(Symmetric Multi-Processing). The following minimal sketch skeleton
illustrates how to create a multicore RP2040 or RP2350 Arduino FreeRTOS
application:

    #define ENABLE_FREERTOS

    #include <Arduino_ARM.h>

    void Task0(void *parameters)
    {
      vTaskCoreAffinitySet(NULL, 0x01); // Pin task to core 0

      for (;;)
      {
        taskYIELD();
      }
    }

    void Task1(void *parameters)
    {
      vTaskCoreAffinitySet(NULL, 0x02); // Pin task to core 1

      for (;;)
      {
        taskYIELD();
      }
    }

    void setup()
    {
      xTaskCreate(Task0, "task0", 512, NULL, 1, NULL);
      xTaskCreate(Task0, "task1", 512, NULL, 1, NULL);
    }

All of **`loop()`**, **`setup1()`**, and **`loop1()`** are optional. For
compatibility, an idle task running on core 0 will call **`loop()`** if
it is defined and an idle task running on core 1 will call **`loop1()`**
if it is defined. The Arduino-Pico **`main()`** function calls
**`vTaskStartScheduler()`** therefore **`setup()`** must **not** call it
again. For this reason, **`Arduino_ARM.h`** defines
**`vTaskStartScheduler()`** as an empty macro for RP2040 and RP2350
platforms.

To build an RP2040 or RP2350 FreeRTOS application, you must append
**`:os=freertos`** to the FQBN (Fully Qualified Board Name). When
building with **`gmake`**, either from the command line or from Visual
Studio Code, this is automatically done by **`RP2040.mk`** or
**`RP2350.mk`**. When building with Arduino IDE 2, this must be done
explicitly from **`Tools → Operating System → FreeRTOS SMP`**.

Because of how well FreeRTOS has been integrated into the Arduino-Pico
core package, it is now probably easier to develop a FreeRTOS
application for an Arduino RP2040 or RP2350 platform than for any other
hardware/software combination.

### STM32

The [STM32FreeRTOS](https://github.com/stm32duino/STM32FreeRTOS) Arduino
library provides FreeRTOS support for STM32 microcontrollers. Since it
is delivered as a library, it is not integrated as tightly with the
STM32 core package, and FreeRTOS applications for Arduino are
implemented exactly the same as with any other GCC C or C++ framework.
The following minimal sketch skeleton illustrates how create an STM32
Arduino FreeRTOS application:

    #define ENABLE_FREERTOS

    #include <Arduino_ARM.h>

    void Task0(void *parameters)
    {
      for (;;)
      {
        taskYIELD();
      }
    }

    void setup()
    {
      xTaskCreate(Task0, "main", 512, NULL, 1, NULL);
      vTaskStartScheduler();
    }

    void loop()
    {
    }

Your **`setup()`** function must call **`xTaskCreate()`** to create at
least one FreeRTOS task and then call **`vTaskStartScheduler()`** which
does not return and replaces all of the normal Arduino background
processing. For compatibility, the FreeRTOS idle task calls
**`loop()`**.

## Libraries

------------------------------------------------------------------------

Questions or comments to Philip Munts <phil@munts.net>
