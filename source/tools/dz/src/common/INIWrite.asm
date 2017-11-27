include io.inc
include cfini.inc
include iost.inc
include dzlib.inc

    .code

    assume esi:ptr S_INI
    assume edi:ptr S_INI

INIWrite proc uses esi edi ebx ini:LPINI, file:LPSTR

    .if osopen(file, _A_NORMAL, M_WRONLY, A_CREATETRUNC) != -1

        mov STDO.ios_file,eax
        or  _osfile[eax],FH_TEXT

        .if ioinit(&STDO, OO_MEM64K)

            mov esi,ini
            .while esi

                .if [esi].flags == INI_SECTION

                    oprintf("\n[%s]\n", [esi].entry)
                .endif

                mov edi,[esi].value
                .while edi

                    .if [edi].flags == INI_ENTRY

                        oprintf("%s=%s\n", [edi].entry, [edi].value)
                    .elseif [edi].flags == INI_COMMENT

                        oprintf("%s\n", [edi].entry)
                    .else
                        oprintf( ";%s\n", [edi].entry)
                    .endif

                    mov edi,[edi].next
                .endw

                mov esi,[esi].next
            .endw

            ioflush(&STDO)
            ioclose(&STDO)
            mov eax,1
        .else

            _close(STDO.ios_file)
            xor eax,eax
        .endif
    .else

        xor eax,eax
    .endif
    ret

INIWrite endp

    END
