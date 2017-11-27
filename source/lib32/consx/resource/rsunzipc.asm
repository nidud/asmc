include consx.inc
include alloc.inc

    .code

rsunzipch proc uses ebx

    .repeat
        lodsb
        mov dl,al
        and dl,0F0h
        .if dl == 0F0h
            mov ah,al
            lodsb
            and eax,0FFFh
            mov ebx,eax
            lodsb
            .repeat
                stosb
                inc edi
                dec ebx
                .break .ifz
            .untilcxz
            .break .if !ecx
        .else
            stosb
            inc edi
        .endif
    .untilcxz
    ret

rsunzipch endp

    END
