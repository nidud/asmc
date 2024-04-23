; _GETMESSAGE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

define MOUSE_BUTTON_UP      0x0010
define MOUSE_BUTTON_DOWN    0x0020
define MOUSE_WHEEL_UP       0x0040
define MOUSE_WHEEL_DOWN     0x0080

    .data
     msbuttons UINT 0

    .code

    assume rdx:PMESSAGE
    assume rbx:PMESSAGE

_getmessage proc uses rsi rdi rbx msg:PMESSAGE, hwnd:THWND, Idle:int_t

    .new Input:INPUT_RECORD

    .while 1

        mov rbx,hwnd
        mov rcx,_console
        mov rdx,[rcx].TCONSOLE.msgptr

        .if ( [rdx].message && !rbx )

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

        .elseif ( [rdx].message && ebx == -1 )

            .for ( rcx = [rdx].prev, rbx = 0 : rdx != rcx : rdx = [rdx].next )

                .if ( rbx == [rdx].hwnd )

                    jmp returnmsg
                .endif
            .endf

        .elseif ( [rdx].message )

            .for ( rcx = [rdx].prev : rdx != rcx : rdx = [rdx].next )

                .if ( rbx == [rdx].hwnd )

                    jmp returnmsg
                .endif
            .endf
        .endif

        .while 1

            .ifd ( _readinput(&Input) == -1 )

                .return
            .endif
            .break .if ( eax )

            .if ( eax == Idle )

                .return
            .endif
            _tidle()
        .endw

        .switch pascal Input.EventType

        .case KEY_EVENT
            ;
            ; lParam
            ;
            ;  0-15 Control Key State
            ;  16   Key Char
            ;
            movzx   ecx,word ptr Input.Event.KeyEvent.dwControlKeyState
            cmp     Input.Event.KeyEvent.bKeyDown,0
            mov     eax,WM_KEYUP
            mov     esi,WM_KEYDOWN
            cmovz   esi,eax
            ;
            ; wParam
            ;
            ; The Char or Virtual Key Code of the key
            ;
            movzx   edi,Input.Event.KeyEvent.wVirtualKeyCode
            mov     eax,ecx
            or      ecx,KEY_WMCHAR
            movzx   edx,TCHAR ptr Input.Event.KeyEvent.uChar.UnicodeChar
            test    ecx,ENHANCED_KEY or RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED
            cmovnz  edx,edi
            cmovnz  ecx,eax
            test    edx,edx
            cmovz   edx,edi
            cmovz   ecx,eax

            _postmessage(rbx, esi, rdx, rcx)

            movzx   edx,TCHAR ptr Input.Event.KeyEvent.uChar.UnicodeChar
            mov     ecx,Input.Event.KeyEvent.dwControlKeyState

            .endc .if ( Input.Event.KeyEvent.bKeyDown == 0 )
            .endc .if ( edx == 0 )
            .endc .if ( ecx & ENHANCED_KEY )

            or      ecx,KEY_WMCHAR
            mov     eax,WM_CHAR
            mov     esi,WM_SYSCHAR
            test    ecx,RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED
            cmovz   esi,eax

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
            mov     eax,edi
            and     eax,0xFFFFFF00
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
                mov eax,msbuttons
                mov msbuttons,0
                .if ( eax & MK_RBUTTON )
                    mov esi,WM_RBUTTONUP
                .elseif ( eax & MK_MBUTTON )
                    mov esi,WM_MBUTTONUP
                .else ;( eax & MK_LBUTTON )
                    mov esi,WM_LBUTTONUP
                .endif
            .case MOUSE_BUTTON_DOWN
                mov msbuttons,ecx
                .if ( ecx & MK_LBUTTON )
                    mov esi,WM_LBUTTONDOWN
                .elseif ( ecx & MK_RBUTTON )
                    mov esi,WM_RBUTTONDOWN
                .elseif ( ecx & MK_MBUTTON )
                    mov esi,WM_MBUTTONDOWN
                .endif
else
            .default
                mov eax,msbuttons
                mov msbuttons,edi
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
            mov rcx,_console
            mov eax,Input.Event.FocusEvent.bSetFocus
            mov [rcx].TCONSOLE.focus,eax
        .case MENU_EVENT
            _postmessage(rbx, Input.Event.MenuEvent.dwCommandId, 0, 0)
        .endsw
    .endw
    ret

_getmessage endp

    end
