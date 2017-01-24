include io.inc
include time.inc

	.code

setftime_access PROC USES edx ecx h:SINT, time:SIZE_T

  local FileTime:FILETIME

	.if getosfhnd( h ) != -1

		mov edx,eax
		.if SetFileTime( edx, 0, __TimeToFT( time, addr FileTime ), 0 )

			xor eax,eax
			mov byte ptr _diskflag,2
		.else
			osmaperr()
		.endif
	.endif
	ret

setftime_access ENDP

	END
