include ini.inc
include string.inc

    .code

INIGetEntry proc __cdecl uses esi edi ini:LPINI, entry:LPSTR

    mov edx,ini
    xor edi,edi
    xor eax,eax

    .if edx && [edx].S_INI.flags & INI_SECTION

        mov eax,[edx].S_INI.value

        .while  eax

            .if [eax].S_INI.flags & INI_ENTRY

                mov esi,eax
                mov edx,[eax].S_INI.entry
                mov ecx,entry

                .while  1

                    mov al,[ecx]
                    mov ah,[edx]
                    .break .if !al

                    add ecx,1
                    add edx,1
                    or  eax,0x2020
                    .break .if al != ah
                .endw

                .if al == ah

                    mov edx,edi ; mother
                    mov ecx,esi ; entry
                    ;
                    ; return value
                    ;
                    mov eax,[esi].S_INI.value
                    .break
                .endif

                mov eax,esi
            .endif
            mov edi,eax
            mov eax,[eax].S_INI.next
        .endw
    .endif
    ret

INIGetEntry endp

    END
