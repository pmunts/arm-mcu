# Make definitions for building and installing Arduino STM32 programs

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
BOARDFAMILY	?= Nucleo_64
BOARDNAME	?= NUCLEO_F411RE
ARDUINOFQBN	:= STMicroelectronics:stm32:$(BOARDFAMILY):pnum=$(BOARDNAME),upload_method=swdMethod
SKETCHBOOK	:= $(ARMSRC)/arduino
COMPILEFLAGS	+= --build-property build.extra_flags="-DMUNTSTECH -D$(BOARDFAMILY) $(EXTRACFLAGS)"
COMPILEFLAGS	+= --libraries "$(SKETCHBOOK)/libraries"

stm32_mk_default: clean install

build:
	$(ARDUINOCLI) compile $(COMPILEFLAGS) -b $(ARDUINOFQBN) -e

install: build
	$(ARDUINOCLI) upload -b $(ARDUINOFQBN)

clean:
	rm -rf build
