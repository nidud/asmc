.pragma list(push, 0)

ifndef PID_FIRST_USABLE
PID_FIRST_USABLE equ 2
endif
ifndef REFPROPERTYKEY
REFPROPERTYKEY typedef ptr PROPERTYKEY
endif

ifdef INITGUID
DEFINE_PROPERTYKEY macro name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid
	exitm<name PROPERTYKEY <<l, w1, w2,<b1, b2, b3, b4, b5, b6, b7, b8 >>, pid >>
	endm
else
DEFINE_PROPERTYKEY macro name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid
	exitm<externdef name:PROPERTYKEY>
	endm
endif

ifndef IsEqualPropertyKey
IsEqualPropertyKey macro a, b
	exitm<(((a).pid EQ (b).pid) AND IsEqualIID((a).fmtid, (b).fmtid) )>
	endm
endif

ifndef _PROPERTYKEY_EQUALITY_OPERATORS_
_PROPERTYKEY_EQUALITY_OPERATORS_ equ 1
endif

.pragma list(pop)
