; _FLTINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

.data
_cfltcvt_tab PF0 0

.code

_fltinit proc

    lea rax,_fltconvert
    mov _cfltcvt_tab,rax
    ret

_fltinit endp

.pragma init(_fltinit, 40)

    end
