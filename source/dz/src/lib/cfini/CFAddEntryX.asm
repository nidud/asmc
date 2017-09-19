include cfini.inc
include stdio.inc

    .code

CFAddEntryX proc C ini:PCFINI, format:LPSTR, argptr:VARARG


    .if ftobufin(format, addr argptr)

        CFAddEntry(ini, edx)
    .endif

    ret

CFAddEntryX endp

    END
