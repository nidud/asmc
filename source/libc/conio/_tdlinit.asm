; _TDLINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include stdio.inc
include malloc.inc
include tchar.inc

    .code

    assume rbx:THWND
    assume rsi:THWND

_dlinit proc uses rsi rdi rbx hwnd:THWND, name:LPTSTR

    ldr rbx,hwnd
    mov rdi,[rbx].window
    mov rsi,[rbx].prev
    xor edx,edx

    .switch pascal [rbx].type

    .case T_PUSHBUTTON

        mov     eax,_getattrib(BG_PUSHBUTTON, FG_PUSHBUTTON)
        movzx   ecx,[rbx].rc.col
        mov     rdx,rdi
        rep     stosd
        mov     al,[rdi+2]
        and     eax,0xF0
        shl     eax,16
        mov     ax,U_LOWER_HALF_BLOCK
        mov     [rdi],eax
        movzx   ecx,[rsi].rc.col
        lea     rdi,[rdx+rcx*4+4]
        movzx   ecx,[rbx].rc.col
        mov     ax,U_UPPER_HALF_BLOCK
        rep     stosd
        lea     rdi,[rdx+8]
        mov     eax,_getattrib(BG_PUSHBUTTON, FG_PUSHBUTTON)
        mov     ecx,_getat(BG_PUSHBUTTON, FG_PBUTTONKEY)
        mov     rdx,name

    .case T_RADIOBUTTON

        mov     wchar_t ptr [rdi],'('
        mov     wchar_t ptr [rdi+8],')'
        add     rdi,4*4
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name

    .case T_CHECKBOX

        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     wchar_t ptr [rdi],'['
        mov     wchar_t ptr [rdi+8],']'
        add     rdi,4*4
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name

    .case T_XCELL
    .case T_TEXTBUTTON
    .case T_MENUITEM

        add     rdi,4
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name

    .case T_EDIT

        mov     eax,_getattrib(FG_EDIT, BG_EDIT)
        mov     ax,U_MIDDLE_DOT
        movzx   ecx,[rbx].rc.col
        rep     stosd

    .case T_TEXTAREA
    .case T_MOUSERECT

        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name
    .endsw

    .if ( rdx )

        .for ( rsi=rdx, edx=0 : dl < [rbx].rc.col : edx++ )

            _tlodsb
            .break .if !_tal

            .if ( _tal == '&' && [rbx].type != T_EDIT )

                _tlodsb
                .break .if !_tal

                mov [rdi],ax
                mov [rdi+2],cx
                add rdi,4

                or  al,0x20
                mov [rbx].syskey,al
            .else
                stosd
               .continue(0)
            .endif
        .endf
    .endif
    .return( rbx )

_dlinit endp

    end
