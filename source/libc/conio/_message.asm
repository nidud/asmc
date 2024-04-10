; _MESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

define MOUSE_BUTTON_UP      0x0010
define MOUSE_BUTTON_DOWN    0x0020
define MOUSE_WHEEL_UP       0x0040
define MOUSE_WHEEL_DOWN     0x0080

    .data
     _msgptr    PMESSAGE 0
     _msbuttons UINT 0
     _focus     UINT 1

    .code

    assume rdx:PMESSAGE
    assume rbx:PMESSAGE

_dispatchmsg proc uses rbx msg:PMESSAGE

    ldr rbx,msg
    mov rbx,[rbx].next
    mov rdx,_msgptr

    .if ( rdx == rbx )
        mov _msgptr,[rbx].next
    .elseif ( rdx )
        .while ( rdx && rbx != [rdx].next )
            mov rdx,[rdx].next
        .endw
        .if ( rdx && rbx == [rdx].next )
            mov [rdx].next,[rbx].next
        .endif
    .endif
    free(rbx)
    ret

_dispatchmsg endp


_postmessage proc hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    .if malloc(MESSAGE)

        mov rdx,rax
        mov [rdx].next,    NULL
        mov [rdx].hwnd,    hwnd
        mov [rdx].message, uiMsg
        mov [rdx].wParam,  wParam
        mov [rdx].lParam,  lParam

        .for ( rax = rdx,
               rdx = _msgptr : rdx && [rdx].next : rdx = [rdx].next )
        .endf
        .if rdx
            mov [rdx].next,rax
        .else
            mov _msgptr,rax
        .endif
        xor eax,eax
    .endif
    ret

_postmessage endp


_postquitmsg proc hwnd:THWND, retval:UINT

    ldr rcx,hwnd
    ldr edx,retval

    test [rcx].TCLASS.flags,W_CHILD
    cmovnz rax,[rcx].TCLASS.prev
    _postmessage(rax, WM_QUIT, edx, 0)
    .return( 0 )

_postquitmsg endp


