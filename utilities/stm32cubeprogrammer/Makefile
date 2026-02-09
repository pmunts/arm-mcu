# Makefile for STM32 Cube Programmer Debian package

DISTVERSION	?= 2-21-0

BUILDNUM	?= 1
OSNAME		?= unknown
PKGNAME		= stm32cubeprogrammer
PKGVERSION	:= $(DISTVERSION)-$(shell date +%Y.%j).$(BUILDNUM)
PKGARCH		:= $(shell dpkg --print-architecture)
PKGDIR		:= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		:= $(PKGDIR).deb

default: $(PKGFILE)

$(PKGDIR): install
	mkdir -p				$(PKGDIR)/DEBIAN
	install -cm 0444 control		$(PKGDIR)/DEBIAN
	sed -i s/@@ARCH@@/$(PKGARCH)/g		$(PKGDIR)/DEBIAN/control
	sed -i s/@@VERSION@@/$(PKGVERSION)/g	$(PKGDIR)/DEBIAN/control
	mkdir -p				$(PKGDIR)/usr/local/bin
	cp -R -P -p install			$(PKGDIR)/usr/local/stm32cubeprogrammer
	sed -i 's#DIR=.*$$#DIR=/usr/local/stm32cubeprogrammer/bin#g' $(PKGDIR)/usr/local/stm32cubeprogrammer/bin/STM32CubeProgrammer
	cd $(PKGDIR)/usr/local/bin && ln -s ../stm32cubeprogrammer/bin/STM32CubeProgrammer STM32_Programmer
	cd $(PKGDIR)/usr/local/bin && ln -s ../stm32cubeprogrammer/bin/STM32_Programmer_CLI
	find $(PKGDIR) -name '*.so' -exec chmod 755 {} ";"

$(PKGFILE): $(PKGDIR)
	chmod -R ugo-w $(PKGDIR)/usr
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R u+w $(PKGDIR)/usr

clean:
	-rm $(PKGFILE)
	-rm -rf $(PKGDIR)

reallyclean: clean
	rm -rf install

distclean: reallyclean
	rm -rf dist
