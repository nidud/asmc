; _NOFLOAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Asmc will include this symbol if option -MT is used
; and no float :vararg params used
;
include fltintrn.inc

externdef c nofloat:int_t

.data
nofloat  label int_t
_fltused int_t 0

end
