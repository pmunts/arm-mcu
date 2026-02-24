# Make definitions for building and installing Arduino RP2040 or RP2350 programs
# using the Arduino-Pico Core (https://github.com/earlephilhower/arduino-pico).

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

ARDUINOCLI	?= arduino-cli
ARDUINOFQBN	:= rp2040:rp2040:$(BOARDNAME)
ARDUINOPORT	?= COM1
SKETCHBOOK	:= $(ARMSRC)/arduino
COMPILEFLAGS	+= --build-property build.extra_flags="-DMUNTSTECH $(EXTRACFLAGS)"
COMPILEFLAGS	+= --libraries "$(SKETCHBOOK)/libraries"

pico_mk_default: clean install

build:
	$(ARDUINOCLI) compile $(COMPILEFLAGS) -b $(ARDUINOFQBN) -e

install: build
	flashpico build/*/*.uf2

clean:
	rm -rf build
