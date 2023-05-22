; _DEFWINPROC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include malloc.inc

    .code

    option proc:private

    assume rcx:THWND

_setfocus proc fastcall hwnd:THWND

    .for ( rdx = rcx,
           rdx = [rdx].TCLASS.prev,
           rdx = [rdx].TCLASS.object,
           eax = 0 : rdx != rcx : eax++, rdx = [rdx].TCLASS.next )
    .endf
    _dlsetfocus(rcx, al)
    .return( 0 )

_setfocus endp


_dlnextitem proc fastcall hwnd:THWND

    .if ( _dlgetfocus(rcx) == NULL )
        .return( 1 )
    .endif
    .for ( rcx = [rax].TCLASS.next : rcx : rcx = [rcx].next )
        .if ( !( [rcx].flags & O_DEACT ) && [rcx].type < T_MOUSERECT )
            .return( _setfocus(rcx) )
        .endif
    .endf
     mov rcx,[rax].TCLASS.prev
    .for ( rcx = [rcx].object : rcx : rcx = [rcx].next )
        .if ( !( [rcx].flags & O_DEACT ) && [rcx].type < T_MOUSERECT )
            .return( _setfocus(rcx) )
        .endif
    .endf
    .return( 1 )

_dlnextitem endp


    assume rbx:THWND

_dlprevitem proc fastcall uses rbx hwnd:THWND

    test    [rcx].flags,W_CHILD
    cmovnz  rcx,[rcx].prev
    mov     rbx,rcx
    movzx   ecx,[rbx].index

    .while ( ecx )
        dec ecx
        .if ( _dlgetid(rbx, ecx) )

            .if ( !( [rax].TCLASS.flags & O_DEACT ) && [rax].TCLASS.type < T_MOUSERECT )

                _dlsetfocus(rbx, cl)
                .return( 0 )
            .endif
        .endif
    .endw
    mov cl,[rbx].index
    inc ecx
    .while ( cl < [rbx].count )
        .if ( _dlgetid(rbx, ecx) )

            .if ( !( [rax].TCLASS.flags & O_DEACT ) && [rax].TCLASS.type < T_MOUSERECT )

                _dlsetfocus(rbx, cl)
                .return( 0 )
            .endif
        .endif
        inc ecx
    .endw
    .return( 1 )

_dlprevitem endp


_dlitemright proc fastcall hwnd:THWND

    .if ( _dlgetfocus(rcx) == NULL )
        .return( 1 )
    .endif
    mov rcx,[rax].TCLASS.next
    mov eax,[rax].TCLASS.rc
    .for ( : rcx : rcx = [rcx].next )
        .if ( !( [rcx].flags & O_DEACT ) && [rcx].type < T_MOUSERECT )
            .if ( ah == [rcx].rc.y && al < [rcx].rc.x )
                .return( _setfocus(rcx) )
            .endif
        .endif
    .endf
    .return( 1 )

_dlitemright endp


_dlitemleft proc uses rbx hwnd:THWND

    .if ( _dlgetfocus(hwnd) == NULL )
        .return( 1 )
    .endif
    mov rcx,[rax].TCLASS.prev
    .if ( [rax].TCLASS.type == T_MENUITEM || ![rcx].count || ![rcx].index )

        .return( 1 )
    .endif
    movzx ecx,[rcx].index
    mov ebx,[rax].TCLASS.rc
    .while ( ecx )
        dec ecx
        .if ( _dlgetid(hwnd, ecx) )

            .if ( !( [rax].TCLASS.flags & O_DEACT ) && [rax].TCLASS.type < T_MOUSERECT )

                .if ( bh == [rax].TCLASS.rc.y && bl > [rax].TCLASS.rc.x )
                    _dlsetfocus(hwnd, cl)
                    .return( 0 )
                .endif
            .endif
        .endif
    .endw
    .return( 1 )

_dlitemleft endp


_dlinside proc fastcall hwnd:THWND, pos:COORD

  local rc:TRECT

    mov eax,[rcx].TCLASS.rc
    .if ( [rcx].TCLASS.flags & W_CHILD )

        mov rcx,[rcx].TCLASS.prev
        add ax,word ptr [rcx].TCLASS.rc
    .endif

    mov rc,eax
    mov ecx,eax
    xor eax,eax
    mov dh,cl

    .if ( dl >= dh )

        add dh,rc.col
        .if ( dl < dh )

            shr edx,16
            mov dh,ch
            .if ( dl >= dh )

                add dh,rc.row
                .if ( dl < dh )

                    mov al,dl
                    sub al,ch
                    inc al
                .endif
            .endif
        .endif
    .endif
    ret