_getmessage proc uses rsi rdi rbx msg:PMESSAGE, hwnd:THWND

    .new Input:INPUT_RECORD
    .new IdleCount:dword

    .while 1

        mov rbx,hwnd
        mov rdx,_msgptr

        .if ( rdx && !rbx )

            returnmsg:

            mov rbx,msg
            mov [rbx].next,rdx
            mov [rbx].hwnd,[rdx].hwnd
            mov [rbx].wParam,[rdx].wParam
            mov [rbx].lParam,[rdx].lParam
            mov [rbx].message,[rdx].message
            mov [rdx].message,WM_NULL

            .if ( eax == WM_QUIT )

                _dispatchmsg(rbx)
                .return( 0 )
            .endif
            .return( 1 )

        .elseif ( rdx && rbx == -1 )

            .for ( rbx = 0 : rdx : rdx = [rdx].next )

                .if ( rbx == [rdx].hwnd )

                    jmp returnmsg
                .endif
            .endf

        .elseif ( rdx )

            .for ( : rdx : rdx = [rdx].next )

                .if ( rbx == [rdx].hwnd )

                    jmp returnmsg
                .endif
            .endf
        .endif

         mov IdleCount,0

        .if ( _readinput(&Input) == 0 )

            .return( -1 )
        .endif

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
            mov     eax,Input.Event.MouseEvent.dwEventFlags

            .switch pascal eax
            .case MOUSE_MOVED
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
ifdef __TTY__
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
else
            .default
                mov eax,_msbuttons
                mov _msbuttons,edi
                .if ( eax != edi )
                    .if ( ( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) && !( edi & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                        mov esi,WM_LBUTTONUP
                    .elseif ( !( eax & FROM_LEFT_1ST_BUTTON_PRESSED ) && ( edi & FROM_LEFT_1ST_BUTTON_PRESSED ) )
                        mov esi,WM_LBUTTONDOWN
                    .elseif ( ( eax & FROM_LEFT_2ND_BUTTON_PRESSED ) && !( edi & FROM_LEFT_2ND_BUTTON_PRESSED ) )
                        mov esi,WM_MBUTTONUP
                    .elseif ( !( eax & FROM_LEFT_2ND_BUTTON_PRESSED ) && ( edi & FROM_LEFT_2ND_BUTTON_PRESSED ) )
                        mov esi,WM_MBUTTONDOWN
                    .elseif ( ( eax & RIGHTMOST_BUTTON_PRESSED ) && !( edi & RIGHTMOST_BUTTON_PRESSED ) )
                        mov esi,WM_RBUTTONUP
                    .elseif ( !( eax & RIGHTMOST_BUTTON_PRESSED ) && ( edi & RIGHTMOST_BUTTON_PRESSED ) )
                        mov esi,WM_RBUTTONDOWN
                    .endif
                .elseif ( ecx & MK_LBUTTON )
                    mov esi,WM_LBUTTONDOWN
                .elseif ( ecx & MK_RBUTTON )
                    mov esi,WM_RBUTTONDOWN
                .elseif ( ecx & MK_MBUTTON )
                    mov esi,WM_MBUTTONDOWN
                .endif
endif
            .endsw
            .if ( esi )
                mov rdi,rcx
                _postmessage(rbx, esi, rdi, Input.Event.MouseEvent.dwMousePosition)
            .endif
        .case WINDOW_BUFFER_SIZE_EVENT
            _postmessage(rbx, WM_SIZE, 0, 0)
        .case FOCUS_EVENT
            mov _focus,Input.Event.FocusEvent.bSetFocus
        .case MENU_EVENT
            _postmessage(rbx, Input.Event.MenuEvent.dwCommandId, 0, 0)
        .endsw

        mov rbx,_msgptr
        .if ( rbx == NULL || _focus == 0 )

            inc IdleCount
            .if IdleCount >= 100

                mov IdleCount,0
                _postmessage(rbx, WM_ENTERIDLE, 0, 0)
            .endif
        .endif
    .endw
    ret

_getmessage endp


    assume rdx:nothing

_translatemsg proc uses rbx msg:PMESSAGE

    ldr rbx,msg

    mov eax,[rbx].message
    .if ( eax == WM_NULL )

        .return
    .endif

    mov rcx,[rbx].hwnd
    .if ( rcx == NULL )

        mov rcx,_console
        .for ( : rcx && [rcx].TCLASS.next : rcx = [rcx].TCLASS.next )
        .endf
        mov [rbx].hwnd,rcx
    .endif

    _sendmessage([rbx].hwnd, [rbx].message, [rbx].wParam, [rbx].lParam)

    .return .if ( !eax )
    .return .if ( [rbx].message != WM_KEYDOWN )

    mov rcx,[rbx].lParam
    .if !( ecx & KEY_EXTENDED )

        mov   edx,WM_CHAR
        mov   eax,WM_SYSCHAR
        test  ecx,ALTKEY_DOWN
        cmovz eax,edx

        _sendmessage([rbx].hwnd, eax, [rbx].wParam, rcx)
    .endif
    ret

_translatemsg endp


    assume rbx:THWND

_sendmessage proc uses rbx hwnd:THWND, uiMsg:UINT, wParam:WPARAM, lParam:LPARAM

    ldr rbx,hwnd
    .if ( [rbx].flags & W_WNDPROC && [rbx].flags & W_CHILD )

        .return( [rbx].winproc(rbx, uiMsg, wParam, lParam) )
    .endif
    .if ( [rbx].flags & O_CHILD )

        .if _dlgetfocus(rbx)

            mov rbx,rax
            .if ( [rbx].flags & W_WNDPROC )
                .return .ifd ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
            .endif
            mov rbx,hwnd
        .endif
        .for ( rbx = [rbx].object : rbx : )
            .if ( [rbx].flags & W_WNDPROC )
                .return .ifd ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
            .endif
            mov rbx,[rbx].next
        .endf
        mov rbx,hwnd
    .endif
    .for ( eax = 1 : rbx : )

        .if ( [rbx].flags & W_WNDPROC )
            .break .ifd ( [rbx].winproc(rbx, uiMsg, wParam, lParam) == 0 )
        .endif
        mov rbx,[rbx].prev
    .endf
    ret

_sendmessage endp

    end
