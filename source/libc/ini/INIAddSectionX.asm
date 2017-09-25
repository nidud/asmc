include ini.inc
include stdio.inc

    .code

INIAddSectionX proc c ini:LPINI, format:LPSTR, argptr:VARARG


    .if ftobufin(format, &argptr)

        INIAddSection(ini, edx)
    .endif

    ret

INIAddSectionX endp

    END
