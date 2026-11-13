; SETSTDHANDLE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include winbase.inc

.code

SetStdHandle proc WINAPI type:DWORD, fh:HANDLE
    xor eax,eax
    ldr ecx,type
    ldr rdx,fh
    .if ( ecx == STD_OUTPUT_HANDLE )
        mov _confd,edx
        mov rax,_confh
        .if ( rax )
            mov [rax].FILE._file,edx
        .endif
        mov eax,1
    .elseif ( ecx == STD_INPUT_HANDLE )
        mov _coninpfd,edx
        inc eax
    .endif
    ret
    endp

    end
