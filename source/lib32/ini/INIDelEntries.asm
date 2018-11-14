; INIDELENTRIES.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include ini.inc

    .code

INIDelEntries proc uses esi ini:LPINI

    mov eax,ini
    mov esi,[eax].S_INI.value
    mov [eax].S_INI.value,0

    .while esi

        .if [esi].S_INI.entry

            free([esi].S_INI.entry)
        .endif

        mov eax,esi
        mov esi,[esi].S_INI.next
        free(eax)
    .endw
    mov eax,ini
    ret

INIDelEntries endp

    END
