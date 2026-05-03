; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include ltype.inc

    .data

     DEFINE_LTYPE _ltype

ifdef _WIN64

    _r15 dq 0

    .code

_ltypeinit proc
    mov _r15,r15
    lea r15,_ltype
    ret
    endp

_ltypeexit proc
    mov r15,_r15
    ret
    endp

.pragma init(_ltypeinit, 100)
endif

    end

