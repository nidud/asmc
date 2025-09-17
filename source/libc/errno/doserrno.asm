; DOSERRNO.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include winerror.inc

    .data
ifndef _WIN64
    _doserrno label errno_t
endif
    DoserrorNoMem errno_t ERROR_NOT_ENOUGH_MEMORY

    .code

__doserrno proc

    lea rax,DoserrorNoMem
    ret

__doserrno endp

    end
