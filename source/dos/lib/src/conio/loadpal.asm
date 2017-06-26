; LOADPAL.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

loadpal PROC _CType PUBLIC USES si di pal:PTR BYTE
	sub si,si
	.repeat
	    les di,pal
	    add di,si
	    sub ax,ax
	    mov al,es:[di]
	    invoke setpal,ax,si
	    inc si
	.until si == 16
	ret
loadpal ENDP

	END
