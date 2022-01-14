; _SCPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpath proc x:int_t, y:int_t, maxlen:int_t, string:string_t

  local b[16]:byte

    .ifd strlen(r9) > maxlen

        lea r10,b
        mov r11,string
        mov edx,maxlen
        mov ecx,[r11]
        add r11,rax
        sub r11,rdx
        mov edx,4
        mov eax,'\..\'

        .if ch == ':'

            mov [r10],cx
            mov [r10+2],eax
            add edx,2

        .else

            mov [r10],eax
        .endif

        mov b[rdx],0
        add r11,rdx
        mov string,r11
        add x,edx
        _scputs(x, y, r10)
    .endif

    mov maxlen,eax
    _scputs(x, y, string)
    add eax,maxlen
    ret

_scpath endp

    END
