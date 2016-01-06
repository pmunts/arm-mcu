# Generic Makefile for compiling ARM microcontroller firmware

# $Id$

# Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

# Toolchain definitions

ARMTOOLS	?= /usr/local/arm-mcu-tools
CROSS_COMPILE	?= $(ARMTOOLS)/bin/arm-none-eabi-

CC		= $(CROSS_COMPILE)gcc
CXX		= $(CROSS_COMPILE)g++
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar
STRIP		= $(CROSS_COMPILE)strip
OBJCOPY		= $(CROSS_COMPILE)objcopy
OBJDUMP		= $(CROSS_COMPILE)objdump
GDB		= $(CROSS_COMPILE)gdb

FIND		?= find

# Framework general definitions

MCUFAMILYNAME	:= $(shell echo $(MCUFAMILY) | tr '[a-z]' '[A-Z]')
MCUDIR		?= $(ARMSRC)/$(MCUFAMILY)
MCULIBRARY	= $(MCUDIR)/lib$(MCU).a
MCULINKSCRIPT	= $(MCUDIR)/$(MCU).ld

# Recursive make flags, to be passed to subordinate makes

RMAKEFLAGS	+= ARMSRC=$(ARMSRC)
RMAKEFLAGS	+= ARMTOOLS=$(ARMTOOLS)
RMAKEFLAGS	+= BOARDNAME=$(BOARDNAME)
RMAKEFLAGS	+= FREERTOS_ARCH=$(FREERTOS_ARCH)

# Compiler and linker flags

CPUFLAGS	+= -D$(MCU) -D$(BOARDNAME) -DBOARDNAME='"$(BOARDNAME)"' -DMCUFAMILYNAME='"$(MCUFAMILYNAME)"'
DEBUGFLAGS	?= -g
OPTFLAGS	?= -O0
CFLAGS		+= $(EARLYFLAGS)
CFLAGS		+= -Wall -ffunction-sections
CFLAGS		+= -I$(ARMSRC)/include -I$(MCUDIR)
CFLAGS		+= $(OPTFLAGS) $(CPUFLAGS) $(BOARDFLAGS) $(CONSOLEFLAGS) $(IOFLAGS) $(CONFIGFLAGS) $(DEBUGFLAGS) $(EXTRAFLAGS)
CXXFLAGS	+= -fno-use-cxa-atexit
LDFLAGS		+= -nostartfiles -T$(MCULINKSCRIPT) -L$(MCUDIR) -l$(MCU) -lm -lstdc++
LDFLAGS		+= -Wl,-Map=$*.map,--cref,--gc-sections $(EXTRAOBJS)

# GDB definitions

GDBSERVERPORT	= 3333
#GDBGUI		?= ddd --gdb --debugger
#GDBFLAGS	?= -tui

# These targets are not files

.PHONY: ARM_mk_default ARM_mk_clean

# These are the target suffixes

.SUFFIXES: .asm .c .cpp .bin .dmp .elf .hex .o .s .S

# Don't delete intermediate files

.SECONDARY:

# Now define some suffix rules

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

.cpp.o:
	$(CXX) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

.o.elf:
	$(MAKE) -C $(MCUDIR) lib$(MCU).a $(RMAKEFLAGS)
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

.elf.asm:
	$(OBJDUMP) -S -d $< >$@

.elf.bin:
	$(OBJCOPY) -S -O binary --gap-fill=0 $< $@

.elf.hex:
	$(OBJCOPY) -S -O ihex --change-addresses=$(FLASHWRITEADDR) --gap-fill=0 $< $@

.bin.dmp:
	hexdump -C $< > $@

.s.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

.S.o:
	$(CC) $(CFLAGS) -c -o $@ -c $<

# Define default target placeholder

ARM_mk_default:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# Support for common library functions

COMMON_DIR	= $(ARMSRC)/common
include $(COMMON_DIR)/common.mk

# Support for lightweight console I/O library

ifeq ($(WITH_CONIO), yes)
IOFLAGS += -DCONIO_STDIO
endif

# Support for floating point I/O

ifeq ($(WITH_FLOATINPUT), yes)
IOFLAGS	+= -DFLOATIO -u _scanf_float
endif

ifeq ($(WITH_FLOATOUTPUT), yes)
IOFLAGS	+= -DFLOATIO -u _printf_float
endif

ifeq ($(WITH_FLOATIO), yes)
IOFLAGS	+= -DFLOATIO -u _printf_float -u _scanf_float
endif

# Support for FreeRTOS

ifeq ($(WITH_FREERTOS), yes)
FREERTOS_DIR	= $(ARMSRC)/FreeRTOS
include $(FREERTOS_DIR)/FreeRTOS.mk
endif

# Build the MCU dependent support library

ARM_mk_lib:
	$(MAKE) -C $(MCUDIR) lib$(MCU).a $(RMAKEFLAGS)

# Clean out working files

ARM_mk_clean:
	$(FIND) * -name '*.o' -exec rm {} ";"
	rm -f *.a *.asm *.bin *.dmp *.elf *.hex *.log *.map *.stackdump *.tmp Default.ini
	cd $(MCUDIR) && $(MAKE) clean_$(MCU) $(RMAKEFLAGS)
	cd $(MCUDIR) && $(FIND) * -name '*.o' -exec rm {} ";"
	cd $(MCUDIR) && rm -f *.a *.asm *.bin *.dmp *.elf *.hex *.log *.map *.stackdump *.tmp Default.ini
	$(MAKE) $(CLEANTARGETS) $(RMAKEFLAGS)

# Include programming and debugging makefiles

include $(ARMSRC)/include/dfu.mk
include $(ARMSRC)/include/jlink.mk
include $(ARMSRC)/include/lpc21isp.mk
include $(ARMSRC)/include/mbed.mk
include $(ARMSRC)/include/openocd.mk
include $(ARMSRC)/include/stlink.mk

# Include MCU dependent makefile

include $(MCUDIR)/$(MCUFAMILY).mk
