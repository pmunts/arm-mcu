# Make definitions for ST-Link

# $Id$

# Copyright (C)2013-2015, Philip Munts, President, Munts AM Corp.
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

# texane/stlink

STLINKFLASH		?= stlink-flash
STLINKFLASHOPTS1	?= --reset write $(STLINKIF)
STLINKFLASHOPTS2	?= $(FLASHWRITEADDR)

STLINKDEBUG		?= $(ARMSRC)/common/main.gdb
STLINKGDB		?= stlink-gdbserver
STLINKGDBOPTS		?= -p $(GDBSERVERPORT)

# ST Microelectronics ST-LINK_CLI.exe

#STLINKFLASH		?=ST-LINK_CLI.exe
#STLINKFLASHOPTS1	?=-c SWD -ME -P
#STLINKFLASHOPTS2	?=$(FLASHWRITEADDR) -Rst

.SUFFIXES: .bin .debugstlink .elf .flashstlink .hex

# Start ST-Link GDB server

startstlink:
	$(STLINKGDB) $(STLINKGDBIF) $(STLINKGDBOPTS) >debug.log 2>&1 &

# Stop ST-Link GDB server

stopstlink:
	-skill `basename $(STLINKGDB) .exe`

# Debug with ST-Link GDB server

.elf.debugstlink:
	$(MAKE) startstlink
	$(GDBGUI) $(GDB) $(GDBFLAGS) -x $(STLINKDEBUG) $<
	$(MAKE) stopstlink

# Program flash with ST-Link

.bin.flashstlink:
	$(STLINKFLASH) $(STLINKFLASHOPTS1) $< $(STLINKFLASHOPTS2)
