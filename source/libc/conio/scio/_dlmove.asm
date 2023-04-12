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

    assume rbx:PCONSOLE

_dlmove proc uses rsi rdi rbx hwnd:THWND, direction:SINT

   .new rc:TRECT
   .new wc:TRECT
   .new retval:int_t = FALSE
   .new line[MAXSCRLINE]:CHAR_INFO

    mov rbx,_console
    mov wc,[rbx].rc
    mov rdi,[rbx].buffer
    dec [rbx].paint
    mov rbx,hwnd
    mov rsi,[rbx].window
    mov rc,[rbx].rc

    .switch pascal direction
    .case TW_MOVELEFT

        .if ( rc.x == 0 )
            .endc
        .endif

        dec     rc.x
        movzx   eax,wc.col
        movzx   ecx,rc.x
        mul     rc.y
        add     eax,ecx
        shl     eax,2
        add     rdi,rax

        .for ( bl = 0 : bl < rc.row : bl++ )
            mov eax,[rdi]
            .for ( bh = 0 : bh < rc.col : bh++, rsi += 4 )
                mov ecx,[rsi]
                mov [rsi],eax
                mov eax,ecx
            .endf
            .for ( rdx = rdi, bh = 0 : bh < rc.col : bh++, rdi += 4 )
                mov ecx,[rdi+4]
                mov [rdi],ecx
            .endf
            mov [rdi],eax
            movzx eax,wc.col
            lea rdi,[rdx+rax*4]
        .endf

    .case TW_MOVERIGHT

        movzx eax,wc.col
        movzx ecx,rc.x
        movzx edx,rc.col
        add   ecx,edx
        .if ( eax <= ecx )
            .endc
        .endif

        inc     rc.x
        movzx   ecx,rc.x
        mul     rc.y
        add     eax,ecx
        shl     eax,2
        add     rdi,rax

        movzx   edx,rc.col
        dec     edx
        shl     edx,2
        add     rdi,rdx
        add     rsi,rdx
        add     rdx,4

        .for ( bl = 0 : bl < rc.row : bl++ )

            mov eax,[rdi]

            .for ( bh = 0 : bh < rc.col : bh++, rsi -= 4 )

                mov ecx,[rsi]
                mov [rsi],eax
                mov eax,ecx
            .endf

            .for ( bh = 0 : bh < rc.col : bh++, rdi -= 4 )

                mov ecx,[rdi-4]
                mov [rdi],ecx
            .endf
            mov   [rdi],eax
            movzx eax,wc.col
            lea   rdi,[rdi+rax*4]
            lea   rsi,[rsi+rdx*2]
            add   rdi,rdx
        .endf

    .case TW_MOVEUP

        .endc .if ( rc.y == 0 )

        dec     rc.y
        movzx   eax,wc.col
        movzx   ecx,rc.x
        mul     rc.y
        add     eax,ecx
        shl     eax,2
        add     rdi,rax

        push    rsi
        push    rdi
        mov     cl,rc.col
        mov     eax,ecx
        mov     rsi,rdi
        lea     rdi,line
        rep     movsd
        pop     rdi
        movzx   edx,wc.col
        shl     edx,2
        shl     eax,2
        lea     rsi,[rdi+rdx]
        sub     rdx,rax

        .for ( bl = 0 : bl < rc.row : bl++ )

            mov cl,rc.col
            rep movsd
            add rdi,rdx
            add rsi,rdx
        .endf

        pop     rsi
        movzx   eax,rc.row
        dec     eax
        mul     rc.col
        lea     rsi,[rsi+rax*4]
        mov     cl,rc.col
        rep     movsd
        sub     rsi,4
        mov     rdi,rsi
        mov     cl,rc.col
        shl     ecx,2
        sub     rsi,rcx
        mov     ecx,eax
        std
        rep     movsd
        cld
        lea     rdi,[rsi+4]
        lea     rsi,line
        mov     cl,rc.col
        rep     movsd

    .case TW_MOVEDOWN

        movzx   ecx,wc.row
        movzx   eax,rc.y
        movzx   edx,rc.row
        add     eax,edx
        .if ( ecx <= eax )
            .endc
        .endif
        inc     rc.y

        movzx   eax,wc.col
        movzx   ecx,rc.x
        movzx   ebx,rc.y
        dec     ebx
        add     ebx,edx
        mul     ebx
        add     eax,ecx
        lea     rdi,[rdi+rax*4]

        push    rsi
        push    rdi

        mov     cl,rc.col
        mov     rsi,rdi
        lea     rdi,line
        rep     movsd
        pop     rdi
        mov     rsi,rdi
        movzx   edx,wc.col
        shl     edx,2
        sub     rsi,rdx
        movzx   eax,rc.col
        shl     eax,2
        lea     rsi,[rsi+rax-4]
        lea     rdi,[rdi+rax-4]
        sub     rdx,rax
        std
        .for ( bl = 0 : bl < rc.row : bl++ )

            mov cl,rc.col
            rep movsd
            sub rdi,rdx
            sub rsi,rdx
        .endf
        cld
        pop     rsi
        mov     cl,rc.col
        lea     eax,[rcx*4-4]
        sub     rdi,rax
        rep     movsd
        mov     rdi,rsi
        sub     rdi,rax
        sub     rdi,4
        movzx   eax,rc.row
        dec     eax
        mul     rc.col
        mov     ecx,eax
        rep     movsd
        lea     rsi,line
        mov     cl,rc.col
        rep     movsd
    .endsw


    mov rbx,hwnd
    mov eax,rc
    .if ( eax != [rbx].rc )

        mov [rbx].rc,eax
        inc retval

        .if ( [rbx].flags & W_TRANSPARENT )

            mov     rdi,[rbx].window
            mov     rbx,_console
            mov     rsi,[rbx].buffer
            movzx   eax,wc.col
            mov     edx,eax
            movzx   ecx,rc.x
            mul     rc.y
            add     eax,ecx
            shl     eax,2
            add     rsi,rax
            sub     dl,rc.col
            shl     edx,2

            .for ( : rc.row : rc.row--, rsi+=rdx )

                .for ( ebx = 0 : bl < rc.col : ebx++, rsi+=4, rdi+=4 )

                    .if ( byte ptr [rsi+2] == DARKGRAY )

                        mov ax,[rdi]
                        mov [rsi],ax
                    .endif
                .endf
            .endf
        .endif
        _cendpaint()
    .else
        mov rbx,_console
        inc [rbx].paint
    .endif
   .return(retval)

_dlmove endp

    end
