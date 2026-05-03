; NOFLT.ASM-- stub out CRT's processing of float arguments
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Asmc will include this file if option -MT is used
; and no float (vararg) params used
;

include fltintrn.inc

.data
_cfltcvt_tab PF0 0

.code

_fltinit proc

    lea rax,_fptrap
    mov _cfltcvt_tab,rax
    ret

_fltinit endp

.pragma init(_fltinit, 40)

    end
