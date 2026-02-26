#! /bin/sh

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

# We want exactly one command line argument, the name of the UF2 file

if [ $# -lt 1 ]; then
  echo ""
  echo "Usage: $0 <UF2 file>"
  echo ""
  exit 1
fi

# Search for the Raspberry Pi Pico mass storage directory

unset DESTDIR

FindDestDir()
{
  test -f $1/INFO_UF2.TXT && export DESTDIR=$1
}

# macOS
FindDestDir /Volumes/RPI-RP2
FindDestDir /Volumes/RP2350
# Debian Linux
FindDestDir /media/${USER}/RPI-RP2
FindDestDir /media/${USER}/RP2350
# Chromeos
FindDestDir /mnt/chromeos/removable/RPI-RP2
FindDestDir /mnt/chromeos/removable/RP2350
# Windows
FindDestDir /d
FindDestDir /e
FindDestDir /f

if [ -z "${DESTDIR}" ] ; then
  echo ""
  echo "ERROR: Cannot find Raspberry Pi Pico mass storage directory."
  echo ""
  exit 1
fi

cp $1 ${DESTDIR}/`basename $1`