_dlinside endp


wm_lbbuttondown proc uses rbx hwnd:THWND, lParam:COORD

   .new rc:TRECT
   .new x:byte

    mov rbx,hwnd
    .ifd ( _dlinside(rbx, lParam) == 0 )

        .if !( [rbx].flags & W_CHILD )

            _postquitmsg(rbx, 0)
        .endif
        .return TRUE
    .endif

    .if ( [rbx].type == T_WINDOW )

        mov ecx,[rbx].flags
        and ecx,W_ISOPEN or W_VISIBLE or W_MOVEABLE
        .if ( eax != 1 || ecx != W_ISOPEN or W_VISIBLE or W_MOVEABLE )
            .return TRUE
        .endif
        _cursoroff()
        mov [rbx].context.state,1
        mov [rbx].context.x,lParam.X
        sub al,[rbx].rc.x
        mov [rbx].context.rc.x,al
        mov [rbx].context.y,lParam.Y
        sub al,[rbx].rc.y
        mov [rbx].context.rc.y,al
        .if ( [rbx].flags & W_SHADE )
            _rcshade([rbx].rc, [rbx].window, 0)
        .endif
        .return( 0 )
    .endif

    .switch [rbx].type
    .case T_PUSHBUTTON
        mov [rbx].context.state,1
        mov rc,ecx
        _scputc(rc.x, rc.y, 1, ' ')
        mov al,rc.x
        add al,rc.col
        dec al
        mov x,al
        _scputc(x, rc.y, 2, ' ')
        inc rc.x
        inc rc.y
        _scputc(rc.x, rc.y, rc.col, ' ')
    .case T_RADIOBUTTON
    .case T_CHECKBOX
    .case T_XCELL
        mov rcx,rbx
        mov rbx,[rbx].prev
        mov rbx,[rbx].object
        xor edx,edx
        .for ( edx = 0 : rcx != rbx : edx++, rbx = [rbx].next )
        .endf
        _dlsetfocus([rbx].prev, dl)
       .endc
    .case T_MOUSERECT
        .if ( [rbx].context.state == 0 )

            mov [rbx].context.state,1
            movzx edx,[rbx].index
            _postmessage([rbx].prev, WM_COMMAND, rdx, rcx)
        .endif
        .endc
    .endsw
    .return( 0 )

wm_lbbuttondown endp


wm_lbuttonup proc fastcall uses rbx hwnd:THWND

   .new rc:TRECT
   .new x:byte

    mov rbx,rcx
    .switch [rbx].type
    .case T_WINDOW
        .if ( [rbx].context.state == 0 )
            .return( 1 )
        .endif
        mov [rbx].context.state,0
        .if ( [rbx].flags & W_SHADE )
            _rcshade([rbx].rc, [rbx].window, 1)
        .endif
        _dlsetfocus(rbx, [rbx].index)
        .endc
    .case T_PUSHBUTTON
        .if ( [rbx].context.state == 0 )
            .return( 1 )
        .endif
        mov [rbx].context.state,0
        mov rcx,[rbx].prev
        mov ecx,[rcx].TCLASS.rc
        mov eax,[rbx].rc
        add ax,cx
        mov rc,eax
        add al,rc.col
        mov x,al
        _scputc(x, rc.y, 1, U_LOWER_HALF_BLOCK)
        inc rc.y
        inc rc.x
        _scputc(rc.x, rc.y, rc.col, U_UPPER_HALF_BLOCK)
        movzx edx,[rbx].index
        .if ( [rbx].flags & O_DEXIT )
            .return _postquitmsg(rbx, edx)
        .endif
        .return _postmessage([rbx].prev, WM_COMMAND, rdx, 0)
    .case T_RADIOBUTTON
        .return 1 .if ( [rbx].context.state == 0 )
         mov [rbx].context.state,0
        .endc
    .case T_MOUSERECT
       .return 1 .if ( [rbx].context.state == 0 )
        mov [rbx].context.state,0
       .endc
    .case T_CHECKBOX
    .case T_XCELL
        ;[rcx].SetFocus( [rcx].Index )
        ;.endc
        .return 1
    .endsw
    .return( 0 )

