# Copyright (C)2017, Philip Munts, President, Munts AM Corp.
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

FPC_VERSION	= 3.0.2
FPC_SRCDIR	= fpc-$(FPC_VERSION)
FPC_TARBALL	= fpc-$(FPC_VERSION).source.tar.gz
FPC_SERVER	= https://downloads.sourceforge.net/project/freepascal/Source/$(FPC_VERSION)
FPC_URL		= $(FPC_SERVER)/$(FPC_TARBALL)
FPC_DIST	= $(TEMP)/$(FPC_TARBALL)

ARMTOOLS	= /usr/local/arm-mcu-tools

BUILDOPTS	= CROSSINSTALL=1 OS_TARGET=embedded
BUILDOPTS	+= CPU_TARGET=arm SUBARCH=armv7m
BUILDOPTS	+= BINUTILSPREFIX=arm-none-eabi-
BUILDOPTS	+= CROSSBINDIR=$(ARMTOOLS)/bin

OSNAME		?= unknown
PKGNAME		:= fpc-$(CONFIGURE_NAME)-linaro-$(BOARDBASE)
PKGVER		:= $(shell date +%Y.%j)
PKGARCH		:= $(shell dpkg --print-architecture)
PKGSUFFIX	:= $(PKGVER)-$(OSNAME)-$(PKGARCH)
PKGDIR		:= $(PKGNAME)-$(PKGSUFFIX)
PKGFILE		:= $(PKGNAME)-$(PKGSUFFIX).deb

INSTALLDIR	:= $(shell pwd)/$(PKGDIR)/usr/local/$(PKGNAME)

default: package.deb

################################################################################

# Download the source distribution

$(FPC_DIST):
	wget -nv -O $@ $(FPC_URL)

################################################################################

# Unpack the source distribution

src.done: $(FPC_DIST)
	tar xzf $^
	touch $@

################################################################################

# Build the cross compiler

build.done: src.done
	$(MAKE) -C $(FPC_SRCDIR) buildbase $(BUILDOPTS)

################################################################################

# Remove working files

clean:
	rm -rf *.done $(FPC_SRCDIR) $(PKGDIR) $(PKGFILE)

reallyclean: clean

distclean: reallyclean
	-rm $(FPC_DIST)
