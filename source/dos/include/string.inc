ifndef __LIBC_INC
 include libc.inc
endif

.xlist

; Inline compare case - uses DX

cmpaxi	macro
	mov dx,ax
	sub al,'A'
	sub ah,'A'
	cmp al,'Z' - 'A' + 1
	sbb al,al
	cmp ah,'Z' - 'A' + 1
	sbb ah,ah
	and ax,2020h
	xor ax,dx
	cmp ah,al
	endm


memcmp		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memcpyw		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memcpyd		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memmovw		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memmovd		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
strncat		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memcpy		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memmove		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
memset		PROTO _CType :PTR BYTE, :WORD, :WORD
strlen		PROTO _CType :PTR BYTE
strcpy		PROTO _CType :PTR BYTE, :PTR BYTE
strncpy		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
strnzcpy	PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
strcat		PROTO _CType :PTR BYTE, :PTR BYTE
strcmp		PROTO _CType :PTR BYTE, :PTR BYTE
strncmp		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
stricmp		PROTO _CType :PTR BYTE, :PTR BYTE
strnicmp	PROTO _CType :PTR BYTE, :PTR BYTE, :WORD
strchr		PROTO _CType :PTR BYTE, :WORD
strrchr		PROTO _CType :PTR BYTE, :WORD
strstr		PROTO _CType :PTR BYTE, :PTR BYTE
strlwr		PROTO _CType :PTR BYTE
strrev		PROTO _CType :PTR BYTE
strupr		PROTO _CType :PTR BYTE

memzero		PROTO _CType :PTR BYTE, :WORD
memxchg		PROTO _CType :PTR BYTE, :PTR BYTE, :WORD

strcmpi		PROTO
strstart	PROTO _CType :PTR BYTE
strtrim		PROTO _CType :PTR BYTE
strfn		PROTO _CType :PTR BYTE
strpath		PROTO _CType :PTR BYTE
strfcat		PROTO _CType :PTR BYTE, :PTR BYTE, :PTR BYTE
cmpwarg		PROTO _CType :PTR BYTE, :PTR BYTE
cmpwargs	PROTO _CType :PTR BYTE, :PTR BYTE
strxchg		PROTO _CType :PTR BYTE, :PTR BYTE, :PTR BYTE, :WORD
dostounix	PROTO _CType :PTR BYTE
unixtodos	PROTO _CType :PTR BYTE
atohex		PROTO _CType :PTR BYTE
hextoa		PROTO _CType :PTR BYTE
strext		PROTO _CType :PTR BYTE
setfext		PROTO _CType :PTR BYTE, :PTR BYTE
ftolower	PROTO _CType

.list
