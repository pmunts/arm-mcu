# Makefile for building GDB server and flash utility for STM32 ST-Link

# $Id$

# Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
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

STLINKURL	= http://github.com/texane/stlink.git
STLINKSRC	= stlink
STLINKFLASH	= stlink-flash
STLINKGDB	= stlink-gdbserver

LIBUSBCFLAGS	= -DLIBUSB_CALL='' $(shell pkg-config --cflags libusb-1.0)
INSTALLDIR	= /usr/local/bin

OSNAME		?= unknown
PKGNAME		= texane-stlink
PKGVERSION	= $(shell awk '/PACKAGE_VERSION=/ { print substr($$1, 18, length($$1)-18); }' $(STLINKSRC)/configure)
PKGARCH		= $(shell dpkg --print-architecture)
PKGDIR		= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		= $(PKGDIR).deb

default: $(STLINKFLASH)

# Download stlink-gdbserver source distribution

$(STLINKSRC):
	git clone --depth 1 $(STLINKURL) $(STLINKSRC)
	cd $(STLINKSRC) && ./autogen.sh && ./configure USB_CFLAGS="$(LIBUSBCFLAGS)"

# Compile stlink-gdbserver

$(STLINKFLASH): $(STLINKSRC)
	$(MAKE) -C $(STLINKSRC)
	cp $(STLINKSRC)/st-flash			$(STLINKFLASH)
	cp $(STLINKSRC)/st-util				$(STLINKGDB)

# Install programs

install: $(STLINKFLASH)
	install -csm 0555 $(STLINKFLASH)		$(INSTALLDIR)
	install -csm 0555 $(STLINKGDB)			$(INSTALLDIR)

# Uninstall programs

uninstall:
	-rm $(INSTALLDIR)/$(STLINKGDB)
	-rm $(INSTALLDIR)/$(STLINKFLASH)

# Create Debian package file

package.deb: $(STLINKFLASH)
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control.template		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@ARCH@@/$(PKGARCH)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@NAME@@/$(PKGNAME)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@VERSION@@/$(PKGVERSION)/g'		$(PKGDIR)/DEBIAN/control
	mkdir -p					$(PKGDIR)/$(INSTALLDIR)
	install -csm 0755 $(STLINKFLASH)		$(PKGDIR)/$(INSTALLDIR)
	install -csm 0755 $(STLINKGDB)			$(PKGDIR)/$(INSTALLDIR)
	chmod -R ugo-w $(PKGDIR)/$(INSTALLDIR)/*
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R ugo+w $(PKGDIR)/$(INSTALLDIR)/*

# Clean out working files

clean:
	-rm -rf $(STLINKFLASH) $(STLINKGDB) $(PKGDIR) $(PKGFILE)
	-$(MAKE) -C $(STLINKSRC) clean

reallyclean: clean

distclean: reallyclean
	-rm -rf $(STLINKSRC)
