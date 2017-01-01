include io.inc
include direct.inc
include alloc.inc

	.code

	OPTION	WIN64:2

_mkdir	proc directory:LPSTR

local	wpath:qword

	.if	!CreateDirectoryA( directory, 0 )

		mov	wpath,__allocwpath( directory )
		add	rax,8
		.if	!CreateDirectoryW( rax, 0 )

			CreateDirectoryW( wpath, 0 )
		.endif
	.endif

	.if	!eax

		osmaperr()
	.else
	    ifdef __DZ__
		mov _diskflag,1
	    endif
		xor eax,eax
	.endif
	ret

_mkdir	endp

	END
