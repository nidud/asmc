ifndef __LIBC_INC
 include libc.inc
endif

.xlist
ifndef _INC_STDARG
_INC_STDARG equ 1

ifdef  _MSC_VER
;
; Currently, all MS C compilers for Win32 platforms default to 8 byte
; alignment.
;
option fieldalign:8
endif

va_list typedef ptr sbyte

ifdef  _M_IX86

_INTSIZEOF macro n
	exitm<( (sizeof(n) + sizeof(size_t) - 1) and not (sizeof(size_t) - 1) )>
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
endif	; _INC_STDARG

.list
