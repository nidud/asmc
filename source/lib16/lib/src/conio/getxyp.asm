; GETXYP.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

.code

getxyp	PROC _CType PUBLIC x:WORD, y:WORD
	mov	al,BYTE PTR x
	mov	ah,BYTE PTR y
	call	__getxyp
	ret
getxyp	ENDP

	END
