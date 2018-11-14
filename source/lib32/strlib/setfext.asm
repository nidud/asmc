; SETFEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include strlib.inc

	.code

setfext PROC path:LPSTR, ext:LPSTR
	strext( path )
	test	eax,eax
	jz	@F
	mov	byte ptr [eax],0
@@:
	strcat( path, ext )
	ret
setfext ENDP

	END
