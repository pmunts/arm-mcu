# Build an Alire crate containing Phil's RP2040 Microcontroller Firmware Template

# Copyright (C)2026, Philip Munts.
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

ALIRE		?= $(shell pwd)/..

REVISION	?= $(shell svn log -l 1 . | awk '/svn/ { print substr($$1, 2) }' | head -n 1)
BUILDNUM	?= 1

CRATE_NAME	:= munts_rp2040_firmware_embedded
CRATE_VERSION	:= 16.$(REVISION).$(BUILDNUM)

default: populate.done

include $(ALIRE)/alire.mk

# Populate the library crate workspace directory

populate.done: alire_mk_init_lib
	install -cm 0644 Makefile.firmware	$(CRATE_DIR)/Makefile
	install -cm 0755 post*			$(CRATE_DIR)
	install -cm 0644 *.adb			$(CRATE_DIR)/src
	mkdir -p				$(CRATE_DIR)/.vscode
	install -cm 0644 tasks.json		$(CRATE_DIR)/.vscode

populate: populate.done

# Build the crate

build: populate.done alire_mk_build

# Create the crate source tarball

tarball: populate.done alire_mk_tarball

# Publish the crate

publish: alire_mk_commit alire_mk_publish

# Push the crate index checkout

push: publish alire_mk_push

# Remove working files

clean: alire_mk_clean
	rm -f *.done

reallyclean: alire_mk_reallyclean clean

distclean: alire_mk_reallyclean reallyclean
