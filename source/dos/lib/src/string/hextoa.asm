; HEXTOA.ASM--
; Copyright (C) 2015 Doszip Developers

include string.inc

	.code

hextoa	PROC _CType PUBLIC USES si di string:PTR BYTE
	les di,string
	mov  si,di
	.repeat
	    mov ax,[si]
	    inc si
	    .continue .if al == ' '
	    inc si
	    mov dl,ah
	    .break .if !al
	    sub ax,'00'
	    .if al > 9
		sub al,7
	    .endif
	    shl al,4
	    .if ah > 9
		sub ah,7
	    .endif
	    or	ah,al
	    mov es:[di],ah
	    inc di
	.until !dl
	sub  al,al
	mov  es:[di],al
	lodm string
	ret
hextoa ENDP

	END
