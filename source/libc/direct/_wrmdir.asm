include direct.inc
include errno.inc
include winbase.inc

	.code

_wrmdir proc directory:LPWSTR

	.if RemoveDirectoryW( directory )

		xor eax,eax
ifdef __DZ__
		mov _diskflag,1
endif
	.else
		osmaperr()
	.endif
	ret

_wrmdir endp

	END
