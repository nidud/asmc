; _SCMOVEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scmovel proc uses rsi rdi rbx r12 rc:TRECT, p:PCHAR_INFO

  local x,y,l

    mov eax,ecx
    .return .if ( al == 0 )

    movzx   eax,al
    lea     rdi,[rax-1]
    mov     x,eax
    mov     al,ch
    mov     y,eax
    mov     al,rc.row
    mov     esi,eax
    not     eax
    mov     l,eax
    movzx   eax,rc.col
    mul     esi
    shl     eax,2

    .if malloc(eax)

        mov rbx,rax
        _scread(rc, rax)
        mov r12,_screadl(edi, y, l)
        dec rc.x
        _scwrite(rc, rbx)
        free(rbx)

        movzx   r8d,rc.col
        lea     rax,[r8-1]
        mov     ebx,eax
        shl     r8d,3
        mov     edx,esi
        shl     eax,2
        mov     rsi,p
        add     rsi,rax
        mov     rdi,r12
        std

        .repeat
            mov eax,[rsi]
            mov r9d,[rdi]
            mov [rdi],eax
            mov ecx,ebx
            mov r10,rdi
            mov rdi,rsi
            sub rsi,4
            rep movsd
            mov rdi,r10
            mov [rsi+4],r9d
            add rsi,r8
            add rdi,4
            dec edx
        .until !edx
        cld
        movzx   ecx,rc.col
        add     ecx,x
        dec     ecx
        _scwritel(ecx, y, l, r12)
    .endif
    mov eax,rc
    ret

_scmovel endp

    end
