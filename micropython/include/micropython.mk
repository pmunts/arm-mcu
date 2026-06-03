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
BOARDFAMILY	?= UNKNOWN
DSTPATH		?= $(shell mpremote tree | tail -n 1)
MPREMOTE	?= mpremote

# Default make target

default: run

# Pull in optional board family specific firmware management

sinclude $(ARMSRC)/micropython/include/$(BOARDFAMILY).mk

# Run Python3 script on target MCU

run:
	$(MPREMOTE) mount src run src/main.py

# Reset target MCU

reset:
	$(MPREMOTE) reset

# Remove working files

clean:
	find . -name "__pycache__" -exec rm -rf {} ";"

# Install Python3 script(s) to target MCU

install:
	-$(MPREMOTE) fs rm -rv $(DSTPATH)
	$(MPREMOTE) fs cp -r src/* $(DSTPATH)
	$(MPREMOTE) reset
	$(MPREMOTE) sleep 1

# List files on target MCU

ls:
	$(MPREMOTE) tree

# Uninstall all Python3 script(s), libraries, modules

uninstall:
	-$(MPREMOTE) fs rm -rv $(DSTPATH)
	$(MPREMOTE) reset
