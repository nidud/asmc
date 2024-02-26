; _TCOUT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include stdio.inc
include stdlib.inc
include tchar.inc

.code

_cout proc uses rbx format:LPTSTR, argptr:vararg

  local stream:_iobuf
  local buffer[1024]:TCHAR
ifdef _UNICODE
  local count:int_t
  local cbuf:int_t
endif
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
        _toutput(&stream, format, &argptr)

ifdef _UNICODE
        .for ( count = eax, ebx = 0 : ebx < count : ebx++ )

            mov cbuf,_wtoutf(buffer[rbx*2])
            _write(_confd, &cbuf, ecx)
        .endf
        mov eax,count
else
        _write(_confd, stream._base, eax)
endif
    .endif
    ret

_cout endp

    end