wm_lbuttonup endp


wm_mousemove proc uses rbx hwnd:THWND, lParam:COORD

   .new moved:int_t = 0

    mov rbx,hwnd
    mov eax,[rbx].flags
    and eax,W_ISOPEN or W_VISIBLE or W_MOVEABLE or W_CHILD

    .if ( [rbx].context.state == 0 || eax != W_ISOPEN or W_VISIBLE or W_MOVEABLE )

        .return( 1 )
    .endif

    mov ax,lParam.X
    .if ( al > [rbx].context.x )
        mov moved,_dlmove(rbx, TW_MOVERIGHT)
    .elseif ( CARRY? && [rbx].rc.x )
        mov moved,_dlmove(rbx, TW_MOVELEFT)
    .endif
    mov ax,lParam.Y
    .if ( al > [rbx].context.y )
        add moved,_dlmove(rbx, TW_MOVEDOWN)
    .elseif ( CARRY? && [rbx].rc.y )
        add moved,_dlmove(rbx, TW_MOVEUP)
    .endif
    .if ( moved )
        mov edx,[rbx].rc
        mov al,[rbx].context.rc.y
        add al,dh
        mov [rbx].context.y,al
        mov al,[rbx].context.rc.x
        add al,dl
        mov [rbx].context.x,al
    .endif
    .return( 0 )

wm_mousemove endp


wm_setfocus proc uses rbx hwnd:THWND

    .new rc:TRECT
    .new x:byte
    .return .if !_dlgetfocus(hwnd)

    mov rc,edx
    mov rbx,rax
    _getcursor(&[rbx].cursor)

    mov al,[rbx].type
    .switch al
    .case T_PUSHBUTTON
        _cursoroff()
        mov eax,' '
        .if ( [rbx].context.state == 0 )
            mov eax,U_BLACK_RIGHT_POINTER
        .endif
        _scputc(rc.x, rc.y, 1, ax)
        mov al,rc.x
        add al,rc.col
        dec al
        mov ecx,' '
        .if ( [rbx].context.state == 0 )
            mov ecx,U_BLACK_LEFT_POINTER
        .endif
        mov x,al
        _scputc(x, rc.y, 1, cx)
       .endc
    .case T_RADIOBUTTON
    .case T_CHECKBOX
        inc rc.x
        .if ( al == T_RADIOBUTTON )
            mov eax,U_BULLET_OPERATOR
            or [rbx].flags,O_RADIO
        .else
            mov eax,'x'
            or [rbx].flags,O_CHECK
        .endif
        _scputc(rc.x, rc.y, 1, ax)
        _cursoron()
        _gotoxy(rc.x, rc.y)
       .endc
    .case T_XCELL
        mov [rbx].context.state,1
        _cursoroff()
        _scgeta(rc.x, rc.y)
        mov [rbx].context.flags,al
        _scputbg(rc.x, rc.y, rc.col, BG_INVERSE)
       .endc
    .endsw
    .return( 0 )

wm_setfocus endp


wm_killfocus proc uses rbx hwnd:THWND

    .new rc:TRECT
    .new x:byte
    .return .if !_dlgetfocus(hwnd)

    mov rc,edx
    mov rbx,rax

    _setcursor(&[rbx].cursor)

    mov al,[rbx].type
    .switch al
    .case T_PUSHBUTTON
        _scputc(rc.x, rc.y, 1, ' ')
        mov al,rc.x
        add al,rc.col
        dec al
        mov x,al
        _scputc(x, rc.y, 1, ' ')
       .endc
    .case T_RADIOBUTTON
    .case T_CHECKBOX
        inc rc.x
        .if ( al == T_RADIOBUTTON )
            and [rbx].flags,not O_RADIO
        .else
            and [rbx].flags,not O_CHECK
        .endif
        _scputc(rc.x, rc.y, 1, ' ')
       .endc
    .case T_XCELL
       .return 1 .if ( [rbx].context.state == 0 )
        mov [rbx].context.state,0
        movzx eax,[rbx].context.flags
        shr eax,4
        _scputbg(rc.x, rc.y, rc.col, al)
       .endc
    .endsw
    .return( 0 )

