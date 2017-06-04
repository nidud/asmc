ifndef __LIBC_INC
 include libc.inc
endif

.xlist

exit		PROTO _CType :WORD
abort		PROTO _CType
terminate	PROTO _CType :WORD
atol		PROTO _CType :PTR BYTE
xtol		PROTO _CType :PTR BYTE
strtol		PROTO _CType :PTR BYTE
qsort		PROTO _CType :DWORD, :WORD, :WORD, :DWORD
qwtostr		PROTO _CType :DWORD, :DWORD
qwtobstr	PROTO _CType :DWORD, :DWORD
mkbstring	PROTO _CType :PTR BYTE, :DWORD, :DWORD
searchp		PROTO _CType :PTR BYTE
getenvp		PROTO _CType :PTR BYTE
getenval	PROTO _CType :PTR BYTE, :PTR BYTE
expenviron	PROTO _CType :PTR BYTE
isexec		PROTO _CType
rand		PROTO _CType
srand		PROTO _CType :WORD
random		PROTO _CType :WORD
randomize	PROTO _CType

.list
