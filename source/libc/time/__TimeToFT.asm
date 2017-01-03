include time.inc

	.code

__TimeToFT PROC USES edx ecx time:TIME_T, lpFileTime:LPFILETIME

local	SystemTime:SYSTEMTIME

	SystemTimeToFileTime( __TimeToST( time, addr SystemTime ), lpFileTime )
	LocalFileTimeToFileTime( lpFileTime, lpFileTime )
	mov eax,lpFileTime
	ret

__TimeToFT ENDP

	END
