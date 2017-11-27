; WCPBUTT.ASM--
; Copyright (C) 2015 Doszip Developers

include conio.inc

	.code

wcpbutt PROC _CType PUBLIC USES si di bx wp:DWORD,
	l:size_t, x:size_t, string:DWORD
	cld
	push	ds
	mov	cx,x
	mov	ah,at_background[B_PushButt]
	or	ah,at_foreground[F_Title]
	mov	al,' '
	les	di,wp
	mov	bx,di
	mov	dx,di
	rep	stosw
	mov	ax,es:[di]
	mov	al,'Ü'
	and	ah,11110000B
	or	ah,at_foreground[F_PBShade]
	stosw
	add	dx,l
	add	dx,l
	add	dx,2
	mov	di,dx
	mov	cx,x
	mov	al,'ß'
	rep	stosw
	mov	ah,at_background[B_PushButt]
	or	ah,at_foreground[F_TitleKey]
	lds	si,string
	mov	di,bx
	add	di,4
    wcpbutt_loop:
	lodsb
	or	al,al
	jz	wcpbutt_end
	cmp	al,'&'
	jz	wcpbutt_01
	stosb
	inc	di
	jmp	wcpbutt_loop
    wcpbutt_01:
	lodsb
	or	al,al
	jz	wcpbutt_end
	stosw
	jmp	wcpbutt_loop
    wcpbutt_end:
	lodm	wp
	pop	ds
	ret
wcpbutt ENDP

	END
