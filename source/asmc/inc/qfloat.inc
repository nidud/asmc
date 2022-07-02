; QFLOAT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __QFLOAT_INC
define __QFLOAT_INC
include fltintrn.inc

ifdef _WIN64
__mul64 proto watcall multiplier:int64_t, multiplicand:int64_t {
    mul rdx
    }
else
__mul64     proto watcall :int64_t, :int64_t
endif
__div64     proto watcall :int64_t, :int64_t
__rem64     proto watcall :int64_t, :int64_t

quad_resize proto __ccall :ptr expr, :int_t
_atoqw      proto fastcall :string_t
_atoow      proto __ccall :string_t, :string_t, :int_t, :int_t
atofloat    proto __ccall :ptr, :string_t, :uint_t, :int_t, :uchar_t

endif
