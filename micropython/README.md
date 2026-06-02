# MicroPython Framework for ARM MCU Platforms

You will need to use whatever command line shell your development
computer operating system has to make use of this framework. macOS and
Linux computers (including [Linux On ChromeOS *aka*
Crostini](https://chromeos.dev/en/linux) containers) always have one or
more command line shells, named something like `Terminal` or `Console`.

First, you must clone the [arm-mcu](https://github.com/pmunts/arm-mcu)
`git` repository with the following command:


    git clone https://github.com/pmunts/arm-mcu.git

It is advisable to define the environment variable `ARMSRC` to the
location of the checkout directory:


    export ARMSRC=$(HOME)/arm-mcu

A **MicroPython Framework for ARM MCU Platforms** project directory
contains a number of files. The easiest way to create a new project is
to copy the contents of the `template` project directory into your new
project directory:


    mkdir myproject
    cp -r $ARMSRC/micropython/programs/template/. myproject

It is **not** necessary for your new project to reside within the
`arm-mcu` directory tree.

# [GNU Make](https://www.gnu.org/software/make)

Each **MicroPython Framework for ARM MCU Platforms** program project
contains a minimal `Makefile` for GNU Make (*aka* `gmake`) that simply
defines a default value for the macro variable `ARMSRC` and then
includes `$(ARMSRC)/micropython/include/micropython.mk`, which defines
default values for some more macro variables (notably `BOARDFAMILY` and
`BOARDNAME`), some universal make targets, and finally includes a
platform dependent board family include file selected by the
`BOARDFAMILY` macro variable.

## Supported Board Families

| `BOARDFAMILY` | Description | Default `BOARDNAME` |
|----|----|----|
| `RP2` | Raspberry Pi [RP2040](https://www.raspberrypi.com/products/rp2040) and [RP2350](https://www.raspberrypi.com/products/rp2350) boards | `SEEED_XIAO_RP2350` |
| `STM32` | STMicroelectronics [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) boards | `NUCLEO_F411RE` |

This is a small subset of the vast variety of 32-bit ARM
microcontrollers supported by the **MicroPython** ecosystem, and limited
to the boards that I actually possess and can validate support for. It
is almost trivially easy to add support for more board families.

All of the STM32 boards I have chosen to support have an on-board
[ST-LINK](https://www.st.com/en/development-tools/st-link-v2.html)
in-circuit debugger/flash programmer.

## Make Targets

### run

Runs your **MicroPython** project on the target board. Press `CONTROL-C`
twice (and ignore the error message from `mpremote`) to terminate the
program, if necessary.

### clean

Removes working files (*i.e.* `__pycache__/`) from the project
directory.

### install

Copies the contents of the project subdirectory `src/` to the target
board's flash file system, and then resets the target board to begin
execution.

*Note: Some boards with limited flash memory do not have a flash file
system, and this make target will always fail.*

### ls

List files in the target board's flash file system.

*Note: Some boards with limited flash memory do not have a flash file
system, and this make target will always fail.*

### uninstall

Remove all project files from the target board's flash file system, and
then resets the target board.

*Note: Some boards with limited flash memory do not have a flash file
system, and this make target will always fail.*

### No target

Equivalent to `run`.

## Make Command Syntax

The exact target board is selected by two `gmake` macro variables:
`BOARDFAMILY` and `BOARDNAME`. Both of these can and should be
initialized by environment variables before invoking `gmake`.

The following command line pseudocode illustrates how to run, install,
or uninstall a **MicroPython Framework for ARM MCU Platforms** project
with `gmake` (*most operating systems symlink or alias `make` to
`gmake`*):


    export ARMSRC=<your arm-mcu checkout directory>
    export BOARDFAMILY=<your board family>
    export BOARDNAME=<your board name>
    make <your make target>

## Make Command examples


    export ARMSRC=$HOME/arm-mcu
    export BOARDFAMILY=RP2
    export BARDNAME=sparkfun_promicrorp2040

    # Run project on the target board
    make run
    make

    # Copy project to target board flash file system
    make install

    # Remove project from target board flash file system
    make uninstall

# [Visual Studio Code](https://code.visualstudio.com)

## [IntelliSense](https://code.visualstudio.com/docs/editing/intellisense)

You will need to install the Microsoft
[Python](https://github.com/microsoft/vscode-python) extension to enable
**IntelliSense** for Python3.

## Usage

Invoke Visual Studio Code by running the command `code .` in your
project directory.

The file `.vscode/tasks.json` within each **MicroPython Framework for
ARM MCU Platforms** project defines some task actions that simply run
`make run` *et al*. These can be invoked from the command menu
`Terminal → Run Task...` or `Terminal → Run Build Task...`.

Run your **MicroPython** project from within **Visual Studio Code** with
`CONTROL + SHIFT + B` (⌘ + SHIFT + B for macOS), the shortcut key
sequence for `Run Build Task...`, which runs `make run`. Press
`CONTROL-C` **twice** in the Visual Studio terminal output tab to
terminate the Python3 program running on the target computer.

------------------------------------------------------------------------

Questions or comments to Philip Munts <phil@munts.net>
