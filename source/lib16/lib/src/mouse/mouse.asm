; MOUSE.ASM--
; Copyright (C) 2015 Doszip Developers

include mouse.inc
ifdef __MOUSE__

MOUSEINT	equ 33h
OFFSETVECTOR	equ MOUSEINT*4

.code

__mouse db 0	; Installed
__mbool db 0	; Visible
__mflag db 0	; Mouse State

mousep	PROC _CType PUBLIC
	xor	ax,ax
	cmp	cs:[__mouse],al
	je	@F
	push	bx
	push	cx
	push	dx
	mov	al,6
	int	33h
	or	al,al
	pop	dx
	pop	cx
	pop	bx
      @@:
	ret
mousep	ENDP

mouseon PROC	_CType PUBLIC
	mov	ax,1
	cmp	al,cs:[__mbool]
	je	@F
	cmp	ah,cs:[__mouse]
	je	@F
	mov	cs:[__mbool],al
	int	33h
      @@:
	ret
mouseon ENDP

mouseoff PROC	_CType PUBLIC
	xor	ax,ax
	cmp	al,cs:[__mbool]
	jz	@F
	mov	cs:[__mbool],al
	mov	ax,2
	int	33h
      @@:
	ret
mouseoff ENDP

mousex	PROC	_CType PUBLIC
	push	bx
	push	cx
	push	dx
	xor	ax,ax
	cmp	al,cs:[__mouse]
	je	@F
	mov	al,3
	int	33h
	mov	ax,cx
	shr	ax,3
      @@:
	pop	dx
	pop	cx
	pop	bx
	ret
mousex	ENDP

mousey	PROC	_CType PUBLIC
	push	bx
	push	cx
	push	dx
	xor	ax,ax
	cmp	al,cs:[__mouse]
	je	@F
	mov	ax,3
	int	33h
	mov	ax,dx
	shr	ax,3
      @@:
	pop	dx
	pop	cx
	pop	bx
	ret
mousey	ENDP

mousehide PROC	_CType PUBLIC
	push	ax
	call	mouseoff
	shr	al,1
	mov	ah,cs:[__mflag]
	shl	ah,1
	or	al,ah
	mov	cs:[__mflag],al
	pop	ax
	ret
mousehide ENDP

mouseshow PROC	_CType PUBLIC
	push	ax
	mov	al,cs:[__mflag]
	shr	al,1
	mov	cs:[__mflag],al
	jnc	@F
	call	mouseon
      @@:
	pop	ax
	ret
mouseshow ENDP

mouseset PROC _CType PUBLIC
	call	mousehide
	mov	cs:[__mouse],al
	call	mouseshow
	ret
mouseset ENDP
if 0
mouseget PROC _CType PUBLIC
	mov	ah,cs:[__mouse]
	mov	al,cs:[__mbool]
	mov	dl,cs:[__mflag]
	ret
mouseget ENDP
endif
Install:
	xor	ax,ax
	mov	cs:[__mouse],al
	mov	es,ax
	cmp	ax,es:[OFFSETVECTOR+2]
	je	mouseinit_00
	les	bx,es:[OFFSETVECTOR]
	cmp	BYTE PTR es:[bx],0CFh
	je	mouseinit_00
	int	33h
	test	ax,ax
	jz	mouseinit_00
	inc	cs:[__mouse]
    mouseinit_00:
	ret

pragma_init Install,10

endif ; __MOUSE__

	END
