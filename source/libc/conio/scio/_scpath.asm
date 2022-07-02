; _SCPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpath proc uses rdi rbx x:int_t, y:int_t, maxlen:int_t, string:string_t

  local b[16]:byte

    .ifd ( strlen( string ) > maxlen )

        lea rbx,b
        mov rdi,string
        mov edx,maxlen
        mov ecx,[rdi]
        add rdi,rax
        sub rdi,rdx
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
        add x,edx

        _scputs( x, y, rbx )
    .endif

    mov maxlen,eax
    _scputs( x, y, string )
    add eax,maxlen
    ret

_scpath endp

    end
