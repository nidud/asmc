; _TREADINPUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc

define MOUSE_BUTTON_UP   0x0010
define MOUSE_BUTTON_DOWN 0x0020
define MOUSE_WHEEL_UP    0x0040
define MOUSE_WHEEL_DOWN  0x0080

ifdef __TTY__

    .data

     cursor_keys db VK_UP,      ; A
                    VK_DOWN,    ; B
                    VK_RIGHT,   ; C
                    VK_LEFT,    ; D
                    0,
                    VK_END,     ; F
                    0,
                    VK_HOME     ; H

     modifiers   db SHIFT_PRESSED,
                    LEFT_ALT_PRESSED,
                    LEFT_ALT_PRESSED or SHIFT_PRESSED,
                    LEFT_CTRL_PRESSED,
                    LEFT_CTRL_PRESSED or SHIFT_PRESSED,
                    LEFT_ALT_PRESSED or LEFT_CTRL_PRESSED,
                    LEFT_ALT_PRESSED or LEFT_CTRL_PRESSED or SHIFT_PRESSED

    .code

    assume rbx:PINPUT_RECORD

_readinput proc uses rsi rdi rbx Input:PINPUT_RECORD

    .new a:CINPUT

    .while 1

        .ifd ( _readansi( &a ) == 0 )

            .return
        .endif
        mov ecx,eax
        mov al,a.final
        mov ah,a.count

        mov rbx,Input
        mov [rbx].EventType,KEY_EVENT
        mov [rbx].Event.KeyEvent.bKeyDown,1
        mov [rbx].Event.KeyEvent.wRepeatCount,1
        mov [rbx].Event.KeyEvent.wVirtualKeyCode,0
        mov [rbx].Event.KeyEvent.wVirtualScanCode,0
        mov [rbx].Event.KeyEvent.uChar.UnicodeChar,ax
        mov [rbx].Event.KeyEvent.dwControlKeyState,0

        .break .if ( ecx == 1 )

        movzx eax,al
        .if ( al == 'M' )

            mov [rbx].EventType,MOUSE_EVENT
            xor ecx,ecx
            xor edx,edx
            xor edi,edi
            mov al,a.param

            .switch al

            ; Left Button Down

            .case '8'
                mov edx,LEFT_CTRL_PRESSED
            .case '('
                or  edx,LEFT_ALT_PRESSED
            .case ' '
                mov ecx,MOUSE_BUTTON_DOWN
                mov edi,FROM_LEFT_1ST_BUTTON_PRESSED
               .endc
            .case '0'
                mov edx,LEFT_CTRL_PRESSED
               .gotosw(' ')

            ; Middle Button Down

            .case '9'
                mov edx,LEFT_CTRL_PRESSED
            .case ')'
                or  edx,LEFT_ALT_PRESSED
            .case '!'
                mov ecx,MOUSE_BUTTON_DOWN
                mov edi,FROM_LEFT_2ND_BUTTON_PRESSED
               .endc
            .case '1'
                mov edx,LEFT_CTRL_PRESSED
               .gotosw('!')

            ; Right Button Down

            .case ':'
                mov edx,LEFT_CTRL_PRESSED
            .case '*'
                or  edx,LEFT_ALT_PRESSED
            .case '"'
                mov ecx,MOUSE_BUTTON_DOWN
                mov edi,RIGHTMOST_BUTTON_PRESSED
               .endc
            .case '6'
                mov edx,LEFT_CTRL_PRESSED
               .gotosw('"')

            ; Button Up

            .case ';'
                or  edx,LEFT_CTRL_PRESSED
            .case '+'
                or  edx,LEFT_ALT_PRESSED
            .case '#'
                mov ecx,MOUSE_BUTTON_UP
               .endc
            .case '3'
                mov edx,LEFT_CTRL_PRESSED
               .gotosw('#')

            ; Mouse Moved

            .case '[' ; Ctrl + Alt
                or  edx,LEFT_CTRL_PRESSED
            .case 'K' ; Alt
                or  edx,LEFT_ALT_PRESSED
            .case 'C' ; Move
                mov ecx,MOUSE_MOVED
               .endc
            .case 'S' ; Ctrl
                mov edx,LEFT_CTRL_PRESSED
               .gotosw('C')
            .case 'G' ; Shift
                or  edx,SHIFT_PRESSED
               .gotosw('C')

            ; Move + Left Button Down

            .case 'T' ; Move + Ctrl + Shift + Left Button Down
                mov edx,LEFT_CTRL_PRESSED
            .case 'D' ; Move + Shift + Left Button Down
                or  edx,SHIFT_PRESSED
            .case '@' ; Move + Left Button Down
                mov edi,FROM_LEFT_1ST_BUTTON_PRESSED
               .gotosw('C')
            .case 'H' ; Move + Alt + Left Button Down
                or  edx,LEFT_ALT_PRESSED
               .gotosw('@')
            .case 'X' ; Move + Ctrl + Alt + Left Button Down
                or  edx,LEFT_ALT_PRESSED
            .case 'P' ; Move + Ctrl + Left Button Down
                or  edx,LEFT_CTRL_PRESSED
               .gotosw('@')

            ; Move + Right Button Down

            .case 'V' ; Move + Ctrl + Shift + Right Button Down
                mov edx,LEFT_CTRL_PRESSED
            .case 'F' ; Move + Shift + Right Button Down
                or  edx,SHIFT_PRESSED
            .case 'B' ; Move + Right Button Down
                mov edi,RIGHTMOST_BUTTON_PRESSED
               .gotosw('C')
            .case 'J' ; Move + Alt + Right Button Down
                or  edx,LEFT_ALT_PRESSED
               .gotosw('B')
            .case 'Z' ; Move + Ctrl + Alt + Right Button Down
                or  edx,LEFT_ALT_PRESSED
            .case 'R' ; Move + Ctrl + Right Button Down
                or  edx,LEFT_CTRL_PRESSED
               .gotosw('B')

            ; Move + Middle Button Down

            .case 'U' ; Move + Ctrl + Shift + Middle Button Down
                mov edx,LEFT_CTRL_PRESSED
            .case 'E' ; Move + Shift + Middle Button Down
                or  edx,SHIFT_PRESSED
            .case 'A' ; Move + Middle Button Down
                mov edi,FROM_LEFT_2ND_BUTTON_PRESSED
               .gotosw('C')
            .case 'I' ; Move + Alt + Middle Button Down
                or  edx,LEFT_ALT_PRESSED
               .gotosw('A')
            .case 'Y' ; Move + Ctrl + Alt + Middle Button Down
                or  edx,LEFT_ALT_PRESSED
            .case 'Q' ; Move + Ctrl + Middle Button Down
                or  edx,LEFT_CTRL_PRESSED
               .gotosw('A')


            ; Mouse Wheeled (Down)

            .case 't'
                or  edx,SHIFT_PRESSED
            .case 'p'
                or  edx,LEFT_CTRL_PRESSED
            .case 96
                mov ecx,MOUSE_WHEELED
               .endc
            .case 'd'
                mov edx,SHIFT_PRESSED
               .gotosw(96)

            ; Mouse Wheeled (Up)

            .case 'u'
                or  edx,SHIFT_PRESSED
            .case 'q'
                or  edx,LEFT_CTRL_PRESSED
            .case 'a'
                mov ecx,MOUSE_WHEELED
                mov edi,0x80000000
               .endc
            .case 'e'
                mov edx,SHIFT_PRESSED
               .gotosw('a')
            .endsw

            mov [rbx].Event.MouseEvent.dwEventFlags,ecx
            mov [rbx].Event.MouseEvent.dwButtonState,edi
            mov [rbx].Event.MouseEvent.dwControlKeyState,edx
            mov eax,a.n[0]
            mov ecx,a.n[4]
            mov [rbx].Event.MouseEvent.dwMousePosition.X,ax
            mov [rbx].Event.MouseEvent.dwMousePosition.Y,cx
           .break
        .endif

        .if ( ecx == 3 && a.param == 'O' )

            ; SS3 - Single Shift Three

            .if ( al >= 'P' && al <= 'S' )

                sub   al,'P'
                add   eax,VK_F1
                mov   [rbx].Event.KeyEvent.wVirtualKeyCode,ax
               .break
            .endif
            .continue
        .endif

        .if ( a.count == 2 )

            mov edx,a.n[4]

            .if ( edx >= 2 && edx <= 8 )

                ; 2 - Shift
                ; 3 - Alt
                ; 4 - Shift + Alt
                ; 5 - Control
                ; 6 - Shift + Control
                ; 7 - Alt + Control
                ; 8 - Shift + Alt + Control

                lea rdi,modifiers
                mov dl,[rdi+rdx-2]
                or  [rbx].Event.KeyEvent.dwControlKeyState,edx
            .endif
        .endif

        .switch al
        .case 'A' ; Up
        .case 'B' ; Down
        .case 'C' ; Right
        .case 'D' ; Left
        .case 'F' ; End
        .case 'H' ; Home
            lea rdi,cursor_keys
            mov al,[rdi+rax-'A']
            mov [rbx].Event.KeyEvent.wVirtualKeyCode,ax
            or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
           .break
        .case 'P'..'S' ; F1..4
            sub   al,'P'
            add   eax,VK_F1
            mov   [rbx].Event.KeyEvent.wVirtualKeyCode,ax
           .break
        .case '~'
            mov eax,a.n
            .switch al
            .case 2 ; 2~  Insert
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_INSERT
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break
            .case 3 ; 3~ Delete
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_DELETE
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break
            .case 5 ; 5~ Page Up
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_PRIOR
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break
            .case 6 ; 6~ Page Down
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_NEXT
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break
            .case 15 ; 15~ F5
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_F5
               .break
            .case 17 ; 17~ F6
            .case 18 ; 18~ F7
            .case 19 ; 19~ F8
            .case 20 ; 20~ F9
            .case 21 ; 21~ F10
                lea eax,[rax+VK_F6-17]
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,ax
               .break
            .case 23 ; 23~ F11
            .case 24 ; 24~ F12
                lea eax,[rax+VK_F11-23]
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,ax
               .break
            .endsw
        .endsw
    .endw
    .return( 1 )

_readinput endp

else

    .code

_readinput proc Input:PINPUT_RECORD

    .new Count:dword
    .new NumberOfEventsRead:dword

    .ifd !GetNumberOfConsoleInputEvents(_coninpfh, &Count)

        dec rax
    .else

        mov eax,Count
        .if ( eax )

            .ifd !ReadConsoleInput(_coninpfh, Input, 1, &NumberOfEventsRead)
                dec rax
            .else
                mov eax,NumberOfEventsRead
            .endif
        .endif
    .endif
    ret

_readinput endp

endif
    end
