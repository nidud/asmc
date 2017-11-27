include strlib.inc
include ltype.inc

    .data
    token dd ?

    .code

strtoken proc string:LPSTR

    mov eax,string
    mov ecx,token
    .if eax

        mov ecx,eax
        xor eax,eax
    .endif
    .repeat

        mov al,[ecx]
        inc ecx
    .until !(_ltype[eax+1] & _SPACE)

    .repeat

        dec ecx
        mov token,ecx
        .break .if !al

        .repeat
            .repeat
                mov al,[ecx]
                inc ecx
                .break(1) .if !al
            .until _ltype[eax+1] & _SPACE
            mov [ecx-1],ah
            inc ecx
        .until 1
        dec ecx
        mov eax,token
        mov token,ecx
    .until 1
    ret

strtoken endp

    END
