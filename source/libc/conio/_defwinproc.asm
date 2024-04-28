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
    assume rbx:THWND

_dlinside proc fastcall hwnd:THWND, pos:COORD

  local rc:TRECT

    mov eax,[rcx].rc
    .if ( [rcx].flags & W_CHILD )

        mov rcx,[rcx].prev
        add ax,word ptr [rcx].rc
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

    movzx edx,[rbx].flags
    .if !( edx & W_CHILD )

        and edx,W_ISOPEN or W_VISIBLE or W_MOVEABLE
        .if ( eax != 1 || edx != W_ISOPEN or W_VISIBLE or W_MOVEABLE )
            .return TRUE
        .endif
        _cursoroff()
        mov [rbx].state,1
        mov [rbx].x,lParam.X
        sub al,[rbx].rc.x
        mov [rbx].rx,al
        mov [rbx].y,lParam.Y
        sub al,[rbx].rc.y
        mov [rbx].ry,al
        .if ( [rbx].flags & W_SHADE )
            _rcshade([rbx].rc, [rbx].window, 0)
        .endif

    .else

        and edx,O_TYPEMASK
        .switch edx
        .case O_PBUTT
            mov [rbx].state,1
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
        .case O_RBUTT
        .case O_CHBOX
        .case O_XCELL
            _dlsetfocus([rbx].prev, [rbx].oindex)
           .endc
        .case O_USERTYPE
            .if ( [rbx].state == 0 )

                mov [rbx].state,1
                movzx edx,[rbx].oindex
                _postmessage([rbx].prev, WM_COMMAND, rdx, rcx)
            .endif
            .endc
        .endsw
    .endif
    .return( 0 )

wm_lbbuttondown endp


wm_lbuttonup proc fastcall uses rbx hwnd:THWND

   .new rc:TRECT
   .new x:byte

    mov rbx,rcx

    movzx ecx,[rbx].flags
    .if !( ecx & W_CHILD )

        .if ( [rbx].state == 0 )
            .return( 1 )
        .endif
        mov [rbx].state,0
        .if ( [rbx].flags & W_SHADE )
            _rcshade([rbx].rc, [rbx].window, 1)
        .endif
        _dlsetfocus(rbx, [rbx].index)

    .else

        and ecx,O_TYPEMASK
        .switch ecx
        .case O_PBUTT
            .if ( [rbx].state == 0 )
                .return( 1 )
            .endif
            mov [rbx].state,0
            mov rcx,[rbx].prev
            mov ecx,[rcx].TDIALOG.rc
            mov eax,[rbx].rc
            add ax,cx
            mov rc,eax
            add al,rc.col
            mov x,al
            _scputc(x, rc.y, 1, U_LOWER_HALF_BLOCK)
            inc rc.y
            inc rc.x
            _scputc(rc.x, rc.y, rc.col, U_UPPER_HALF_BLOCK)
            movzx edx,[rbx].oindex
            .if ( [rbx].flags & O_DEXIT )
                movzx edx,[rbx].retval
                .return _postquitmsg(rbx, edx)
            .endif
            .return _postmessage([rbx].prev, WM_COMMAND, rdx, VK_RETURN)
        .case O_RBUTT
            .return 1 .if ( [rbx].state == 0 )
             mov [rbx].state,0
            .endc
        .case _O_MOUSE
           .return 1 .if ( [rbx].state == 0 )
            mov [rbx].state,0
           .endc
        .case O_CHBOX
        .case O_XCELL
        .case _O_LLMSU
        .case _O_LLMSD
            .return 1
        .endsw
    .endif
    .return( 0 )

wm_lbuttonup endp


wm_mousemove proc uses rbx hwnd:THWND, lParam:COORD

   .new moved:int_t

    ldr rbx,hwnd

    movzx eax,[rbx].flags
    and eax,W_ISOPEN or W_VISIBLE or W_MOVEABLE or W_CHILD

    .if ( [rbx].state == 0 || eax != W_ISOPEN or W_VISIBLE or W_MOVEABLE )

        .return( 1 )
    .endif

    .while 1

        mov moved,0
        mov ax,lParam.X
        .if ( al > [rbx].x )
            mov moved,_dlmove(rbx, TW_MOVERIGHT)
        .elseif ( CARRY? && [rbx].rc.x )
            mov moved,_dlmove(rbx, TW_MOVELEFT)
        .endif
        mov ax,lParam.Y
        .if ( al > [rbx].y )
            add moved,_dlmove(rbx, TW_MOVEDOWN)
        .elseif ( CARRY? && [rbx].rc.y )
            add moved,_dlmove(rbx, TW_MOVEUP)
        .endif
        .break .if ( moved == 0 )

        mov edx,[rbx].rc
        mov al,[rbx].ry
        add al,dh
        mov [rbx].y,al
        mov al,[rbx].rx
        add al,dl
        mov [rbx].x,al
    .endw
    .return( 0 )

