# Makefile definitions for compiling Oberon firmware for the RP2040 MCU

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

# Note: Install both Astrobe programs and Astrobe examples & libraries to
# C:\Program Files\AstrobeRP2040

ASTROBEBINDIR	?= "$(PROGRAMFILES)/AstrobeRP2040"
ASTROBECOMPILE	:= $(ASTROBEBINDIR)/AstrobeCompile
ASTROBEBUILD	:= $(ASTROBEBINDIR)/AstrobeBuild
ASTROBELINK	:= $(ASTROBEBINDIR)/AstrobeLink
ASTROBECONFIG	:= astrobe.ini
FLASHPICO	?= flashpico

# Default make target

astrobe_mk_default: install

# Define a pattern rule to compile an Oberon main module source program to binary flash image

%.uf2: %.mod
	$(ASTROBEBUILD) $(ASTROBECONFIG) $<
	$(ASTROBELINK)  $(ASTROBECONFIG) $<

# Define a pattern rule to install the UF2 binary flash image

%.flash: %.uf2
	$(FLASHPICO) $<

# Remove working files

astrobe_mk_clean:
	rm -f *.arm *.bin *.drf *.hex *.lst *.map *.ref *.smb *.uf2
