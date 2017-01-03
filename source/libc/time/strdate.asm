include time.inc

strsdate proto :LPSTR, :LPSYSTEMTIME

	.code

strdate PROC string:LPSTR, tm:TIME_T
local	SystemTime:SYSTEMTIME
	__TimeToST( tm, addr SystemTime )
	strsdate( string, addr SystemTime )
	ret
strdate ENDP

	END
