; _SCPATHA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_scpathA proc uses rbx r12 r13 r14 x:BYTE, y:BYTE, maxlen:BYTE, string:LPSTR

   .new b[16]:char_t

    mov r12,string
    mov r13b,x
    mov r14b,y
    movzx ebx,maxlen
    .ifd ( strlen(r12) > ebx )

        mov rdi,r12
        mov ecx,[rdi]
        add rdi,rax
        sub rdi,rbx
        lea rbx,b
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
        mov r12,rdi
        add x,dl

        _scputsA(r13b, r14b, rbx)
    .endif

    mov ebx,eax
    _scputsA(r13b, r14b, r12)
    add eax,ebx
    ret

_scpathA endp

    end
