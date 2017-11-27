; FPUTC.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

fputc	PROC _CType PUBLIC USES bx char:size_t, fp:DWORD
	les	bx,fp
	dec	es:[bx].S_FILE.iob_cnt
	jl	fputc_flush
	inc	WORD PTR es:[bx].S_FILE.iob_bp
	les	bx,es:[bx].S_FILE.iob_bp
	mov	al,BYTE PTR char
	mov	es:[bx],al
	mov	ah,0
    fputc_end:
	ret
    fputc_flush:
	invoke	_flsbuf,char,fp
	jmp	fputc_end
fputc	ENDP

	END
