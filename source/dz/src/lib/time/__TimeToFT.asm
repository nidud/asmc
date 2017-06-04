include time.inc
include winbase.inc

	.code

__TimeToFT PROC USES edx ecx t:time_t, lpFileTime:LPFILETIME

local	SystemTime:SYSTEMTIME

	SystemTimeToFileTime( __TimeToST( t, addr SystemTime ), lpFileTime )
	LocalFileTimeToFileTime( lpFileTime, lpFileTime )
	mov eax,lpFileTime
	ret

__TimeToFT ENDP

	END
