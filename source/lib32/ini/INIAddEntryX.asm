; INIADDENTRYX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ini.inc
include stdio.inc

    .code

INIAddEntryX proc c ini:LPINI, format:LPSTR, argptr:VARARG


    .if ftobufin(format, &argptr)

        INIAddEntry(ini, edx)
    .endif

    ret

INIAddEntryX endp

    END
