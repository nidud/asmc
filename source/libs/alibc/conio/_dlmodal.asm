; _DLMODAL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include malloc.inc
include termios.inc

wm_mousemove proto hwnd:THWND, lParam:COORD

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

_dlgetid proc uses rbx hwnd:THWND, id:UINT

    mov     rbx,rdi
    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev
    xor     eax,eax

    .if ( [rbx].flags & O_CHILD )

        imul  eax,esi,TCLASS
        add   rax,[rbx].object
    .endif
    ret

_dlgetid endp


_dlgetfocus proc uses rbx hwnd:THWND

    mov     rbx,rdi
    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev
    xor     eax,eax

    .if ( [rbx].flags & O_CHILD )

        movzx   edx,word ptr [rbx].rc
        movzx   eax,[rbx].index
        imul    eax,eax,TCLASS
        add     rax,[rbx].object
        add     edx,[rax].TCLASS.rc
    .endif
    ret

_dlgetfocus endp


_sendmessage proc uses rbx r12 r13 r14 hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov rbx,rdi
    mov r12d,esi
    mov r13,rdx
    mov r14,rcx

    .if ( [rbx].flags & W_WNDPROC && [rbx].flags & W_CHILD )
        .return .ifd ( [rbx].winproc(rbx, r12d, r13, r14) == 0 )
    .endif
    .if _dlgetfocus(rbx)
        mov rbx,rax
        .if ( [rbx].flags & W_WNDPROC )
            .return .ifd ( [rbx].winproc(rbx, r12d, r13, r14) == 0 )
        .endif
        mov rbx,[rbx].prev
    .endif

    test [rbx].flags,O_CHILD
    cmovnz rbx,[rbx].object

    .for ( eax = 1 : rbx : )

        .if ( [rbx].flags & W_WNDPROC )
            .break .ifd ( [rbx].winproc(rbx, r12d, r13, r14) != 1 )
        .endif
        .if ( [rbx].flags & O_CHILD && [rbx].flags & W_CHILD )
            mov rbx,[rbx].object
        .elseif ( [rbx].flags & W_CHILD && [rbx].next )
            mov rbx,[rbx].next
        .else
            mov rbx,[rbx].prev
        .endif
    .endf
    ret

_sendmessage endp

    assume rdx:PMESSAGE

_postmessage proc uses rbx r12 r13 hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    mov ebx,esi
    mov r12,rdx
    mov r13,rcx

    .if malloc(MESSAGE)

        mov rdx,rax
        mov [rdx].Next,0
        mov [rdx].Message,ebx
        mov [rdx].wParam,r12
        mov [rdx].lParam,r13

        .for ( rax = rdx, rdx = _msg : rdx && [rdx].Next : rdx = [rdx].Next )
        .endf
        .if rdx
            mov [rdx].Next,rax
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
        .while ( rdx && rcx != [rdx].Next )
            mov rdx,[rdx].Next
        .endw
        .if ( rdx && rcx == [rdx].Next )
            mov [rdx].Next,rax
        .endif
    .endif
    free(rcx)
    ret

_dispatch endp

define ALT_PRESSED  0x20000000

    assume r12:PMESSAGE

_translate proc private uses rbx r12 r13 hwnd:THWND, msg:PMESSAGE

    mov r13,rdi
    mov r12,rsi
    mov ebx,[r12].Message
    mov [r12].Message,WM_NULL
    _sendmessage(r13, ebx, [r12].wParam, [r12].lParam)
    .return .if ( !eax || ebx != WM_KEYDOWN )

    mov rcx,[r12].lParam
    .if !( ecx & ( KF_EXTENDED shl 16 ) )

        mov   eax,WM_CHAR
        mov   edi,WM_SYSCHAR
        test  ecx,ALT_PRESSED
        cmovz edi,eax

        _sendmessage(r13, edi, [r12].wParam, rcx)
    .endif
    ret

_translate endp

    assume rdx:nothing
    assume rcx:THWND

