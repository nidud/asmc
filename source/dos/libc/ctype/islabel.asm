; ISLABEL.ASM--
; Copyright (C) 2015 Doszip Developers

include ctype.inc

	.code

islabel PROC PUBLIC USES ax
	call	getctype
	test	ah,_UPPER or _LOWER or _DIGIT
	jnz	islabel_end
	cmp	al,'_'
	je	islabel_ok
    islabel_no:
	xor	al,al
	jmp	islabel_end
    islabel_ok:
	test	al,al
    islabel_end:
	ret
islabel ENDP

	END

