include iost.inc

    .code

ogetc proc
    lea eax,STDI
ogetc endp

iogetc proc uses edx

    assume edx:ptr S_IOST

    mov edx,eax
    mov eax,[edx].ios_i

    .repeat

        .if eax == [edx].ios_c

            .while 1

                .if !([edx].ios_flag & IO_MEMBUF)

                    push ecx
                    ioread(edx)
                    pop ecx
                    mov eax,[edx].ios_i
                    .break .ifnz
                .endif
                or  eax,-1
                xor edx,edx
                .break(1)
            .endw
        .endif

        inc   [edx].ios_i
        add   eax,[edx].ios_bp
        movzx eax,byte ptr [eax]

    .until 1
    ret

iogetc endp

    END
