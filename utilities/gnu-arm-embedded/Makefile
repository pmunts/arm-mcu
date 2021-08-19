# Makefile for packaging GNU ARM Embedded for Debian

# Copyright (C)2019, Philip Munts, President, Munts AM Corp.
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

# You have to manually download the GNU ARM Embedded distribution file and
# then do make DISTFILE=<filename>

DISTFILE	?= unknown
INSTALLDIR	= /usr/local/bin

OSNAME		?= unknown
PKGNAME		:= gnu-arm-embedded
PKGVERSION	:= $(shell basename $(DISTFILE) | awk -F '[-]' '{ printf("%s-%s\n", $$5, $$6) }')
PKGARCH		:= $(shell dpkg --print-architecture)
PKGDIR		:= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		:= $(PKGDIR).deb

# Create Debian package file

package.deb:
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control			$(PKGDIR)/DEBIAN
	sed -i 's/@@ARCH@@/$(PKGARCH)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@NAME@@/$(PKGNAME)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@VERSION@@/$(PKGVERSION)/g'		$(PKGDIR)/DEBIAN/control
	install -cm 0755 postinst			$(PKGDIR)/DEBIAN
	install -cm 0755 prerm				$(PKGDIR)/DEBIAN
	mkdir -p					$(PKGDIR)/usr/local
	tar xjf $(DISTFILE) -C				$(PKGDIR)/usr/local
	sed -i "s#@@DESTDIR@@#`ls $(PKGDIR)/usr/local`#g" $(PKGDIR)/DEBIAN/postinst
	chmod -R ugo-w $(PKGDIR)/usr
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R ugo+w $(PKGDIR)/usr

# Clean out working files

clean:
	-rm -rf $(PKGDIR) $(PKGFILE)

reallyclean: clean

distclean: reallyclean
	-rm -rf $(DISTFILE)
