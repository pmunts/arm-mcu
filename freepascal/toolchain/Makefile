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

default: tarball.done

ifeq ($(shell uname), Linux)
OSNAME		?= unknown
PKGNAME		:= fpc-$(CONFIGURENAME)
PKGVER		:= $(shell date +%Y.%j)
PKGARCH		:= $(shell dpkg --print-architecture)
PKGSUFFIX	:= $(PKGVER)-$(OSNAME)-$(PKGARCH)
PKGDIR		:= $(PKGNAME)-$(PKGSUFFIX)
PKGFILE		:= $(PKGNAME)-$(PKGSUFFIX).deb
endif

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

# Build and install cross compiler (for a single subarchitecture)

build_subarch:
	$(MAKE) -C $(FPC_SRCDIR) $(BUILDOPTS) clean installbase SUBARCH=$(SUBARCH)
	mkdir -p $(RTLDIR)/$(SUBARCH)
	mv $(RTLDIR)/*.* $(RTLDIR)/$(SUBARCH)
	
################################################################################

# Build and install the cross compiler (for all subarchitectures)

build.done: src.done
	for S in $(SUBARCHS) ; do $(MAKE) build_subarch SUBARCH=$$S ; done
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	cp $(INSTALLDIR)/lib/fpc/$(FPC_VERSION)/ppcrossarm $(INSTALLDIR)/bin
else
	ln -s ../lib/fpc/$(FPC_VERSION)/ppcrossarm	$(INSTALLDIR)/bin/ppcrossarm
endif
	mkdir -p					$(INSTALLDIR)/lib/fpc/etc
	install -cm 0644 fpc.cfg			$(INSTALLDIR)/lib/fpc/etc
	sed -i 's#@@ARMTOOLS@@#$(ARMTOOLS)#g'		$(INSTALLDIR)/lib/fpc/etc/fpc.cfg
	sed -i 's#@@CONFIGURENAME@@#$(CONFIGURENAME)#g'	$(INSTALLDIR)/lib/fpc/etc/fpc.cfg
	touch $@

################################################################################

# Create tarball

tarball.done: build.done
ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
	tar czf $(TARBALL) $(INSTALLDIR) --mode=ugo-w
else
	tar czf $(TARBALL) $(INSTALLDIR) --mode=ugo-w --owner=root --group=root
endif
	touch $@

################################################################################

# Create Debian package

package.deb: build.done
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control			$(PKGDIR)/DEBIAN
	sed -i s/@@NAME@@/$(PKGNAME)/g			$(PKGDIR)/DEBIAN/control
	sed -i s/@@ARCH@@/$(PKGARCH)/g			$(PKGDIR)/DEBIAN/control
	sed -i s/@@VERSION@@/$(PKGVER)/g		$(PKGDIR)/DEBIAN/control
	sed -i s/@@BOARDNAME@@/$(BOARDBASE)/g		$(PKGDIR)/DEBIAN/control
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
