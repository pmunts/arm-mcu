#! /bin/sh

# Flash Alire built ELF program to Raspberry Pi Pico using boot loader

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
