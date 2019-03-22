; __DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc

    .data
    DoserrorNoMem ulong_t ERROR_NOT_ENOUGH_MEMORY

    .code

__doserrno proc
if 1
    lea rax,DoserrorNoMem
else
    .if !_getptd_noexit()
        lea rax,DoserrorNoMem
    .else
        lea rax,[rax]._tiddata._tdoserrno
    .endif
endif
    ret

__doserrno endp

    end
