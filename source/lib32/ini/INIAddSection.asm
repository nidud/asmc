include io.inc
include string.inc
include ini.inc

    .code

INIAddSection proc uses esi ini:LPINI, section:LPSTR

    .if !INIGetSection(ini, section)

        .if INIAlloc()

            mov esi,eax
            mov [esi].S_INI.flags,INI_SECTION
            mov [esi].S_INI.entry,_strdup(section)

            mov eax,ini
            .if eax
                .while [eax].S_INI.next

                    mov eax,[eax].S_INI.next
                .endw
                mov [eax].S_INI.next,esi
            .endif
            mov eax,esi
        .endif
    .endif
    ret

INIAddSection endp

    END
