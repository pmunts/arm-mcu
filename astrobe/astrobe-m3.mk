# Makefile definitions for compiling Oberon for Cortex-M3 programs

# $Id$

# Copyright (C)2014-2015, Philip Munts, President, Munts AM Corp.
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

# Keep intermediate files

.SECONDARY:

ASTROBEBINDIR	?= "C:/PROGRA~1/AstrobeM3 Professional Edition"/

ASTROBECOMPILE	= $(ASTROBEBINDIR)AstrobeCompile
ASTROBEBUILD	= $(ASTROBEBINDIR)AstrobeBuild
ASTROBELINK	= $(ASTROBEBINDIR)AstrobeLink
ASTROBECONFIG	= $(ASTROBESRC)/$(MCU)/astrobe.ini

# Default make target

astrobe_mk_default:
	@echo ERROR: You must explicitly specify a make target!
	@exit 1

# Define a pattern rule to compile an Oberon source program

%.arm: %.mod
	$(ASTROBECOMPILE) $(ASTROBECONFIG) $<

# Define a pattern rule to compile an Oberon main module source program to binary flash image

%.bin: %.mod
	$(ASTROBEBUILD) $(ASTROBECONFIG) ./$<
	$(ASTROBELINK) $(ASTROBECONFIG) $<

# Define a pattern rule to compile an Oberon main module source program to Intel hex flash image

%.hex: %.mod
	$(ASTROBEBUILD) $(ASTROBECONFIG) ./$<
	$(ASTROBELINK) $(ASTROBECONFIG) $<

# Remove working files

astrobe_mk_clean:
	rm -f *.arm *.bin *.hex *.lst *.map *.ref *.smb
