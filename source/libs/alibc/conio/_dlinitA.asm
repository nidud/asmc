; _DLINITA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include stdio.inc
include malloc.inc
include ctype.inc

    .code

    assume rbx:THWND
    assume r12:THWND

_dlinitA proc uses rbx r12 r13 r14 r15 hwnd:THWND,
        index:UINT, rc:TRECT, flags:UINT, type:BYTE, id:BYTE, name:LPSTR

    mov     rbx,rdi
    imul    r12d,esi,TCLASS
    add     r12,[rbx].object

    mov     [r12].rc,edx
    mov     [r12].index,r9b
    mov     [r12].type,r8b
    mov     eax,W_CHILD or W_WNDPROC
    or      eax,ecx
    or      [r12].flags,eax
    mov     [r12].winproc,&_defwinproc
    mov     [r12].window,_rcbprc([rbx].rc, [r12].rc, [rbx].window)

    mov     rdi,rax
    xor     edx,edx

    .switch pascal [r12].type
    .case T_PUSHBUTTON ;  [ > Selectable text < ] + shade
        mov     eax,_getattrib(BG_PUSHBUTTON, FG_PUSHBUTTON)
        movzx   ecx,[r12].rc.col
        mov     rdx,rdi
        rep     stosd
        mov     al,[rdi+2]
        and     eax,0xF0
        shl     eax,16
        mov     ax,U_LOWER_HALF_BLOCK
        mov     [rdi],eax
        movzx   ecx,[rbx].rc.col
        lea     rdi,[rdx+rcx*4+4]
        movzx   ecx,[r12].rc.col
        mov     ax,U_UPPER_HALF_BLOCK
        rep     stosd
        lea     rdi,[rdx+8]
        mov     eax,_getattrib(BG_PUSHBUTTON, FG_PUSHBUTTON)
        mov     ecx,_getat(BG_PUSHBUTTON, FG_PBUTTONKEY)
        mov     rdx,name
    .case T_RADIOBUTTON ;  (*)
        mov     wchar_t ptr [rdi],'('
        mov     wchar_t ptr [rdi+8],')'
        add     rdi,4*4
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name
    .case T_CHECKBOX            ;  [x]
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     wchar_t ptr [rdi],'['
        mov     wchar_t ptr [rdi+8],']'
        add     rdi,4*4
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name
    .case T_XCELL               ;  [ Selectable text ]
    .case T_TEXTBUTTON          ;  [>Selectable text<]
    .case T_MENUITEM            ;  XCELL + Stausline info
        add     rdi,4
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name
    .case T_EDIT                ;  [Text input]
        mov     eax,_getattrib(FG_EDIT, BG_EDIT)
        mov     ax,U_MIDDLE_DOT
        movzx   ecx,[r12].rc.col
        rep     stosd
    .case T_TEXTAREA            ;  [Selectable text]
    .case T_MOUSERECT           ;  Clickable area -- no focus
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name
    .endsw

    .if ( rdx )

        .for ( rsi = rdx, edx = 0 : dl < [r12].rc.col : edx++ )

            lodsb
            .break .if !al

            .if ( al == '&' && [r12].type != T_EDIT )

                lodsb
                .break .if !al

                mov [rdi],ax
                mov [rdi+2],cx
                add rdi,4
                or  al,0x20
                mov [r12].syskey,al
            .else
                stosd
               .continue(0)
            .endif
        .endf
    .endif
    .return( r12 )

_dlinitA endp

    end
