ifndef __IN6ADDR_INC
define __IN6ADDR_INC

ifndef s6_addr

in6_addr	struct
union u
 _Byte		db 16 dup(?)
 _Word		dw 8 dup(?)
ends
in6_addr	ends

IN6_ADDR	typedef in6_addr
PIN6_ADDR	typedef ptr IN6_ADDR
LPIN6_ADDR	typedef ptr IN6_ADDR

define in_addr6 <in6_addr>
define _S6_un	<u>
define _S6_u8	<_Byte>

define s6_addr	<_S6_un._S6_u8>
define s6_bytes <u._Byte>
define s6_words <u._Word>

endif
endif
