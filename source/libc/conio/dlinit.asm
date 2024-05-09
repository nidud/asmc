; DLINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

.code

dlinit proc uses rsi rdi rbx td:PDOBJ

  local object:PTOBJ, wp:PCHAR_INFO, window:ptr

    ldr rbx,td
    mov edi,[rbx]

    .if ( edi & W_VISIBLE )

        mov wp,[rbx].DOBJ.window
        .if ( _rcalloc([rbx].DOBJ.rc, W_UNICODE) == NULL )

            .return
        .endif

        mov [rbx].DOBJ.window,rax
        _rcread( [rbx].DOBJ.rc, rax)
    .endif

    .new flags:int_t  = edi
    .new count:byte   = [rbx].DOBJ.count
    .new rc:TRECT     = [rbx].DOBJ.rc
    .new p:PCHAR_INFO = [rbx].DOBJ.window

    .for ( rbx = [rbx].DOBJ.object : count : count--, rbx += TOBJ )

        mov     rdi,_rcbprc(rc, [rbx].TOBJ.rc, p)
        movzx   eax,[rbx].TOBJ.flags
        and     eax,0x000F

        .switch eax
        .case _O_PBUTT
            movzx ecx,[rbx].TOBJ.rc.col
            .repeat
                mov ah,[rdi+2]
                mov al,ah
                and al,0x0F
                .if ( [rbx].TOBJ.flags & O_STATE )
                    .if !al
                        and ah,0x70
                        or  ah,0x08
                        mov [rdi+2],ah
                    .endif
                .elseif al == 8
                    and ah,0x70
                    mov [rdi+2],ah
                .endif
                add rdi,4
            .untilcxz
            .endc
        .case _O_RBUTT
            mov eax,' '
            .if ( [rbx].TOBJ.flags & O_RADIO )
                mov eax,U_BULLET_OPERATOR
            .endif
            mov [rdi+4],ax
           .endc
        .case _O_CHBOX
            mov eax,' '
            .if ( [rbx].TOBJ.flags & O_CHECK )
                mov eax,'x'
            .endif
            mov [rdi+4],ax
           .endc

        .case _O_XCELL
            .for ( ecx = 0 : cl < [rbx].TOBJ.rc.col : ecx++ )
                mov word ptr [rdi+rcx*4],' '
            .endf
            mov rsi,[rbx].TOBJ.data
            .if rsi
                add rdi,4
                movzx ecx,[rbx].TOBJ.rc.col
                sub ecx,2
                wcpath(rdi, ecx, rsi)
            .endif
            .endc

        .case _O_TEDIT
            mov edx,U_MIDDLE_DOT
            .for ( ecx = 0 : cl < [rbx].TOBJ.rc.col : ecx++ )
                mov [rdi+rcx*4],dx
            .endf
            mov rsi,[rbx].TOBJ.data
            .if rsi
                .for ( eax = 0, ecx = 0 : cl < [rbx].TOBJ.rc.col : ecx++ )

                    mov al,[rsi+rcx]
                    .break .if !al
                    mov [rdi+rcx*4],ax
                .endf
            .endif
            .endc
        .case _O_MENUS
            .if ( [rbx].TOBJ.flags & O_CHECK )
                mov word ptr [rdi-4],0x00BB
            .elseif ( [rbx].TOBJ.flags & O_RADIO )
                mov word ptr [rdi-4],U_BULLET_OPERATOR
            .endif
            .endc
        .endsw
    .endf

    .if ( flags & W_VISIBLE )

        mov rbx,td
        _rcwrite([rbx].DOBJ.rc, [rbx].DOBJ.window)
        free([rbx].DOBJ.window)
        mov [rbx].DOBJ.window,wp
    .endif
    ret

dlinit endp

    end
