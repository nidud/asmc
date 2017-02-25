include time.inc
include stdio.inc
include winbase.inc

	.code

fdatetostr PROC USES ecx edx string:LPSTR, ft:LPFILETIME

local	ftime:FILETIME,
	stime:SYSTEMTIME

	FileTimeToLocalFileTime( ft, addr ftime )
	FileTimeToSystemTime( addr ftime, addr stime )
	SystemDateToString( string, addr stime )
	ret

fdatetostr ENDP

	END
