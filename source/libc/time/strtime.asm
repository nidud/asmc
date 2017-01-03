include time.inc

	.code

strtime PROC string:LPSTR, tm:TIME_T

  local SystemTime:SYSTEMTIME

	__TimeToST( tm, addr SystemTime )
	strstime( string, addr SystemTime )
	ret

strtime ENDP

	END
