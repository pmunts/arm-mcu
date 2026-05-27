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

install:
ifeq ($(shell uname -o), Cygwin)
	install -cm 0555 arduino-clean		/usr/local/bin/arduino-clean.sh
	install -cm 0555 arduino-distclean	/usr/local/bin/arduino-distclean.sh
	install -cm 0555 arduino-install-cores	/usr/local/bin/arduino-install-cores.sh
	install -cm 0555 arduino-zip-library	/usr/local/bin/arduino-zip-library.sh
	install -cm 0555 arduino-arm-newproject	/usr/local/bin/arduino-arm-newproject.sh
else
	install -cm 0555 arduino-clean		/usr/local/bin
	install -cm 0555 arduino-distclean	/usr/local/bin
	install -cm 0555 arduino-install-cores	/usr/local/bin
	install -cm 0555 arduino-zip-library	/usr/local/bin
	install -cm 0555 arduino-arm-newproject	/usr/local/bin
endif
ifeq ($(shell uname), Darwin)
	install -cm 0555 arduino-link-port	/usr/local/bin
endif
ifeq ($(shell uname), Linux)
	install -cm 0555 arduino-select-port	/usr/local/bin
endif

uninstall:
ifeq ($(shell uname -o), Cygwin)
	rm -f /usr/local/bin/arduino-clean.sh
	rm -f /usr/local/bin/arduino-distclean.sh
	rm -f /usr/local/bin/arduino-install-cores.sh
	rm -f /usr/local/bin/arduino-zip-library.sh
	rm -f /usr/local/bin/arduino-arm-newproject.sh
else
	rm -f /usr/local/bin/arduino-clean
	rm -f /usr/local/bin/arduino-distclean
	rm -f /usr/local/bin/arduino-install-cores
	rm -f /usr/local/bin/arduino-zip-library
	rm -f /usr/local/bin/arduino-arm-newproject
endif
ifeq ($(shell uname), Darwin)
	rm -f /usr/local/bin/arduino-link-port
endif
ifeq ($(shell uname), Linux)
	rm -f /usr/local/bin/arduino-select-port
endif
