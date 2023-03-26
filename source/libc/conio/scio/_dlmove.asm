; _DLMOVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

define _CONIO_RETRO_COLORS
include conio.inc
include malloc.inc
include crtl.inc

    .code

    assume rbx:THWND

_dlmove proc uses rsi rdi rbx hwnd:THWND, direction:SINT

   .new x:int_t
   .new y:int_t
   .new l:int_t
   .new z:int_t
   .new rc:TRECT
   .new w:PCHAR_INFO
   .new b:PCHAR_INFO
   .new p:PCHAR_INFO
   .new retval:int_t = FALSE

    mov     rbx,hwnd
    mov     p,.window
    mov     rc,.rc
    movzx   eax,rc.col
    mul     rc.row
    shl     eax,2
    mov     w,malloc(eax)

    _rcread(rc, rax)

    .switch direction
    .case TW_MOVELEFT

        mov     ecx,rc
        mov     eax,ecx

        .endc   .if ( al == 0 )

        movzx   eax,al
        lea     rdi,[rax-1]
        mov     x,eax
        mov     al,ch
        mov     y,eax
        mov     al,rc.row
        mov     esi,eax
        not     eax
        mov     l,eax
        mov     b,_scgetl( edi, y, l )
        dec     rc.x
        movzx   ebx,rc.col
        lea     rax,[rbx-1]
        mov     z,eax
        shl     ebx,3
        mov     edx,esi
        shl     eax,2
        mov     rsi,p
        add     rsi,rax
        mov     rdi,b
        std

        .repeat
            mov     ecx,[rsi]
            mov     eax,[rdi]
            mov     [rdi],ecx
            push    rdi
            mov     rdi,rsi
            sub     rsi,4
            mov     ecx,z
            rep     movsd
            pop     rdi
            mov     [rsi+4],eax
            add     rsi,rbx
            add     rdi,4
            dec     edx
        .until !edx

        cld
        movzx   ecx,rc.col
        add     ecx,x
        dec     ecx
        _scputl(ecx, y, l, b)
        .endc

    .case TW_MOVERIGHT

        movzx   edi,_consize.X
        movzx   ecx,rc.x
        movzx   edx,rc.col
        mov     esi,ecx
        add     ecx,edx
        mov     eax,rc

        .endc .if ( edi <= ecx )

        mov     edi,ecx
        mov     x,esi
        mov     cl,rc.y
        mov     y,ecx
        mov     cl,rc.row
        mov     eax,ecx
        not     ecx
        mov     l,ecx
        mov     b,_scgetl( edi, y, l )
        inc     rc.x

        movzx   ebx,rc.col
        dec     ebx
        movzx   edx,rc.row
        mov     rsi,p
        mov     rdi,b

        .repeat
            mov ecx,[rsi]
            mov eax,[rdi]
            mov [rdi],ecx
            push rdi
            mov rdi,rsi
            add rsi,4
            mov ecx,ebx
            rep movsd
            pop rdi
            mov [rsi-4],eax
            add rdi,4
            dec edx
        .untilz
        _scputl(x, y, l, b)
        .endc

    .case TW_MOVEUP

        movzx   eax,rc.y

        .endc   .if ( eax < 1 )

        movzx   esi,rc.row
        dec     eax
        add     esi,eax
        mov     edi,eax
        mov     al,rc.x
        mov     x,eax
        mov     al,rc.col
        mov     l,eax
        mov     b,_scgetl( x, edi, l )
        dec     rc.y

        mov     ebx,l
        shl     ebx,2
        movzx   eax,rc.row
        dec     eax
        mov     z,eax
        mul     ebx
        mov     rdi,p
        add     rdi,rax

        memxchg( b, rdi, rbx )
        _scputl( x, esi, l, b )

        mov     b,rdi
        sub     b,rbx
        mov     esi,z

        .while esi

            memxchg( b, rdi, rbx )
            sub rdi,rbx
            sub b,rbx
            dec esi
        .endw
        .endc

    .case TW_MOVEDOWN

        movzx   edi,_consize.Y
        movzx   eax,rc.y
        movzx   edx,rc.row
        mov     esi,eax
        add     eax,edx

        .endc   .if ( edi <= eax )

        mov     edi,eax
        mov     al,rc.x
        mov     x,eax
        mov     al,rc.col
        mov     l,eax
        mov     b,_scgetl( x, edi, l )
        inc     rc.y

        mov     ebx,l
        shl     ebx,2

        memxchg( b, p, rbx )
        _scputl( x, esi, l, rax )

        movzx   esi,rc.row
        dec     esi
        mov     rdi,p

        .while esi

            memxchg( rdi, &[rdi+rbx], rbx )
            add rdi,rbx
            dec esi
        .endw
        .endc
    .endsw

    mov rbx,hwnd
    mov eax,rc
    .if ( eax != .rc )

        mov .rc,eax
        inc retval

        .if ( .flags & W_TRANSPARENT )

            mov rdi,p
            mov rsi,w
            movzx eax,rc.col
            mul rc.row

            .for ( ecx = eax, edx = 0 : edx < ecx : edx++ )

                .if ( byte ptr [rsi+rdx*4+2] == DARKGRAY )

                    mov ax,[rdi+rdx*4]
                    mov [rsi+rdx*4],ax
                .endif
            .endf
        .endif
        _rcwrite(rc, w)
    .endif
    free(w)
   .return(retval)

_dlmove endp

    end
