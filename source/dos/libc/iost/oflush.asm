; OFLUSH.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include errno.inc
include conio.inc
ifdef __TE__
include clip.inc
endif
	.code

oflush	PROC _CType PUBLIC USES si
	mov	si,offset STDO
	mov	ax,[si].S_IOST.ios_i
	test	ax,ax
	jz	oflush_01
	mov	dx,[si].S_IOST.ios_flag
	test	dx,IO_USECRC
	jnz	oflush_crc
  ifdef __TE__
	test	dx,IO_CLIPBOARD
	jnz	oflush_clipcopy
  endif
    oflush_write:
	invoke	oswrite,[si].S_IOST.ios_file,[si].S_IOST.ios_bp,[si].S_IOST.ios_i
    oflush_clip:
	cmp	ax,[si].S_IOST.ios_i
	jne	oflush_error
	add	WORD PTR [si].S_IOST.ios_total,ax
	adc	WORD PTR [si].S_IOST.ios_total[2],0
	sub	ax,ax
	mov	[si].S_IOST.ios_c,ax
	mov	[si].S_IOST.ios_i,ax
	test	[si].S_IOST.ios_flag,IO_USEUPD
	jnz	oflush_update
    oflush_01:
	inc	ax
    oflush_end:
	ret
    oflush_update:
	inc	ax
	push	ax
	call	oupdate
	dec	ax
	jmp	oflush_01
    oflush_error:
	or	[si].S_IOST.ios_flag,IO_ERROR
	xor	ax,ax
	jmp	oflush_end
    oflush_crc:
	xor	dx,dx
	call	oupdcrc
	jmp	oflush_write
  ifdef __TE__
    oflush_clipcopy:
	invoke	ClipboardCopy,[si].S_IOST.ios_bp,ax
	xor	ax,ax
	jmp	oflush_end
  endif
oflush	ENDP

	END
