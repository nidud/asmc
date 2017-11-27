; DWTOLSTR.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc

.code

dwtolstr PROC _CType PUBLIC USES cx string:DWORD, date:size_t
	push	bx
	les	bx,string
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
	jb	dwtolstr_19
	sub	ax,2000
	mov	WORD PTR es:[bx],'02'
    dwtolstr_end:
	add	bx,2
	call	putedxal
	mov	es:[bx],ch
	mov	dx,es
	mov	ax,WORD PTR string
	pop	bx
	ret
    dwtolstr_19:
	sub	ax,1900
	mov	WORD PTR es:[bx],'91'
	jmp	dwtolstr_end
dwtolstr ENDP

	END
