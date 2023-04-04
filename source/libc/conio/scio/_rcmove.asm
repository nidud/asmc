; _RCMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc
include crtl.inc

    .code

_rcmoveu proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new l:int_t
   .new z:int_t
   .new b:PCHAR_INFO
   .new cz:TRECT

    mov rbx,_console
    mov cz,[rbx].TCLASS.rc

    movzx eax,rc.y
    .if ( eax > 1 )

        movzx esi,rc.row
        dec eax
        add esi,eax
        mov edi,eax
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
            mov b,_scgetl( x, edi, l )
            dec rc.y
            _rcwrite( rc, rbx )
            free( rbx )

            mov ebx,l
            shl ebx,2
            movzx eax,rc.row
            dec eax
            mov z,eax
            mul ebx
            mov rdi,p
            add rdi,rax

            memxchg( b, rdi, rbx )
            _scputl( x, esi, l, b )

            mov b,rdi
            sub b,rbx
            mov esi,z

            .while esi

                memxchg( b, rdi, rbx )
                sub rdi,rbx
                sub b,rbx
                dec esi
            .endw
            _cendpaint()
        .endif
    .endif
    .return( rc )

_rcmoveu endp


_rcmoved proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new l:int_t
   .new b:PCHAR_INFO
   .new cz:TRECT

    mov rbx,_console
    mov cz,[rbx].TCLASS.rc
    movzx edi,cz.row
    movzx eax,rc.y
    movzx edx,rc.row
    mov esi,eax
    add eax,edx

    .if ( edi > eax )

        mov edi,eax
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
            mov b,_scgetl( x, edi, l )
            inc rc.y
            _rcwrite( rc, rbx )
            free( rbx )

            mov ebx,l
            shl ebx,2
            memxchg( b, p, rbx )
            _scputl( x, esi, l, rax )

            movzx esi,rc.row
            dec esi
            mov rdi,p
            .while esi

                memxchg( rdi, &[rdi+rbx], rbx )
                add rdi,rbx
                dec esi
            .endw
            _cendpaint()
        .endif
    .endif
    .return( rc )

_rcmoved endp


_rcmovel proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

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
        _cbeginpaint()
        _rcread(rc, rbx)
        mov b,_scgetl( edi, y, l )
        dec rc.x
        _rcwrite( rc, rbx )
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

        _scputl( ecx, y, l, b )
        _cendpaint()
    .endif
    .return( rc )

_rcmovel endp


_rcmover proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new b:PCHAR_INFO
   .new cz:TRECT

    mov     rbx,_console
    mov     cz,[rbx].TCLASS.rc
    movzx   edi,cz.col
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
        _cbeginpaint()
        _rcread( rc, rbx )
        mov b,_scgetl( edi, y, l )
        inc rc.x
        _rcwrite( rc, rbx )
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

        _scputl( x, y, l, b )
        _cendpaint()
    .endif
    .return( rc )

_rcmover endp

    end
