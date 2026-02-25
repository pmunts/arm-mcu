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

BOARDNAME	?= NUCLEO_F411RE
ARDUINOFQBN	:= STMicroelectronics:stm32:$(BOARDFAMILY):pnum=$(BOARDNAME),upload_method=swdMethod
ARDUINOCORESRC	:= $(ARDUINOPKGSDIR)/STMicroelectronics/hardware/stm32/2.12.0
ARDUINOCOREGCC	:= $(ARDUINOPKGSDIR)/STMicroelectronics/tools/xpack-arm-none-eabi-gcc/14.2.1-1.1/bin/arm-none-eabi-gcc

# Fix Arduino core pathnames for Windows

ifeq ($(shell uname -o), Cygwin)
ARDUINOCORESRC	:= $(shell cygpath -m $(ARDUINOCORESRC))
ARDUINOCOREGCC	:= $(shell cygpath -m $(ARDUINOCOREGCC))
endif

build:
	$(ARDUINOCLI) compile $(COMPILEFLAGS) -b $(ARDUINOFQBN) -e

install: build
	$(ARDUINOCLI) upload -b $(ARDUINOFQBN)

clean:
	rm -rf build

code edit:
	CORESRC=$(ARDUINOCORESRC) COREGCC=$(ARDUINOCOREGCC) code .
