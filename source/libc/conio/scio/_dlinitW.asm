; _DLINITW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include stdio.inc
include malloc.inc
include ctype.inc

define U_UPPER_HALF_BLOCK   0x2580
define U_LOWER_HALF_BLOCK   0x2584
define U_MIDDLE_DOT         0x00B7

    .code

    assume rbx:THWND
    assume rsi:THWND

_dlinitW proc uses rsi rdi rbx hwnd:THWND, index:UINT, rc:TRECT, flags:UINT, type:BYTE, id:BYTE, name:LPWSTR

    mov     rbx,hwnd
    imul    esi,index,TCLASS
    add     rsi,[rbx].object

    mov     .rc,     rc
    mov     .index,  id
    mov     .ttype,  type
    mov     eax,     W_CHILD or W_WNDPROC
    or      eax,     flags
    or      .flags,  eax
    mov     .winproc,&_defwinproc
    mov     .window, _rcbprc([rbx].rc, rc, [rbx].window)

    mov     rdi,rax
    xchg    rsi,rbx
    xor     edx,edx

    .switch pascal type
    .case T_PUSHBUTTON ;  [ > Selectable text < ] + shade

        _getattrib(FG_TITLE, BG_PUSHBUTTON)

        movzx   ecx,rc.col
        mov     rdx,rdi
        rep     stosd
        mov     al,[rdi+2]
        and     eax,0xF0
        or      al,at_foreground[FG_PBSHADE]
        shl     eax,16
        mov     ax,U_LOWER_HALF_BLOCK
        mov     [rdi],eax
        movzx   ecx,[rsi].rc.col
        lea     rdi,[rdx+rcx*4+4]
        movzx   ecx,rc.col
        mov     ax,U_UPPER_HALF_BLOCK
        rep     stosd
        lea     rdi,[rdx+8]
        movzx   eax,at_background[BG_PUSHBUTTON]
        mov     cl,al
        or      al,at_foreground[FG_TITLE]
        or      cl,at_foreground[FG_TITLEKEY]
        shl     eax,16
        mov     rdx,name

    .case T_RADIOBUTTON ;  (*)
        _getattrib(FG_DIALOG, BG_DIALOG)
        mov     wchar_t ptr [rdi],'('
        mov     wchar_t ptr [rdi+8],')'
        add     rdi,4*4
        mov     cl,at_background[FG_DIALOG]
        or      cl,at_foreground[FG_DIALOGKEY]
        mov     rdx,name

    .case T_CHECKBOX            ;  [x]
        _getattrib(FG_DIALOG, BG_DIALOG)
        mov     wchar_t ptr [rdi],'['
        mov     wchar_t ptr [rdi+8],']'
        add     rdi,4*4
        mov     cl,at_background[FG_DIALOG]
        or      cl,at_foreground[FG_DIALOGKEY]
        mov     rdx,name
    .case T_XCELL               ;  [ Selectable text ]
    .case T_TEXTBUTTON          ;  [>Selectable text<]
    .case T_MENUITEM            ;  XCELL + Stausline info
        _getattrib(FG_DIALOG, BG_DIALOG)
        add     rdi,4
        mov     cl,at_background[FG_DIALOG]
        or      cl,at_foreground[FG_DIALOGKEY]
        mov     rdx,name
    .case T_EDIT                ;  [Text input]
        _getattrib(FG_TEXTEDIT, BG_TEXTEDIT)
        mov     ax,U_MIDDLE_DOT
        movzx   ecx,rc.col
        rep     stosd
    .case T_TEXTAREA            ;  [Selectable text]
    .case T_MOUSERECT           ;  Clickable area -- no focus
        _getattrib(FG_DIALOG, BG_DIALOG)
        mov     cl,at_background[FG_DIALOG]
        or      cl,at_foreground[FG_DIALOGKEY]
        mov     rdx,name
    .endsw

    .if ( rdx )

        .new _cx:int_t
        .new _ax:int_t
        .for ( rsi = rdx, edx = 0 : dl < rc.col : edx++ )

            lodsw
            .break .if !ax
            .if ( ax == '&' && type != T_EDIT )
                lodsw
                .break .if !ax
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

_dlinitW endp

    end
