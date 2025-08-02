; QFLOAT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __QFLOAT_INC
define __QFLOAT_INC

include expreval.inc

define _ST_SIGN         0x000001
define _ST_NEGNUM       0x000002
define _ST_NEGEXP       0x000004
define _ST_ISZERO       0x000008
define _ST_ISHEX        0x000010
define _ST_ISNAN        0x000020
define _ST_ISINF        0x000040
define _ST_INVALID      0x000080
define _ST_UNDERFLOW    0x000100
define _ST_OVERFLOW     0x000200
define _ST_DIGITS       0x000400
define _ST_DOT          0x000800
define _ST_E            0x001000 ; 'E' format
define _ST_F            0x002000 ; 'F' format
define _ST_G            0x004000 ; 'G' format
define _ST_CVT          0x008000 ; cvt routine format rules
define _ST_CAPEXP       0x010000 ; 1.0E-10
define _ST_NO_TRUNC     0x020000 ; always provide ndigits in buffer
define _ST_FLOAT        0x040000 ; REAL4
define _ST_DOUBLE       0x080000 ; REAL8
define _ST_LONGDOUBLE   0x100000 ; REAL10
define _ST_QUADFLOAT    0x200000 ; REAL16
define _ST_ALTERNATE    0x400000 ; alternate form requested
define _ST_UNICODE      0x800000

.template FLTINFO
    ndigits     int_t ?
    scale       int_t ?
    flags       int_t ?
    expchar     int_t ?
    expwidth    int_t ?
    sign        int_t ?
    dec_place   int_t ?
    n1          int_t ?
    nz1         int_t ?
    n2          int_t ?
    nz2         int_t ?
    bufsize     int_t ?
   .ends

; 128-bit unsigned integer functions

__mulo      proto __ccall :ptr uint128_t, :ptr uint128_t, :ptr uint128_t
__divo      proto __ccall :ptr uint128_t, :ptr uint128_t, :ptr uint128_t
__shlo      proto __ccall :ptr uint128_t, :int_t, :int_t
__shro      proto __ccall :ptr uint128_t, :int_t, :int_t
__saro      proto __ccall :ptr uint128_t, :int_t, :int_t
__rolo      proto __ccall :ptr uint128_t, :int_t, :int_t
__roro      proto __ccall :ptr uint128_t, :int_t, :int_t

; Convert float, double, long double

__cvtq_ss   proto __ccall :ptr float_t, :ptr qfloat_t
__cvtq_sd   proto __ccall :ptr double_t, :ptr qfloat_t
__cvtq_ld   proto __ccall :ptr ldouble_t, :ptr qfloat_t

; */+-

__mulq      proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__divq      proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__addq      proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__subq      proto __ccall A:ptr qfloat_t, B:ptr qfloat_t
__cmpq      proto __ccall A:ptr qfloat_t, B:ptr qfloat_t

__sqrtq     proto __ccall A:ptr qfloat_t

ifdef _WIN64
__mul64 proto watcall multiplier:int64_t, multiplicand:int64_t {
    mul rdx
    }
else
__mul64     proto watcall :int64_t, :int64_t
endif
__div64     proto watcall :int64_t, :int64_t
__rem64     proto watcall :int64_t, :int64_t
__udiv64    proto watcall :uint64_t, :uint64_t

quad_resize proto __ccall :ptr expr, :int_t
_atoqw      proto fastcall :string_t
_atoow      proto __ccall :string_t, :string_t, :int_t, :int_t
_flttostr   proto __ccall :ptr, :ptr FLTINFO, :string_t, :uint_t
atofloat    proto __ccall :ptr, :string_t, :uint_t, :int_t, :uchar_t
CreateFloat proto __ccall :int_t, :expr_t, :string_t

endif
