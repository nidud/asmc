include io.inc
include time.inc
include winbase.inc

	.code

getftime_create PROC USES ecx edx handle:SINT

  local FileTime:FILETIME

	.if getosfhnd( handle ) != -1

		mov edx,eax
		.if !GetFileTime( edx, addr FileTime, 0, 0 )

			osmaperr()
		.else
			__FTToTime( addr FileTime )
		.endif
	.endif
	ret

getftime_create ENDP

	END
