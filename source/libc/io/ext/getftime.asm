include io.inc
include time.inc

	.code

getftime PROC USES ecx edx handle:SINT

  local FileTime:FILETIME

	.if getosfhnd( handle ) != -1

		mov edx,eax
		.if !GetFileTime( edx, 0, 0, addr FileTime )

			osmaperr()
		.else
			__FTToTime( addr FileTime )
		.endif
	.endif
	ret

getftime ENDP

	END
