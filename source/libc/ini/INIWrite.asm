include ini.inc
include stdio.inc

    .code

    assume esi:ptr S_INI
    assume edi:ptr S_INI

INIWrite proc uses esi edi ebx ini:LPINI, file:LPSTR

    .if fopen(file, "wt")

        mov ebx,eax
        mov esi,ini

        .while esi

            .if [esi].flags == INI_SECTION

                fprintf(ebx, "\n[%s]\n", [esi].entry)
            .endif

            mov edi,[esi].value
            .while edi

                .if [edi].flags == INI_ENTRY

                    fprintf(ebx, "%s=%s\n", [edi].entry, [edi].value)
                .elseif [edi].flags == INI_COMMENT

                    fprintf(ebx, "%s\n", [edi].entry)
                .else
                    fprintf(ebx, ";%s\n", [edi].entry)
                .endif

                mov edi,[edi].next
            .endw

            mov esi,[esi].next
        .endw

        fclose(ebx)
        mov eax,1
    .endif
    ret

INIWrite endp

    END
