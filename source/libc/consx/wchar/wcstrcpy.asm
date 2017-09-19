include consx.inc
include string.inc

    .code

wcstrcpy proc uses esi edi ebx cp:LPSTR, wc:PVOID, count

    mov edi,cp
    mov esi,wc
    mov ecx,count
    mov bl,[esi+1]
    and bl,0x0F
    .repeat
        .break .if !ecx
        dec ecx
        lodsw
        .continue(0) .if al <= ' '
        .continue(0) .if al > 176
        sub esi,2
        .break .if !ecx
        .repeat
            lodsw
            .break(1) .if al > 176
            and ah,0x0F
            .if ah != bl
                mov ah,al
                mov al,'&'
                stosb
                mov al,ah
            .endif
            stosb
        .untilcxz
    .until 1
    mov byte ptr [edi],0
    strtrim(cp)
    ret

wcstrcpy endp

    END
