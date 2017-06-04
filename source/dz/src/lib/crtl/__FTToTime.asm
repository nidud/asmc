include time.inc
include winbase.inc

	.code

__FTToTime PROC USES ecx edx ft:LPFILETIME

  local ftime:FILETIME
  local stime:SYSTEMTIME

	FileTimeToLocalFileTime( ft, addr ftime )
	FileTimeToSystemTime( addr ftime, addr stime )
	__STToTime( addr stime )
	ret

__FTToTime ENDP

	END
