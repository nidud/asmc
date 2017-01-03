; RSOPEN.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc
include alloc.inc

rsunzipch PROTO
rsunzipat PROTO

.code

rsopen	PROC _CType PUBLIC USES di si idd:DWORD
local	result:size_t
	push	ds
	lds	si,idd
	mov	ax,[si+8]	; rc_rows * rc_cols
	mov	dx,ax
	mul	ah
	mov	WORD PTR idd,ax
	add	ax,ax		; WORD size
	mov	di,ax
	test	WORD PTR [si+2],_D_SHADE
	jz	rsopen_00
	add	dl,dh
	add	dl,dh
	mov	dh,0
	sub	dx,2
	add	di,dx
    rsopen_00:
	mov	ax,[si]
	invoke	malloc,ax
	mov	result,ax
	mov	es,dx
	mov	bx,di
	mov	di,ax
	mov	dx,ax
	mov	cx,[si]
	jz	rsopen_end
	sub	ax,ax
	shr	cx,1
	cld?
	rep	stosw
	mov	cx,dx
	mov	di,dx
	lodsw			; skip size
	; -- copy dialog
	lodsw			; .flag
	or	ax,_D_SETRC
	push	ax
	stosw			; .flag
	movsw			; .count + .index
	movsw
	movsw
	sub	ax,ax
	mov	al,BYTE PTR [si-6]
	inc	ax
	shl	ax,4		; * size of objects (16)
	add	ax,cx		; + adress
	stosw			; = .wp (off)
	mov	dx,ax
	mov	ax,es
	stosw			; .wp (seg)
	mov	ax,16+4
	stosw			; .object (off)
	mov	ax,es
	stosw			; .object (seg)
	; -- copy objects
	add	dx,bx		; end of wp = start of object alloc
	sub	bx,bx
	mov	bl,[si-6]
	inc	bx
	jmp	rsopen_04
    rsopen_01:
	movsw
	movsw
	movsw
	movsw
	sub	ax,ax
	mov	al,BYTE PTR [si-6]
	shl	ax,4		; * 16
	test	ax,ax
	jz	rsopen_02
	xchg	ax,dx		; offset of mem (.data)
	stosw
	add	dx,ax
	mov	ax,es
	stosw
	sub	ax,ax
	jmp	rsopen_03
    rsopen_02:
	stosw
	stosw
    rsopen_03:
	stosw
	stosw
    rsopen_04:
	dec	bx
	jnz	rsopen_01
	pop	ax
	push	di
	inc	di
	mov	cx,WORD PTR idd
	and	ax,_D_RESAT
	jz	rsopen_05
	call	rsunzipat
	jmp	rsopen_06
    rsopen_05:
	call	rsunzipch
    rsopen_06:
	pop	di
	mov	cx,WORD PTR idd
	call	rsunzipch
	mov	dx,es
	mov	ax,result
	test	ax,ax
    rsopen_end:
	pop	ds
	mov	bx,ax
	ret
rsopen	ENDP

	END
