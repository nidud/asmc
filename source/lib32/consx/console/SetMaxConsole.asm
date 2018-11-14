; SETMAXCONSOLE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc

    .code

SetMaxConsole proc

    SetWindowPos(GetConsoleWindow(),0,0,0,0,0,SWP_NOSIZE or SWP_NOACTIVATE or SWP_NOZORDER)
    mov edx,GetLargestConsoleWindowSize(hStdOutput)
    shr edx,16
    movzx eax,ax
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
    SetConsoleSize(eax, edx)
    ret

SetMaxConsole endp

    END
