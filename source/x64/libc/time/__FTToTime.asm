include time.inc
include winbase.inc

	.code

	OPTION	WIN64:2, STACKBASE:rsp

__FTToTime PROC ft:LPFILETIME

local	ftime:FILETIME
local	stime:SYSTEMTIME

	FileTimeToLocalFileTime( rcx, addr ftime )
	FileTimeToSystemTime( addr ftime, addr stime )
	__STToTime( addr stime )

	ret

__FTToTime ENDP

	END
