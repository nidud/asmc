; _TUI64TOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char * _ui64toa(unsigned _int64 value, char *str, int radix);
; wchar_t * _ui64tow(unsigned __int64 value, wchar_t *str, int radix);
;
include stdlib.inc
include tchar.inc

    .code

_ui64tot proc val:uint64_t, buffer:tstring_t, radix:int_t

ifdef _WIN64
 ifdef __UNIX__
    _txtoa( rdi, rsi, edx, 0 )
 else
    _txtoa( rcx, rdx, r8d, 0 )
 endif
else
    _txtoa( val, buffer, radix, 0 )
endif
    ret

_ui64tot endp

    end
