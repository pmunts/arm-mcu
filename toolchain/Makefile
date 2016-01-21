# Download and build GNU toolchain for ARM microcontrollers

# $Id$

# Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
# All rights reserved.
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

TARGETNAME	= arm-none-eabi
PKGNAME		= arm-mcu-tools
INSTBASE	= $(shell pwd)/$(PKGNAME)

CC		= gcc
CXX		= g++
FIND		= find
TAR		= tar

BINUTILVER	= 2.25.1
BINUTILSERVER	= http://ftp.gnu.org/pub/gnu/binutils
BINUTILDIST	= $(TEMP)/binutils-$(BINUTILVER).tar.bz2
BINUTILURL	= $(BINUTILSERVER)/`basename $(BINUTILDIST)`
BINUTILSRC	= binutils-$(BINUTILVER)
BINUTILBLD	= build/binutils-$(BINUTILVER)

GCCVER		= 5.3.0
GCCSERVER	= http://ftp.gnu.org/pub/gnu/gcc/gcc-$(GCCVER)
GCCDIST		= $(TEMP)/gcc-$(GCCVER).tar.bz2
GCCURL		= $(GCCSERVER)/`basename $(GCCDIST)`
GCCSRC		= gcc-$(GCCVER)
GCCBLD		= build/gcc-$(GCCVER)

LIBICONVVER	= 1.14
LIBICONVSERVER	= http://ftp.gnu.org/pub/gnu/libiconv
LIBICONVDIST	= $(TEMP)/libiconv-$(LIBICONVVER).tar.gz
LIBICONVURL	= $(LIBICONVSERVER)/`basename $(LIBICONVDIST)`
LIBICONVSRC	= libiconv-$(LIBICONVVER)

NEWLIBVER	= 2.3.0.20160104
NEWLIBSERVER	= http://mirrors.kernel.org/sources.redhat.com/newlib
NEWLIBDIST	= $(TEMP)/newlib-$(NEWLIBVER).tar.gz
NEWLIBURL	= $(NEWLIBSERVER)/`basename $(NEWLIBDIST)`
NEWLIBSRC	= newlib-$(NEWLIBVER)
LIBCPDFURL	= $(NEWLIBSERVER)/libc.pdf
LIBMPDFURL	= $(NEWLIBSERVER)/libm.pdf
LIBCPDF		= $(TEMP)/libc.pdf
LIBMPDF		= $(TEMP)/libm.pdf

GDBVER		= 7.10.1
GDBSERVER	= http://ftp.gnu.org/gnu/gdb
GDBDIST		= $(TEMP)/gdb-$(GDBVER).tar.gz
GDBURL		= $(GDBSERVER)/`basename $(GDBDIST)`
GDBSRC		= gdb-$(GDBVER)
GDBBLD		= build/gdb-$(GDBVER)

VERSION		= $(BINUTILVER)_$(GCCVER)_$(NEWLIBVER)_$(GDBVER)
RELEASE		= 1

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
PKGSUFFIX	= cygwin
TARBALL		= $(PKGNAME)-$(VERSION)-$(PKGSUFFIX).tgz
TAROWNER	=
TARGROUP	=
endif

ifeq ($(shell uname), Darwin)
CC		= gcc-4
CXX		= g++-4
PKGSUFFIX	= $(shell uname -s)-$(shell uname -r)-$(shell uname -m)
TARBALL		= $(PKGNAME)-$(VERSION)-$(PKGSUFFIX).tgz
TAROWNER	= --owner root
TARGROUP	= --group wheel
endif

ifeq ($(shell uname), Linux)
OSNAME		?= unknown
PKGARCH		= $(shell dpkg --print-architecture)
PKGSUFFIX	= $(OSNAME)-$(PKGARCH)
PKGDIR		= $(PKGNAME)-$(VERSION)-$(PKGSUFFIX)
PKGFILE		= $(PKGDIR).deb
TARBALL		= $(PKGNAME)-$(VERSION)-$(PKGSUFFIX).tgz
TAROWNER	= --owner root
TARGROUP	= --group root
endif

ifeq ($(shell uname), OpenBSD)
CC		= egcc
CXX		= eg++
TAR		= gtar
PKGFILE		= $(PKGNAME)-$(VERSION)-$(shell uname -p)_$(shell uname -r).tgz
endif

BUILDCONFIG	= CC=$(CC) CXX=$(CXX)

default: readme.done

################################################################################

DISTFILES	= $(BINUTILDIST) $(GCCDIST) $(LIBICONVDIST) $(NEWLIBDIST) $(GDBDIST) $(LIBCPDF) $(LIBMPDF)

# Download all source distributions

download: $(DISTFILES)

################################################################################

# Unpack all source distributions

