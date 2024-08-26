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

ifdef _WIN64
 ifdef __UNIX__
    _txtoa( rdi, rsi, edx, 0 )
 else
    _txtoa( rcx, rdx, r8d, 0 )
 endif
else
    mov eax,val
    xor edx,edx
    _txtoa( edx::eax, buffer, radix, 0 )
endif
    ret

_ultot endp

    end
