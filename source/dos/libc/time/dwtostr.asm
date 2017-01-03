; DWTOSTR.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

dwtostr PROC _CType PUBLIC USES cx buf:DWORD, date:size_t
	push	bx
	les	bx,buf
	mov	cx,'.'
	mov	ax,date
	and	ax,001Fh
	call	putedxal
	mov	es:[bx],cl
	inc	bx
	mov	ax,date
	shr	ax,5
	and	ax,000Fh
	call	putedxal
	mov	es:[bx],cl
	inc	bx
	mov	ax,date
	shr	ax,9
	add	ax,DT_BASEYEAR
	cmp	ax,2000
	jb	dwtostr_01
	sub	ax,2000
    dwtostr_00:
	call	putedxal
	mov	es:[bx],ch
	mov	dx,es
	mov	ax,WORD PTR buf
	pop	bx
	ret
    dwtostr_01:
	sub	ax,1900
	jmp	dwtostr_00
dwtostr ENDP

	END
