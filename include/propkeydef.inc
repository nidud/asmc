.pragma list(push, 0)

ifndef PID_FIRST_USABLE
define PID_FIRST_USABLE 2
endif
ifndef REFPROPERTYKEY
REFPROPERTYKEY typedef ptr PROPERTYKEY
endif

ifndef DEFINE_PROPERTYKEY
DEFINE_PROPERTYKEY macro name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid
ifdef _DLL
_&name& equ <{{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}},pid}>
elseifdef INITGUID
echo name PROPERTYKEY {{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}},pid}
else
externdef name:PROPERTYKEY
endif
    exitm<>
    endm
endif

ifndef IsEqualPropertyKey
IsEqualPropertyKey proto watcall :ptr, :ptr {
	xchg	rax,rsi
	xchg	rdx,rdi
	mov	ecx,PROPERTYKEY/4
	repz	cmpsd
	mov	rsi,rax
	mov	rdi,rdx
	setz	al
	movzx	eax,al
	}
endif

ifndef _PROPERTYKEY_EQUALITY_OPERATORS_
define _PROPERTYKEY_EQUALITY_OPERATORS_ 1
endif

.pragma list(pop)
