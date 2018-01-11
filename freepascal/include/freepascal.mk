# Makefile definitions for building Free Pascal application programs
# for ARM microcontrollers

# Copyright (C)2017-2018, Philip Munts, President, Munts AM Corp.
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

###############################################################################

FPCDIR		?= /usr/local/fpc-arm-none-eabi
FPC		?= $(FPCDIR)/bin/ppcrossarm
FPC_FLAGS	+= -Mobjfpc -Sh -FE. $(FPC_EXTRAFLAGS)

###############################################################################

# Define a pattern rule to compile a Pascal program for an ARM microcontroller

%.bin %.elf %.hex: %.pas
	$(FPC) $(FPC_FLAGS) $(FPC_LDFLAGS) $<

# We dislike the .pp file extension, but we support it anyway

%.bin %.elf %.hex: %.pp
	$(FPC) $(FPC_FLAGS) $(FPC_LDFLAGS) $<

###############################################################################

# Define a pattern rule to compile a Pascal unit

%.ppu: %.pas
	$(FPC) $(FPC_FLAGS) -o$@ $^

# We dislike the .pp file extension, but we support it anyway

%.ppu: %.pp
	$(FPC) $(FPC_FLAGS) -o$@ $^

###############################################################################

# Define a default target placeholder

freepascal_mk_default: default

###############################################################################

# Clean out working files

freepascal_mk_clean:
	-rm -f *.bin *.elf *.hex *.log *.o *.ppu ppas.sh *.tmp link.res

freepascal_mk_reallyclean: freepascal_mk_clean

freepascal_mk_distclean: freepascal_mk_reallyclean
