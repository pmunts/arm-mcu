# Makefile definitions for building and deploying GHI Electronics TinyCLR
# C# application programs

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

APPCONFIG	?= Release
APPKEY		?= 00-00-00-00-00-00-00-00-00-00-00-00-00-00-00-00
APPVERSION	?= 1.0.0.0
DEVICE		?= SC13048
NUGET		?= nuget.exe
PROJECTNAME	?= $(shell basename *.csproj .csproj)
PROJECTFILE	:= $(PROJECTNAME).csproj
TCAFILE		:= $(PROJECTNAME).tca
TINYCLRCONFIG	?= GHIElectronics.TinyCLR.Config.exe

BUILDFLAGS	:= -cmd:build-tca
BUILDFLAGS	+= --project:$(PROJECTNAME).csproj
BUILDFLAGS	+= --configuration:$(APPCONFIG)
BUILDFLAGS	+= --device:$(DEVICE)
BUILDFLAGS	+= --key:$(APPKEY)
BUILDFLAGS	+= --version:$(APPVERSION)

LOADAPPFLAGS	:= -cmd:load-app
LOADAPPFLAGS	+= --port:$(DEVICE)
LOADAPPFLAGS	+= --file:bin/$(APPCONFIG)/$(TCAFILE)
LOADAPPFLAGS	+= --key:$(APPKEY)

REBOOTFLAGS	:= -cmd:reboot
REBOOTFLAGS	+= --port:$(DEVICE)

# Default target

tinyclr_mk_default: tinyclr_mk_deploy

# Build project

tinyclr_mk_restore:
	"$(NUGET)" restore packages.config -PackagesDirectory packages

# Build project

tinyclr_mk_build: tinyclr_mk_restore
	"$(TINYCLRCONFIG)" $(BUILDFLAGS)

# Deploy project

tinyclr_mk_deploy: clean tinyclr_mk_build
	"$(TINYCLRCONFIG)" $(LOADAPPFLAGS)
	"$(TINYCLRCONFIG)" $(REBOOTFLAGS)
	"$(TINYCLRCONFIG)" $(REBOOTFLAGS)

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
	rm -rf *.bin *.key.txt *.pdbx *.pe *.tca *.tinyresources
	$(ARMSRC)/tinyclr/include/vsclean.sh

reallyclean: clean

distclean: reallyclean
	rm -rf packages
