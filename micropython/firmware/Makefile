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

SRCURL		:= https://github.com/micropython/micropython.git
SRCDIR		:= micropython.src
MPYCROSS	:= $(SRCDIR)/mpy-cross/build/mpy-cross
TOOLCHAIN	?= $(HOME)/.arduino15/packages/rp2040/tools/pqt-gcc/4.1.0-1aec55e
TARGETPORT	?= rp2
TARGETBOARD	?= SEEED_XIAO_RP2350

default: $(TARGETBOARD).uf2

# Clone git repository

$(SRCDIR):
	git clone $(SRCURL) $@
	touch $@

# Compile mpy-cross

$(MPYCROSS): $(SRCDIR)
	$(MAKE) -C $(SRCDIR)/mpy-cross
	touch $@

# Build firmware

$(TARGETBOARD).uf2: $(MPYCROSS)
	PICO_TOOLCHAIN_PATH=$(TOOLCHAIN) $(MAKE) -C $(SRCDIR)/ports/$(TARGETPORT) BOARD=$(TARGETBOARD) submodules
	PICO_TOOLCHAIN_PATH=$(TOOLCHAIN) $(MAKE) -C $(SRCDIR)/ports/$(TARGETPORT) BOARD=$(TARGETBOARD) clean
	PICO_TOOLCHAIN_PATH=$(TOOLCHAIN) $(MAKE) -C $(SRCDIR)/ports/$(TARGETPORT) BOARD=$(TARGETBOARD)
	cp $(SRCDIR)/ports/$(TARGETPORT)/build-$(TARGETBOARD)/firmware.uf2 $@

# Install firmware

install: $(TARGETBOARD).uf2
	flashpico $^

# Remove working files

clean:
	rm -rf $(SRCDIR)
