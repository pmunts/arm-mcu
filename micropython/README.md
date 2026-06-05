# [MicroPython](https://micropython.org) Framework for ARM MCU Platforms

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

A **MicroPython** project directory contains a number of files. The
easiest way to create a new project is to copy the contents of the
`template` project directory into your new project directory:

    mkdir myproject
    cp -r $ARMSRC/micropython/programs/template/. myproject

It is **not** necessary for your new project to reside within the
`arm-mcu` directory tree.

# [GNU Make](https://www.gnu.org/software/make)

Each **MicroPython** program project contains a minimal `Makefile` for
GNU Make (*aka* `gmake`) that simply defines a default value for the
macro variable `ARMSRC` and then includes
`$(ARMSRC)/micropython/include/micropython.mk`, which defines default
values for some more macro variables, defines some make targets
applicable to all target boards (`make run` *et al*), and finally
includes an *optional* a target board family dependent include file
(selected by the `BOARDFAMILY` macro variable) that defines some
firmware management targets (`make install_firmware` and `make nuke`).

## Make Targets

### run

Executes your **MicroPython** project on the target board and connects
to its serial console.  
Press `CONTROL-X` to terminate the project running on the target board
and disconnect from its serial console.

### reset

Resets the target board, exactly as if you pressed its reset button.
This will stop a **MicroPython** project started by `make run` or
(re)start a project stored in flash memory by `make install`.

### clean

Removes working files (*i.e.* `__pycache__/`) from the project
directory.

### ls

List files in the target board's file system(s).

### install

Copies your **MicroPython** project to the target board's flash memory,
and then resets the target board to begin execution.

*Note: Some boards with limited flash memory do not have a flash file
system, and this make target will always fail.*

### uninstall

Remove all files from the target board's flash memory, and then resets
the target board.

*Note: Some boards with limited flash memory do not have a flash file
system, and this make target will always fail.*

### No target

Equivalent to `run`.

## *Optional* Firmware Management Targets

These are not necessary for routine **MicroPython** usage. Use only with
great caution.

#### Supported Board Families

The target board flash memory programming mechanism (*e.g.*
[ST-Link](https://www.st.com/en/development-tools/st-link-v2.html)) is
selected by the `BOARDFAMILY` macro variable and the target board
firmware image file is selected by the `BOARDNAME` macro variable.

| `BOARDFAMILY` | Description                                                                                                                         | Default `BOARDNAME` |
|---------------|-------------------------------------------------------------------------------------------------------------------------------------|---------------------|
| `RP2`         | Raspberry Pi [RP2040](https://www.raspberrypi.com/products/rp2040) and [RP2350](https://www.raspberrypi.com/products/rp2350) boards | `SEEED_XIAO_RP2350` |
| `STM32`       | STMicroelectronics [STM32](https://www.st.com/en/microcontrollers-microprocessors/stm32-32-bit-arm-cortex-mcus.html) boards         | `NUCLEO_F411RE`     |

This is a small subset of the vast variety of 32-bit ARM
microcontrollers supported by the **MicroPython** ecosystem, and limited
to the boards that I actually possess and can validate support for. It
is almost trivially easy to add support for more board families.

All of the STM32 boards I have chosen to support have enough memory for
a flash file system as well as an on-board
[ST-Link](https://www.st.com/en/development-tools/st-link-v2.html)
in-circuit debugger/flash programmer.

### install_firmware

Installs **MicroPython** firmware to the target board flash memory.

### nuke

Erases all of the target board flash memory (*i.e.* factory reset).

## Make Command Syntax

The exact target board is selected by two `gmake` macro variables:
`BOARDFAMILY` and `BOARDNAME`. Both of these can and should be
initialized by environment variables before invoking `gmake`.

The following command line pseudocode illustrates how to run, install,
or uninstall a **MicroPython** project with `gmake` (*most operating
systems symlink or alias `make` to `gmake`*):

    export ARMSRC=<your arm-mcu checkout directory>
    make <your make target>

## Make Command examples

    export ARMSRC=$HOME/arm-mcu

    # Run project on the target board
    make run
    make

    # Copy project to target board flash memory
    make install

    # Remove project from target board flash memory
    make uninstall

# [Visual Studio Code](https://code.visualstudio.com)

## [IntelliSense](https://code.visualstudio.com/docs/editing/intellisense)

You will need to install the Microsoft
[Python](https://github.com/microsoft/vscode-python) extension to enable
**IntelliSense** for Python3.

## Usage

Start **Visual Studio Code** by running the command `code .` in your
**MicroPython** project directory.

## Terminal Tasks

The file `.vscode/tasks.json` within each **MicroPython** project
defines **tasks** (*i.e.* actions) that can be invoked from the **Visual
Studio Code** command menu. These actions just run some of the `make`
commands described above.

### `CONTROL + SHIFT + B` or ⌘ + SHIFT + B `Terminal → Run Build Task...` `Terminal → Run Task... → Run project`

Executes `make run` to run your **MicroPython** project on your target
MCU. Press `CONTROL-X` in the **Visual Studio Code** terminal output tab
to terminate the project.

### `Terminal → Run Task... → Reset target MCU`

Executes `make reset` to reset the target MCU.

### `Terminal → Run Task... → Write project files to flash memory file system`

Executes `make install` to copy the project to the target MCU.

### `Terminal → Run Task... → Remove project files from flash memory file system`

Executes `make uninstall` to remove the project from the target MCU.

------------------------------------------------------------------------

Questions or comments to Philip Munts <phil@munts.net>
