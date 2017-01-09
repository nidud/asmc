include stdlib.inc
include alloc.inc
include crtl.inc

PUBLIC	cp_temp
PUBLIC	envtemp
EXTERN	_pgmpath:dword

	.data
	envtemp dd 0
	cp_temp db "TEMP",0

	.code

GetEnvironmentTEMP PROC
	free  ( envtemp )
	getenvp( addr cp_temp )
	mov	envtemp,eax
	.if	!eax
		mov	eax,_pgmpath
		.if	eax
			salloc( eax )
			mov	envtemp,eax
			SetEnvironmentVariable( addr cp_temp, eax )
			mov	eax,envtemp
		.endif
	.endif
	ret
GetEnvironmentTEMP ENDP

pragma_init GetEnvironmentTEMP, 102

	END
