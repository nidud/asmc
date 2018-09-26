ifndef s6_addr

IN6_ADDR	STRUC
union u
 _Byte		db 16 dup(?)
 _Word		dw 8 dup(?)
ends
IN6_ADDR	ENDS
PIN6_ADDR	typedef ptr IN6_ADDR
LPIN6_ADDR	typedef ptr IN6_ADDR

in_addr6	equ <IN6_ADDR>
_S6_un		equ u
_S6_u8		equ _Byte
s6_addr		equ _S6_un._S6_u8
s6_bytes	equ u._Byte
s6_words	equ u._Word

endif
