; _SCPATHA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpathA proc uses rsi rdi rbx x:BYTE, y:BYTE, maxlen:BYTE, string:LPSTR

  local b[16]:char_t

    movzx esi,maxlen
    .ifd ( strlen( string ) > esi )

        lea rbx,b
        mov rdi,string
        mov ecx,[rdi]
        add rdi,rax
        sub rdi,rsi
        mov edx,4
        mov eax,'\..\'

        .if ch == ':'

            mov [rbx],cx
            mov [rbx+2],eax
            add edx,2
        .else
            mov [rbx],eax
        .endif

        mov b[rdx],0
        add rdi,rdx
        mov string,rdi
        add x,dl

        _scputsA( x, y, rbx )
    .endif

    mov ebx,eax
    _scputsA( x, y, string )
    add eax,ebx
    ret

_scpathA endp

    end
