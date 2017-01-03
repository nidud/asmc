; FGETC.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

fgetc	PROC _CType PUBLIC fp:DWORD
	les	bx,fp
	dec	es:[bx].S_FILE.iob_cnt
	jl	fgetc_01
	inc	WORD PTR es:[bx].S_FILE.iob_bp
	les	bx,es:[bx]
	dec	bx
	mov	al,es:[bx]
	mov	ah,0
    fgetc_00:
	ret
    fgetc_01:
	invoke	_filebuf,fp
	jmp	fgetc_00
fgetc	ENDP

	END
