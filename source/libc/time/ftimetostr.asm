include time.inc

strstime proto :LPSTR, :LPSYSTEMTIME

	.code

ftimetostr PROC USES ecx edx string:LPSTR, ft:LPFILETIME

local	ftime:FILETIME,
	stime:SYSTEMTIME

	FileTimeToLocalFileTime( ft, addr ftime )
	FileTimeToSystemTime( addr ftime, addr stime )
	strstime( string, addr stime )
	ret

ftimetostr ENDP

	END
