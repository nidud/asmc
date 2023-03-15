; _SCMOVER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_scmover proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new b:PCHAR_INFO
   .new ci:CONSOLE_SCREEN_BUFFER_INFO

    mov edi,80
    .if GetConsoleScreenBufferInfo(_confh, &ci)

        movzx edi,ci.dwSize.X
    .endif

    movzx   ecx,rc.x
    movzx   edx,rc.col
    mov     esi,ecx
    add     ecx,edx
    mov     eax,rc

    .if ( edi <= ecx )

        .return
    .endif

    mov     edi,ecx
    mov     x,esi
    mov     cl,rc.y
    mov     y,ecx
    mov     cl,rc.row
    mov     eax,ecx
    not     ecx
    mov     l,ecx
    mul     rc.col
    shl     eax,2

    .if malloc( eax )

        mov rbx,rax
        _scread( rc, rax )
        mov b,_screadl( edi, y, l )
        inc rc.x
        _scwrite( rc, rbx )
        free( rbx )

        movzx   ebx,rc.col
        dec     ebx
        movzx   edx,rc.row
        mov     rsi,p
        mov     rdi,b

        .repeat

            mov     ecx,[rsi]
            mov     eax,[rdi]
            mov     [rdi],ecx
            push    rdi
            mov     rdi,rsi
            add     rsi,4
            mov     ecx,ebx
            rep     movsd
            pop     rdi
            mov     [rsi-4],eax
            add     rdi,4
            dec     edx
        .untilz

        _scwritel( x, y, l, b )
    .endif
    .return( rc )

_scmover endp

    end
