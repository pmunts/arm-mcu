# Arduino Framework for ARM MCU Platforms

Unless you use *only* **Arduino IDE 2**, you will need to use whatever
command line shell your development computer operating system has to
make use of this framework. macOS and Linux computers (including [Linux
On ChromeOS *aka* Crostini](https://chromeos.dev/en/linux) containers)
always have one or more command line shells, named something like
`Terminal` or `Console`.

In order to use this framework, you will first need to clone the
[arm-mcu](https://github.com/pmunts/arm-mcu) `git` repository with the
following command:

    git clone https://github.com/pmunts/arm-mcu.git

After you have cloned the repository, you will most likely want to set
the `ARMSKETCHBOOK` environment variable to point to the `arduino/`
subdirectory of the `arm-mcu` checkout directory (*e.g.*
`export ARMSKETCHBOOK=$HOME/arm-mcu/arduino`). You can add the `export`
command to *e.g.* `~/.bashrc` to make it permanent.

An **Arduino Framework for ARM MCU Platforms** project directory
contains a number of files. The easiest way to create a new project is
with the `arduino-arm-newproject` shell script:

    $HOME/arm-mcu/arduino/scripts/arduino-arm-newproject myproject

# [GNU Make](https://www.gnu.org/software/make)

Each **Arduino Framework for ARM MCU Platforms** program project
contains a minimal `Makefile` for `gmake` that simply defines a default
value for the macro `ARMSKETCHBOOK` and then includes
`$(ARMSKETCHBOOK)/libraries/MuntsTech_ARM/Arduino_ARM.mk`, which defines
default values for some more macros and the project default target
`arduino_arm_mk_default`, and finally includes a platform dependent
board family `gmake` include file selected by the `BOARDFAMILY` macro.

## Supported Board Families

| `BOARDFAMILY` Value | Description                                                                                                                                                                 | Core Package                                                   | Default `BOARDNAME`       |
|---------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|----------------------------------------------------------------|---------------------------|
| `RP2040`            | [Raspberry Pi RP2040](https://www.raspberrypi.com/products/rp2040/) boards                                                                                                  | [Arduino-Pico](https://github.com/earlephilhower/arduino-pico) | `sparkfun_promicrorp2040` |
| `RP2350`            | [Raspberry Pi RP2350](https://www.raspberrypi.com/products/rp2350/) boards                                                                                                  | [Arduino-Pico](https://github.com/earlephilhower/arduino-pico) | `sparkfun_promicrorp2350` |
| `Disco`             | [STMicroelectronics Discovery](https://www.st.com/en/evaluation-tools/stm32-discovery-kits.html) evaluation boards                                                          | [STM32Duino](https://github.com/stm32duino)                    | `DISCO_F407VG`            |
| `Nucleo_32`         | [STMicroelectronics Nucleo-32](https://www.st.com/en/evaluation-tools/stm32-nucleo-boards/products.html?querycriteria=productId=LN1847$$1574=Nucleo-32) evaluation boards   | [STM32Duino](https://github.com/stm32duino)                    | `NUCLEO_L432KC`           |
| `Nucleo_64`         | [STMicroelectronics Nucleo-64](https://www.st.com/en/evaluation-tools/stm32-nucleo-boards/products.html?querycriteria=productId=LN1847$$1574=Nucleo-64) evaluation boards   | [STM32Duino](https://github.com/stm32duino)                    | `NUCLEO_F411RE`           |
| `Nucleo_144`        | [STMicroelectronics Nucleo-144](https://www.st.com/en/evaluation-tools/stm32-nucleo-boards/products.html?querycriteria=productId=LN1847$$1574=Nucleo-144) evaluation boards | [STM32Duino](https://github.com/stm32duino)                    | `NUCLEO_F767ZI`           |

This is a small subset of the vast variety of 32-bit ARM
microcontrollers supported by the Arduino ecosystem, and limited to the
boards that I actually possess and can validate support for. It is
almost trivially easy to add support for more board families.

All of the STM32 board families I have chosen to support have an
on-board
[ST-LINK](https://www.st.com/en/development-tools/st-link-v2.html)
in-circuit debugger/flash programmer.

## Make Targets

### build

Builds the sketch with `arduino-cli compile`.

### install

Uploads (more properly: *Downloads*) the compiled sketch with
`arduino-cli upload` to a target microcontroller board.

*For the `RP2040` and `RP2350` board families, setting environment
variable `FLASHPICO=yes` before `make install` switches from
`arduino-cli upload` to a script named
[`flashpico`](https://github.com/pmunts/arm-mcu/tree/main/utilities/flashpico).
Across the range of RP2040 and RP2350 boards, and
Chromebook/Linux/macOS/Windows development host computers, I have found
`flashpico` to be more reliable than `arduino-cli upload`.*

### clean

Removes working files (*i.e.* `build/`).

### No target

Equivalent to `clean install`.

## Make Command Syntax

The exact target board is selected by two `gmake` macros: `BOARDFAMILY`
and `BOARDNAME`. Both of these can and should be initialized by
environment variables before invoking `gmake`.

For the RP2040 and RP2350 board families, the Arduino FQBN (Fully
Qualified Board Name) shall be defined as:

    ARDUINOFQBN := rp2040:rp2040:$(BOARDNAME)

For the various STM32 board families, the Arduino FQBN passed to
`arduino-cli` shall be defined as:

    ARDUINOFQBN := STMicroelectronics:stm32:$(BOARDFAMILY):pnum=$(BOARDNAME),upload_method=swdMethod

The following shell pseudocode illustrates how to build an **Arduino
Framework for ARM MCU Platforms** project with `gmake` (most operating
systems symlink or alias `make` to `gmake`):

    export ARMSKETCHBOOK=<your arm-mcu checkout directory>/arduino
    export BOARDFAMILY=<your board family>
    export BOARDNAME=<your board name>
    make <your make target>

## Make Command examples

    export ARMSKETCHBOOK=$HOME/arm-mcu/arduino
    export BOARDFAMILY=RP2040
    export BARDNAME=sparkfun_promicrorp2040

    # Build without flashing target board
    make build

    # Flash target board without rebuilding unnecessarily
    make install

    # The two following commands are equivalent:
    # Build from scratch and then flash target board
    make clean install
    make

    # Use flashpico instead of arduino-cli upload
    export FLASHPICO=yes
    make

# [Arduino IDE 2](https://docs.arduino.cc/software/ide/#ide-v2)

To use this framework within the **Arduino IDE 2**, all you need to do
is:

- Start **Arduino IDE 2**.
- Select your **target platform** from `Tools → Board`.
- Select the **communication port** from `Tools → Port`.
- Set the **sketchbook directory** to your **Arduino Framework for ARM
  MCU Platforms** checkout directory (*e.g.* `~/arm-mcu/arduino/`) from
  `File → Preferences → Sketchbook location`.

Your project directory does ***not*** need to be within the **Arduino
Framework for ARM MCU Platforms** checkout directory tree.

The **Arduino IDE 2** does not use anything from the GNU `make` project
except for the sketch source file(s).

An **official** **Arduino IDE 2** release Debian package for Linux
x86-64 *aka* amd64 machines and an **unofficial** release Debian package
for arm64 *aka* AArch64 machines are available at the [Munts
Technologies Debian Package
Repository](https://repo.munts.com/debian13/).

# [Visual Studio Code](https://code.visualstudio.com)

## [IntelliSense](https://code.visualstudio.com/docs/editing/intellisense)

You will need to install the [Microsoft C/C++ for Visual Studio
Code](https://github.com/microsoft/vscode-cpptools) extension *and*
invoke **Visual Studio Code** with `make code` or `make edit` instead of
the usual `code .`. The `gmake` targets `code` or `edit` prepend some
environment variables to the `code` command that are necessary for
**IntelliSense** to find system header files.

**IntelliSense** for **Arduino Framework for ARM MCU Platforms**
projects is not perfect: Indexing library source files within the
Arduino core packages can take a **very** long time, and declarations
and/or definitions qualified by preprocessing directives are often
invisible, as they often cannot be resolved until compile time. On the
whole, I still prefer **Visual Studio Code** over **Arduino IDE 2**,
because the latter does not store target configuration in the project
directory.

## Usage

The file `.vscode/tasks.json` within each **Arduino Framework for ARM
MCU Platforms** project defines some task actions `make <program>` *et
al* that simply run `make clean install` *et al*. These can be invoked
from the command menu `Terminal → Run Task...` or
`Terminal → Run Build Task...`.

The most efficient way to build and install from within **Visual Studio
Code** is to press `CONTROL + SHIFT + B` (⌘ + SHIFT + B for macOS), the
shortcut key sequence for `Run Build Task...`.

# [FreeRTOS](https://www.freertos.org)

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

To enable FreeRTOS, just add `#define ENABLE_FREERTOS` before
`#include <Arduino_ARM.h>`.

## RP2040/RP2350

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

All of `loop()`, `setup1()`, and `loop1()` are optional. For
compatibility, an idle task running on core 0 will call `loop()` if it
is defined and an idle task running on core 1 will call `loop1()` if it
is defined. The Arduino-Pico `main()` function calls
`vTaskStartScheduler()` therefore `setup()` must **not** call it again.
For this reason, `Arduino_ARM.h` defines `vTaskStartScheduler()` as an
empty macro for RP2040 and RP2350 platforms, *with the side effect that
the classic STM32 FreeRTOS sketch in the next subsection will also run
on RP2040 and RP2350 boards.*

To build an RP2040 or RP2350 FreeRTOS application, you must append
`:os=freertos` to the FQBN (Fully Qualified Board Name). When building
with `gmake`, either from the command line or from Visual Studio Code,
this is automatically done by `RP2040.mk` or `RP2350.mk`. When building
with Arduino IDE 2, this must be done explicitly from
`Tools → Operating System → FreeRTOS SMP`.

Because of how well FreeRTOS has been integrated into the Arduino-Pico
core package, it is now probably easier to develop a FreeRTOS
application for an Arduino RP2040 or RP2350 platform than for any other
hardware/software combination.

## STM32

*Note: Many, if not most, STM32 Nucleo evaluation boards have too little
RAM to run FreeRTOS, especially if the sketch creates C++ object
instances with the `new` operator which uses memory from the
[heap](https://dev.to/olivestem/understanding-heap-memory-allocation-in-c-sbrk-and-brk-3coj).
The
**[Nucleo-L432KC](https://www.st.com/en/evaluation-tools/nucleo-l432kc.html)**
and
**[Nucleo-F411RE](https://www.st.com/en/evaluation-tools/nucleo-f411re.html)**
successfully run
[`test_button_led_freertos`](programs/test_button_led_freertos).*

The [STM32FreeRTOS](https://github.com/stm32duino/STM32FreeRTOS) Arduino
library provides FreeRTOS support for STM32 microcontrollers. Since it
is delivered as a library, it is not integrated as tightly with the
STM32 core package, and FreeRTOS applications for Arduino are
implemented exactly the same as with any other GCC C or C++ framework,
albeit with the FreeRTOS setup code moved from `main()` to `setup()`.
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

Your `setup()` function must call `xTaskCreate()` to create at least one
FreeRTOS task and then call `vTaskStartScheduler()` which does not
return and replaces all of the normal Arduino background processing. For
compatibility, the FreeRTOS idle task calls `loop()`, which is not
optional.

# Libraries

------------------------------------------------------------------------

Questions or comments to Philip Munts <phil@munts.net>