wm_killfocus endp


wm_syschar proc uses rbx hwnd:THWND, wParam:UINT

    mov eax,wParam
    .if ( ah || !eax )
        .return( 1 )
    .endif

    mov rbx,hwnd
    .if ( eax == 'x' )
        .return _postquitmsg(rbx, 0)
    .endif

    test [rbx].flags,W_CHILD
    cmovnz rbx,[rbx].prev
    .for ( ecx = 0, rbx = [rbx].object : rbx : ecx++, rbx = [rbx].next )

        .if ( al == [rbx].syskey )

            _dlsetfocus(rbx, cl)
            .return( 0 )
        .endif
    .endf
    .return( 1 )

wm_syschar endp

    assume rcx:THWND

wm_char proc uses rbx hwnd:THWND, wParam:UINT

    .new rc:TRECT
    .new x:byte
    .new y:byte
    .if !_dlgetfocus(hwnd)

        .return( 1 )
    .endif

    mov rc,edx
    mov rbx,rax
    mov eax,wParam

    .if ( eax == VK_RETURN )

        movzx edx,[rbx].index
        .if ( [rbx].flags & O_DEXIT )
            .return _postquitmsg(rbx, edx)
        .endif
        .return _postmessage([rbx].prev, WM_COMMAND, rdx, 0)
    .elseif ( eax == VK_TAB )
        .return _dlnextitem(rbx)
    .elseif ( eax == VK_ESCAPE )
        .return _postquitmsg(rbx, 0)
    .endif

    .switch [rbx].type
    .case T_RADIOBUTTON
        .if ( eax == VK_SPACE )

            .for ( rcx = [rcx].object : rcx : rcx = [rcx].next )

                .if ( [rcx].flags & O_RADIO )

                    and     [rcx].flags,not O_RADIO
                    mov     rax,[rcx].prev
                    movzx   eax,word ptr [rax].TCLASS.rc
                    add     eax,[rcx].rc
                    inc     al
                    mov     y,ah
                    mov     x,al

                    _scputc(x, y, 1, ' ')
                    .break
                .endif
            .endf
            inc rc.x
            or [rbx].flags,O_RADIO
            _scputc(rc.x, rc.y, 1, U_BULLET_OPERATOR)
            .return( 0 )
        .endif
        .endc

    .case T_CHECKBOX
        .if ( eax == VK_SPACE )

            xor [rbx].flags,O_CHECK
            mov eax,' '
            .if ( [rbx].flags & O_CHECK )
                mov eax,'x'
            .endif
            inc rc.x
            _scputc(rc.x, rc.y, 1, ax)
            .return( 0 )
        .endif
        .endc
    .endsw
    .return( 1 )

wm_char endp


wm_keydown proc hwnd:THWND, wParam:UINT, lParam:UINT

    .if ( lParam & KEY_EXTENDED )

        mov rcx,hwnd
        .switch wParam
        .case VK_UP:    .return _dlprevitem(rcx)
        .case VK_DOWN:  .return _dlnextitem(rcx)
        .case VK_LEFT:  .return _dlitemleft(rcx)
        .case VK_RIGHT: .return _dlitemright(rcx)
        .endsw
    .endif
    .return( 1 )

wm_keydown endp


_defwinproc proc public hwnd:THWND, uiMsg:uint_t, wParam:WPARAM, lParam:LPARAM

    mov rcx,hwnd
    mov rax,wParam
    mov rdx,lParam

    .switch pascal uiMsg
    .case WM_ENTERIDLE
ifdef __UNIX__
else
        Sleep( 4 )
endif
       .return( 0 )
    .case WM_SETFOCUS:      .return wm_setfocus(rcx)
    .case WM_KILLFOCUS:     .return wm_killfocus(rcx)
    .case WM_LBUTTONDOWN:   .return wm_lbbuttondown(rcx, edx)
    .case WM_LBUTTONUP:     .return wm_lbuttonup(rcx)
    .case WM_MOUSEMOVE:     .return wm_mousemove(rcx, edx)
    .case WM_KEYDOWN:       .return wm_keydown(rcx, eax, edx)
    .case WM_SYSCHAR:       .return wm_syschar(rcx, eax)
    .case WM_CHAR:          .return wm_char(rcx, eax)
    .endsw
    .return( 1 )

_defwinproc endp

    end
