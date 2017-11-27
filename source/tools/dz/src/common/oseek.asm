include iost.inc

    .code

oseek proc offs, from

    mov eax,offs
    xor edx,edx
    ioseek(&STDI, edx::eax, from)
    .ifnz
        .if !( STDI.ios_flag & IO_MEMBUF )
            push edx
            push eax
            ioread(&STDI)
            pop eax
            pop edx
        .endif
    .endif
    ret

oseek endp

    END
