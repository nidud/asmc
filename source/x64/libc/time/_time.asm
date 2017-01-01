include time.inc

	.code

_time	PROC timeptr:LPTIME

local	STime:SYSTEMTIME

	GetLocalTime( addr STime )
	_loctotime_t( STime.wYear,
		      STime.wMonth,
		      STime.wDay,
		      STime.wHour,
		      STime.wMinute,
		      STime.wSecond )
	mov	rcx,timeptr
	test	rcx,rcx
	jz	@F
	mov	[rcx],eax
@@:
	ret
_time	ENDP

	END
