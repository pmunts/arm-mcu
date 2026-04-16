#! /bin/sh

# Flash Alire built ELF program to Raspberry Pi Pico using boot loader

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

# Test implicit mount point candidate

TestDestDir()
{
  test -f $1/INFO_UF2.TXT && export RP2040_DESTDIR=$1
}

# Search for an implicit mount point

FindDestDir()
{
  # Chromeos
  TestDestDir /mnt/chromeos/removable/RPI-RP2
  # Linux
  TestDestDir /media/${USER}/RPI-RP2
  # macOS
  TestDestDir /Volumes/RPI-RP2
  # Windows
  TestDestDir /d
  TestDestDir /e
  TestDestDir /f
  TestDestDir /g
  TestDestDir /h
  TestDestDir /i
  TestDestDir /j
  TestDestDir /k
}

# If no explicit mount point specified, search for an implicit one

test -z "${RP2040_DESTDIR}" && FindDestDir

PROGNAME=`basename bin/*`

test -n "${RP2040_DESTDIR}" && test -f "${RP2040_DESTDIR}/INFO_UF2.TXT" && ${ELF2UF2-elf2uf2} bin/${PROGNAME} ${RP2040_DESTDIR}/${PROGNAME}.uf2
exit 0
