; _SCMOVED.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc
include strlib.inc

    .code

_scmoved proc uses rsi rdi rbx r12 rc:TRECT, p:PCHAR_INFO

  local x,l
  local ci: CONSOLE_SCREEN_BUFFER_INFO

    mov edi,25
    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        movzx edi,ci.dwSize.y
    .endif

    movzx eax,rc.y
    movzx edx,rc.row
    mov   esi,eax
    add   eax,edx

    .if edi > eax

        mov edi,eax
        mov al,rc.x
        mov x,eax
        mov al,rc.col
        mov l,eax
        mul rc.row
        shl eax,2

        .if malloc(eax)

            mov rbx,rax
            _scread(rc, rax)
            mov r12,_screadl(x, edi, l)
            inc rc.y
            _scwrite(rc, rbx)
            free(rbx)
            mov ebx,l
            shl ebx,2
            memxchg( r12, p, rbx )
            _scwritel( x, esi, l, rax )
            movzx esi,rc.row
            dec esi
            mov rdi,p
            .while esi
                memxchg(rdi, &[rdi+rbx], rbx)
                add rdi,rbx
                dec esi
            .endw
        .endif
    .endif
    mov eax,rc
    ret

_scmoved endp

    end
