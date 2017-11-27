; STRTODW.ASM--
; Copyright (C) 2015 Doszip Developers

include time.inc
include stdlib.inc

.code

strtodw PROC _CType PUBLIC USES di string:DWORD
	push	si
	push	bx
	mov	si,WORD PTR string+2
	mov	di,WORD PTR string
	invoke	atol,string
	test	al,al
	jz	strtodw_end
	push	ax
	mov	es,si
    strtodw_00:
	inc	di
	mov	al,es:[di]
	cmp	al,'0'
	jb	strtodw_01
	cmp	al,'9'
	jna	strtodw_00
    strtodw_01:
	inc	di
	invoke	atol,si::di
	push	ax
	mov	es,si
    strtodw_02:
	inc	di
	mov	al,es:[di]
	cmp	al,'0'
	jb	strtodw_03
	cmp	al,'9'
	jna	strtodw_02
    strtodw_03:
	push	si
	mov	si,es:[di]
	inc	di
	push	di
	call	atol
	mov	dx,1900
	cmp	ax,dx
	ja	strtodw_05
	cmp	ax,80
	jae	strtodw_04
	add	dx,100
    strtodw_04:
	add	ax,dx
    strtodw_05:
	sub	ax,DT_BASEYEAR
	pop	cx
	pop	dx
	mov	bx,si
	cmp	bl,'/'	; mm/dd/yy | yyyy
	je	strtodw_06
	xchg	cx,dx
    strtodw_06:
	shl	ax,9
	shl	dx,5
	or	ax,dx
	or	ax,cx
    strtodw_end:
	pop	bx
	pop	si
	ret
strtodw ENDP

	END
