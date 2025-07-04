ifndef _INC_VADEFS
define _INC_VADEFS
.pragma list(push, 0)

define _CRT_PACKING size_t
.pragma pack(push, _CRT_PACKING)

ifndef _VA_LIST_DEFINED
define _VA_LIST_DEFINED
va_list typedef ptr sbyte
endif

_ADDRESSOF macro v
	exitm<addr v>
	endm
_SLOTSIZEOF macro t
	exitm<sizeof(t)>
	endm
_APALIGN macro t,ap
	exitm<__alignof(t)>
	endm

ifdef _M_IX86

_INTSIZEOF macro n
	exitm<((sizeof(n) + SINT - 1) and not (SINT - 1))>
	endm

__crt_va_start_a macro ap, v
	mov ap,v
	add ap,_INTSIZEOF(v)
	exitm<ap>
	endm
__crt_va_arg macro ap, t
	add ap,_INTSIZEOF(t)
	sub ap,_INTSIZEOF(t)
	exitm<t ptr [ap]>
	endm
__crt_va_end macro ap
	mov ap,0
	exitm<ap>
	endm

elseifdef _M_X64

__va_start proto __cdecl :ptr, :vararg

__crt_va_start_a macro ap, x
	exitm<__va_start(addr ap, x)>
	endm
__crt_va_arg macro ap, t
	add ap,sizeof(qword)
	exitm<t ptr [ap - sizeof(qword)]>
	endm
__crt_va_end macro ap
	mov ap,0
	exitm<ap>
	endm

endif

__crt_va_start macro ap, x
	exitm<__crt_va_start_a(ap, x)>
	endm

.pragma pack(pop)
.pragma list(pop)
endif
