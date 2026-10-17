# Makefile for building STM32 ELF2UF2 flash utility elf2uf2

# Copyright (C)2013-2018, Philip Munts, President, Munts AM Corp.
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

ELF2UF2NAME	:= elf2uf2
ELF2UF2SRC	:= elf2uf2.src
BUILDNUM	?= 1
OSNAME		?= unknown
PKGNAME		:= $(ELF2UF2NAME)
PKGVERSION	:= $(shell date +%Y.%j).$(BUILDNUM)
PKGARCH		:= $(shell dpkg --print-architecture)
PKGDIR		:= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		:= $(PKGDIR).deb

default: package.deb

# Download source distribution

source.done:
	git clone https://github.com/rej696/elf2uf2.git elf2uf2.src
	touch $@

# Compile elf2uf2

build.done: source.done
	$(MAKE) -C $(ELF2UF2SRC)
	touch $@

# Create Debian package file

package.deb: build.done
	mkdir -p					$(PKGDIR)/DEBIAN
	install -cm 0644 control			$(PKGDIR)/DEBIAN
	sed -i 's/@@ARCH@@/$(PKGARCH)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@NAME@@/$(PKGNAME)/g'		$(PKGDIR)/DEBIAN/control
	sed -i 's/@@VERSION@@/$(PKGVERSION)/g'		$(PKGDIR)/DEBIAN/control
	mkdir -p					$(PKGDIR)/usr/local/share/elf2uf2
	install -cm 0644 $(ELF2UF2SRC)/LICENSE.TXT	$(PKGDIR)/usr/local/share/elf2uf2
	mkdir -p					$(PKGDIR)/usr/local/bin
	install -csm 0755 $(ELF2UF2SRC)/elf2uf2		$(PKGDIR)/usr/local/bin
	chmod -R ugo-w					$(PKGDIR)/usr/local/bin/*
	fakeroot dpkg-deb --build			$(PKGDIR)
	chmod -R ugo+w					$(PKGDIR)/usr/local/bin/*

# Clean out working files

clean:
	-rm -rf *.done $(ELF2UF2SRC) $(PKGDIR) $(PKGFILE)

reallyclean: clean

distclean: reallyclean
	-rm -rf $(ELF2UF2DIST)
