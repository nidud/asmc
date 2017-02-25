include io.inc
include time.inc
include winbase.inc

	.code

getftime_access proc uses ecx edx handle:SINT

  local FileTime:FILETIME

	.if getosfhnd(handle) != -1

		mov edx,eax
		.if !GetFileTime( edx, 0, addr FileTime, 0 )

			osmaperr()
		.else
			__FTToTime( addr FileTime )
		.endif
	.endif
	ret

getftime_access endp

	END
