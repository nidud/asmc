; GETCONSOLECURSORINFO.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include winbase.inc

.data
 cursor_size uint_t CURSOR_DEFAULT
 cursor_visible uint_t TRUE

.code
 assume rbx:PCONSOLE_CURSOR_INFO

 GetConsoleCursorInfo proc WINAPI uses rbx fh:HANDLE, cp:PCONSOLE_CURSOR_INFO
    ldr rbx,cp
    mov [rbx].dwSize,cursor_size
    mov [rbx].bVisible,cursor_visible
    mov eax,1
    ret
    endp

 SetConsoleCursorInfo proc WINAPI uses rbx fp:HANDLE, cp:PCONSOLE_CURSOR_INFO
    ldr rbx,cp
    mov cursor_visible,[rbx].bVisible
    mov eax,[rbx].dwSize
    .if ( eax != cursor_size )
        .if ( eax > CURSOR_BAR )
            mov eax,CURSOR_DEFAULT
        .endif
        mov cursor_size,eax
        fprintf(fp, CSI "%d q", eax)
    .endif
    .if ( [rbx].bVisible )
        fprintf(fp, CSI "?25h")
    .else
        fprintf(fp, CSI "?25l")
    .endif
    fflush(fp)
    mov eax,1
    ret
    endp

    end
