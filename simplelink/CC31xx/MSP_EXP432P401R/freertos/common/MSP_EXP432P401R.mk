# Common make definitions for building SimpleLink WiFi Applications for the
# MSP-EXP432P401R + CC31xxBOOST dev boards.
#
# The project Makefile must define the CC31XXSRC macro before including this
# file.

COMMON		:= $(CC31XXSRC)/$(PLATFORM)/freertos/common

GCC_ARMCOMPILER	?= /usr/local/gcc-arm-none-eabi
SDK_INSTALL_DIR ?= /opt/simplelink

FREERTOS_INSTALL_DIR := $(SDK_INSTALL_DIR)/freertos
SIMPLELINK_MSP432_SDK_INSTALL_DIR := $(SDK_INSTALL_DIR)/simplelink_msp432p4_sdk
SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR := $(SDK_INSTALL_DIR)/simplelink_sdk_wifi_plugin
XDC_INSTALL_DIR	:= $(SDK_INSTALL_DIR)/xdctools

include $(SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR)/imports.mak

# Compile flags

CC		= "$(GCC_ARMCOMPILER)"/bin/arm-none-eabi-gcc

CFLAGS		+= -Wall -std=c99 -g -gstrict-dwarf
CFLAGS		+= -march=armv7e-m
CFLAGS		+= -mcpu=cortex-m4
CFLAGS		+= -mfloat-abi=hard
CFLAGS		+= -mfpu=fpv4-sp-d16
CFLAGS		+= -mthumb
CFLAGS		+= -fdata-sections
CFLAGS		+= -ffunction-sections
CFLAGS		+= -D__MSP432P401R__
CFLAGS		+= -DDeviceFamily_MSP432P401x
CFLAGS		+= -I.
CFLAGS		+= -I$(COMMON)
CFLAGS		+= -I"$(FREERTOS_INSTALL_DIR)"/FreeRTOS/Source/include
CFLAGS		+= -I"$(FREERTOS_INSTALL_DIR)"/FreeRTOS/Source/portable/GCC/ARM_CM4F
CFLAGS		+= -I"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/kernel/freertos/builds/MSP_EXP432P401R/release
CFLAGS		+= -I"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/source
CFLAGS		+= -I"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/source/third_party/CMSIS/Include
CFLAGS		+= -I"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/source/ti/posix/gcc
CFLAGS		+= -I"$(SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR)"/source
CFLAGS		+= -I"$(SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR)"/source/third_party/mbedtls/include

# Link flags

LDFLAGS		+= --specs=nano.specs
LDFLAGS		+= -march=armv7e-m
LDFLAGS		+= -mcpu=cortex-m4
LDFLAGS		+= -mfloat-abi=hard
LDFLAGS		+= -mfpu=fpv4-sp-d16
LDFLAGS		+= -mthumb
LDFLAGS		+= -nostartfiles
LDFLAGS		+= -Wl,-T,$(COMMON)/MSP_EXP432P401R.lds
LDFLAGS		+= -Wl,--gc-sections
LDFLAGS		+= -Wl,-Map,$(PROJECT).map
LDFLAGS		+= -L"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/kernel/freertos/builds/MSP_EXP432P401R/release/gcc
LDFLAGS		+= -L"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/source/ti/devices/msp432p4xx/driverlib/gcc
LDFLAGS		+= -L"$(SIMPLELINK_MSP432_SDK_INSTALL_DIR)"/source/ti/drivers/lib
LDFLAGS		+= -L"$(SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR)"/source/ti/drivers/net/wifi/gcc/rtos
LDFLAGS		+= -L"$(SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR)"/source/ti/drivers/net/wifi/slnetif/ccs/Release/
LDFLAGS		+= -L"$(SIMPLELINK_MSP432_SDK_WIFI_PLUGIN_INSTALL_DIR)"/source/ti/net/lib/gcc/m4f/
LDFLAGS		+= -l:drivers_msp432p401x.am4fg
LDFLAGS		+= -l:msp432p4xx_driverlib.a
LDFLAGS		+= -l:simplelink/simplelink.a
LDFLAGS		+= -l:slnetifwifi.a
LDFLAGS		+= -l:slnetsock_release.a
LDFLAGS		+= -l:freertos.lib
LDFLAGS		+= -lc
LDFLAGS		+= -lnosys

# Object files

OBJECTS		+= $(COMMON)/MSP_EXP432P401R.o
OBJECTS		+= $(COMMON)/console.o
OBJECTS		+= $(COMMON)/events.o
OBJECTS		+= $(COMMON)/main.o
OBJECTS		+= $(COMMON)/tasklist.o
OBJECTS		+= $(COMMON)/ti_drivers_net_wifi_Config.o
OBJECTS		+= $(COMMON)/wifi.o

# Define a pattern rule for compiling C source code files

%.o: %.c
	@echo $@
	@$(CC) $(CFLAGS) -c -o $@ $<

# Define a pattern rule for building the project

%.out:
	$(MAKE) $(OBJECTS)
	@echo $@
	@$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

# Default target--Build the target

msp_exp432p401r_default: $(PROJECT).out

# Remove working files

msp_exp432p401r_clean:
	rm -f $(PROJECT).out $(PROJECT).map $(OBJECTS)
