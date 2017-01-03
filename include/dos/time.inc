ifndef __LIBC_INC
 include libc.inc
endif

.xlist

DT_BASEYEAR	equ 1980

putedxal	PROTO
wcputnum	PROTO

dosdate		PROTO _CType
dostime		PROTO _CType

getyear		PROTO _CType
getmnd		PROTO _CType
getday		PROTO _CType
gethour		PROTO _CType
getmin		PROTO _CType
getsec		PROTO _CType

dwtolstr	PROTO _CType :DWORD, :WORD
dwtostr		PROTO _CType :DWORD, :WORD
strtodw		PROTO _CType :DWORD
strtotw		PROTO _CType :DWORD
twtostr		PROTO _CType :DWORD, :WORD

tupdtime	PROTO _CType
tupddate	PROTO _CType

.list
