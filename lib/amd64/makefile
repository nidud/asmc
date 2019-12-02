#
# msvcrt.lib fails with LIBW. Use MAKE LIB=1 to use LIB.
#

asmc_args = -q -win64 -pe

!ifdef LIB
asmc_args += -D__LIB__
!endif

import.exe:
    asmc $(asmc_args) $*.asm
!ifdef LIB
    set PATH=%MSVS_PATH%;%PATH%
    $@ import.txt
!endif
    $@ import.inc
    del $@
