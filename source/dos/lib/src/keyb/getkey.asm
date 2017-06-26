; GETKEY.ASM--
; Copyright (C) 2015 Doszip Developers

include keyb.inc
include conio.inc

.data
keyboard dw 1

.code

InstallKeyboard:
	sub	ax,ax
	mov	es,ax
	mov	ah,12h		; GET EXTENDED SHIFT STATES
	int	16h		; (enh kbd support only)
	mov	bx,0417h	; 0040:0017 (keyshift)
	cmp	al,es:[bx]
	jne	@F
	mov	ah,80h
	xor	es:[bx],ah
	mov	ah,12h
	int	16h
	cmp	al,es:[bx]
	jne	@F
	mov	keyboard,1001h
      @@:
	test	console,CON_INT2F
	jz	@F
	and	console,not CON_INT2F
	mov	ax,1680h	; MS Windows, DPMI, various
	int	2Fh		; - RELEASE CURRENT VIRTUAL MACHINE TIME-SLICE
	test	al,al		; 00h if the call is supported
	jnz	@F		; 80h (unchanged) if the call is not supported
	or	console,CON_INT2F
      @@:
	ret

keystroke:
	mov	ax,keyboard	; 01h: CHECK FOR KEYSTROKE
	inc	ah		; 11h: CHECK FOR ENHANCED KEYSTROKE
	int	16h
	jz	keystroke_end	; ZF clear if keystroke available
	mov	ax,keyboard	; 00h: GET KEYSTROKE
	int	16h		; 10h: GET ENHANCED KEYSTROKE
	;-----------------------
	test	ah,ah		; Yury - 04 Apr 2012
	jz	@F		; - Russian letter 224 (0xE0) discarded
	cmp	al,0E0h
	jne	keystroke_end
	sub	al,al
      @@:
	test	ax,ax
	;------------------------
    keystroke_end:
	ret

getkey PROC _CType PUBLIC
	call	keystroke
	jnz	getkey_end
	test	console,CON_INT2F
	jz	getkey_nul
	mov	ax,1680h; added 05/05/2008 (bttr)
	int	2Fh	; RELEASE CURRENT VIRTUAL MACHINE TIME-SLICE
    getkey_nul:
	xor	ax,ax
    getkey_end:
	test	ax,ax
	ret
getkey ENDP

getesc PROC _CType PUBLIC
	call	keystroke
	jz	getesc_nul
	cmp	ax,011Bh	; ESC
	je	getesc_end
    getesc_nul:
	xor	ax,ax
    getesc_end:
	test	ax,ax
	ret
getesc ENDP

pragma_init InstallKeyboard, 7

	END
