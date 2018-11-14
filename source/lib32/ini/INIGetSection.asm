; INIGETSECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ini.inc
include string.inc

    .code

INIGetSection proc uses esi edi ini:LPINI, section:LPSTR

    mov eax,ini
    xor edi,edi

    .while  eax

        .if [eax].S_INI.flags & INI_SECTION

            mov esi,eax
            .if !strcmp([esi].S_INI.entry, section)

                mov edx,edi
                mov eax,esi
                .break
            .endif
            mov eax,esi
        .endif
        mov edi,eax
        mov eax,[eax].S_INI.next
    .endw
    ret

INIGetSection endp

    END
