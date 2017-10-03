; char *strshr(char *string, char ch);
;
; shift string to the right and insert char in front of string
;
include strlib.inc

    .code

strshr proc uses edx ecx string:LPSTR, char:UINT

    mov edx,string
    mov eax,[edx]
    shl eax,8
    mov al,byte ptr char

    .while 1

        mov ecx,[edx+3]
        mov [edx],eax

        .break .if !(eax & 0x000000FF)
        .break .if !(eax & 0x0000FF00)
        .break .if !(eax & 0x00FF0000)
        .break .if !(eax & 0xFF000000)

        mov eax,ecx
        add edx,4
    .endw
    mov eax,string
    ret

strshr endp

    END
