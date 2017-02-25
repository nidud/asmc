include time.inc
include winbase.inc

	.code

_time	PROC timeptr:LPTIME
  local SystemTime:SYSTEMTIME
	GetLocalTime( addr SystemTime )
	_loctotime_t( SystemTime.wYear,
		      SystemTime.wMonth,
		      SystemTime.wDay,
		      SystemTime.wHour,
		      SystemTime.wMinute,
		      SystemTime.wSecond )
	mov	ecx,timeptr
	test	ecx,ecx
	jz	@F
	mov	[ecx],eax
@@:
	ret
_time	ENDP

	END
