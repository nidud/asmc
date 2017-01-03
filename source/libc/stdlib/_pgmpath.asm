include stdlib.inc
include string.inc
include alloc.inc
include crtl.inc

PUBLIC	_pgmpath
strpath proto :dword

	.data
	_pgmpath LPSTR 0

	.code

Install PROC PRIVATE
local	path[256]
	mov _pgmpath,salloc( strpath( strcpy( addr path, _pgmptr ) ) )
	ret
Install ENDP

pragma_init Install, 30

	END
