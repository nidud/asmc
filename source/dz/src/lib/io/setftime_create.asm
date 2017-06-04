include io.inc
include time.inc
include winbase.inc
include dzlib.inc

	.code

setftime_create PROC USES edx ecx h:SINT, t:SIZE_T

  local FileTime:FILETIME

	.if getosfhnd( h ) != -1

		mov edx,eax
		.if SetFileTime( edx, __TimeToFT( t, addr FileTime ), 0, 0 )

			xor eax,eax
			mov byte ptr _diskflag,2
		.else
			osmaperr()
		.endif
	.endif
	ret

setftime_create ENDP

	END
