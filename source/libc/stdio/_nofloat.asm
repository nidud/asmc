; _FLTINIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include fltintrn.inc

public _nofloat
.data
_nofloat label int_t
_fltused int_t 0
end
