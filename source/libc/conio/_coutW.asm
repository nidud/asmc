; _COUTW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include conio.inc
include stdio.inc
include stdlib.inc

.code

_coutW proc uses rbx format:wstring_t, argptr:vararg

  local stream:_iobuf
  local buffer[1024]:wchar_t
  local count:int_t
  local cbuf:int_t

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
        mov count,_woutput(&stream, format, &argptr)

        .for ( ebx = 0 : ebx < count : ebx++ )

            mov cbuf,_wtoutf(buffer[rbx*2])
            _write(_confd, &cbuf, ecx)
        .endf
        mov eax,count
    .endif
    ret

_coutW endp

    end
