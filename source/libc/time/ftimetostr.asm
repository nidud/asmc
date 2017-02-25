include time.inc
include winbase.inc

	.code

ftimetostr PROC USES ecx edx string:LPSTR, ft:LPFILETIME

local	ftime:FILETIME,
	stime:SYSTEMTIME

	FileTimeToLocalFileTime( ft, addr ftime )
	FileTimeToSystemTime( addr ftime, addr stime )
	SystemTimeToString( string, addr stime )
	ret

ftimetostr ENDP

	END
