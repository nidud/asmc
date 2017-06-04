; CMEXIT.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

include doszip.inc
include consx.inc

	.code

cmexit	PROC
	.if config.c_cflag & _C_CONFEXIT
		.if !rsmodal( IDD_DZExit )
			ret
		.endif
	.endif
cmexit	ENDP

cmquit	PROC
	xor	eax,eax
	mov	mainswitch,eax
	inc	eax
	mov	dzexitcode,eax
	ret
cmquit	ENDP

	END