_postquitmsg proc fastcall hwnd:THWND, retval:UINT

    test [rcx].flags,W_CHILD
    cmovnz rcx,[rcx].prev
    mov rdi,rcx
    _postmessage(rdi, WM_QUIT, edx, 0)
    .return(0)

_postquitmsg endp

    assume rcx:nothing

_dlsetfocus proc uses rbx hwnd:THWND, index:BYTE

    mov rbx,rdi
    .if _dlgetfocus(rbx)
        _sendmessage(rax, WM_KILLFOCUS, 0, 0)
    .endif

    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev
    mov     [rbx].index,index
    movzx   eax,al
    imul    edi,eax,TCLASS
    add     rdi,[rbx].object

    _sendmessage(rdi, WM_SETFOCUS, 0, 0)
    ret

_dlsetfocus endp

define MOUSE_BUTTON_UP      0x0010
define MOUSE_BUTTON_DOWN    0x0020
define MOUSE_WHEEL_UP       0x0040
define MOUSE_WHEEL_DOWN     0x0080


_dlmodal proc uses rbx r12 r13 hwnd:THWND, wndp:TPROC

   .new Input:INPUT_RECORD
   .new IdleCount:dword
   .new cNumRead:dword
   .new term:termios
   .new told:termios
   .new cursor_keys[8]:byte = {
        VK_UP,      ; A
        VK_DOWN,    ; B
        VK_RIGHT,   ; C
        VK_LEFT,    ; D
        0,
        VK_END,     ; F
        0,
        VK_HOME     ; H
        }
   .new modifiers[7]:byte = {
        SHIFT_PRESSED,
        LEFT_ALT_PRESSED,
        LEFT_ALT_PRESSED or SHIFT_PRESSED,
        LEFT_CTRL_PRESSED,
        LEFT_CTRL_PRESSED or SHIFT_PRESSED,
        LEFT_ALT_PRESSED or LEFT_CTRL_PRESSED,
        LEFT_ALT_PRESSED or LEFT_CTRL_PRESSED or SHIFT_PRESSED
        }

    mov rbx,rdi
    mov [rbx].winproc,rsi
    or  [rbx].flags,W_WNDPROC
    mov IdleCount,0

    [rbx].winproc(rbx, WM_CREATE, 0, 0)
    _dlsetfocus(rbx, [rbx].index)

    ; Switch to raw mode (no line input, no echo input)

    tcgetattr(_coninpfh, &term)
    memcpy(&told, &term, termios)

    and term.c_lflag,not (ICANON or _ECHO)
    mov term.c_cc[VMIN],1
    mov term.c_cc[VTIME],0

    tcsetattr(_coninpfh, TCSANOW, &term)

    _cout("\e[?1003h")

    .while 1

        .whiled ( _getch() != -1 )

            mov Input.EventType,KEY_EVENT
            mov Input.Event.KeyEvent.bKeyDown,1
            mov Input.Event.KeyEvent.wRepeatCount,1
            mov Input.Event.KeyEvent.wVirtualKeyCode,0
            mov Input.Event.KeyEvent.wVirtualScanCode,0
            mov Input.Event.KeyEvent.uChar.UnicodeChar,0
            mov Input.Event.KeyEvent.dwControlKeyState,0

            .if ( eax != VK_ESCAPE )

                mov Input.Event.KeyEvent.uChar.UnicodeChar,ax
               .break

            .elseif ( _kbhit() == 0 )

                mov Input.Event.KeyEvent.uChar.UnicodeChar,VK_ESCAPE
               .break
            .endif

            .switch _getch()

            .case 'O'
                 mov Input.Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
                .switch _getch()
                .case 'P'
                    mov Input.Event.KeyEvent.wVirtualKeyCode,VK_F1
                   .break
                .case 'Q'
                    mov Input.Event.KeyEvent.wVirtualKeyCode,VK_F2
                   .break
                .case 'R'
                    mov Input.Event.KeyEvent.wVirtualKeyCode,VK_F3
                   .break
                .case 'S'
                    mov Input.Event.KeyEvent.wVirtualKeyCode,VK_F4
                   .break
                .endsw
                .endc

            .case '['

                .switch _getch()

                .case 'A'
                .case 'B'
                .case 'C'
                .case 'D'
                .case 'F'
                .case 'H'
                    sub eax,'A'
                    mov al,cursor_keys[rax]
                    mov Input.Event.KeyEvent.wVirtualKeyCode,ax
                    mov Input.Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
                   .break

                .case 1

                    .endc .if ( _kbhit() == 0 )
                     mov Input.Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
                    .switch _getch()
                    .case '~'
                        .break
                    .case ';'
                        .switch _getch()
                        .case '~'
                            .break
                        .case 2
                        .case 3
                        .case 4
                        .case 5
                        .case 6
                        .case 7
                        .case 8
                            mov al,modifiers[rax-2]
                            mov Input.Event.KeyEvent.dwControlKeyState,eax
                            .switch _kbhit()
                            .case 'P'
                            .case 'Q'
                            .case 'R'
                            .case 'S'
                                .gotosw(4:'O')
                            .case '~'
                                .gotosw(2:';')
                            .endsw
                        .endsw
                        .endc
                    .case 1
                    .case 2
                    .case 3
                    .case 4
                    .case 5
                        lea eax,[rax-1+VK_F1]
                        mov Input.Event.KeyEvent.wVirtualKeyCode,ax
                       .gotosw(1:1)
                    .case 7
                    .case 8
                    .case 9
                        lea eax,[rax-7+VK_F6]
                        mov Input.Event.KeyEvent.wVirtualKeyCode,ax
                       .gotosw(1:1)
                    .endsw
                    .endc

                .case 2

                    .endc .if ( _kbhit() == 0 )
                     mov Input.Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
                    .switch _getch()
                    .case 0
                    .case 1
                    .case 3
                    .case 4
                        add eax,VK_F9
                        mov Input.Event.KeyEvent.wVirtualKeyCode,ax
                        _getch()
                       .break
                    .endsw
                    .endc

                .case 'M'

                    mov Input.EventType,MOUSE_EVENT
                    mov Input.Event.MouseEvent.dwMousePosition,0
                    mov Input.Event.MouseEvent.dwButtonState,0
                    mov Input.Event.MouseEvent.dwControlKeyState,0
                    mov Input.Event.MouseEvent.dwEventFlags,0

                    .switch _getch()
                    .case 32
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_BUTTON_DOWN
                        mov Input.Event.MouseEvent.dwButtonState,FROM_LEFT_1ST_BUTTON_PRESSED
                       .endc
                    .case 33
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_BUTTON_DOWN
                        mov Input.Event.MouseEvent.dwButtonState,FROM_LEFT_2ND_BUTTON_PRESSED
                       .endc
                    .case 34
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_BUTTON_DOWN
                        mov Input.Event.MouseEvent.dwButtonState,RIGHTMOST_BUTTON_PRESSED
                       .endc
                    .case 35
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_BUTTON_UP
                       .endc
                    .case 67
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_MOVED
                       .endc
                    .case 96
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_WHEELED
                       .endc
                    .case 97
                        mov Input.Event.MouseEvent.dwEventFlags,MOUSE_WHEELED
                        mov Input.Event.MouseEvent.dwButtonState,0x80000000
                       .endc
                    .endsw
                    _getch()
                    sub eax,33
                    mov Input.Event.MouseEvent.dwMousePosition.Y,ax
                    _getch()
                    sub eax,33
                    mov Input.Event.MouseEvent.dwMousePosition.X,ax
                   .break
                .endsw
                .endc
            .endsw
            _kbflush()
        .endw


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
            mov     eax,CTRLKEY_DOWN
            cmovz   eax,edi
            or      ecx,eax
            test    edx,SHIFT_PRESSED
            mov     eax,SHIFTKEY_DOWN
            cmovz   eax,edi
            or      ecx,eax
            test    edx,RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED
            mov     eax,ALTKEY_DOWN
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
            mov     esi,WM_KEYDOWN
            cmovz   esi,eax
            ;
            ; wParam
            ;
            ; The character code of the key
            ;
            movzx   edi,Input.Event.KeyEvent.wVirtualKeyCode
            movzx   edx,Input.Event.KeyEvent.uChar.UnicodeChar
            test    ecx,0x01000000
            cmovnz  edx,edi

            _postmessage(rbx, esi, rdx, rcx)

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
            xor     esi,esi
            mov     edx,ecx

            .switch pascal Input.Event.MouseEvent.dwEventFlags
            .case MOUSE_MOVED
                .if ( [rbx].context.state )
                    wm_mousemove(rbx, Input.Event.MouseEvent.dwMousePosition)
                   .continue
                .endif
                mov esi,WM_MOUSEMOVE
            .case MOUSE_HWHEELED
                mov esi,WM_MOUSEHWHEEL
            .case MOUSE_WHEELED
                mov esi,WM_MOUSEWHEEL
            .case DOUBLE_CLICK
                .if ( ecx & MK_LBUTTON )
                    mov esi,WM_LBUTTONDBLCLK
                .elseif ( ecx & MK_RBUTTON )
                    mov esi,WM_RBUTTONDBLCLK
                .else
                    mov esi,WM_XBUTTONDBLCLK
                .endif
            .case MOUSE_BUTTON_UP
                mov eax,_msbuttons
                mov _msbuttons,0
                .if ( eax & MK_RBUTTON )
                    mov esi,WM_RBUTTONUP
                .elseif ( eax & MK_MBUTTON )
                    mov esi,WM_MBUTTONUP
                .else ;( eax & MK_LBUTTON )
                    mov esi,WM_LBUTTONUP
                .endif
            .case MOUSE_BUTTON_DOWN
                mov _msbuttons,ecx
                .if ( ecx & MK_LBUTTON )
                    mov esi,WM_LBUTTONDOWN
                .elseif ( ecx & MK_RBUTTON )
                    mov esi,WM_RBUTTONDOWN
                .elseif ( ecx & MK_MBUTTON )
                    mov esi,WM_MBUTTONDOWN
                .endif
            .endsw
            .if ( esi )
                _postmessage(rbx, esi, rdx, Input.Event.MouseEvent.dwMousePosition)
            .endif
        .case WINDOW_BUFFER_SIZE_EVENT
            _postmessage(rbx, WM_SIZE, 0, 0)
        .case FOCUS_EVENT
            mov _focus,Input.Event.FocusEvent.bSetFocus
        .case MENU_EVENT
            _postmessage(rbx, Input.Event.MenuEvent.dwCommandId, 0, 0)
        .endsw

        mov r12,_msg
        .if ( r12 == NULL || _focus == 0 )

            inc IdleCount
            .if IdleCount >= 100

                mov IdleCount,0
                _sendmessage(rbx, WM_ENTERIDLE, 0, 0)
            .endif
            .continue .if _focus
        .endif
        mov IdleCount,0

        .while r12

            .break(1) .if ( [r12].MESSAGE.Message == WM_QUIT )

            _translate(rbx, r12)
            _dispatch(r12)
            mov r12,_msg
        .endw
    .endw

    ; Restore previous console mode.

    _cout("\e[?1003l")
    tcsetattr(_coninpfh, TCSANOW, &told)

    mov r13,[r12].MESSAGE.wParam
    _dispatch(r12)
    _sendmessage(rbx, WM_CLOSE, r13, 0)
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


