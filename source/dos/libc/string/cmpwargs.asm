; CMPWARGS.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

cmpwargs PROC _CType PUBLIC USES di filep:PTR BYTE, maskp:PTR BYTE
	les di,maskp
	.repeat
	    .if strchr(es::di,' ')
		mov di,ax
		mov BYTE PTR es:[di],0
		invoke cmpwarg,filep,dx::ax
		mov BYTE PTR es:[di],' '
		inc di
	    .else
		invoke cmpwarg,filep,es::di
		.break
	    .endif
	.until ax
	ret
cmpwargs ENDP

	END
