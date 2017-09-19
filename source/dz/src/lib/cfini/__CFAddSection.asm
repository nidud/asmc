include io.inc
include alloc.inc
include cfini.inc

    .code

__CFAddSection proc uses esi ini:PCFINI, section:LPSTR

    .if !__CFGetSection(ini, section)

        .if __CFAlloc()

            mov esi,eax
            mov [esi].S_CFINI.cf_flag,_CFSECTION
            mov [esi].S_CFINI.cf_name,salloc(section)

            mov eax,ini
            .if eax
                .while [eax].S_CFINI.cf_next

                    mov eax,[eax].S_CFINI.cf_next
                .endw
                mov [eax].S_CFINI.cf_next,esi
            .endif
            mov eax,esi
        .endif
    .endif
    ret

__CFAddSection endp

    END