_dlnextitem proc fastcall private uses rbx hwnd:THWND

    mov     rbx,rcx
    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev

    movzx   eax,[rbx].count
    movzx   ecx,[rbx].index
    lea     edx,[rcx+1]
    imul    edx,edx,TCLASS
    add     rdx,[rbx].object
    add     ecx,2

    .while ( ecx <= eax )

        .if ( !( [rdx].TCLASS.flags & O_DEACT ) && [rdx].TCLASS.type < T_MOUSERECT )

            dec ecx
            _dlsetfocus(rbx, cl)
            .return(0)
        .endif
        inc ecx
        add rdx,TCLASS
    .endw

    mov     rdx,[rbx].object
    movzx   eax,[rbx].index
    inc     eax
    mov     ecx,1

    .while ( ecx <= eax )

        .if ( !( [rdx].TCLASS.flags & O_DEACT ) && [rdx].TCLASS.type < T_MOUSERECT )

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
    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev

    movzx   eax,[rbx].count
    movzx   ecx,[rbx].index
    imul    edx,ecx,TCLASS
    add     rdx,[rbx].object

    .if ecx

        sub rdx,TCLASS
        .repeat

            .if ( !( [rdx].TCLASS.flags & O_DEACT ) && [rdx].TCLASS.type < T_MOUSERECT )

                dec ecx
                _dlsetfocus(rbx, cl)
                .return(0)
            .endif
            sub rdx,TCLASS
        .untilcxz
        xor ecx,ecx
    .endif

    add cl,[rbx].count
    .ifnz

        movzx   eax,[rbx].index
        lea     edx,[rcx-1]
        imul    edx,ecx,TCLASS
        add     rdx,[rbx].object

        .repeat

            .break .if eax > ecx
            .if ( !( [rdx].TCLASS.flags & O_DEACT ) && [rdx].TCLASS.type < T_MOUSERECT )

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
    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev

    .if ( [rbx].type == T_MENUITEM || ![rbx].count )

        .return( 1 )
    .endif

    movzx   ecx,[rbx].index
    inc     ecx
    imul    edx,ecx,TCLASS
    add     rdx,[rbx].object
    mov     eax,[rdx-TCLASS].TCLASS.rc

    .while ( cl < [rbx].count )

        .if ( ah == [rdx].TCLASS.rc.y && al < [rdx].TCLASS.rc.x )

            .if ( !( [rdx].TCLASS.flags & O_DEACT ) && [rdx].TCLASS.type < T_MOUSERECT )

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
    test    [rbx].flags,W_CHILD
    cmovnz  rbx,[rbx].prev

    .if ( [rbx].type == T_MENUITEM || ![rbx].count|| ![rbx].index )

        .return( 1 )
    .endif

    movzx   ecx,[rbx].index
    dec     ecx
    imul    edx,ecx,TCLASS
    add     rdx,[rbx].object
    mov     eax,[rdx+TCLASS].TCLASS.rc
    inc     ecx

    .repeat
        .if ( ah == [rdx].TCLASS.rc.y && al > [rdx].TCLASS.rc.x )

            .if ( !( [rdx].TCLASS.flags & O_DEACT ) && [rdx].TCLASS.type < T_MOUSERECT )

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


