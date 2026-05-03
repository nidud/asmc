ifndef _INTSAFE_H_INCLUDED_
define _INTSAFE_H_INCLUDED_

include specstrings.inc

CHAR		typedef sbyte
INT8		typedef sbyte
UCHAR		typedef byte
UINT8		typedef byte
INT16		typedef sword
SSHORT		typedef sword
USHORT		typedef word
UINT16		typedef word
INT32		typedef sdword
UINT		typedef dword
UINT32		typedef dword
LONG		typedef sdword
ULONG		typedef dword
LONGLONG	typedef sqword
LONG64		typedef sqword
INT64		typedef sqword
ULONGLONG	typedef qword
DWORDLONG	typedef qword
ULONG64		typedef qword
DWORD64		typedef qword
UINT64		typedef qword

ifdef _WIN64
INT_PTR		typedef sqword
UINT_PTR	typedef qword
LONG_PTR	typedef sqword
ULONG_PTR	typedef qword
else
INT_PTR		typedef sdword
UINT_PTR	typedef dword
LONG_PTR	typedef sdword
ULONG_PTR	typedef dword
endif
DWORD_PTR	typedef ULONG_PTR

undef _USE_INTRINSIC_MULTIPLY128

if NOT defined(_M_CEE) AND (defined(_AMD64_) OR (defined(_IA64_) AND (_MSC_VER GE 1400)))
define _USE_INTRINSIC_MULTIPLY128 1
endif

HRESULT typedef LONG
SUCCEEDED proto watcall hr:HRESULT {
	retm<(sdword ptr eax !>= 0)>
	}
FAILED proto watcall hr:HRESULT {
	retm<(sdword ptr eax !< 0)>
	}

define S_OK 0

INT8_MIN		equ (-127i8 - 1)
SHORT_MIN		equ (-32768)
INT16_MIN		equ (-32767i16 - 1)
INT_MIN			equ (-2147483647 - 1)
INT32_MIN		equ (-2147483647i32 - 1)
LONG_MIN		equ (-2147483647 - 1)
LONGLONG_MIN		equ (-9223372036854775807i64 - 1)
LONG64_MIN		equ (-9223372036854775807i64 - 1)
INT64_MIN		equ (-9223372036854775807i64 - 1)
INT128_MIN		equ (-170141183460469231731687303715884105727i128 - 1)

ifdef _WIN64
INT_PTR_MIN		equ (-9223372036854775807i64 - 1)
LONG_PTR_MIN		equ (-9223372036854775807i64 - 1)
PTRDIFF_T_MIN		equ (-9223372036854775807i64 - 1)
SSIZE_T_MIN		equ (-9223372036854775807i64 - 1)
else
INT_PTR_MIN		equ (-2147483647 - 1)
LONG_PTR_MIN		equ (-2147483647 - 1)
PTRDIFF_T_MIN		equ (-2147483647 - 1)
SSIZE_T_MIN		equ (-2147483647 - 1)
endif

INT8_MAX		equ 127
UINT8_MAX		equ 0xffu
BYTE_MAX		equ 0xff
SHORT_MAX		equ 32767
INT16_MAX		equ 32767
USHORT_MAX		equ 0xffff
UINT16_MAX		equ 0xffff
WORD_MAX		equ 0xffff
INT_MAX			equ 2147483647
INT32_MAX		equ 2147483647
UINT_MAX		equ 0xffffffff
UINT32_MAX		equ 0xffffffff
LONG_MAX		equ 2147483647
ULONG_MAX		equ 0xffffffff
DWORD_MAX		equ 0xffffffff
LONGLONG_MAX		equ 9223372036854775807
LONG64_MAX		equ 9223372036854775807
INT64_MAX		equ 9223372036854775807
ULONGLONG_MAX		equ 0xffffffffffffffff
DWORDLONG_MAX		equ 0xffffffffffffffff
ULONG64_MAX		equ 0xffffffffffffffff
DWORD64_MAX		equ 0xffffffffffffffff
UINT64_MAX		equ 0xffffffffffffffff
INT128_MAX		equ 170141183460469231731687303715884105727
UINT128_MAX		equ 0xffffffffffffffffffffffffffffffff

undef SIZE_T_MAX

ifdef _WIN64
INT_PTR_MAX		equ 9223372036854775807
UINT_PTR_MAX		equ 0xffffffffffffffff
LONG_PTR_MAX		equ 9223372036854775807
ULONG_PTR_MAX		equ 0xffffffffffffffff
DWORD_PTR_MAX		equ 0xffffffffffffffff
PTRDIFF_T_MAX		equ 9223372036854775807
SIZE_T_MAX		equ 0xffffffffffffffff
SSIZE_T_MAX		equ 9223372036854775807
_SIZE_T_MAX		equ 0xffffffffffffffff
else
INT_PTR_MAX		equ 2147483647
UINT_PTR_MAX		equ 0xffffffff
LONG_PTR_MAX		equ 2147483647
ULONG_PTR_MAX		equ 0xffffffff
DWORD_PTR_MAX		equ 0xffffffff
PTRDIFF_T_MAX		equ 2147483647
SIZE_T_MAX		equ 0xffffffff
SSIZE_T_MAX		equ 2147483647
_SIZE_T_MAX		equ 0xffffffff
endif


INT8_ERROR		equ (-1)
UINT8_ERROR		equ 0xff
BYTE_ERROR		equ 0xff
SHORT_ERROR		equ (-1)
INT16_ERROR		equ (-1)
USHORT_ERROR		equ 0xffff
UINT16_ERROR		equ 0xffff
WORD_ERROR		equ 0xffff
INT_ERROR		equ (-1)
INT32_ERROR		equ (-1)
UINT_ERROR		equ 0xffffffff
UINT32_ERROR		equ 0xffffffff
LONG_ERROR		equ (-1)
ULONG_ERROR		equ 0xffffffff
DWORD_ERROR		equ 0xffffffff
LONGLONG_ERROR		equ (-1)
LONG64_ERROR		equ (-1)
INT64_ERROR		equ (-1)
ULONGLONG_ERROR		equ 0xffffffffffffffff
DWORDLONG_ERROR		equ 0xffffffffffffffff
ULONG64_ERROR		equ 0xffffffffffffffff
UINT64_ERROR		equ 0xffffffffffffffff

ifdef _WIN64
INT_PTR_ERROR		equ (-1)
UINT_PTR_ERROR		equ 0xffffffffffffffff
LONG_PTR_ERROR		equ (-1)
ULONG_PTR_ERROR		equ 0xffffffffffffffff
DWORD_PTR_ERROR		equ 0xffffffffffffffff
PTRDIFF_T_ERROR		equ (-1)
SIZE_T_ERROR		equ 0xffffffffffffffff
SSIZE_T_ERROR		equ (-1)
_SIZE_T_ERROR		equ 0xffffffffffffffff
else
INT_PTR_ERROR		equ (-1)
UINT_PTR_ERROR		equ 0xffffffff
LONG_PTR_ERROR		equ (-1)
ULONG_PTR_ERROR		equ 0xffffffff
DWORD_PTR_ERROR		equ 0xffffffff
PTRDIFF_T_ERROR		equ (-1)
SIZE_T_ERROR		equ 0xffffffff
SSIZE_T_ERROR		equ (-1)
_SIZE_T_ERROR		equ 0xffffffff
endif


endif

