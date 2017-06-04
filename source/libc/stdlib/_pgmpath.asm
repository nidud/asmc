include stdlib.inc
include string.inc
include alloc.inc
include crtl.inc

PUBLIC	_pgmpath

	.data
	_pgmpath LPSTR 0

	.code

Install PROC USES edi PRIVATE
local	path[256]

	lea edi,path
	strcpy( edi, _pgmptr )
	.if strfn( edi ) > edi

		mov byte ptr [eax-1],0
		strlen( edi )
		inc edi
		mov _pgmpath,malloc( eax )
		strcpy( eax, edi )
	.endif
	ret

Install ENDP

pragma_init Install, 30

	END
