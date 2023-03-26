; _DLMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include malloc.inc

wm_mousemove proto hwnd:THWND, lParam:COORD

set macro reg,arg
    assume reg:ptr @SubStr(typeid(arg), 4)
    mov reg,arg
    exitm<>
    endm

.template MESSAGE
    Next        ptr MESSAGE ?
    Message     UINT ?
    wParam      WPARAM ?
    lParam      LPARAM ?
   .ends
    PMESSAGE    typedef ptr MESSAGE

    .data
     _msg       PMESSAGE 0
     _msbuttons UINT 0
     _focus     UINT 1

    .code

    assume rbx:THWND

_sendmessage proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov    rbx,hwnd
    test   .flags,O_CHILD
    cmovnz rbx,.object

    .for ( eax = 1 : rbx : )

        .if ( .flags & W_WNDPROC )
            .break .ifd ( .winproc(rbx, uiMsg, wParam, lParam) != 1 )
        .endif
        .if ( .flags & O_CHILD && .flags & W_CHILD )
            mov rbx,.object
        .elseif ( .flags & W_CHILD && .next )
            mov rbx,.next
        .else
            mov rbx,.prev
        .endif
    .endf
    ret

_sendmessage endp

    assume rdx:PMESSAGE

_postmessage proc hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if malloc(MESSAGE)

        mov rdx,rax

        mov .Next,    0
        mov .Message, uiMsg
        mov .wParam,  wParam
        mov .lParam,  lParam

        .for ( rax = rdx, rdx = _msg : rdx && .Next : rdx = .Next )
        .endf
        .if rdx
            mov .Next,rax
        .else
            mov _msg,rax
        .endif
    .endif
    ret

_postmessage endp


_dispatch proc fastcall private msg:PMESSAGE

    mov rax,[rcx].MESSAGE.Next
    mov rdx,_msg

    .if ( rdx == rcx )
        mov _msg,rax
    .elseif rdx
        .while ( rdx && rcx != .Next )
            mov rdx,.Next
        .endw
        .if ( rdx && rcx == .Next )
            mov .Next,rax
        .endif
    .endif
    free(rcx)
    ret

_dispatch endp

define ALT_PRESSED  0x20000000

_translate proc private uses rdi hwnd:THWND, msg:PMESSAGE

    mov rdx,msg
    mov edi,[rdx].Message
    mov [rdx].Message,WM_NULL
    _sendmessage(hwnd, edi, [rdx].wParam, [rdx].lParam)
    .return .if ( !eax || edi != WM_KEYDOWN )

    mov rdx,msg
    mov rcx,[rdx].lParam
    .if !( ecx & ( KF_EXTENDED shl 16 ) )

        mov   eax,WM_CHAR
        mov   edi,WM_SYSCHAR
        test  ecx,ALT_PRESSED
        cmovz edi,eax

        _sendmessage(hwnd, edi, [rdx].wParam, rcx)
    .endif
    ret

_translate endp

    assume rdx:nothing
    assume rcx:THWND

_postquitmsg proc fastcall hwnd:THWND, retval:UINT

    test   .flags,W_CHILD
    cmovnz rcx,.prev

    _postmessage(rcx, WM_QUIT, edx, 0)
    .return(0)

_postquitmsg endp

    assume rcx:nothing

_dlsetfocus proc uses rbx hwnd:THWND, index:BYTE

    mov rbx,hwnd
    _sendmessage(rbx, WM_KILLFOCUS, 0, 0)

    test    .flags,W_CHILD
    cmovnz  rbx,.prev
    mov     .index,index
    movzx   eax,al
    imul    ecx,eax,TCLASS
    add     rcx,.object

    _sendmessage(rcx, WM_SETFOCUS, 0, 0)
    ret

_dlsetfocus endp


