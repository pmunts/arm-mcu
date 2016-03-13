# Makefile for EFM32 libraries imported from Engery Micro and other sources

# $Id: SDK.mk 9918 2016-02-09 07:53:15Z svn $

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

SDKDIR		= $(ARMSRC)/efm32/SDK

# Definitions for the EFM32 CMSIS library

CMSISDIR	= $(SDKDIR)/CMSIS
DEVICEDIR	= $(SDKDIR)/Device/SiliconLabs/$(MCUSUBFAMILY)
EMLIBDIR	= $(SDKDIR)/emlib

CFLAGS		+= -I$(CMSISDIR)/Include
CFLAGS		+= -I$(DEVICEDIR)/Include
CFLAGS		+= -I$(EMLIBDIR)/inc

# Compile source files and add objects to the library

sdklibs:
	for F in $(DEVICEDIR)/Source/*.c ; do $(MAKE) $${F%.c}.o ; done
	for F in $(EMLIBDIR)/src/*.c ; do $(MAKE) $${F%.c}.o ; done
	$(FIND) $(SDKDIR) -type f -name '*.o' -exec $(AR) crs lib$(MCU).a {} ";"

# Add to target lists

LIBTARGETS	+= sdklibs
