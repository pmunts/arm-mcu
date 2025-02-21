# Makefile for packaging GNU ARM Embedded for Debian

# Copyright (C)2019-2025, Philip Munts dba Munts Technologies.
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

PKGNAME		:= $(strip $(shell basename $(DISTFILE) .tar.xz | awk -F '[-]' '{ printf("%s-%s-%s-%s-%s-%s-%s", $$1, $$2, $$3, $$4, $$6, $$7, $$8) }'))
PKGVERSION	:= $(strip $(shell basename $(DISTFILE) .tar.xz | awk -F '[-]' '{ printf("%s", $$4) }'))
PKGTARGET	:= $(strip $(shell basename $(DISTFILE) .tar.xz | awk -F '[-]' '{ printf("gcc-%s-%s-%s", $$6, $$7, $$8) }'))
PKGARCH		:= $(shell dpkg --print-architecture)
PKGDIR		:= $(PKGNAME)-$(PKGARCH)
PKGFILE		:= $(PKGDIR).deb

SRCDIR		:= /usr/local/$(shell basename $(DISTFILE) .tar.xz)
DSTDIR		:= /usr/local/$(PKGNAME)

# Create Debian package fil

package.deb:
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control			$(PKGDIR)/DEBIAN
	sed -i 's/@@ARCH@@/$(PKGARCH)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@NAME@@/$(PKGNAME)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@VERSION@@/$(PKGVERSION)/g'		$(PKGDIR)/DEBIAN/control
	install -cm 0755 postinst			$(PKGDIR)/DEBIAN
	sed -i 's#@@DESTDIR@@#$(PKGNAME)#g'		$(PKGDIR)/DEBIAN/postinst
	sed -i 's/@@LINKNAME@@/$(PKGTARGET)/g'		$(PKGDIR)/DEBIAN/postinst
	install -cm 0755 prerm				$(PKGDIR)/DEBIAN
	sed -i 's/@@LINKNAME@@/$(PKGTARGET)/g'		$(PKGDIR)/DEBIAN/prerm
	mkdir -p					$(PKGDIR)/usr/local
	tar xJf $(DISTFILE) -C				$(PKGDIR)/usr/local
	mv $(PKGDIR)$(SRCDIR) $(PKGDIR)$(DSTDIR)
	chmod -R ugo-w $(PKGDIR)/usr
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R ugo+w $(PKGDIR)/usr

# Clean out working files

clean:
	-rm -rf $(PKGDIR) $(PKGFILE)

reallyclean: clean

distclean: reallyclean
	-rm -rf $(DISTFILE)
