# Makefile for building the ARM Mbed OS CLI package for Debian Linux

# Copyright (C)2017-2019, Philip Munts, President, Munts AM Corp.
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

OSNAME		?= unknown
PKGNAME		= mbedos
PKGARCH		:= all
PKGVERSION	:= $(shell date +%Y.%j)
PKGDIR		:= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		:= $(PKGDIR).deb
TARBALL		:= $(PKGNAME)-$(PKGVERSION).tgz
TARFLAGS	?= --owner=root --group=root --mode=ugo-w

default: $(PKGFILE)

$(PKGFILE): $(PKGDIR)
	chmod -R ugo-w $(PKGDIR)/usr
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R u+w $(PKGDIR)/usr

$(PKGDIR):
	mkdir -p $(PKGDIR)/DEBIAN
	install -cm 0444 control		$(PKGDIR)/DEBIAN
	install -cm 0755 postinst		$(PKGDIR)/DEBIAN
	sed -i s/@@ARCH@@/$(PKGARCH)/g		$(PKGDIR)/DEBIAN/control
	sed -i s/@@NAME@@/$(PKGNAME)/g		$(PKGDIR)/DEBIAN/control
	sed -i s/@@VERSION@@/$(PKGVERSION)/g	$(PKGDIR)/DEBIAN/control
	mkdir -p				$(PKGDIR)/usr/local/lib
	cd $(PKGDIR)/usr/local/lib ; mbed new mbedos
ifneq ($(BRANCH),)
	cd $(PKGDIR)/usr/local/lib/mbedos/mbed-os ; git reset --hard origin/$(BRANCH) ; git checkout $(BRANCH)
endif
	cd $(PKGDIR) ; patch -b -p0 <../FEZ.patch
	rm $(PKGDIR)/usr/local/lib/mbedos/mbed_app.json
	rm $(PKGDIR)/usr/local/lib/mbedos/mbed-os.lib
	-find $(PKGDIR) -name '.git*' -exec rm -rf {} ";"
	-find $(PKGDIR) -name '*.orig' -exec rm {} ";"

populate: $(PKGDIR)

# Create tarball for e.g. MacOS

$(TARBALL): populate
	cd $(PKGDIR)/usr/local/lib && tar czf ../../../../$(TARBALL) mbedos $(TARFLAGS)

tarball: $(TARBALL)

# Remove working files

clean:
	-rm -rf $(PKGDIR) $(PKGFILE) $(TARBALL)

reallyclean: clean

distclean: reallyclean
