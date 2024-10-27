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

    _txtoa( ldr(val), ldr(buffer), ldr(radix), 0 )
    ret

_ui64tot endp

    end
