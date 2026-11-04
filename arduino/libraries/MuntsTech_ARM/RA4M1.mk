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

BOARDNAME	?= nanor4
ARDUINOFQBN	:= arduino:renesas_uno:$(BOARDNAME)
ARDUINOCORESRC	:= $(ARDUINOPKGSDIR)/arduino/hardware/renesas_uno/1.6.0
ARDUINOCOREGCC	:= $(ARDUINOPKGSDIR)/arduino/tools/arm-none-eabi-gcc/7-2017q4/bin/arm-none-eabi-gcc
ARDUINOPORT	?= COM1
VSCODE		?= code

# Fix Arduino core pathnames for Windows

ifeq ($(shell uname -o), Cygwin)
ARDUINOCORESRC	:= $(shell cygpath -m $(ARDUINOCORESRC))
ARDUINOCOREGCC	:= $(shell cygpath -m $(ARDUINOCOREGCC))
endif

build:
	$(ARDUINOCLI) compile $(COMPILEFLAGS) -b $(ARDUINOFQBN) -e

install: build
	$(ARDUINOCLI) upload -b $(ARDUINOFQBN) -p $(ARDUINOPORT)

clean:
	rm -rf build

code edit:
	CORESRC=$(ARDUINOCORESRC) COREGCC=$(ARDUINOCOREGCC) $(VSCODE) .
