; _RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc
include crtl.inc

    .code

_rcmoveu proc uses rbx r12 r13 _rc:TRECT, _p:PCHAR_INFO

   .new x:int_t
   .new l:int_t
   .new z:int_t
   .new b:PCHAR_INFO
   .new cz:TRECT
   .new rc:TRECT = _rc
   .new p:PCHAR_INFO = _p

    mov rbx,_console
    mov cz,[rbx].TCLASS.rc

    movzx eax,rc.y
    .if ( eax > 1 )

        movzx r12d,rc.row
        dec eax
        add r12d,eax
        mov r13d,eax
        mov al,rc.x
        mov x,eax
        mov al,rc.col
        mov l,eax
        mul rc.row
        shl eax,2

        .if malloc( eax )

            mov rbx,rax
            _cbeginpaint()
            _rcread( rc, rbx )
            mov b,_scgetl( x, r13d, l )
            dec rc.y
            _rcwrite( rc, rbx )
            free( rbx )

            mov ebx,l
            shl ebx,2
            movzx eax,rc.row
            dec eax
            mov z,eax
            mul ebx
            mov r13,p
            add r13,rax

            memxchg( b, r13, rbx )
            _scputl( x, r12d, l, b )

            mov b,r13
            sub b,rbx
            mov r12d,z

            .while r12d

                memxchg( b, r13, rbx )
                sub r13,rbx
                sub b,rbx
                dec r12d
            .endw
            _cendpaint()
        .endif
    .endif
    .return( rc )

_rcmoveu endp


_rcmoved proc uses rbx r12 r13 _rc:TRECT, _p:PCHAR_INFO

   .new x:int_t
   .new l:int_t
   .new b:PCHAR_INFO
   .new cz:TRECT
   .new rc:TRECT = _rc
   .new p:PCHAR_INFO = _p

    mov rbx,_console
    mov cz,[rbx].TCLASS.rc
    movzx r12d,cz.row
    movzx eax,rc.y
    movzx edx,rc.row
    mov r13d,eax
    add eax,edx

    .if ( r12d > eax )

        mov r12d,eax
        mov al,rc.x
        mov x,eax
        mov al,rc.col
        mov l,eax
        mul rc.row
        shl eax,2

        .if malloc( eax )

            mov rbx,rax
            _cbeginpaint()
            _rcread(rc, rbx)
            mov b,_scgetl( x, r12d, l )
            inc rc.y
            _rcwrite( rc, rbx )
            free( rbx )

            mov ebx,l
            shl ebx,2
            memxchg( b, p, rbx )
            _scputl( x, r13d, l, rax )

            movzx r13d,rc.row
            dec r13d
            mov r12,p
            .while r13d

                memxchg( r12, &[r12+rbx], rbx )
                add r12,rbx
                dec r13d
            .endw
            _cendpaint()
        .endif
    .endif
    .return( rc )

_rcmoved endp


_rcmovel proc uses rbx r12 r13 _rc:TRECT, _p:PCHAR_INFO

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new z:int_t
   .new b:PCHAR_INFO
   .new rc:TRECT = _rc
   .new p:PCHAR_INFO = _p

    mov ecx,rc
    mov eax,ecx
    .if ( al == 0 )
        .return
    .endif

    movzx   eax,al
    lea     r12,[rax-1]
    mov     x,eax
    mov     al,ch
    mov     y,eax
    mov     al,rc.row
    mov     r13d,eax
    not     eax
    mov     l,eax
    movzx   eax,rc.col
    mul     r13d
    shl     eax,2

    .if malloc( eax )

        mov rbx,rax
        _cbeginpaint()
        _rcread(rc, rbx)
        mov b,_scgetl( r12d, y, l )
        dec rc.x
        _rcwrite( rc, rbx )
        free( rbx )

        movzx ebx,rc.col
        lea rax,[rbx-1]
        mov z,eax
        shl ebx,3
        mov edx,r13d
        shl eax,2
        mov rsi,p
        add rsi,rax
        mov r12,b
        std

        .repeat
            mov ecx,[rsi]
            mov eax,[r12]
            mov [r12],ecx
            mov rdi,rsi
            sub rsi,4
            mov ecx,z
            rep movsd
            mov [rsi+4],eax
            add rsi,rbx
            add r12,4
            dec edx
        .until !edx

        cld
        movzx edi,rc.col
        add edi,x
        dec edi

        _scputl( edi, y, l, b )
        _cendpaint()
    .endif
    .return( rc )

_rcmovel endp


_rcmover proc uses rbx r12 r13 _rc:TRECT, _p:PCHAR_INFO

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new b:PCHAR_INFO
   .new cz:TRECT
   .new rc:TRECT = _rc
   .new p:PCHAR_INFO = _p

    mov     rbx,_console
    mov     cz,[rbx].TCLASS.rc
    movzx   r12d,cz.col
    movzx   ecx,rc.x
    movzx   edx,rc.col
    mov     r13d,ecx
    add     ecx,edx
    mov     eax,rc

    .if ( r12d <= ecx )

        .return
    .endif

    mov     r12d,ecx
    mov     x,r13d
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
        _cbeginpaint()
        _rcread( rc, rbx )
        mov b,_scgetl( r12d, y, l )
        inc rc.x
        _rcwrite( rc, rbx )
        free( rbx )

        movzx   ebx,rc.col
        dec     ebx
        movzx   edx,rc.row
        mov     rsi,p
        mov     r12,b

        .repeat
            mov     ecx,[rsi]
            mov     eax,[r12]
            mov     [r12],ecx
            mov     rdi,rsi
            add     rsi,4
            mov     ecx,ebx
            rep     movsd
            mov     [rsi-4],eax
            add     r12,4
            dec     edx
        .untilz

        _scputl( x, y, l, b )
        _cendpaint()
    .endif
    .return( rc )

_rcmover endp

    end
