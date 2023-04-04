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
    assume rsi:THWND

_dlinitA proc uses rsi rdi rbx hwnd:THWND, index:UINT, rc:TRECT, flags:UINT, type:BYTE, id:BYTE, name:LPSTR

    mov     rbx,hwnd
    imul    esi,index,TCLASS
    add     rsi,[rbx].object

    mov     [rsi].rc,rc
    mov     [rsi].index,id
    mov     [rsi].type,type
    mov     eax,W_CHILD or W_WNDPROC
    or      eax,flags
    or      [rsi].flags,eax
    mov     [rsi].winproc,&_defwinproc
    mov     [rsi].window,_rcbprc([rbx].rc, rc, [rbx].window)

    mov     rdi,rax
    xchg    rsi,rbx
    xor     edx,edx

    .switch pascal type
    .case T_PUSHBUTTON ;  [ > Selectable text < ] + shade
        mov     eax,_getattrib(BG_PUSHBUTTON, FG_PUSHBUTTON)
        movzx   ecx,rc.col
        mov     rdx,rdi
        rep     stosd
        mov     al,[rdi+2]
        and     eax,0xF0
        shl     eax,16
        mov     ax,U_LOWER_HALF_BLOCK
        mov     [rdi],eax
        movzx   ecx,[rsi].rc.col
        lea     rdi,[rdx+rcx*4+4]
        movzx   ecx,rc.col
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
        movzx   ecx,rc.col
        rep     stosd
    .case T_TEXTAREA            ;  [Selectable text]
    .case T_MOUSERECT           ;  Clickable area -- no focus
        mov     eax,_getattrib(BG_MENU, FG_MENU)
        mov     ecx,_getat(BG_MENU, FG_MENUKEY)
        mov     rdx,name
    .endsw

    .if ( rdx )

        .new _cx:int_t
        .new _ax:int_t
        .for ( rsi = rdx, edx = 0 : dl < rc.col : edx++ )

            lodsb
            .break .if !al
            .if ( al == '&' && type != T_EDIT )
                lodsb
                .break .if !al
                mov [rdi],ax
                mov [rdi+2],cx
                add rdi,4
                mov _cx,ecx
                mov _ax,eax
                movzx ecx,al
                tolower(ecx)
                mov ecx,_cx
                mov [rbx].syskey,al
                mov eax,_ax
            .else
                stosd
               .continue(0)
            .endif
        .endf
    .endif
    .return( rbx )

_dlinitA endp

    end
