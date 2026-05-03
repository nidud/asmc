.pragma list(push, 0)

ifndef PID_FIRST_USABLE
PID_FIRST_USABLE equ 2
endif
ifndef REFPROPERTYKEY
REFPROPERTYKEY typedef ptr PROPERTYKEY
endif

DEFINE_PROPERTYKEY macro name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8, pid
if defined(__PE__) or defined(__GUID__)
_&name& equ <{{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}},pid}>
elseifdef INITGUID
echo name PROPERTYKEY {{l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}},pid}
else
externdef name:PROPERTYKEY
endif
    exitm<>
    endm

ifndef IsEqualPropertyKey
IsEqualPropertyKey macro a, b
	exitm<(((a).pid EQ (b).pid) AND IsEqualIID((a).fmtid, (b).fmtid) )>
	endm
endif

ifndef _PROPERTYKEY_EQUALITY_OPERATORS_
_PROPERTYKEY_EQUALITY_OPERATORS_ equ 1
endif

.pragma list(pop)
