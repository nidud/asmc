; FGETS.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc

	.code

fgets PROC _CType PUBLIC USES di buf:DWORD, count:size_t, fp:DWORD
	push	si
	mov	ax,count
	cmp	ax,0
	jle	fgets_nul
	les	di,buf
	mov	si,es
	dec	ax
	jz	fgets_ret
    fgets_loop:
	invoke	fgetc,fp
	mov	es,si
	cmp	ax,-1
	je	fgets_eof
	mov	es:[di],al
	inc	di
	cmp	al,10
	jne	fgets_loop
    fgets_ret:
	mov	BYTE PTR es:[di],0
	lodm	buf
    fgets_end:
	pop	si
	ret
    fgets_eof:
	cmp	di,WORD PTR buf
	jne	fgets_ret
    fgets_nul:
	sub	ax,ax
	mov	dx,ax
	jmp	fgets_end
fgets	ENDP

	END
