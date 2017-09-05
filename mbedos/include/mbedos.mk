# Common make definitions for building Mbed OS applications

# Copyright (C)2017, Philip Munts, President, Munts AM Corp.
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

# To install the common Mbed OS libraries, either install Debian package
# munts-mbed-cli, or run the following commands:
#
# sudo pip install mbed-cli
# sudo mbed new /usr/local/lib/mbed-cli

MBEDCLIPATH	?= /usr/local/lib/mbed-cli
OUTPUTPATH	?= ./BUILD/$(BOARDNAME)/$(TOOLCHAINNAME)

MBEDCLIFLAGS	+= -D__mbedos__

# Default target placeholder

mbedos_mk_default: default

# Prepare for mbed compile

prepare.done:
	ln -s $(MBEDCLIPATH)/mbed-os
	ln -s $(MBEDCLIPATH)/mbed-os.lib
	ln -s $(MBEDCLIPATH)/mbed_settings.py
	touch $@

# Perform mbed compile

compile.done: prepare.done
	mbed compile $(MBEDCLIFLAGS)
	touch $@

mbedos_mk_build: compile.done

# Remove working files

mbedos_mk_clean:
	-rm -rf BUILD compile.done

mbedos_mk_reallyclean: mbedos_mk_clean
	-rm -f .mbed
	-rm -f mbed-os
	-rm -f mbed-os.lib
	-rm -f mbed_settings.py
	-rm -f mbed_settings.pyc
	-rm -f prepare.done

mbedos_mk_distclean: mbedos_mk_reallyclean
