# STM32F4 family make definitions

# Copyright (C)2013-2016, Philip Munts, President, Munts AM Corp.
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

CPUFLAGS	+= -mcpu=cortex-m4 -mthumb -DCORTEX_M4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
FLASHWRITEADDR	?= 0x08000000
TEXTBASE	?= 0x00000000

CFLAGS		+= -DSTM32F4XX
LDFLAGS		+= -Ttext $(TEXTBASE)

FREERTOS_ARCH	= ARM_CM4F

OPENOCDCFG	= $(MCUDIR)/$(MCUFAMILY).openocd
OPENOCDFLASH	= $(MCUDIR)/$(MCUFAMILY).flashocd
OPENOCDIF	= stlink-v2

# Include subordinate makefiles

include $(MCUDIR)/boards.mk
include $(MCUDIR)/CMSIS/cmsis.mk
#include $(MCUDIR)/usb_serial/usb_serial.mk

# Build processor dependent support library

LIBOBJS		= $(MCU).o adc.o cpu.o gpiopins.o serial.o $(EXTRALIBOBJS)

lib$(MCU).a: $(LIBOBJS)
	$(AR) crs lib$(MCU).a $(LIBOBJS)
	$(MAKE) $(LIBTARGETS)

# Clean out working files

clean_$(MCU):

reallyclean_$(MCU): clean_$(MCU)

distclean_$(MCU): reallyclean_$(MCU)
