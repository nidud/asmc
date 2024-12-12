; _TGETEVENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

; wParam
;
; 0x0008 MK_CONTROL     The CTRL key is down
; 0x0001 MK_LBUTTON     The left mouse button is down
; 0x0010 MK_MBUTTON     The middle mouse button is down
; 0x0002 MK_RBUTTON     The right mouse button is down
; 0x0004 MK_SHIFT       The SHIFT key is down
; 0x0020 MK_XBUTTON1    The first X button is down
; 0x0040 MK_XBUTTON2    The second X button is down

.data
 msg        MESSAGE <>
 mouse_x    dd 0
 mouse_y    dd 0
 mouse_b    dd 0

.code

mousex proc
    mov eax,mouse_x
    ret
mousex endp

mousey proc
    mov eax,mouse_y
    ret
mousey endp


readevent proc private
ifdef __TTY__
    _write(_confd, SET_ANY_EVENT_MOUSE, 8)
else
   .new oldstate:uint_t
    GetConsoleMode(_coninpfh, &oldstate)
    SetConsoleMode(_coninpfh, ENABLE_WINDOW_INPUT or ENABLE_MOUSE_INPUT)
endif
    .ifsd ( _getmessage(&msg, NULL, 0) > 0 )

        _dispatchmsg(&msg)
    .else
        _tupdate()
        _tidle()
        mov msg.message,0
    .endif

ifdef __TTY__
    _write(_confd, RST_ANY_EVENT_MOUSE, 8)
else
    SetConsoleMode(_coninpfh, oldstate)
endif
    mov eax,msg.message
    .switch eax
    .case WM_MOUSEMOVE
    .case WM_MOUSEHWHEEL
    .case WM_MOUSEWHEEL
    .case WM_LBUTTONDBLCLK
    .case WM_RBUTTONDBLCLK
    .case WM_XBUTTONDBLCLK
    .case WM_LBUTTONDOWN
    .case WM_MBUTTONDOWN
    .case WM_RBUTTONDOWN
    .case WM_LBUTTONUP
    .case WM_MBUTTONUP
    .case WM_RBUTTONUP
        movzx   eax,word ptr msg.lParam
        mov     mouse_x,eax
        movzx   eax,word ptr msg.lParam[2]
        mov     mouse_y,eax
        mov     eax,dword ptr msg.wParam
        mov     mouse_b,eax
       .endc
    .endsw
    xor eax,eax
    ret

readevent endp


mousep proc

    readevent()
    mov eax,mouse_b
    and eax,MK_LBUTTON or MK_RBUTTON
    ret

mousep endp


mousewait proc uses rbx x:int_t, y:int_t, l:int_t

    ldr ebx,x
    add ebx,l

    .whiled mousep()

        .break .if mouse_y != y
        .break .if mouse_x < x
        .break .if mouse_x > ebx
    .endw
    ret

mousewait endp


msloop proc

    .repeat
    .untild !mousep()
    ret

msloop endp


getkey proc

    readevent()

    movzx ecx,word ptr msg.wParam
    mov edx,msg.message

    .switch edx
    .case WM_KEYDOWN
        mov  edx,dword ptr msg.lParam

        .endc .if ( edx & KEY_WMCHAR )
        .endc .if ( cx == VK_SHIFT )
        .endc .if ( cx == VK_CONTROL )

        shl     ecx,8
        mov     eax,ecx
        or      ecx,KEY_ALT
        test    edx,RIGHT_ALT_PRESSED or LEFT_ALT_PRESSED
        cmovnz  eax,ecx
        mov     ecx,eax
        or      ecx,KEY_CTRL
        test    edx,RIGHT_CTRL_PRESSED or LEFT_CTRL_PRESSED
        cmovnz  eax,ecx
        mov     ecx,eax
        or      ecx,KEY_SHIFT
        test    edx,SHIFT_PRESSED
        cmovnz  eax,ecx
       .endc
    .case WM_SYSCHAR
        or      ecx,KEY_ALT
    .case WM_CHAR
        mov     eax,ecx
       .endc
    .endsw
    ret

getkey endp


getevent proc

    .whiled !getkey()

        .if ( msg.message == WM_MOUSEWHEEL )

            mov ecx,dword ptr msg.wParam
            mov eax,KEY_MOUSEUP
            .ifs ecx <= 0
                mov eax,KEY_MOUSEDN
            .endif
            .break
        .endif

        .if ( mouse_b & MK_LBUTTON or MK_RBUTTON )

            _postmessage(0, msg.message, msg.wParam, msg.lParam)
            mov eax,MOUSECMD
           .break
        .endif
    .endw
    ret

getevent endp

    END
