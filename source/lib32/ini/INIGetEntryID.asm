; INIGETENTRYID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ini.inc

    .code

INIGetEntryID proc __cdecl ini:LPINI, entry:UINT

    mov eax,entry ; 0..99
    .while  al > 9
        add ah,1
        sub al,10
    .endw
    .if ah
        xchg    al,ah
        or  ah,'0'
    .endif
    or  al,'0'
    mov entry,eax

    INIGetEntry(ini, &entry)
    ret

INIGetEntryID endp

    END
