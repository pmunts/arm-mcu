# Makefile definitions for building GNAT Ada application programs for the
# STM32F4 microcontroller family

# $Id$

# Copyright (C)2015, Philip Munts, President, Munts AM Corp.
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

# Don't delete intermediate files

.SECONDARY:

# Toolchain definitions

ADA_INCLUDES		?= -I. -I$(ADA_SRC)
ADA_OBJ			?= obj
ADA_VERSION		?= -gnat2012

GNATARCH		= arm-eabi
GNATRELEASE		= 2015
GNATDIR			?= /usr/local/gnat-gpl-$(GNATRELEASE)-$(GNATARCH)
GNATBIN			= $(GNATDIR)/bin
GNATPROFILE		?= ravenscar-full
GNATRTS			= $(GNATPROFILE)-$(MCUFAMILY)-$(GNATRELEASE)
GNATRTSDIR		= $(ADA_SRC)/runtimes/$(GNATRTS)
GPRBUILD		= env PATH=$(GNATBIN)':'$(PATH) ADA_SRC=$(ADA_SRC) ADA_OBJ=$(ADA_OBJ) MCUFAMILY=$(MCUFAMILY) BOARDNAME=$(BOARDNAME) gprbuild
GPRBUILDFLAGS		= -p --RTS=$(GNATRTSDIR) --target=$(GNATARCH)
GPRBUILDCFLAGS		= -cargs:Ada $(ADA_VERSION) $(ADA_CFLAGS)
GPRBUILDLDFLAGS		= -largs -Wl,-Map=test_console.map,--cref

# Override the following macros previously defined in ARM.mk

OBJCOPY			= $(GNATBIN)/$(GNATARCH)-objcopy
GDB			= $(GNATBIN)/$(GNATARCH)-gdb
OPENOCDDEBUG		= $(ADA_SRC)/ada.gdb
STLINKDEBUG		= $(ADA_SRC)/ada.gdb

# Build program from project file

%.elf: %.gpr
	$(MAKE) -C $(GNATRTSDIR) ADA_SRC=$(ADA_SRC) MCUFAMILY=$(MCUFAMILY) BOARDNAME=$(BOARDNAME)
	$(GPRBUILD) $< $(GPRBUILDFLAGS) $(GPRBUILDCFLAGS) $(GPRBUILDLDFLAGS)

# Default make target

ada_mk_default:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# Clean out working files

ada_mk_clean:
	-rm -rf *.asm *.bin *.elf *.hex *.log *.map *.o *.stackdump obj

ada_mk_reallyclean: ada_mk_clean
	$(MAKE) -C $(GNATRTSDIR) clean

ada_mk_distclean: ada_mk_reallyclean
