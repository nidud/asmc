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

    assume r13:PCONSOLE
    assume r14:PCONSOLE

_dlmove proc uses rbx r12 r13 r14 hwnd:THWND, direction:SINT

   .new rc:TRECT
   .new wc:TRECT
   .new retval:int_t = FALSE
   .new line[MAXSCRLINE]:CHAR_INFO

    mov r13,_console
    mov r14,hwnd
    mov r12d,direction
    mov wc,[r13].rc
    mov rdi,[r13].buffer
    dec [r13].paint
    mov rsi,[r14].window
    mov rc,[r14].rc

    .switch pascal r12d
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

        .if ( rc.y == 0 )
            .endc
        .endif

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
        sub     rsi,8
        mov     rdi,rsi
        mov     cl,rc.col
        shl     ecx,2
        sub     rsi,rcx
        mov     ecx,eax
        std
        rep     movsd
        cld
        lea     rdi,[rsi+8]
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


    mov eax,rc
    .if ( eax != [r14].rc )

        mov [r14].rc,eax
        inc retval

        .if ( [r14].flags & W_TRANSPARENT )

            mov     rdi,[r14].window
            mov     rsi,[r13].buffer
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
        inc [r13].paint
    .endif
   .return(retval)

_dlmove endp

    end
