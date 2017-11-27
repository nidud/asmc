; OSFTYPE.ASM--
; Copyright (C) 2015 Doszip Developers

include io.inc

	.code

osfiletype PROC _CType PUBLIC handle:size_t
	mov	ax,4400h	; GET DEVICE INFORMATION
	mov	bx,handle
	int	21h
	jc	osfiletype_error
	test	dl,80h		; set if device
	jz	osfiletype_file
	mov	ax,2		; return 2 if device
	jmp	osfiletype_end
    osfiletype_file:
	mov	ax,dx
	and	ax,8000h	; set if file is remote
	jnz	osfiletype_end	; return 8000h if file is remote
	inc	ax		; return 1 if disk file
    osfiletype_end:
	ret
    osfiletype_error:
	call	osmaperr
	xor	ax,ax		; return 0 and ZF
	jmp	osfiletype_end
osfiletype ENDP

	END