_dlmodal proc uses rsi rdi rbx hwnd:THWND, wndp:TPROC

  local Input:INPUT_RECORD
  local IdleCount:dword
  local cNumRead:dword

    mov rbx,hwnd

    mov .winproc,wndp
    or  .flags,W_WNDPROC
    mov IdleCount,0

    .winproc(rbx, WM_CREATE, 0, 0)

    .while 1

        .if !ReadConsoleInput(_coninpfh, &Input, 1, &cNumRead)

            .return( -1 )
        .endif

        .if ( cNumRead )

            .switch pascal Input.EventType

            .case KEY_EVENT

                ;
                ; lParam
                ;
                ;  0-15 repeat count
                ; 16-23 scan code
                ;    24 extended key - Ctrl or right Alt
                ; 25-28 reserved
                ;    29 1 if the ALT key is held down while the key is pressed
                ;    30 previous key state
                ;    31 transition state - 1 if the key is being released
                ;

                xor     edi,edi
                mov     edx,Input.Event.KeyEvent.dwControlKeyState
                test    edx,ENHANCED_KEY
                mov     ecx,KEY_EXTENDED
                cmovz   ecx,edi
                test    edx,LEFT_CTRL_PRESSED or RIGHT_CTRL_PRESSED
                mov     eax,KEY_CONTROL
                cmovz   eax,edi
                or      ecx,eax
                test    edx,SHIFT_PRESSED
                mov     eax,KEY_SHIFT
                cmovz   eax,edi
                or      ecx,eax
                test    edx,RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED
                mov     eax,KEY_ALTDOWN
                cmovz   eax,edi
                or      ecx,eax
                movzx   eax,Input.Event.KeyEvent.wVirtualScanCode
                shl     eax,16
                mov     ax,Input.Event.KeyEvent.wVirtualKeyCode
                or      ecx,eax
                mov     eax,KF_UP shl 16
                cmp     edi,Input.Event.KeyEvent.bKeyDown
                cmovz   eax,edi
                or      ecx,eax
                cmp     edi,Input.Event.KeyEvent.bKeyDown
                mov     eax,WM_KEYUP
                mov     edx,WM_KEYDOWN
                cmovz   edx,eax
                ;
                ; wParam
                ;
                ; The character code of the key
                ;
                movzx   edi,Input.Event.KeyEvent.wVirtualKeyCode
                movzx   eax,Input.Event.KeyEvent.uChar.UnicodeChar
                test    ecx,0x01000000
                cmovnz  eax,edi

                _postmessage(rbx, edx, rax, rcx)

            .case MOUSE_EVENT

                ;
                ; lParam
                ;
                ; low-order word specifies the x-coordinate of the cursor
                ; high-order word specifies the y-coordinate of the cursor
                ;
                ; wParam
                ;
                ; 0x0008 MK_CONTROL     The CTRL key is down
                ; 0x0001 MK_LBUTTON     The left mouse button is down
                ; 0x0010 MK_MBUTTON     The middle mouse button is down
                ; 0x0002 MK_RBUTTON     The right mouse button is down
                ; 0x0004 MK_SHIFT       The SHIFT key is down
                ; 0x0020 MK_XBUTTON1    The first X button is dow
                ; 0x0040 MK_XBUTTON2    The second X button is down
                ;
                xor     ecx,ecx
                mov     edx,Input.Event.MouseEvent.dwControlKeyState
                test    edx,SHIFT_PRESSED
                mov     eax,MK_SHIFT
                cmovz   eax,ecx
                test    edx,RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED
                mov     edx,MK_CONTROL
                cmovnz  ecx,edx
                or      ecx,eax
                xor     edx,edx
                mov     eax,MK_LBUTTON
                mov     edi,Input.Event.MouseEvent.dwButtonState
                test    edi,FROM_LEFT_1ST_BUTTON_PRESSED
                cmovz   eax,edx
                or      ecx,eax
                mov     eax,MK_MBUTTON
                test    edi,FROM_LEFT_2ND_BUTTON_PRESSED
                cmovz   eax,edx
                or      ecx,eax
                mov     eax,MK_RBUTTON
                test    edi,RIGHTMOST_BUTTON_PRESSED
                cmovz   eax,edx
                or      ecx,eax
                xor     edx,edx

                .switch pascal Input.Event.MouseEvent.dwEventFlags
                .case MOUSE_MOVED
                    .if ( [rbx].context.state )
                        wm_mousemove(rbx, Input.Event.MouseEvent.dwMousePosition)
                       .continue
                    .endif
                    mov edx,WM_MOUSEMOVE
                .case MOUSE_HWHEELED
                    mov edx,WM_MOUSEHWHEEL
                .case MOUSE_WHEELED
                    mov edx,WM_MOUSEWHEEL
                .case DOUBLE_CLICK
                    .if ( ecx & MK_LBUTTON )
                        mov edx,WM_LBUTTONDBLCLK
                    .elseif ( ecx & MK_RBUTTON )
                        mov edx,WM_RBUTTONDBLCLK
                    .else
                        mov edx,WM_XBUTTONDBLCLK
                    .endif
                .default
                    mov eax,_msbuttons
                    mov _msbuttons,edi
                    .if ( eax != edi )
                        .if ( ( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) && !( edi & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov edx,WM_LBUTTONUP
                        .elseif ( !( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) && ( edi & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                            mov edx,WM_LBUTTONDOWN
                        .elseif ( ( eax & FROM_LEFT_2ND_BUTTON_PRESSED ) && !( edi & FROM_LEFT_2ND_BUTTON_PRESSED ) )
                            mov edx,WM_MBUTTONUP
                        .elseif ( !( eax & FROM_LEFT_2ND_BUTTON_PRESSED ) && ( edi & FROM_LEFT_2ND_BUTTON_PRESSED ) )
                            mov edx,WM_MBUTTONDOWN
                        .elseif ( ( eax & RIGHTMOST_BUTTON_PRESSED ) && !( edi & RIGHTMOST_BUTTON_PRESSED ) )
                            mov edx,WM_RBUTTONUP
                        .elseif ( !( eax & RIGHTMOST_BUTTON_PRESSED ) && ( edi & RIGHTMOST_BUTTON_PRESSED ) )
                            mov edx,WM_RBUTTONDOWN
                        .endif
                    .elseif ( ecx & MK_LBUTTON )
                        mov edx,WM_LBUTTONDOWN
                    .elseif ( ecx & MK_RBUTTON )
                        mov edx,WM_RBUTTONDOWN
                    .elseif ( ecx & MK_MBUTTON )
                        mov edx,WM_MBUTTONDOWN
                    .endif
                .endsw
                .if ( edx )
                    _postmessage(hwnd, edx, rcx, Input.Event.MouseEvent.dwMousePosition)
                .endif
            .case WINDOW_BUFFER_SIZE_EVENT
                _postmessage(hwnd, WM_SIZE, 0, 0)
            .case FOCUS_EVENT
                mov _focus,Input.Event.FocusEvent.bSetFocus
            .case MENU_EVENT
                _postmessage(hwnd, Input.Event.MenuEvent.dwCommandId, 0, 0)
            .endsw
        .endif

        mov rdi,_msg
        .if ( rdi == NULL || _focus == 0 )

            inc IdleCount
            .if IdleCount >= 100

                mov IdleCount,0
                _sendmessage(hwnd, WM_ENTERIDLE, 0, 0)
            .endif
            .continue .if _focus
        .endif
        mov IdleCount,0

        .while rdi

            .break(1) .if ( [rdi].MESSAGE.Message == WM_QUIT )

            _translate(hwnd, rdi)
            _dispatch(rdi)
            mov rdi,_msg
        .endw
    .endw

    mov rbx,[rdi].MESSAGE.wParam
    _dispatch(rdi)
    _sendmessage(hwnd, WM_CLOSE, rbx, 0)
   .return(rbx)

_dlmodal endp


    option proc:private

GetItemRect proto fastcall :THWND {
    mov     rax,[_1].TCLASS.prev
    movzx   eax,word ptr [rax].TCLASS.rc
    add     eax,[_1].TCLASS.rc
    retm    <eax>
    }

ContextRect proto fastcall :THWND {
    mov     [_1].TCLASS.context.rc,GetItemRect(_1)
    }


    assume rcx:THWND

_getfocus proc fastcall private hwnd:THWND

    xor     eax,eax
    test    .flags,W_CHILD
    cmovnz  rcx,.prev
    test    .flags,O_CHILD
    jz      O
    movzx   edx,word ptr [rcx].rc
    movzx   eax,.index
    imul    eax,eax,TCLASS
    add     rax,.object
    add     edx,[rax].TCLASS.rc
O:
    ret

_getfocus endp

    assume rcx:nothing


_dlnextitem proc fastcall private uses rbx hwnd:THWND

    mov     rbx,rcx
    test    .flags,W_CHILD
    cmovnz  rbx,.prev

    movzx   eax,.count
    movzx   ecx,.index
    lea     edx,[rcx+1]
    imul    edx,edx,TCLASS
    add     rdx,.object
    add     ecx,2

    .while ( ecx <= eax )

        .if !( [rdx].TCLASS.flags & O_DEACT )

            dec ecx
            _dlsetfocus(rbx, cl)
            .return(0)
        .endif
        inc ecx
        add rdx,TCLASS
    .endw

    mov     rdx,.object
    movzx   eax,.index
    inc     eax
    mov     ecx,1

    .while ( ecx <= eax )

        .if !( [rdx].TCLASS.flags & O_DEACT )

            dec ecx
            _dlsetfocus(rbx, cl)
            .return(0)
        .endif
        inc ecx
        add rdx,TCLASS
    .endw
    .return(1)

_dlnextitem endp


_dlprevitem proc fastcall private uses rbx hwnd:THWND

    mov     rbx,rcx
    test    .flags,W_CHILD
    cmovnz  rbx,.prev

    movzx   eax,.count
    movzx   ecx,.index
    imul    edx,ecx,TCLASS
    add     rdx,.object

    .if ecx

        sub rdx,TCLASS
        .repeat

            .if !( [rdx].TCLASS.flags & O_DEACT )

                dec ecx
                _dlsetfocus(rbx, cl)
                .return(0)
            .endif
            sub rdx,TCLASS
        .untilcxz
        xor ecx,ecx
    .endif

    add cl,.count
    .ifnz

        movzx   eax,.index
        lea     edx,[rcx-1]
        imul    edx,ecx,TCLASS
        add     rdx,.object

        .repeat

            .break .if eax > ecx
            .if !( [rdx].TCLASS.flags & O_DEACT )

                dec ecx
                _dlsetfocus(rbx, cl)
                .return(0)
            .endif
            sub rdx,TCLASS
        .untilcxz
    .endif
    .return(1)

_dlprevitem endp


_dlitemright proc fastcall private uses rbx hwnd:THWND

    mov     rbx,rcx
    test    .flags,W_CHILD
    cmovnz  rbx,.prev

    .if ( .ttype == T_MENUITEM || !.count )

        .return( 1 )
    .endif

    movzx   ecx,.index
    inc     ecx
    imul    edx,ecx,TCLASS
    add     rdx,.object
    mov     eax,[rdx-TCLASS].TCLASS.rc

    .while ( cl < .count )

        .if ( ah == [rdx].TCLASS.rc.y && al < [rdx].TCLASS.rc.x )

            .if !( [rdx].TCLASS.flags & O_DEACT )

                _dlsetfocus(rbx, cl)
                .return(0)
            .endif
        .endif
        inc ecx
        add rdx,TCLASS
    .endw
    .return(1)

_dlitemright endp


_dlitemleft proc fastcall uses rbx hwnd:THWND

    mov     rbx,rcx
    test    .flags,W_CHILD
    cmovnz  rbx,.prev

    .if ( .ttype == T_MENUITEM || !.count|| !.index )

        .return( 1 )
    .endif

    movzx   ecx,.index
    dec     ecx
    imul    edx,ecx,TCLASS
    add     rdx,.object
    mov     eax,[rdx+TCLASS].TCLASS.rc
    inc     ecx

    .repeat
        .if ( ah == [rdx].TCLASS.rc.y && al > [rdx].TCLASS.rc.x )

            .if !( [rdx].TCLASS.flags & O_DEACT )

                dec ecx
                _dlsetfocus(rbx, cl)
                .return(0)
            .endif
        .endif
        sub rdx,TCLASS
    .untilcxz
    .return( 1 )

_dlitemleft endp


_dlinside proc fastcall hwnd:THWND, pos:COORD

  local rc:TRECT

    mov eax,.rc
    .if ( .flags & W_CHILD )

        mov rcx,.prev
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


wm_lbbuttondown proc uses rsi rdi rbx hwnd:THWND, lParam:COORD

   .new rc:TRECT
    mov rbx,hwnd
    .ifd ( _dlinside(rbx, lParam) == 0 )

        .if !( [rbx].flags & W_CHILD )

            _postquitmsg(rbx, 0)
        .endif
        .return TRUE
    .endif

    .if ( [rbx].ttype == T_WINDOW )

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

    .switch [rbx].ttype
    .case T_PUSHBUTTON
        mov [rbx].context.state,1
        mov rc,ecx
        _scputc(cl, ch, 1, ' ')
        mov cl,rc.x
        add cl,rc.col
        dec cl
        _scputc(cl, rc.y, 2, ' ')
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
    .case T_EDIT
        ;mov rax,[rsi]
        ;[rax].TEdit.OnLBDown(rcx)
        .endc
    .endsw
    .return( 0 )

wm_lbbuttondown endp


define U_UPPER_HALF_BLOCK 0x2580
define U_LOWER_HALF_BLOCK 0x2584

wm_lbuttonup proc fastcall uses rsi rdi rbx hwnd:THWND

   .new rc:TRECT
    mov rbx,rcx

    .switch [rbx].ttype
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
        mov eax,[rcx].TCLASS.rc
        mov ecx,[rbx].rc
        add cx,ax
        mov rc,ecx
        add cl,rc.col
        _scputc(cl, rc.y, 1, U_LOWER_HALF_BLOCK)
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
    .case T_CHECKBOX
    .case T_XCELL
        ;[rcx].SetFocus( [rcx].Index )
        ;.endc
        .return 1
    .endsw
    .return( 0 )

wm_lbuttonup endp


wm_mousemove proc uses rsi rbx hwnd:THWND, lParam:COORD

    mov rbx,hwnd
    mov eax,[rbx].flags
    and eax,W_ISOPEN or W_VISIBLE or W_MOVEABLE or W_CHILD

    .if ( [rbx].context.state == 0 || eax != W_ISOPEN or W_VISIBLE or W_MOVEABLE )

        .return( 1 )
    .endif

    xor esi,esi
    mov ax,lParam.X
    .if ( al > [rbx].context.x )
        mov esi,_dlmove(rbx, TW_MOVERIGHT)
    .elseif ( CARRY? && [rbx].rc.x )
        mov esi,_dlmove(rbx, TW_MOVELEFT)
    .endif
    mov ax,lParam.Y
    .if ( al > [rbx].context.y )
        add esi,_dlmove(rbx, TW_MOVEDOWN)
    .elseif ( CARRY? && [rbx].rc.y )
        add esi,_dlmove(rbx, TW_MOVEUP)
    .endif
    .if ( esi )
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


define U_BLACK_RIGHT_POINTER 0x25BA
define U_BLACK_LEFT_POINTER  0x25C4
define U_BULLET_OPERATOR     0x2219

wm_setfocus proc uses rbx hwnd:THWND

    .return .if !_getfocus(hwnd)
    .new rc:TRECT = edx
     mov rbx,rax
    _getcursor(&[rbx].cursor)
    mov al,[rbx].ttype
    .switch al
    .case T_PUSHBUTTON
        _cursoroff()
        mov eax,' '
        .if ( [rbx].context.state == 0 )
            mov eax,U_BLACK_RIGHT_POINTER
        .endif
        _scputc(rc.x, rc.y, 1, ax)
        mov cl,rc.x
        add cl,rc.col
        dec cl
        mov eax,' '
        .if ( [rbx].context.state == 0 )
            mov eax,U_BLACK_LEFT_POINTER
        .endif
        _scputc(cl, rc.y, 1, ax)
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
        _cursoroff()
        _scgeta(rc.x, rc.y)
        mov [rbx].context.flags,al
        and eax,0xF0
        or  al,at_background[BG_INVERSE]
        _scputbg(rc.x, rc.y, rc.col, al)
        .endc
    .case T_EDIT
        mov rax,[rbx].context.object
        ;[rax].TEdit.OnSetFocus(rcx)
        ;_gotoxy(eax, r8d)
       .endc
    .endsw
    .return(0)

wm_setfocus endp


wm_killfocus proc uses rbx hwnd:THWND

    .return .if !_getfocus(hwnd)
    .new rc:TRECT = edx
     mov rbx,rax
    _setcursor(&[rbx].cursor)
    mov al,[rbx].ttype
    .switch al
    .case T_PUSHBUTTON
        _scputc(rc.x, rc.y, 1, ' ')
        mov cl,rc.x
        add cl,rc.col
        dec cl
        _scputc(cl, rc.y, 1, ' ')
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
        movzx eax,[rbx].context.flags
        shr eax,4
        _scputbg(rc.x, rc.y, rc.col, al)
       .endc
    .endsw
    .return(0)

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
    .if !_getfocus(hwnd)

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

    .switch [rbx].ttype
    .case T_EDIT
        mov rax,[rbx].context.object
       .return 0;[rax].TEdit.OnChar(rcx, r8)

    .case T_RADIOBUTTON
        .if ( eax == VK_SPACE )

            .for ( rcx = [rcx].object : rcx : rcx = [rcx].next )

                .if ( [rcx].flags & O_RADIO )

                    and [rcx].flags,not O_RADIO
                    GetItemRect(rcx)
                    inc al
                    mov dl,ah
                    _scputc(al, dl, 1, ' ')
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
        .case VK_UP
            .return _dlprevitem(rcx)
        .case VK_DOWN
            .return _dlnextitem(rcx)
        .case VK_LEFT
            .return _dlitemleft(rcx)
        .case VK_RIGHT
            .return _dlitemright(rcx)
        .endsw
    .endif
    .return( 1 )

wm_keydown endp


    option proc:public

_defwinproc proc hwnd:THWND, uiMsg:uint_t, wParam:WPARAM, lParam:LPARAM

    mov rcx,hwnd
    mov rdx,wParam
    mov rax,lParam

    .switch pascal uiMsg
    .case WM_ENTERIDLE
        Sleep(4)
       .return(0)
    .case WM_SETFOCUS
        .return wm_setfocus(rcx)
    .case WM_KILLFOCUS
        .return wm_killfocus(rcx)
    .case WM_LBUTTONDOWN
        .return wm_lbbuttondown(rcx, eax)
    .case WM_LBUTTONUP
        .return wm_lbuttonup(rcx)
    .case WM_MOUSEMOVE
        .return wm_mousemove(rcx, eax)
    .case WM_KEYDOWN
        .return wm_keydown(rcx, edx, eax)
    .case WM_SYSCHAR
        .return wm_syschar(rcx, edx)
    .case WM_CHAR
        .return wm_char(rcx, edx)
    .endsw
    .return( 1 )

_defwinproc endp

    end
