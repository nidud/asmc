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

    .new keys:CINPUT

    .while 1

        mov keys.q,0
        mov keys.count,_read(_coninpfd, &keys.b, 8)

        .if ( eax == 0 )

            .return
        .endif

        mov rbx,Input
        mov [rbx].EventType,KEY_EVENT
        mov [rbx].Event.KeyEvent.bKeyDown,1
        mov [rbx].Event.KeyEvent.wRepeatCount,1
        mov [rbx].Event.KeyEvent.wVirtualKeyCode,0
        mov [rbx].Event.KeyEvent.wVirtualScanCode,0
        mov [rbx].Event.KeyEvent.uChar.UnicodeChar,0
        mov [rbx].Event.KeyEvent.dwControlKeyState,0

        mov rax,keys.q
        mov ecx,keys.count

        .if ( al != VK_ESCAPE )

            movzx eax,al
            mov [rbx].Event.KeyEvent.uChar.UnicodeChar,ax
           .break

        .elseif ( ecx == 1 )

            mov [rbx].Event.KeyEvent.uChar.UnicodeChar,VK_ESCAPE
           .break
        .endif

        shr rax,8
        dec ecx

        .switch al

        .case 'O'
            .if ( ah >= 'P' && ah <= 'S' )

                sub   ah,'P'
                movzx eax,ah
                add   eax,VK_F1
                mov   [rbx].Event.KeyEvent.wVirtualKeyCode,ax
               .break
            .endif
            .endc

        .case '['
            ;
            ; [1;2P     Shift F1
            ; [15;2~    Shift F5
            ;

            .if ( ah != 'M' )

                .for ( esi = 1 : esi < ecx : esi++ )

                    .if ( keys.b[rsi] == ';' )

                        movzx edx,keys.b[rsi+1]
                        .if ( dl >= '2' && dl <= '8' )

                            ; '2' ; Shift
                            ; '3' ; Alt
                            ; '4' ; Shift + Alt
                            ; '5' ; Control
                            ; '6' ; Shift + Control
                            ; '7' ; Alt + Control
                            ; '8' ; Shift + Alt + Control

                            lea rdi,modifiers
                            mov dl,[rdi+rdx-'2']
                            or  [rbx].Event.KeyEvent.dwControlKeyState,edx
                        .endif
                    .endif
                .endf
            .endif

            shr rax,8
            dec ecx

            .switch al
            .case 'A' ; Up
            .case 'B' ; Down
            .case 'C' ; Right
            .case 'D' ; Left
            .case 'F' ; End
            .case 'H' ; Home
                movzx eax,al
                lea rdi,cursor_keys
                mov al,[rdi+rax-'A']
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,ax
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break

            .case '1'
                .endc .ifs ( ecx <= 0 )
                shr rax,8
                dec ecx
                .switch al
                .case ';'
                    shr rax,8
                    dec ecx
                    .while ( al >= '0' && al <= '9' )
                        shr rax,8
                        dec ecx
                    .endw
                    .if ( al >= 'A' && al <= 'H' )
                        .gotosw(1: 'A')
                    .endif
                    .gotosw .if al
                .case '~'
                    .break
                .case 'P' ; F1 1P
                .case 'Q' ; F2 1Q
                .case 'R' ; F3 1R
                .case 'S' ; F4 1S
                    shl eax,8
                   .gotosw(2:'O')
                .case '1' ; F1 11~
                .case '2' ; F2 12~
                .case '3' ; F3 13~
                .case '4' ; F4 14~
                .case '5' ; F5 15~
                    movzx edx,al
                    lea edx,[rdx+VK_F1-'1']
                    mov [rbx].Event.KeyEvent.wVirtualKeyCode,dx
                   .gotosw(1:'1')
                .case '7' ; F6 17~
                .case '8' ; F7 18~
                .case '9' ; F8 19~
                    movzx edx,al
                    lea edx,[rdx+VK_F6-'7']
                    mov [rbx].Event.KeyEvent.wVirtualKeyCode,dx
                   .gotosw(1:'1')
                .endsw
                .endc

            .case '2'
                movzx eax,ah
                .switch al
                .case '~' ; 2~  Insert
                    mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_INSERT
                    or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
                   .break
                .case '0' ; 20~ F9
                .case '1' ; 21~ F10
                    lea eax,[rax+VK_F9-'0']
                    mov [rbx].Event.KeyEvent.wVirtualKeyCode,ax
                   .break
                .case '3' ; 23~ F11
                .case '4' ; 24~ F12
                    lea eax,[rax+VK_F11-'3']
                    mov [rbx].Event.KeyEvent.wVirtualKeyCode,ax
                   .break
                .endsw
                .endc

            .case '3' ; 3~ Delete
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_DELETE
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break
            .case '5' ; 5~ Page Up
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_PRIOR
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break
            .case '6' ; 6~ Page Down
                mov [rbx].Event.KeyEvent.wVirtualKeyCode,VK_NEXT
                or  [rbx].Event.KeyEvent.dwControlKeyState,ENHANCED_KEY
               .break

            .case 'M'

                mov [rbx].EventType,MOUSE_EVENT
                xor ecx,ecx
                xor edx,edx
                xor edi,edi
                shr eax,8
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
                shr eax,8
                sub eax,0x2121
                movzx ecx,al
                movzx eax,ah
                mov [rbx].Event.MouseEvent.dwMousePosition.Y,ax
                mov [rbx].Event.MouseEvent.dwMousePosition.X,cx
               .break
            .endsw
            .endc
        .default
            .if ( ecx == 1 )

                movzx eax,al
                mov [rbx].Event.KeyEvent.uChar.UnicodeChar,ax
                mov [rbx].Event.KeyEvent.dwControlKeyState,LEFT_ALT_PRESSED
               .break
            .endif
            .endc
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
