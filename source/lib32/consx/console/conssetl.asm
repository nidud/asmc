include consx.inc
include stdio.inc

    .data
    _scrmax dd 0,0

    .code

conssetl proc l ; line: 24..max
local bz:COORD
local rc:SMALL_RECT
local ci:CONSOLE_SCREEN_BUFFER_INFO

    .if GetConsoleScreenBufferInfo(hStdOutput, &ci)

        xor eax,eax
        mov rc.Left,ax
        mov rc.Top,ax
        mov rc.Right,79
        mov rc.Bottom,24
        mov edx,l
        mov eax,ci.dwSize
        shr eax,16
        dec eax

        .if edx != eax
            .if edx == 24
                inc edx
                mov eax,80
            .else
                ;
                ; japheth 2014-01-10 - reposition to desktop position 0,0
                ;
                GetConsoleWindow()
                SetWindowPos(eax,0,0,0,0,0,SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER)

                mov edx,GetLargestConsoleWindowSize(hStdOutput)
                shr edx,16
                movzx eax,ax
                mov ecx,_scrmax
                .if ecx <= eax && ecx >= 80

                    mov eax,_scrmax
                    mov edx,_scrmax[4]
                .endif
                and eax,-2

                .if eax < 80 || edx < 16
                    mov eax,80
                    mov edx,25
                .elseif eax > 255 || edx > 255
                    .if eax > 255
                        mov eax,240
                    .endif
                    .if edx > 255
                        mov edx,240
                    .endif
                .endif
                mov ecx,eax
                dec ecx
                mov rc.Right,cx
                mov ecx,edx
                dec ecx
                mov rc.Bottom,cx
            .endif
            mov bz.x,ax
            mov bz.y,dx

            SetConsoleWindowInfo(hStdOutput, 1, &rc)
            SetConsoleScreenBufferSize(hStdOutput, bz)
            SetConsoleWindowInfo(hStdOutput, 1, &rc)
            .if GetConsoleScreenBufferInfo(hStdOutput, &ci)
                mov eax,ci.dwSize
                movzx edx,ax
                mov _scrcol,edx
                shr eax,16
                dec eax
                mov _scrrow,eax
            .endif
        .endif
    .endif
    ret

conssetl endp

    END
