ifndef _STDARG_
define _STDARG_
.pragma list(push, 0)
ifndef _LIBC_
include libc.inc
endif

va_list typedef ptr sbyte

ifdef  _M_IX86

_INTSIZEOF macro n
	exitm<( (sizeof(n) + size_t - 1) and not (size_t - 1) )>
	endm
va_start macro ap, v
	mov ap,v
	add ap,_INTSIZEOF(v)
	exitm<ap>
	endm
va_arg	macro ap, t
	add ap,_INTSIZEOF(t)
	sub ap,_INTSIZEOF(t)
	exitm<t ptr [ap]>
	endm
va_end	macro ap
	mov ap,0
	exitm<ap>
	endm
endif

.pragma list(pop)
endif
