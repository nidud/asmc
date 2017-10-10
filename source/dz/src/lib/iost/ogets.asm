include iost.inc
include io.inc
include stdio.inc
include string.inc
include alloc.inc
include dzlib.inc

    .code

ogetl proc filename:LPSTR, buffer:LPSTR, bsize

    memset(&STDI, 0, sizeof(S_IOST))

    .if osopen(filename, _A_NORMAL, M_RDONLY, A_OPEN) != -1

        mov STDI.ios_file,eax
        .if malloc(OO_MEM64K)

            mov STDI.ios_bp,eax
            mov STDI.ios_size,OO_MEM64K
            mov eax,bsize
            mov STDI.ios_line,eax
            mov eax,buffer
            mov STDI.ios_crc,eax
        .else
            _close(STDI.ios_file)
            xor eax,eax
        .endif
    .else
        xor eax,eax
    .endif
    ret
ogetl endp

ogets proc uses edi

    mov edi,STDI.ios_crc
    mov ecx,STDI.ios_line

    .repeat

        sub ecx,2
        ogetc()
        .break .ifz

        .repeat

            .if al == 0x0D

                ogetc()
                .break(1)
            .endif
            .break .if al == 0x0A
            .break(1) .if !al
            mov [edi],al
            inc edi
            dec ecx
            .break .ifz
            ogetc()
        .untilz
        inc al
    .until 1

    mov eax,0
    mov [edi],al

    .ifnz
        mov eax,STDI.ios_crc
        mov ecx,edi
        sub ecx,eax
        test edi,edi
    .endif
    ret

ogets endp

    END
