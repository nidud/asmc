.pragma list(push, 0)

STRING_GUID macro l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8
	exitm<l-w1-w2-&b1&&b2&-&b3&&b4&&b5&&b6&&b7&&b8&>
	endm

GUID_BUILDER macro n,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8
	exitm<DEFINE_GUID(n,0x&l&,0x&w1&,0x&w2&,0x&b1&,0x&b2&,0x&b3&,0x&b4&,0x&b5&,0x&b6&,0x&b7&,0x&b8&)>
	endm

IMMEDIATE_GUID_USE equ 1
INCLUDING_ADOGUIDS equ 1
.pragma list(pop)
include adogpool.inc
