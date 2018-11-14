; INIDELSECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include malloc.inc
include ini.inc

    .code

INIDelSection proc __cdecl ini:LPINI, section:LPSTR

    .if INIGetSection(ini, section)

        .if edx

            mov ecx,[eax].S_INI.next
            mov [edx].S_INI.next,ecx
        .endif

        .if free([INIDelEntries(eax)].S_INI.entry) == ini

            mov [eax].S_INI.flags,0
            mov [eax].S_INI.entry,0
        .else
            free(eax)
        .endif
        mov eax,ini
    .endif
    ret

INIDelSection endp

    END
