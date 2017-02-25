include io.inc
include time.inc
include winbase.inc

	.code

setftime PROC USES ecx edx h:SINT, time:SIZE_T

  local FileTime:FILETIME

	.if getosfhnd( h ) != -1

		mov edx,eax
		.if SetFileTime( edx, 0, 0, __TimeToFT( time, addr FileTime ) )

			xor eax,eax
			mov byte ptr _diskflag,2
		.else
			osmaperr()
		.endif
	.endif
	ret

setftime ENDP

	END
