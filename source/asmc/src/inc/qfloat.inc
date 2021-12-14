; QFLOAT.INC--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
ifndef __QFLOAT_INC
define __QFLOAT_INC

; Half precision - binary16 -- REAL2 (half)

define H_SIGBITS   11
define H_EXPBITS   5
define H_EXPMASK   ((1 shl H_EXPBITS) - 1)
define H_EXPBIAS   (H_EXPMASK shr 1)
define H_EXPMAX    (H_EXPMASK - H_EXPBIAS)

; Single precision - binary32 -- REAL4 (float)

define F_SIGBITS   24
define F_EXPBITS   8
define F_EXPMASK   ((1 shl F_EXPBITS) - 1)
define F_EXPBIAS   (F_EXPMASK shr 1)
define F_EXPMAX    (F_EXPMASK - F_EXPBIAS)

; Double precision - binary64 -- REAL8 (double)

define D_SIGBITS   53
define D_EXPBITS   11
define D_EXPMASK   ((1 shl D_EXPBITS) - 1)
define D_EXPBIAS   (D_EXPMASK shr 1)
define D_EXPMAX    (D_EXPMASK - D_EXPBIAS)

; Long Double precision - binary80 -- REAL10 (long double)

define LD_SIGBITS  64
define LD_EXPBITS  15
define LD_EXPMASK  ((1 shl LD_EXPBITS) - 1)
define LD_EXPBIAS  (LD_EXPMASK shr 1)
define LD_EXPMAX   (LD_EXPMASK - LD_EXPBIAS)

; Quadruple precision - binary128 -- real16 (__float128)

define Q_SIGBITS   113
define Q_EXPBITS   15
define Q_EXPMASK   ((1 shl Q_EXPBITS) - 1)
define Q_EXPBIAS   (Q_EXPMASK shr 1)
define Q_EXPMAX    (Q_EXPMASK - Q_EXPBIAS)
define Q_DIGITS    38
define Q_SIGDIG    49

.template EXTFLOAT          ; extended (134-bit, 128+16) float
    l           uint64_t ?
    h           uint64_t ?
    e           short_t ?
   .ends

.template STRFLT
    mantissa    EXTFLOAT <> ; 128-bit mantissa
    flags       int_t ?     ; parsing flags
    exponent    int_t ?     ; exponent of floating point number
    string      string_t ?  ; pointer to buffer or string
   .ends


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

.template U128
    union
     i8         sbyte 16 dup(?)
     i16        sword  8 dup(?)
     i32        sdword 4 dup(?)
     i64        sqword 2 dup(?)
     u8         byte  16 dup(?)
     u16        word   8 dup(?)
     u32        dword  4 dup(?)
     u64        qword  2 dup(?)
     u128       oword  ?
    ends
   .ends

; QWORD

__mul64     proto watcall :uint64_t, :uint64_t
__div64     proto watcall :uint64_t, :uint64_t
__rem64     proto watcall :uint64_t, :uint64_t

; OWORD

__mulo      proto :ptr, :ptr, :ptr
__divo      proto :ptr, :ptr, :ptr
__shlo      proto :ptr, :int_t, :int_t
__shro      proto :ptr, :int_t, :int_t
__saro      proto :ptr, :int_t, :int_t

; REAL16

__mulq      proto :ptr, :ptr
__divq      proto :ptr, :ptr
__addq      proto :ptr, :ptr
__subq      proto :ptr, :ptr
__cmpq      proto :ptr, :ptr
__cvtq_ss   proto :ptr, :ptr
__cvtq_sd   proto :ptr, :ptr
__cvtq_ld   proto :ptr, :ptr
quad_resize proto :ptr expr, :int_t
_flttostr   proto :ptr, :ptr FLTINFO, :string_t, :uint_t

_atoow      proto :string_t, :string_t, :int_t, :int_t
atofloat    proto :ptr, :string_t, :uint_t, :int_t, :uchar_t

endif
