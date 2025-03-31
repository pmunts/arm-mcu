# Flash Alire built ELF program to Raspberry Pi Pico using boot loader

# Copyright (C)2025, Philip Munts dba Munts Technologies.
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

ELF2UF2		?= elf2uf2
PROGNAME	:= $(shell basename `pwd`)

ifeq ($(shell uname), Darwin)
PICOBOOTDEST	?= /Volumes/RPI-RP2
endif
ifeq ($(shell uname), Linux)
ifneq ($(wildcard /mnt/chromeos/removable),)
PICOBOOTDEST	?= /mnt/chromeos/removable/RPI-RP2
else
PICOBOOTDEST	?= /media/$(USER)/RPI-RP2
endif
endif
ifeq ($(OS), Windows_NT)
PICOBOOTDEST	?= /d
endif

# Flash Alire program to target

picoboot_mk_flash:
	test -f $(PICOBOOTDEST)/INFO_UF2.TXT && $(ELF2UF2) bin/$(PROGNAME) $(PICOBOOTDEST)/$(PROGNAME)
