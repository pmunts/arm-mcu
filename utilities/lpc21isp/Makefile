# Makefile for building LPC21ISP RPM package

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

LPC21ISP_NAME	= lpc21isp
LPC21ISP_URL	= http://github.com/capiman/lpc21isp.git
LPC21ISP_DIR	= lpc21isp.src
LPC21ISP_VER	= $(shell awk '/define VERSION_STR/ { print substr($$3, 2, length($$3)-2); }' $(LPC21ISP_DIR)/lpc21isp.c)
LPC21ISP_PROG	= $(LPC21ISP_NAME)

CC		= $(CROSS_COMPILE)gcc
CFLAGS		= -Wall
INSTALLDIR	= /usr/local/bin

OSNAME		?= unknown
PKGNAME		= $(LPC21ISP_NAME)
PKGVERSION	= $(LPC21ISP_VER)
PKGARCH		= $(shell dpkg --print-architecture)
PKGDIR		= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		= $(PKGDIR).deb

default: $(LPC21ISP_PROG)

# Fetch lpc21isp source tree

$(LPC21ISP_DIR):
	git clone --depth 1 $(LPC21ISP_URL) $(LPC21ISP_DIR)

# Compile lpc21isp

$(LPC21ISP_PROG): $(LPC21ISP_DIR)
	$(MAKE) -C $(LPC21ISP_DIR) CC=$(CC) CFLAGS=$(CFLAGS)
	cp $(LPC21ISP_DIR)/$(LPC21ISP_PROG) $(LPC21ISP_PROG)

# Install lpc21isp

install: $(LPC21ISP_PROG)
	install -csm 0555 $(LPC21ISP_PROG) $(INSTALLDIR)

# Uninstall lpc21isp

uninstall:
	-rm $(INSTALLDIR)/$(LPC21ISP_PROG)

# Install lpc21isp to fakeroot

fakeroot: $(LPC21ISP_PROG)
	mkdir -p fakeroot/$(INSTALLDIR)
	install -csm 0555 $(LPC21ISP_PROG) fakeroot/$(INSTALLDIR)

# Create RPM package

specfile: fakeroot specfile.template
	sed s#@@VERSION@@#$(LPC21ISP_VER)#g <specfile.template >specfile

package.rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .

# Create Deb package

package.deb: $(LPC21ISP_PROG)
	mkdir -p					$(PKGDIR)/DEBIAN
	mkdir -p					$(PKGDIR)/$(INSTALLDIR)
	install -cm 0644 control.template		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@ARCH@@/$(PKGARCH)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@NAME@@/$(PKGNAME)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@VERSION@@/$(PKGVERSION)/g'		$(PKGDIR)/DEBIAN/control
	install -csm 0755 $(LPC21ISP_PROG)		$(PKGDIR)/$(INSTALLDIR)
	chmod -R ugo-w $(PKGDIR)/$(INSTALLDIR)/*
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R ugo+w $(PKGDIR)/$(INSTALLDIR)/*

# Clean out working files

clean:
	-$(MAKE) -C $(LPC21ISP_DIR) clean
	-rm -rf $(LPC21ISP_PROG)
	-rm -rf fakeroot
	-rm -rf rpmbuild
	-rm -rf $(PKGDIR)
	-rm *.deb
	-rm *.rpm
	-rm specfile

reallyclean: clean
	-rm -rf $(LPC21ISP_DIR)

distclean: reallyclean
