; _SCMOVEL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scmovel proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new z:int_t
   .new b:PCHAR_INFO

ifndef _WIN64
    mov ecx,rc
endif

    mov eax,ecx
    .if ( al == 0 )
        .return
    .endif

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

    .if malloc( eax )

        mov rbx,rax
        _scread(rc, rax)
        mov b,_screadl( edi, y, l )
        dec rc.x
        _scwrite( rc, rbx )
        free( rbx )

        movzx ebx,rc.col
        lea rax,[rbx-1]
        mov z,eax
        shl ebx,3
        mov edx,esi
        shl eax,2
        mov rsi,p
        add rsi,rax
        mov rdi,b
        std

        .repeat
            mov ecx,[rsi]
            mov eax,[rdi]
            mov [rdi],ecx
            push rdi
            mov rdi,rsi
            sub rsi,4
            mov ecx,z
            rep movsd
            pop rdi
            mov [rsi+4],eax
            add rsi,rbx
            add rdi,4
            dec edx
        .until !edx

        cld
        movzx ecx,rc.col
        add ecx,x
        dec ecx

        _scwritel( ecx, y, l, b )
    .endif
    .return( rc )

_scmovel endp

    end
