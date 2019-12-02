; _PGMPATH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include crtl.inc

PUBLIC	_pgmpath

	.data
	_pgmpath LPSTR 0

	.code

Install proc private uses edi
local	path[256]

	lea edi,path
	strcpy( edi, _pgmptr )
	.if strfn( edi ) > edi

		mov byte ptr [eax-1],0
		strlen( edi )
		mov _pgmpath,malloc(addr [eax+1])
		strcpy( eax, edi )
	.endif
	ret

Install endp

.pragma init(Install, 30)

	END
