include cfini.inc
include stdio.inc

    .code

__CFAddSectionX proc C ini:PCFINI, format:LPSTR, argptr:VARARG


    .if ftobufin(format, addr argptr)

        __CFAddSection(ini, edx)
    .endif

    ret

__CFAddSectionX endp

    END