wm_lbbuttondown proc uses rsi rdi rbx hwnd:THWND, lParam:COORD

   .new rc:TRECT
    mov rbx,rdi
    .ifd ( _dlinside(rbx, esi) == 0 )

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
        mov eax,lParam
        mov [rbx].context.x,al
        sub al,[rbx].rc.x
        mov [rbx].context.rc.x,al
        shr eax,16
        mov [rbx].context.y,al
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
        mov al,ch
        mov dil,cl
        _scputc(dil, al, 1, ' ')
        mov dil,rc.x
        add dil,rc.col
        dec dil
        _scputc(dil, rc.y, 2, ' ')
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
    .case T_EDIT
        ;mov rax,[rsi]
        ;[rax].TEdit.OnLBDown(rcx)
        .endc
    .endsw
    .return( 0 )

wm_lbbuttondown endp


wm_lbuttonup proc fastcall uses rsi rdi rbx hwnd:THWND

   .new rc:TRECT
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
        mov eax,[rcx].TCLASS.rc
        mov ecx,[rbx].rc
        add cx,ax
        mov rc,ecx
        add cl,rc.col
        mov dil,cl
        _scputc(dil, rc.y, 1, U_LOWER_HALF_BLOCK)
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


wm_mousemove proc uses rsi rbx hwnd:THWND, lParam:COORD

    mov rbx,rdi
    mov eax,[rbx].flags
    and eax,W_ISOPEN or W_VISIBLE or W_MOVEABLE or W_CHILD

    .if ( [rbx].context.state == 0 || eax != W_ISOPEN or W_VISIBLE or W_MOVEABLE )

        .return( 1 )
    .endif

    mov eax,esi
    xor esi,esi
    .if ( al > [rbx].context.x )
        mov esi,_dlmove(rbx, TW_MOVERIGHT)
    .elseif ( CARRY? && [rbx].rc.x )
        mov esi,_dlmove(rbx, TW_MOVELEFT)
    .endif
    mov eax,lParam
    shr eax,16
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


