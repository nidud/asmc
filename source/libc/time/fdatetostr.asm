include time.inc
include stdio.inc

strsdate proto :LPSTR, :LPSYSTEMTIME

	.code

fdatetostr PROC USES ecx edx string:LPSTR, ft:LPFILETIME

local	ftime:FILETIME,
	stime:SYSTEMTIME

	FileTimeToLocalFileTime( ft, addr ftime )
	FileTimeToSystemTime( addr ftime, addr stime )
	strsdate( string, addr stime )
	ret

fdatetostr ENDP

	END
