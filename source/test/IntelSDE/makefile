#
# Intel Software Development Emulator
#
# Download:
#     http://www.intel.com/software/sde
#
# Adjust the path to the SDE tools below:
#

SDE = \sde-external-8.35.0-2019-03-11-win

test.exe:
    asmc64 $*.asm
    linkw system con_64 file $*
    $(SDE)\sde -- $@
    pause


