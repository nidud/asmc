include stdlib.inc
include crtl.inc
include alloc.inc
include dzlib.inc

PUBLIC	envpath

	.data
	envpath dd curpath
	curpath db ".",0

	.code

GetEnvironmentPATH PROC
	.if getenvp( "PATH" )
	    mov ecx,envpath
	    mov envpath,eax
	    .if ecx != offset envpath
		free(ecx)
	    .endif
	.endif
	mov eax,envpath
	ret
GetEnvironmentPATH ENDP

pragma_init GetEnvironmentPATH, 101

	END