source.done: $(DISTFILES)
	$(TAR) xjf $(BINUTILDIST)
	$(TAR) xjf $(GCCDIST)
	if [ -f multilibs.patch ]; then cd $(GCCSRC) ; patch -b -p0 <../multilibs.patch ; fi
	cd $(GCCSRC) ; ./contrib/download_prerequisites
	$(TAR) xzf $(LIBICONVDIST)
	if [ -f libiconv.patch ]; then cd $(LIBICONVSRC) ; patch -b -p0 <../libiconv.patch ; fi
	ln -s "../$(LIBICONVSRC)" $(GCCSRC)/libiconv
	$(TAR) xzf $(NEWLIBDIST)
	ln -s "../$(NEWLIBSRC)/newlib" $(GCCSRC)/newlib
	$(TAR) xzf $(GDBDIST)
	touch $@

################################################################################

# Download binutils

$(BINUTILDIST):
	wget -nv -P $(TEMP) $(BINUTILURL)

# Compile binutils

binutils.done: source.done
	rm -rf $(BINUTILBLD)
	mkdir -p $(BINUTILBLD)
	cd $(BINUTILBLD) && ../../$(BINUTILSRC)/configure --prefix=$(INSTBASE) $(BUILDCONFIG) --target=$(TARGETNAME) --with-march=armv4t --with-float=soft --enable-interwork --enable-multilib --enable-lto --disable-nls --disable-shared --disable-werror
	$(MAKE) $(MAKEJOBS) -C $(BINUTILBLD)
	$(MAKE) -C $(BINUTILBLD) install
	touch binutils.done

################################################################################

# Download libiconv

$(LIBICONVDIST):
	wget -nv -P $(TEMP) $(LIBICONVURL)

################################################################################

# Download gcc

$(GCCDIST):
	wget -nv -P $(TEMP) $(GCCURL)
 
# Compile gcc

gcc.done: binutils.done
	rm -rf $(GCCBLD)
	mkdir -p $(GCCBLD)
	cd $(GCCBLD) && ../../$(GCCSRC)/configure --prefix=$(INSTBASE) $(BUILDCONFIG) --target=$(TARGETNAME) --with-march=armv4t --with-float=soft --enable-interwork --enable-multilib --enable-lto --disable-nls --disable-shared --disable-werror --enable-languages=c,c++ --disable-libssp --disable-libgomp --with-newlib --disable-newlib-libgloss --disable-newlib-supplied-syscalls --disable-mb --disable-newlib-wide-orient --disable-newlib-multithread --disable-newlib-iconv --enable-newlib-global-atexit --enable-newlib-reent-small --enable-newlib-nano-malloc --enable-newlib-nano-formatted-io --with-system-zlib
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) $(MAKEJOBS) -C $(GCCBLD)
	export PATH=$$PATH':'$(INSTBASE)/bin && $(MAKE) -C $(GCCBLD) install
	touch gcc.done

################################################################################

# Download newlib

$(NEWLIBDIST):
	wget -nv -P $(TEMP) $(NEWLIBURL)

# Note: newlib is built by gcc

# Download newlib docs

$(LIBCPDF):
	wget -nv -P $(TEMP) $(LIBCPDFURL)

$(LIBMPDF):
	wget -nv -P $(TEMP) $(LIBMPDFURL)

# Install newlib docs

newlibdocs.done: $(LIBCPDF) $(LIBMPDF)
	mkdir -p $(INSTBASE)/doc
	install -cm 0444 $(LIBCPDF) $(INSTBASE)/doc
	install -cm 0444 $(LIBMPDF) $(INSTBASE)/doc
	touch newlibdocs.done

################################################################################

# Download gdb

$(GDBDIST):
	wget -nv -P $(TEMP) $(GDBURL)

# Compile gdb

gdb.done: $(GDBDIST)
	test -f /usr/include/expat.h
	rm -rf $(GDBBLD)
	mkdir -p $(GDBBLD)
	cd $(GDBBLD) && ../../$(GDBSRC)/configure --prefix=$(INSTBASE) $(BUILDCONFIG) --target=$(TARGETNAME) --enable-interwork --enable-multilib --disable-libssp --disable-nls --disable-shared --disable-werror
	$(MAKE) $(MAKEJOBS) -C $(GDBBLD)
	$(MAKE) -C $(GDBBLD) install
	touch gdb.done

################################################################################

# Create README.txt

readme.done: binutils.done gcc.done newlibdocs.done gdb.done
	echo "GNU ARM microcontroller toolchain"	>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "Built on `date` from:"			>>$(INSTBASE)/README.txt
	echo " "					>>$(INSTBASE)/README.txt
	echo "$(BINUTILSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GCCSRC)"				>>$(INSTBASE)/README.txt
	echo "$(NEWLIBSRC)"				>>$(INSTBASE)/README.txt
	echo "$(GDBSRC)"				>>$(INSTBASE)/README.txt
	unix2dos $(INSTBASE)/README.txt
	touch readme.done