wm_mousemove endp


wm_setfocus proc uses rbx hwnd:THWND

    .new rc:TRECT
    .new x:byte

    ldr rcx,hwnd
    .ifd !_dlgetfocus(rcx)
        .return
    .endif

    mov rc,edx
    mov rbx,rax
    _getcursor(&[rbx].cursor)

    movzx eax,[rbx].flags
    and eax,O_TYPEMASK
    .switch eax
    .case O_PBUTT
        _cursoroff()
        mov eax,' '
        .if ( [rbx].state == 0 )
            mov eax,U_BLACK_POINTER_RIGHT;U_BLACK_TRIANGLE_RIGHT
        .endif
        _scputc(rc.x, rc.y, 1, ax)
        mov al,rc.x
        add al,rc.col
        dec al
        mov ecx,' '
        .if ( [rbx].state == 0 )
            mov ecx,U_BLACK_POINTER_LEFT;U_BLACK_TRIANGLE_LEFT
        .endif
        mov x,al
        _scputc(x, rc.y, 1, cx)
       .endc
    .case O_RBUTT
    .case O_CHBOX
        inc rc.x
        .if ( al == _O_RBUTT )
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
    .case O_XCELL
        _cursoroff()
        _scgeta(rc.x, rc.y)
        shr al,4
        mov [rbx].attrib,al
        mov [rbx].state,1
        mov al,at_background[BG_INVERSE]
        shr al,4
        _scputbg(rc.x, rc.y, rc.col, al)

        .if ( [rbx].flags & O_LIST )

            movzx eax,[rbx].oindex
            mov rbx,[rbx].prev
            mov rdx,[rbx].llist
            sub eax,[rdx].TLIST.dlgoff
            mov [rdx].TLIST.celoff,eax
        .endif
       .endc
    .endsw
    .return( 0 )

wm_setfocus endp


wm_killfocus proc uses rbx hwnd:THWND

    .new rc:TRECT
    .new x:byte

    ldr rcx,hwnd
    .ifd !_dlgetfocus(rcx)
        .return
    .endif

    mov rc,edx
    mov rbx,rax

    _setcursor(&[rbx].cursor)

    movzx eax,[rbx].flags
    and eax,O_TYPEMASK
    .switch eax
    .case O_PBUTT
        _scputc(rc.x, rc.y, 1, ' ')
        mov al,rc.x
        add al,rc.col
        dec al
        mov x,al
        _scputc(x, rc.y, 1, ' ')
       .endc
    .case O_RBUTT
    .case O_CHBOX
        inc rc.x
        .if ( al == _O_RBUTT )
            and [rbx].flags,not O_RADIO
        .else
            and [rbx].flags,not O_CHECK
        .endif
        _scputc(rc.x, rc.y, 1, ' ')
       .endc
    .case O_XCELL
       .return 1 .if ( [rbx].state == 0 )
        mov [rbx].state,0
        _scputbg(rc.x, rc.y, rc.col, [rbx].attrib)
       .endc
    .endsw
    .return( 0 )

wm_killfocus endp

    assume rcx:THWND

wm_syschar proc hwnd:THWND, wParam:UINT

    ldr eax,wParam
    .if ( ah || !eax )
        .return( 1 )
    .endif

    ldr rcx,hwnd
    .if ( eax == 'x' )
        .return _postquitmsg(rcx, 0)
    .endif

    test [rcx].flags,W_CHILD
    cmovnz rcx,[rcx].prev
    .for ( rcx = [rcx].object : rcx : rcx = [rcx].next )

        .if ( al == [rcx].syskey )

            .return( _dlsetfocus(rcx, [rcx].oindex) )
        .endif
    .endf
    .return( 1 )

wm_syschar endp


