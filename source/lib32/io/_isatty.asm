; _ISATTY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

	.code

_isatty PROC handle:SINT
	mov	eax,handle
	mov	al,_osfile[eax]
	and	eax,FH_DEVICE
	ret
_isatty ENDP

	END
