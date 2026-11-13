; SetConsoleCursorPosition.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc

.code

 SetConsoleCursorPosition proc WINAPI fp:HANDLE, pos:COORD
    ldr edx,pos
    mov ecx,edx
    shr edx,16
    movzx ecx,cx
    inc ecx
    inc edx
    fprintf(fp, CSI "%d;%dH", edx, ecx)
    fflush(fp)
    mov eax,1
    ret
    endp

    end