wm_char proc uses rbx hwnd:THWND, wParam:UINT

    .new rc:TRECT
    .new x:byte
    .new y:byte

    ldr rcx,hwnd
    ldr ebx,wParam

    .if !_dlgetfocus(rcx)

        .return( 1 )
    .endif

    mov  rc,edx
    xchg rbx,rax

    .if ( eax == VK_RETURN )

        movzx edx,[rbx].retval
        .if ( [rbx].flags & O_DEXIT )
            .return _postquitmsg(rbx, edx)
        .endif
        mov dl,[rbx].oindex
        .return _postmessage([rbx].prev, WM_COMMAND, rdx, rax)

    .elseif ( eax == VK_TAB )

        .ifd _sendmessage([rbx].prev, WM_KEYDOWN, VK_DOWN, ENHANCED_KEY)

            mov rcx,[rbx].prev
            .for ( rcx = [rcx].object : rcx != rbx : rcx = [rcx].next )

                .if ( !( [rcx].flags & O_STATE or O_NOFOCUS ) )

                    .return( _dlsetfocus( rcx, [rcx].oindex ) )
                .endif
            .endf
        .endif
        .return

    .elseif ( eax == VK_ESCAPE )
        .return _postquitmsg(rbx, 0)
    .endif

    movzx edx,[rcx].flags
    and edx,O_TYPEMASK

    .switch edx
    .case O_RBUTT
        .if ( eax == VK_SPACE )

            .for ( rcx = [rcx].object : rcx : rcx = [rcx].next )

                .if ( [rcx].flags & O_RADIO )

                    and     [rcx].flags,not O_RADIO
                    mov     rax,[rcx].prev
                    movzx   eax,word ptr [rax].TDIALOG.rc
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

    .case O_CHBOX
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


wm_keydown proc uses rbx hwnd:THWND, wParam:UINT, lParam:UINT

    ldr eax,lParam

    .if ( eax & ENHANCED_KEY )

        ldr rcx,hwnd
        ldr ebx,wParam

        .if ( _dlgetfocus(rcx) )

            xchg rax,rbx
            mov  rcx,[rbx].prev

            .switch eax
            .case VK_UP
                .for ( eax = 0, rcx = [rcx].object : rcx != rbx : rcx = [rcx].next )

                    .if ( !( [rcx].flags & O_STATE or O_NOFOCUS ) )

                        mov rax,rcx
                    .endif
                .endf
                .if ( rax )

                    mov rcx,rax
                   .return( _dlsetfocus( rcx, [rcx].oindex ) )
                .endif
                .endc
            .case VK_DOWN
                .for ( edx = 0, rcx = [rbx].next : rcx : edx++, rcx = [rcx].next )

                    .if ( !( [rcx].flags & O_STATE or O_NOFOCUS ) )

                        .return( _dlsetfocus( rcx, [rcx].oindex ) )
                    .endif
                .endf
                .endc
            .case VK_LEFT
                 movzx eax,[rbx].flags
                 and eax,O_TYPEMASK
                .endc .if ( eax == O_MENUS )

                .for ( edx = [rbx].rc, eax = 0, rcx = [rcx].object : rcx != rbx : rcx = [rcx].next )

                    .if ( !( [rcx].flags & O_STATE or O_NOFOCUS ) && dh == [rcx].rc.y && dl > [rcx].rc.x )

                        mov rax,rcx
                    .endif
                .endf
                .if ( rax )

                    mov rcx,rax
                   .return( _dlsetfocus( rcx, [rcx].oindex ) )
                .endif
                .endc
            .case VK_RIGHT
                .for ( rcx = [rbx].next, eax = [rbx].rc : rcx : rcx = [rcx].next )

                    .if ( !( [rcx].flags & O_STATE or O_NOFOCUS ) && ah == [rcx].rc.y && al < [rcx].rc.x )

                        .return( _dlsetfocus( rcx, [rcx].oindex ) )
                    .endif
                .endf
                .endc
            .case VK_RETURN
                .return( wm_char(rbx, eax) )
            .endsw
        .endif
    .endif
    .return( 1 )

wm_keydown endp


_defwinproc proc public hwnd:THWND, uiMsg:uint_t, wParam:WPARAM, lParam:LPARAM

    ldr rax,wParam
    ldr rdx,lParam
    ldr rcx,hwnd

    .switch pascal uiMsg
    .case WM_ENTERIDLE:     .return( _tidle() )
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
