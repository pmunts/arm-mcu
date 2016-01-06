# Makefile template for building a customized GNAT Ada Ravenscar profile
# run time library for the STM32F4 microcontroller family

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

# Override the following macros to build out of tree

ARMSRC		?= $(HOME)/src/ARM
ADA_SRC		?= $(ARMSRC)/gnat

# Build the Run Time Library

adalib/libgnat.a:
	cp arch/s-bbpara.ads.$(BOARDNAME) arch/s-bbpara.ads
	cp arch/setup_pll.adb.$(BOARDNAME) arch/setup_pll.adb
#TODO: a-intnam.ads also needs to be customized for each MCU
	$(GPRBUILD) runtime_build.gpr -p --target=$(GNATARCH)

# Remove working files

clean:
	rm -rf adalib/*.a adalib/*.ali obj
	rm -f arch/s-bbpara.ads arch/setup_pll.adb

include $(ADA_SRC)/ada.mk
sinclude $(HOME)/src/include/subversion.mk
