; _TSTAT64I32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include sys/stat.inc
include tchar.inc

    .code

ifdef _WIN64
ifdef __UNIX__
_tstat64i32 proc file:tstring_t, buf:ptr _stati64i32
    _stat64( ldr(file), ldr(buf) )
else
_tstat64i32 proc uses rsi rdi file:tstring_t, buf:ptr _stati64i32
   .new s:_stati64
    ldr rdi,buf
    .ifd ( _stat64( ldr(file), &s ) == 0 )
        lea rsi,s
        mov ecx,_stati64.st_rdev+4
        rep movsb
        lea rsi,s.st_size
        movsd
        lea rsi,s.st_atime
        mov ecx,3*8
        rep movsb
    .endif
endif
    ret
    endp
endif
    end