################################################################################

# Create toolchain tarball

tarball: readme.done
	$(TAR) czf $(TARBALL) `basename $(INSTBASE)` --mode=ugo-w $(TAROWNER) $(TARGROUP)

################################################################################

# Create Debian package

package.deb: readme.done
	mkdir -p					$(PKGDIR)/DEBIAN
	mkdir -p					$(PKGDIR)/usr/local
	install -cm 0644 control.template		$(PKGDIR)/DEBIAN/control
	sed -i s/@@ARCH@@/$(PKGARCH)/g			$(PKGDIR)/DEBIAN/control
	sed -i s/@@NAME@@/$(PKGNAME)/g			$(PKGDIR)/DEBIAN/control
	sed -i s/@@VERSION@@/$(VERSION)/g		$(PKGDIR)/DEBIAN/control
	sed -i /Version:/s/_/-/g			$(PKGDIR)/DEBIAN/control
	cp -R -P -p $(PKGNAME)				$(PKGDIR)/usr/local
	chmod -R ugo-w					$(PKGDIR)/usr/local/$(PKGNAME)
	fakeroot dpkg-deb --build			$(PKGDIR)
	chmod -R ugo+w					$(PKGDIR)

################################################################################

# Create RPM package

fakeroot.rpm: readme.done
	mkdir -p fakeroot.rpm/usr/local
	cp -R -P -p $(PKGNAME) fakeroot.rpm/usr/local

specfile: specfile.template fakeroot.rpm
	sed s/@@PKGNAME@@/$(PKGNAME)/g <specfile.template | sed s/@@VERSION@@/$(VERSION)/g | sed s/@@RELEASE@@/$(RELEASE)/g >specfile
	$(FIND) fakeroot.rpm/usr/local/$(PKGNAME) -type d | awk '{ printf("%%dir /%s\n", substr($$1, 14)); }' >>specfile
	$(FIND) fakeroot.rpm/usr/local/$(PKGNAME) -type f | cut -c 13- >>specfile
	$(FIND) fakeroot.rpm/usr/local/$(PKGNAME) -type l | cut -c 13- >>specfile

package.rpm: specfile
	rpmbuild --buildroot=`pwd`/fakeroot.rpm --define="_topdir `pwd`/rpmbuild" -bb specfile
	cp rpmbuild/RPMS/*/*.rpm .

################################################################################

# Create OpenBSD package

fakeroot.openbsd: readme.done
	mkdir -p fakeroot.openbsd/usr/local
	cp -R -P -p $(PKGNAME) fakeroot.openbsd/usr/local
# Why aren't these links already created on OpenBSD?
	ln -s liblto_plugin.so.0.0 fakeroot.openbsd/usr/local/$(PKGNAME)/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so
	ln -s liblto_plugin.so.0.0 fakeroot.openbsd/usr/local/$(PKGNAME)/libexec/gcc/arm-none-eabi/$(GCCVER)/liblto_plugin.so.0

CONTENTS: fakeroot.openbsd
	echo "@owner root"				>CONTENTS
	echo "@group wheel"				>>CONTENTS
	echo "@mode -w"					>>CONTENTS
	echo "@cwd /usr/local"				>>CONTENTS
	find fakeroot.openbsd/usr/local/$(PKGNAME) -type d | awk '{ printf("@dir %s\n", substr($$1, 28)); }' >>CONTENTS
	find fakeroot.openbsd -type f | cut -c 28- | sort	>>CONTENTS
	find fakeroot.openbsd -type l | awk '{ printf("echo %s `readlink %s`\n", $$1, $$1); }' | sh | \
	awk '{ printf("@exec ln -s %s %s\n", $$2, substr($$1,17)); }'            >>CONTENTS
	find fakeroot.openbsd -type l | awk '{ printf("@unexec rm %s\n", substr($$1, 17)); }' >>CONTENTS

COMMENT:
	echo "ARM Microcontroller Toolchain"		>COMMENT

package.openbsd: CONTENTS COMMENT
	pkg_create -A `uname -m` -f CONTENTS -D COMMENT="`cat COMMENT`" -d COMMENT -p / -B fakeroot.openbsd $(PKGFILE)
	@-rm CONTENTS
	@-rm COMMENT

################################################################################

# Clean out working files

clean:
	rm -rf $(INSTBASE)
	rm -rf $(BINUTILSRC)
	rm -rf $(GCCSRC)
	rm -rf $(LIBICONVSRC)
	rm -rf $(NEWLIBSRC)
	rm -rf $(GDBSRC)
	rm -rf build fakeroot.* specfile rpmbuild *.done *.deb *.rpm *.tgz $(PKGDIR)

distclean: clean
