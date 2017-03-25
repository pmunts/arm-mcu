# Makefile for building a Free Pascal cross compiler for ARM microcontrollers

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

ARMTOOLS	?= /usr/local/arm-mcu-tools
CONFIGURENAME	?= arm-none-eabi
SUBARCHS	:= armv4t armv6m armv7m armv7em
INSTALLDIR	:= $(shell pwd)/fpc-$(CONFIGURENAME)
RTLDIR		:= $(INSTALLDIR)/lib/fpc/$(FPC_VERSION)/units/arm-embedded/rtl
TARBALL		:= fpc-$(CONFIGURENAME).tgz

BUILDOPTS	+= CROSSINSTALL=1
BUILDOPTS	+= CPU_TARGET=arm
BUILDOPTS	+= OS_TARGET=embedded
BUILDOPTS	+= CROSSBINDIR=$(ARMTOOLS)/bin
BUILDOPTS	+= BINUTILSPREFIX=$(CONFIGURENAME)-
BUILDOPTS	+= INSTALL_PREFIX=$(INSTALLDIR)

ifeq ($(shell uname), Linux)
DEFAULT		:= package.deb
SED		:= sed
TAR		:= tar
OSNAME		?= unknown
PKGNAME		:= fpc-$(CONFIGURENAME)
PKGVER		:= $(shell date +%Y.%j)
PKGARCH		:= $(shell dpkg --print-architecture)
PKGSUFFIX	:= $(PKGVER)-$(OSNAME)-$(PKGARCH)
PKGDIR		:= $(PKGNAME)-$(PKGSUFFIX)
PKGFILE		:= $(PKGNAME)-$(PKGSUFFIX).deb
endif

ifeq ($(shell uname), Darwin)
DEFAULT		:= tarball.done
SED		:= gsed
TAR		:= gnutar
PKGNAME		:= fpc-$(CONFIGURENAME)
PKGSUFFIX	:= $(shell uname -s)-$(shell uname -r)-$(shell uname -m)
PKGVER		:= $(shell date +%Y.%j)
TARBALL		:= $(PKGNAME)-$(PKGVER)-$(PKGSUFFIX).tgz
TAROWNER	:= --owner root
TARGROUP	:= --group wheel
endif

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
DEFAULT		:= tarball.done
SED		:= sed
TAR		:= tar
PKGNAME		:= fpc-$(CONFIGURENAME)
PKGSUFFIX	:= $(shell uname -o)-$(shell uname -m)
PKGVER		:= $(shell date +%Y.%j)
TARBALL		:= $(PKGNAME)-$(PKGVER)-$(PKGSUFFIX).tgz
TAROWNER	:=
TARGROUP	:=
endif

default: $(DEFAULT)

################################################################################

# Download the source distribution

$(FPC_DIST):
	wget -nv -O $@ $(FPC_URL)

################################################################################

# Unpack the source distribution

src.done: $(FPC_DIST)
	$(TAR) xzf $^
	touch $@

################################################################################

# Build and install cross compiler (for a single subarchitecture)

build_subarch:
	$(MAKE) -C $(FPC_SRCDIR) $(BUILDOPTS) clean installbase SUBARCH=$(SUBARCH)
	mkdir -p $(RTLDIR)/$(SUBARCH)
	mv $(RTLDIR)/*.* $(RTLDIR)/$(SUBARCH)

################################################################################

# Build the cross compiler (for all subarchitectures)

build.done: src.done
	for S in $(SUBARCHS) ; do $(MAKE) build_subarch SUBARCH=$$S ; done
	touch $@

################################################################################

# Do final installation

install.done: build.done
	ln -s ../lib/fpc/$(FPC_VERSION)/ppcrossarm		$(INSTALLDIR)/bin/ppcrossarm
	mkdir -p						$(INSTALLDIR)/lib/fpc/etc
	install -cm 0644 fpc.cfg				$(INSTALLDIR)/lib/fpc/etc
	$(SED) -i 's#@@ARMTOOLS@@#$(ARMTOOLS)#g'		$(INSTALLDIR)/lib/fpc/etc/fpc.cfg
	$(SED) -i 's#@@CONFIGURENAME@@#$(CONFIGURENAME)#g'	$(INSTALLDIR)/lib/fpc/etc/fpc.cfg
	ln -s lib/fpc/etc					$(INSTALLDIR)/etc
	touch $@

################################################################################

# Create tarball

tarball.done: install.done
	$(TAR) czf $(TARBALL) fpc-$(CONFIGURENAME) --mode=ugo-w $(TAROWNER) $(TARGROUP)
	touch $@

################################################################################

# Create Debian package

package.deb: install.done
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control			$(PKGDIR)/DEBIAN
	$(SED) -i s/@@NAME@@/$(PKGNAME)/g		$(PKGDIR)/DEBIAN/control
	$(SED) -i s/@@ARCH@@/$(PKGARCH)/g		$(PKGDIR)/DEBIAN/control
	$(SED) -i s/@@VERSION@@/$(PKGVER)/g		$(PKGDIR)/DEBIAN/control
	$(SED) -i s/@@BOARDNAME@@/$(BOARDBASE)/g	$(PKGDIR)/DEBIAN/control
	mkdir -p					$(PKGDIR)/usr/local
	cp -R -P -p $(INSTALLDIR)			$(PKGDIR)/usr/local
	chmod -R ugo-w					$(PKGDIR)/usr/local/*
	fakeroot dpkg-deb --build			$(PKGDIR)
	chmod -R ugo+w					$(PKGDIR)

################################################################################

# Remove working files

clean:
	rm -rf *.done $(FPC_SRCDIR) $(INSTALLDIR) $(TARBALL) $(PKGDIR) $(PKGFILE)

reallyclean: clean

distclean: reallyclean
	-rm $(FPC_DIST)
