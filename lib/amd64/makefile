#
# The 64-bit import libraries built with LIBW is not compatible with LINK.
# To build them using LIB from Visual Studio add -D__LIB__ to asmc or
# LIB=1 to make. Note: make sure LIB and LINK is in the PATH if used.
#

!ifdef LIB
asmc_args = -q -win64 -pe -D__LIB__
!else
asmc_args = -q -win64 -pe
!endif

import.exe:
    asmc $(asmc_args) $*.asm
!ifdef LIB
    #set PATH=D:\VS12\bin;%PATH%
!endif
    $@ import.txt
    del $*.exe
    if exist user32.exp del *.exp
