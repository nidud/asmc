; GETSTDHANDLE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include winbase.inc

.code

GetStdHandle proc WINAPI type:DWORD
    xor eax,eax
    .if ( ldr(type) == STD_OUTPUT_HANDLE )
        mov rax,_confh
        mov edx,_confd
    .elseif ( ldr(type) == STD_INPUT_HANDLE )
        mov eax,_coninpfd
    .endif
    ret
    endp

    end
