; OSEEK.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
ifdef __TE__
include conio.inc
include tinfo.inc
include string.inc
tiseekst PROTO
endif
ifdef __MEMVIEW__
externdef tvmem_size: DWORD
externdef tvmem_offs: DWORD
endif
	.code

oseekst:
  ifdef __MEMVIEW__
	test	[si].S_IOST.ios_flag,IO_MEMREAD
	jz	@F
	cmp	cx,SEEK_CUR
	je	oseekst_fail
	cmp	cx,SEEK_END
	jne	oseekst_end
	lodm	tvmem_offs
	add	ax,WORD PTR tvmem_size
	adc	dx,WORD PTR tvmem_size+2
	jmp	oseekst_end
      @@:
  endif
  ifdef __TE__
	test	[si].S_IOST.ios_flag,IO_LINEBUF
	jz	@F
	jmp	tiseekst;oseekst_linebuf
      @@:
  endif
	cmp	cx,SEEK_CUR
	jne	@F
	test	dx,dx
	jnz	@F
	mov	dx,[si].S_IOST.ios_c
	sub	dx,[si].S_IOST.ios_i
	cmp	dx,ax
	mov	dx,0
	jb	@F
	add	[si].S_IOST.ios_i,ax
	ret
      @@:
	invoke	lseek,[si].S_IOST.ios_file,dx::ax,cx
	cmp	dx,-1
	jne	oseekst_end
	cmp	ax,-1
	je	oseekst_fail
    oseekst_end:
	stom	[si].S_IOST.ios_offset
	sub	ax,ax
	mov	[si].S_IOST.ios_i,ax
	mov	[si].S_IOST.ios_c,ax
	inc	ax
	ret
    oseekst_fail:
	sub	ax,ax
	ret
if 0
  ifdef __TE__
    oseekst_linebuf:
	push	dx
	mov	[si].S_IOST.ios_l,cx
	mov	[si].S_IOST.ios_c,0
	call	tiofread
	pop	ax
	jz	oseekst_fail
	cmp	[si].S_IOST.ios_c,ax
	ja	oseekst_linebuf_end
	inc	cx
	xor	dx,dx
	jmp	oseekst_linebuf
    oseekst_linebuf_end:
	mov	[si].S_IOST.ios_i,ax
	inc	ax
	ret
  endif
endif

oseekl	PROC _CType PUBLIC USES si offs:DWORD, from:size_t
	mov	si,offset STDI
	mov	cx,from
	lodm	offs
	call	oseekst
	ret
oseekl	ENDP

oseek	PROC _CType PUBLIC offs:DWORD, from:size_t
	invoke	oseekl,offs,from
	jz	@F
    ifdef __TE__
	test	STDI.ios_flag,IO_LINEBUF
	jnz	@F
    endif
	call	ofread
      @@:
	ret
oseek	ENDP

	END
