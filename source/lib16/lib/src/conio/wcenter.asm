; WCENTER.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

wcenter PROC _CType PUBLIC USES ax cx dx si di wp:DWORD, l:size_t, string:DWORD
	push ds
	push es
	invoke wcpath,wp,l,string
	.if cx
	    les di,wp
	    lds si,string
	    mov si,dx
	    .if di == ax
		mov ax,l
		sub ax,cx
		and al,not 1
		add di,ax
	    .else
		mov di,ax
	    .endif
	    .repeat
		movsb
		inc di
	    .untilcxz
	.endif
	pop es
	pop ds
	ret
wcenter ENDP

	END
