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

  local stream:_iobuf
  local buffer[1024]:char_t

    .if ( _confd == -1 )

        xor eax,eax
    .else
        ;
        ; write character to console file handle
        ;
        mov stream._flag,_IOWRT or _IOSTRG
        mov stream._cnt,_INTIOBUF
        lea rax,buffer
        mov stream._ptr,rax
        mov stream._base,rax
        _write(_confd, stream._base, _output(&stream, format, &argptr))
    .endif
    ret

_coutA endp

    end
