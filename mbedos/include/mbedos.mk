# Common make definitions for building Mbed OS applications

# Copyright (C)2017-2019, Philip Munts, President, Munts AM Corp.
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

# To install the common Mbed OS libraries, either install Debian package
# mbedos from http://repo.munts.com, or run the following commands:
#
# sudo pip install mbed-cli
# sudo mbed new /usr/local/lib/mbedos

MBED		?= mbed
MBEDOSDIR	?= /usr/local/lib/mbedos

BLDDIRBASE	?= build
LIBDIRBASE	?= $(HOME)/.mbedos

BLDDIR		?= $(BLDDIRBASE)/$(BOARDNAME)
LIBDIR		?= $(LIBDIRBASE)/$(BOARDNAME)
SRCDIR		?= src

PROJECTNAME	?= $(shell basename $(shell pwd))
TOOLCHAINNAME	?= GCC_ARM

MBEDCLIFLAGS	+= -m $(BOARDNAME) -N $(PROJECTNAME) -t $(TOOLCHAINNAME)
MBEDCLIFLAGS	+= -D__mbedos__
MBEDCLIFLAGS	+= -DBOARDNAME='"$(BOARDNAME)"'
MBEDCLIFLAGS	+= -DPROJECTNAME='"$(PROJECTNAME)"'
MBEDCLIFLAGS	+= -DTOOLCHAINNAME='"$(TOOLCHAINNAME)"'
MBEDCLIFLAGS	+= --source=$(SRCDIR) --source=$(LIBDIR) --build=$(BLDDIR)

# Default target placeholder

mbedos_mk_default: default

# Import board specific definitions

include $(ARMSRC)/mbedos/include/boards.mk

# Build the Mbed OS library

$(LIBDIR)/libmbed-os.a:
	ln -s -f $(MBEDOSDIR)/mbed-os
	ln -s -f $(MBEDOSDIR)/mbed_settings.py
	$(MBED) compile -t $(TOOLCHAINNAME) -m $(BOARDNAME) --library --source=mbed-os --build=$(LIBDIR)

library: $(LIBDIR)/libmbed-os.a

# Build the Mbed OS application

$(PROJECTNAME).bin:
	$(MAKE) $(LIBDIR)/libmbed-os.a
	ln -s -f $(MBEDOSDIR)/mbed-os
	ln -s -f $(MBEDOSDIR)/mbed_settings.py
	$(MBED) compile $(MBEDCLIFLAGS)
	cp $(BLDDIR)/$(PROJECTNAME).bin .

mbedos_mk_build: $(PROJECTNAME).bin

# Flash the compiled firmware to the target board

mbedos_mk_install: $(PROJECTNAME).$(FLASHSUFFIX)

# Remove working files

mbedos_mk_clean:
	-rm -rf $(PROJECTNAME).bin $(BLDDIR)

mbedos_mk_reallyclean: mbedos_mk_clean
	-rm -rf .mbed mbed* $(BLDDIRBASE)

mbedos_mk_distclean: mbedos_mk_reallyclean
	-rm -rf $(LIBDIRBASE)

# Include some more subordinate makefiles

sinclude $(ARMSRC)/gcc/include/dfu.mk
sinclude $(ARMSRC)/gcc/include/jlink.mk
sinclude $(ARMSRC)/gcc/include/lpc21isp.mk
sinclude $(ARMSRC)/gcc/include/mbed.mk
sinclude $(ARMSRC)/gcc/include/openocd.mk
sinclude $(ARMSRC)/gcc/include/stlink.mk
