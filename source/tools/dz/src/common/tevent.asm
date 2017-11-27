include tinfo.inc

extern IDD_TEReload:dword

    .code
    assume esi: ptr S_TINFO

tevent proc uses esi edi

    mov esi,tinfo

    .while 1

        tiseto(esi)
        tiputs(esi)

        .while 1

            .if tiftime(esi)

                .if eax != [esi].ti_time

                    .if rsmodal(IDD_TEReload)

                        timemzero(esi)
                        tiread(esi)

                        mov edi,KEY_ESC
                        .break(1) .ifz

                        tiseto(esi)
                        tiputs(esi)
                    .endif
                .endif
            .endif

            timenus(esi)
            tgetevent()
            mov edi,eax
            tihandler()
            mov esi,tinfo

            .break .if eax == _TI_NOTEVENT
            .break(1) .if eax == _TI_RETEVENT
        .endw
        tievent(esi, edi)
    .endw
    mov edx,esi
    mov eax,edi
    ret

tevent endp

    END
