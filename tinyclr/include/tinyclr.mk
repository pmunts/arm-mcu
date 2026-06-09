# Makefile definitions for GHI Electronics TinyCLR C# application programs

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

CONFIGURATION	?= Release
MSBUILD		?= C:/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/MSBuild.exe
MSBUILDTARGET	?= /t:Build
MSBUILDFLAGS	?= /p:Configuration=$(CONFIGURATION)
NUGET		?= nuget.exe

# Build project

tinyclr_mk_build:
	"$(NUGET)" restore packages.config -PackagesDirectory packages
	"$(MSBUILD)" $(MSBUILDTARGET) $(MSBUILDFLAGS)

# TODO: Deploy project with TinyCLR Config CLI

# Fixup target for Cygwin development host

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
tinyclr_mk_fixup:
	-$(FIND) * -type d -exec chmod 755 {}  ";"
	-$(FIND) * -type f -exec chmod 644 {}  ";"
	-$(FIND) * -type f -exec bom_remove {} ";"
	-$(FIND) * -type f -exec unix2dos {}   ";"
	-dos2unix Makefile
endif

# Clean out working files

clean:
	$(ARMSRC)/tinyclr/include/vsclean.sh

reallyclean: clean

distclean: reallyclean
	rm -rf packages
