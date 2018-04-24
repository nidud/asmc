ifndef _STDINT
_STDINT equ <>
include vcruntime.inc
.xlist

int8_t			typedef sbyte
int16_t			typedef sword
int32_t			typedef sdword
int64_t			typedef sqword
uint8_t			typedef byte
uint16_t		typedef word
uint32_t		typedef dword
uint64_t		typedef qword

int_least8_t		typedef sbyte
int_least16_t		typedef sword
int_least32_t		typedef sdword
int_least64_t		typedef sqword
uint_least8_t		typedef byte
uint_least16_t		typedef word
uint_least32_t		typedef dword
uint_least64_t		typedef qword

int_fast8_t		typedef sbyte
int_fast16_t		typedef sdword
int_fast32_t		typedef sdword
int_fast64_t		typedef sqword
uint_fast8_t		typedef byte
uint_fast16_t		typedef dword
uint_fast32_t		typedef dword
uint_fast64_t		typedef qword

intmax_t		typedef sqword
uintmax_t		typedef qword

;; These macros must exactly match those in the Windows SDK's intsafe.h.

INT8_MIN		equ (-127 - 1)
INT16_MIN		equ (-32767 - 1)
INT32_MIN		equ (-2147483647 - 1)
INT64_MIN		equ (-9223372036854775807 - 1)
INT8_MAX		equ 127
INT16_MAX		equ 32767
INT32_MAX		equ 2147483647
INT64_MAX		equ 9223372036854775807
UINT8_MAX		equ 0xff
UINT16_MAX		equ 0xffff
UINT32_MAX		equ 0xffffffff
UINT64_MAX		equ 0xffffffffffffffff

INT_LEAST8_MIN		equ INT8_MIN
INT_LEAST16_MIN		equ INT16_MIN
INT_LEAST32_MIN		equ INT32_MIN
INT_LEAST64_MIN		equ INT64_MIN
INT_LEAST8_MAX		equ INT8_MAX
INT_LEAST16_MAX		equ INT16_MAX
INT_LEAST32_MAX		equ INT32_MAX
INT_LEAST64_MAX		equ INT64_MAX
UINT_LEAST8_MAX		equ UINT8_MAX
UINT_LEAST16_MAX	equ UINT16_MAX
UINT_LEAST32_MAX	equ UINT32_MAX
UINT_LEAST64_MAX	equ UINT64_MAX

INT_FAST8_MIN		equ INT8_MIN
INT_FAST16_MIN		equ INT32_MIN
INT_FAST32_MIN		equ INT32_MIN
INT_FAST64_MIN		equ INT64_MIN
INT_FAST8_MAX		equ INT8_MAX
INT_FAST16_MAX		equ INT32_MAX
INT_FAST32_MAX		equ INT32_MAX
INT_FAST64_MAX		equ INT64_MAX
UINT_FAST8_MAX		equ UINT8_MAX
UINT_FAST16_MAX		equ UINT32_MAX
UINT_FAST32_MAX		equ UINT32_MAX
UINT_FAST64_MAX		equ UINT64_MAX

ifdef _WIN64
INTPTR_MIN		equ INT64_MIN
INTPTR_MAX		equ INT64_MAX
UINTPTR_MAX		equ UINT64_MAX
else
INTPTR_MIN		equ INT32_MIN
INTPTR_MAX		equ INT32_MAX
UINTPTR_MAX		equ UINT32_MAX
endif

INTMAX_MIN		equ INT64_MIN
INTMAX_MAX		equ INT64_MAX
UINTMAX_MAX		equ UINT64_MAX

PTRDIFF_MIN		equ INTPTR_MIN
PTRDIFF_MAX		equ INTPTR_MAX

ifndef SIZE_MAX
SIZE_MAX		equ UINTPTR_MAX
endif

SIG_ATOMIC_MIN		equ INT32_MIN
SIG_ATOMIC_MAX		equ INT32_MAX

WCHAR_MIN		equ 0x0000
WCHAR_MAX		equ 0xffff

WINT_MIN		equ 0x0000
WINT_MAX		equ 0xffff

INT8_C macro x
	exitm<(x)>
	endm
INT16_C macro x
	exitm<(x)>
	endm
INT32_C macro x
	exitm<(x)>
	endm
INT64_C macro x
	exitm<(&x&&LL&)>
	endm

UINT8_C macro x
	exitm<(x)>
	endm
UINT16_C macro x
	exitm<(x)>
	endm
UINT32_C macro x
	exitm<(&x&&U&)>
	endm
UINT64_C macro x
	exitm<(&x&&ULL&)>
	endm

INTMAX_C macro x
	exitm<INT64_C(x)>
	endm
UINTMAX_C macro x
	exitm<UINT64_C(x)>
	endm

.list
endif ;; _STDINT
