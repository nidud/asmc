; _COUTA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include stdio.inc

.code

_coutA proc format:string_t, argptr:vararg

    .new stream:_iobuf
    .new buffer[1024]:char_t

    .if ( _confh < 0 )

        xor eax,eax
    .else
        ;
        ; write character to console file handle
        ;
        mov stream._flag,_IOWRT or _IOSTRG
        mov stream._cnt,_INTIOBUF
        lea rcx,buffer
        mov stream._ptr,rcx
        mov stream._base,rcx
        write(_confh, stream._base, _output(&stream, rdi, rax))
    .endif
    ret

_coutA endp

    end
