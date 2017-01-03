include stdlib.inc
include crtl.inc
include alloc.inc

PUBLIC	envpath
getenvp proto :dword

	.data
	envpath dd curpath
	curpath db ".",0

	.code

GetEnvironmentPATH PROC
	free  ( envpath )
	mov	envpath,offset curpath
	.if	getenvp( "PATH" )
		mov envpath,eax
	.endif
	ret
GetEnvironmentPATH ENDP

pragma_init GetEnvironmentPATH, 101

	END
