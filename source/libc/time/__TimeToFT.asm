include time.inc
include winbase.inc

	.code

__TimeToFT PROC USES edx ecx time:time_t, lpFileTime:LPFILETIME

local	SystemTime:SYSTEMTIME

	SystemTimeToFileTime( __TimeToST( time, addr SystemTime ), lpFileTime )
	LocalFileTimeToFileTime( lpFileTime, lpFileTime )
	mov eax,lpFileTime
	ret

__TimeToFT ENDP

	END
