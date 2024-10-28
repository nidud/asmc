; _TUITOA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *_ultoa(unsigned long value, char *str, int radix);
; wchar_t *_ultow(unsigned long value, wchar_t *str, int radix);
;
include stdlib.inc
include tchar.inc

    .code

_ultot proc val:uint_t, buffer:tstring_t, radix:int_t

    _txtoa( ldr(val), ldr(buffer), ldr(radix), 0 )
    ret

_ultot endp

    end
