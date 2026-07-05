# Copyright (C)2026, Philip Munts dba Munts Technologies.
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

DESTDIR	?= /usr/local/bin

install:
ifeq ($(shell uname -o), Cygwin)
	install -cm 0555 arduino-clean		$(DESTDIR)/arduino-clean.sh
	install -cm 0555 arduino-distclean	$(DESTDIR)/arduino-distclean.sh
	install -cm 0555 arduino-install-cores	$(DESTDIR)/arduino-install-cores.sh
	install -cm 0555 arduino-zip-library	$(DESTDIR)/arduino-zip-library.sh
	install -cm 0555 arduino-arm-newproject	$(DESTDIR)/arduino-arm-newproject.sh
else ifeq ($(shell uname -o), Msys)
	install -cm 0555 arduino-clean		$(DESTDIR)/arduino-clean.sh
	install -cm 0555 arduino-distclean	$(DESTDIR)/arduino-distclean.sh
	install -cm 0555 arduino-install-cores	$(DESTDIR)/arduino-install-cores.sh
	install -cm 0555 arduino-zip-library	$(DESTDIR)/arduino-zip-library.sh
	install -cm 0555 arduino-arm-newproject	$(DESTDIR)/arduino-arm-newproject.sh
else
	install -cm 0555 arduino-clean		$(DESTDIR)
	install -cm 0555 arduino-distclean	$(DESTDIR)
	install -cm 0555 arduino-install-cores	$(DESTDIR)
	install -cm 0555 arduino-zip-library	$(DESTDIR)
	install -cm 0555 arduino-arm-newproject	$(DESTDIR)
endif
ifeq ($(shell uname), Darwin)
	install -cm 0555 arduino-link-port	$(DESTDIR)
endif
ifeq ($(shell uname), Linux)
	install -cm 0555 arduino-select-port	$(DESTDIR)
endif

uninstall:
ifeq ($(shell uname -o), Cygwin)
	rm -f $(DESTDIR)/arduino-clean.sh
	rm -f $(DESTDIR)/arduino-distclean.sh
	rm -f $(DESTDIR)/arduino-install-cores.sh
	rm -f $(DESTDIR)/arduino-zip-library.sh
	rm -f $(DESTDIR)/arduino-arm-newproject.sh
else
	rm -f $(DESTDIR)/arduino-clean
	rm -f $(DESTDIR)/arduino-distclean
	rm -f $(DESTDIR)/arduino-install-cores
	rm -f $(DESTDIR)/arduino-zip-library
	rm -f $(DESTDIR)/arduino-arm-newproject
endif
ifeq ($(shell uname), Darwin)
	rm -f $(DESTDIR)/arduino-link-port
endif
ifeq ($(shell uname), Linux)
	rm -f $(DESTDIR)/arduino-select-port
endif
