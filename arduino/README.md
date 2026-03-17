# Arduino Framework for ARM Platforms

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
  Platforms** checkout directory (*e.g.* **`~/arm-mcu/arduino/`**) from
  **`File → Preferences → Sketchbook location`**.

Your project does ***not*** need to be within the **Arduino Framework
for ARM Platforms** checkout directory.

The Arduino IDE 2 does not use anything from the GNU make project except
for the sketch source file(s).

An Arduino IDE 2 Debian package for Linux x86-64 *aka* amd64 machines is
available at the [Munts Technologies Debian Package
Repository](https://repo.munts.com/debian13/). It is packaged from the
official Arduino release. Unfortunately there is no official Arduino IDE
2 release for ARMv8 *aka* arm64 machines.

## Visual Studio Code

## FreeRTOS

## Libraries

------------------------------------------------------------------------

Questions or comments to Philip Munts <phil@munts.net>
