#
# The 64-bit import libraries built with LIBW is not compatible with LINK so
# this builds them using LIB from Visual Studio. Note: make sure the PATH is
# set to LIB and LINK before build.
#
msvsimp.exe:
        asmc -win64 -pe $*.asm
        $@ import.txt
        del $*.exe
        del *.exp
