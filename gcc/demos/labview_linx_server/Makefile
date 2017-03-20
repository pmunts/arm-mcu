# Makefile for STM32F411 IoT Responder

# Copyright (C)2016-2017, Philip Munts, President, Munts AM Corp.
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

ARMSRC		?= $(HOME)/arm-mcu
MCUFAMILY	?= stm32f4
BOARDNAME	?= NUCLEO_F411RE

CFLAGS		+= -D_GLIBCXX_USE_C99=1 -std=c++1y -I.

SOURCES		= main.cpp
SOURCES		+= linx/analog.cpp
SOURCES		+= linx/command.cpp
SOURCES		+= linx/common.cpp
SOURCES		+= linx/executive.cpp
SOURCES		+= linx/gpio.cpp
SOURCES		+= linx/pwm.cpp
SOURCES		+= linx/servo.cpp
SOURCES		+= gpio-gpiopins.cpp

default: linx_server.bin

include $(ARMSRC)/gcc/include/ARM.mk

linx_server.elf: $(SOURCES)
	$(MAKE) ARM_mk_lib
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)	

install: linx_server.flashstlink

clean:
	rm -f *.bin *.elf *.exe *.hex *.map *.o client

reallyclean: clean ARM_mk_clean

distclean: reallyclean
