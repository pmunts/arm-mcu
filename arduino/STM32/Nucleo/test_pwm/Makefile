# Makefile for building and installing an Arduino application program

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

ARMSRC		?= $(HOME)/arm-mcu
BOARDFAMILY	?= Nucleo_64
BOARDNAME	?= NUCLEO_F411RE
ARDUINOCLI	?= arduino-cli
ARDUINOFQBN	:= STMicroelectronics:stm32:$(BOARDFAMILY):pnum=$(BOARDNAME),upload_method=swdMethod
EXTRACFLAGS	+= -D$(BOARDFAMILY)
COMPILEFLAGS	+= --build-property build.extra_flags="$(EXTRACFLAGS)"
COMPILEFLAGS	+= --libraries "$(ARMSRC)/arduino/libraries"

install: build
	$(ARDUINOCLI) upload -b $(ARDUINOFQBN)

build:
	$(ARDUINOCLI) compile $(COMPILEFLAGS) -b $(ARDUINOFQBN) -e

clean:
	rm -rf build
