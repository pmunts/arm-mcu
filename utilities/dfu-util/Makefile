# Makefile for building STM32 DFU flash utility dfu-util

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

TEMP		?= /tmp

DFUNAME		= dfu-util
DFUVERSION	= 0.8
DFUSRC		= $(DFUNAME)-$(DFUVERSION)
DFUTARBALL	= $(DFUSRC).tar.gz
DFUDIST		= $(TEMP)/$(DFUTARBALL)
DFUSERVER	= http://dfu-util.sourceforge.net/releases
DFUURL		= $(DFUSERVER)/$(DFUTARBALL)

INSTALLDIR	= /usr/local/bin

OSNAME		?= unknown
PKGNAME		= $(DFUNAME)
PKGVERSION	= $(shell awk '/PACKAGE_VERSION=/ { print substr($$1, 18, length($$1)-18); }' $(DFUSRC)/configure)
PKGARCH		= $(shell dpkg --print-architecture)
PKGDIR		= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		= $(PKGDIR).deb

default: build.done

# Download source distribution

$(DFUDIST):
	wget -P $(TEMP) $(DFUURL)

# Unpack source distribution

source.done: $(DFUDIST)
	tar xzf $(DFUDIST)
	touch $@

# Compile dfu-util

build.done: source.done
	cd $(DFUSRC) ; ./configure
	$(MAKE) -C $(DFUSRC)
	touch $@

# Install dfu-util

install: build.done
	$(MAKE) -C $(DFUSRC) install

# Create Debian package file

package.deb: build.done
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control.template		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@ARCH@@/$(PKGARCH)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@NAME@@/$(PKGNAME)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@VERSION@@/$(PKGVERSION)/g'		$(PKGDIR)/DEBIAN/control
	mkdir -p					$(PKGDIR)/$(INSTALLDIR)
	$(MAKE) -C $(DFUSRC) install DESTDIR=$(shell pwd)/$(PKGDIR)
	chmod -R ugo-w $(PKGDIR)/$(INSTALLDIR)/*
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R ugo+w $(PKGDIR)/$(INSTALLDIR)/*

# Clean out working files

clean:
	-rm -rf *.done $(DFUSRC) $(PKGDIR) $(PKGFILE)

reallyclean: clean

distclean: reallyclean
	-rm -rf $(DFUDIST)
