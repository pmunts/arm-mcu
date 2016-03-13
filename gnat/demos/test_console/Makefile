# Makefile for building the GNAT Ada serial console test

# Copyright (C)2015-2016, Philip Munts, President, Munts AM Corp.
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

ARMSRC		?= $(HOME)/src/ARM
ADA_SRC		?= $(ARMSRC)/gnat

# Select the target board

#BOARDNAME	?= FEZ_CERB40
#BOARDNAME	?= NETDUINOPLUS2
BOARDNAME	?= NUCLEO_F411RE
#BOARDNAME	?= STM32F4_DISCOVERY
#BOARDNAME	?= STM32_M4_MINI

# Build the program

build: test_console.elf

# Write the program to code flash

install: test_console.flash

# Remove working files

clean: ada_mk_clean

reallyclean: ada_mk_reallyclean

distclean: ada_mk_distclean

# Include subordinate makefiles

include $(ADA_SRC)/boards/$(BOARDNAME)/bsp.mk
include $(ADA_SRC)/ada.mk
include $(ARMSRC)/include/ARM.mk
sinclude $(HOME)/src/include/subversion.mk
