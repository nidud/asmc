; BTOHEX.ASM--
; Copyright (C) 2017 Asmc Developers
;
include string.inc

.code

btohex proc string:LPSTR, count:SINT

    mov edx,string
    mov eax,count
    dec eax
    mov ecx,edx
    add ecx,eax
    add eax,eax
    add edx,eax
    mov byte ptr [edx+2],0
    .repeat
        mov al,[ecx]
        mov ah,al
        shr al,4
        and ah,15
        add ax,'00'
        .if al > '9'
            add al,7
        .endif
        .if ah > '9'
            add ah,7
        .endif
        mov [edx],ax
        dec ecx
        sub edx,2
    .until edx < ecx
    mov eax,string
    ret

btohex endp

    end