wm_setfocus proc uses rbx hwnd:THWND

    .return .if !_dlgetfocus(rdi)
    .new rc:TRECT = edx
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
        mov cl,rc.x
        add cl,rc.col
        dec cl
        mov eax,' '
        .if ( [rbx].context.state == 0 )
            mov eax,U_BLACK_LEFT_POINTER
        .endif
        mov dil,cl
        _scputc(dil, rc.y, 1, ax)
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
    .case T_EDIT
        mov rax,[rbx].context.object
        ;[rax].TEdit.OnSetFocus(rcx)
        ;_gotoxy(eax, r8d)
       .endc
    .endsw
    .return(0)

wm_setfocus endp


wm_killfocus proc uses rbx hwnd:THWND

    .return .if !_dlgetfocus(rdi)
    .new rc:TRECT = edx
     mov rbx,rax
    _setcursor(&[rbx].cursor)
    mov al,[rbx].type
    .switch al
    .case T_PUSHBUTTON
        _scputc(rc.x, rc.y, 1, ' ')
        mov dil,rc.x
        add dil,rc.col
        dec dil
        _scputc(dil, rc.y, 1, ' ')
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
    .return(0)

wm_killfocus endp


wm_syschar proc uses rbx hwnd:THWND, wParam:UINT

    mov eax,esi
    .if ( ah || !eax )
        .return( 1 )
    .endif

    mov rbx,rdi
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
    .if !_dlgetfocus(rdi)

        .return( 1 )
    .endif

    mov rc,edx
    mov rbx,rax
    mov eax,esi

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
                    mov esi,eax
                    shr esi,8
                    _scputc(al, sil, 1, ' ')
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

    .if ( rdx & KEY_EXTENDED )

        mov rcx,rdi
        .switch esi
        .case VK_UP:    .return _dlprevitem(rcx)
        .case VK_DOWN:  .return _dlnextitem(rcx)
        .case VK_LEFT:  .return _dlitemleft(rcx)
        .case VK_RIGHT: .return _dlitemright(rcx)
        .endsw
    .endif
    .return( 1 )

wm_keydown endp


_defwinproc proc public hwnd:THWND, uiMsg:uint_t, wParam:WPARAM, lParam:LPARAM

    .switch pascal esi
    .case WM_ENTERIDLE
        ;Sleep(4)
       .return(0)
    .case WM_SETFOCUS
       .return wm_setfocus(rdi)
    .case WM_KILLFOCUS
       .return wm_killfocus(rdi)
    .case WM_LBUTTONDOWN
       .return wm_lbbuttondown(rdi, ecx)
    .case WM_LBUTTONUP
       .return wm_lbuttonup(rdi)
    .case WM_MOUSEMOVE
       .return wm_mousemove(rdi, ecx)
    .case WM_KEYDOWN
        mov eax,edx
       .return wm_keydown(rdi, eax, ecx)
    .case WM_SYSCHAR
       .return wm_syschar(rdi, edx)
    .case WM_CHAR
       .return wm_char(rdi, edx)
    .endsw
    .return( 1 )

_defwinproc endp

    end
