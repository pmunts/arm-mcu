# Makefile for mbed CLI package

OSNAME		?= unknown
PKGNAME		= munts-mbed-cli
PKGARCH		:= all
PKGVERSION	:= $(shell date +%Y.%j)
PKGDIR		:= $(PKGNAME)-$(PKGVERSION)-$(OSNAME)-$(PKGARCH)
PKGFILE		:= $(PKGDIR).deb

default: $(PKGFILE)

$(PKGFILE): $(PKGDIR)
	chmod -R ugo-w $(PKGDIR)/usr
	fakeroot dpkg-deb --build $(PKGDIR)
	chmod -R u+w $(PKGDIR)/usr

$(PKGDIR):
	mkdir -p $(PKGDIR)/DEBIAN
	install -cm 0444 control		$(PKGDIR)/DEBIAN
	install -cm 0755 postinst		$(PKGDIR)/DEBIAN
	install -cm 0755 prerm			$(PKGDIR)/DEBIAN
	sed -i s/@@ARCH@@/$(PKGARCH)/g		$(PKGDIR)/DEBIAN/control
	sed -i s/@@NAME@@/$(PKGNAME)/g		$(PKGDIR)/DEBIAN/control
	sed -i s/@@VERSION@@/$(PKGVERSION)/g	$(PKGDIR)/DEBIAN/control
	mkdir -p				$(PKGDIR)/usr/local/lib
	cd $(PKGDIR)/usr/local/lib ; mbed new mbed-cli ; rm -rf .git .mbed
	cd $(PKGDIR) ; patch -p0 <../mbed-cli.patch

populate: $(PKGDIR)

clean:
	-rm $(PKGFILE)
	-rm -rf $(PKGDIR)

reallyclean: clean

distclean: reallyclean
