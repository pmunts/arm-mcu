# Makefile for building an Mbed OS application

# Copyright (C)2019, Philip Munts, President, Munts AM Corp.
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

# Override the following macros to build out of tree

ARMSRC		?= $(HOME)/arm-mcu
MBEDOSSRC	?= $(ARMSRC)/mbed5

# Project settings

PROJECTNAME	:= test_usbhid
BOARDNAME	:= NUCLEO_F401RE
TOOLCHAINNAME	:= GCC_ARM

MBEDCLIFLAGS	= -m $(BOARDNAME) -N $(PROJECTNAME) -t $(TOOLCHAINNAME)
MBEDCLIFLAGS	+= --source $(MBEDOSSRC)/FEZ/include
MBEDCLIFLAGS	+= --source mbed-os/features/unsupported/USBDevice

# Flash programmer settings

FLASHSUFFIX	:= flashdfu
FLASHWRITEADDR	:= 0x08000000

include $(ARMSRC)/gcc/include/dfu.mk
include $(MBEDOSSRC)/include/mbed5.mk

# Build the application

default: mbed5_mk_build

# Install the application

install: mbed5_mk_install

# Remove working files

clean: mbed5_mk_clean

reallyclean: mbed5_mk_reallyclean

distclean: mbed5_mk_distclean
