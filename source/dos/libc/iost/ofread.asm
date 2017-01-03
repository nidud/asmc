; OFREAD.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include string.inc
ifdef __TE__
include conio.inc
include tinfo.inc
tiofread PROTO
endif
ifdef __MEMVIEW__
	extrn tvmem_size: DWORD
	extrn tvmem_offs: DWORD
endif
ifdef __ZIP__
	extrn odecrypt: near
endif

	.data
	oupdate p? 0
PUBLIC	oupdate

	.code

ofread	PROC _CType PUBLIC USES si di
	mov	si,STDI.ios_flag
  ifdef __MEMVIEW__
	test	si,IO_MEMREAD
	jnz	ofread_memory
  endif
  ifdef __TE__
	test	si,IO_LINEBUF
	jnz	ofread_linebuf
  endif
	mov	di,STDI.ios_c
	sub	di,STDI.ios_i
	jnz	ofread_copy
    ofread_read:
	xor	ax,ax
	mov	STDI.ios_i,ax
	mov	STDI.ios_c,di
	mov	cx,STDI.ios_size
	sub	cx,di
	lodm	STDI.ios_bp
	add	ax,di
	invoke	osread,STDI.ios_file,dx::ax,cx
	add	STDI.ios_c,ax
	add	ax,di
	jz	ofread_end
	and	si,IO_UPDTOTAL or IO_USECRC or IO_USEUPD or IO_CRYPT
	jnz	ofread_user
    ofread_end:
	test	ax,ax
	ret
  ifdef __MEMVIEW__
    ofread_memory:
	call	iomemread
	jmp	ofread_end
  endif
  ifdef __TE__
    ofread_linebuf:
	call	tiofread
	jmp	ofread_end
  endif
    ofread_user:
  ifdef __ZIP__
	test	si,IO_CRYPT
	jz	@F
	call	odecrypt
    @@:
  endif
	test	si,IO_UPDTOTAL
	jz	ofread_crc
	add	WORD PTR STDI.ios_total,ax
	adc	WORD PTR STDI.ios_total+2,0
    ofread_crc:
	test	si,IO_USECRC
	jz	ofread_progress
	mov	dx,di
	mov	si,offset STDI
	call	oupdcrc
	mov	si,STDI.ios_flag
    ofread_progress:
	test	si,IO_USEUPD
	jz	ofread_end
      ifdef __CDECL__
	push	0
	push	ax
      else
	push	ax
	push	0
      endif
	call	oupdate
	dec	ax
	pop	ax
	jnz	ofread_error
	jmp	ofread_end
    ofread_copy:
	cmp	di,STDI.ios_c
	je	ofread_eof
	lodm	STDI.ios_bp
	add	ax,STDI.ios_i
	invoke	memcpy,STDI.ios_bp,dx::ax,di
	jmp	ofread_read
    ofread_error:
	call	osmaperr
	or	STDI.ios_flag,IO_ERROR
    ofread_eof:
	xor	ax,ax
	jmp	ofread_end
ofread	ENDP

ifdef __MEMVIEW__

iomemread PROC PRIVATE
  ifdef __3__
	mov	eax,tvmem_size
	cmp	eax,STDI.ios_offset
	jbe	iomemread_02
	mov	eax,STDI.ios_offset
	push	STDI.ios_bp
	mov	dx,ax
	and	dx,000Fh
	and	al,0F0h
	shl	eax,12
	mov	ax,dx
	push	eax
	mov	ecx,STDI.ios_offset
	xor	eax,eax
	mov	STDI.ios_i,ax
	cmp	ax,STDI.ios_c
	mov	ax,STDI.ios_size
	mov	STDI.ios_c,ax
	jz	@F
	add	ecx,eax
	cmp	ecx,tvmem_size
	jbe	@F
	sub	ecx,eax
	mov	eax,tvmem_size
	sub	eax,ecx
	mov	STDI.ios_c,ax
	add	ecx,eax
      @@:
	mov	STDI.ios_offset,ecx
	push	STDI.ios_c
	call	memcpy
	mov	ax,1
	ret
    iomemread_02:
	mov	STDI.ios_offset,eax
  else
	lodm	tvmem_size
	cmp	dx,WORD PTR STDI.ios_offset+2
	jne	@F
	cmp	ax,WORD PTR STDI.ios_offset
      @@:
	jbe	iomemread_02
	pushm	STDI.ios_bp
	lodm	STDI.ios_offset
	mov	bx,ax
	and	bx,000Fh
	shl	dx,12
	shr	ax,4
	or	dx,ax
	push	dx
	push	bx
	xor	ax,ax
	mov	STDI.ios_i,ax
	cmp	ax,STDI.ios_c
	mov	dx,WORD PTR STDI.ios_offset+2
	mov	cx,WORD PTR STDI.ios_offset
	mov	ax,STDI.ios_size
	mov	STDI.ios_c,ax
	jz	@F
	add	cx,ax
	adc	dx,0
	cmp	dx,WORD PTR tvmem_size+2
	jbe	@F
	mov	dx,WORD PTR STDI.ios_offset+2
	mov	cx,WORD PTR STDI.ios_offset
	mov	ax,WORD PTR tvmem_size
	mov	bx,WORD PTR tvmem_size+2
	sub	ax,cx
	sbb	bx,dx
	mov	STDI.ios_c,ax
	add	cx,ax
	adc	dx,bx
      @@:
	mov	WORD PTR STDI.ios_offset,cx
	mov	WORD PTR STDI.ios_offset+2,dx
	push	STDI.ios_c
	call	memcpy
	mov	ax,1
	ret
    iomemread_02:
	stom	STDI.ios_offset
  endif
	xor	ax,ax
	mov	STDI.ios_i,ax
	mov	STDI.ios_c,ax
	ret
iomemread ENDP

endif

	END
