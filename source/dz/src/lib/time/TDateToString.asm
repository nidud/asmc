include time.inc

	.code

TDateToString PROC string:ptr sbyte, tptr:time_t

local	SystemTime:SYSTEMTIME

	__TimeToST( tptr, addr SystemTime )

	SystemDateToString( string, addr SystemTime )
	ret

TDateToString ENDP

	END
