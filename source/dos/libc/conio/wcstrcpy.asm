; WCSTRCPY.ASM--
; Copyright (C) 2015 Doszip Developers
include conio.inc
include string.inc

	.code

wcstrcpy PROC _CType PUBLIC USES si di cp:DWORD, wc:DWORD, count:size_t
	push	ds
	les	di,cp
	lds	si,wc
	mov	cx,count
	mov	dx,es
	cld?
    wcstrcpy_start:
	test	cx,cx
	jz	wcstrcpy_end
	dec	cx
	lodsw
	cmp	al,' '
	jbe	wcstrcpy_start
	cmp	al,176
	ja	wcstrcpy_start
	sub	si,2
	test	cx,cx
	jz	wcstrcpy_end
    wcstrcpy_loop:
	lodsw
	cmp	al,176
	ja	wcstrcpy_end
	and	ah,0Fh
	cmp	ah,13
	jb	wcstrcpy_cpy
	mov	ah,al
	mov	al,'&'
	stosb
	mov	al,ah
    wcstrcpy_cpy:
	stosb
	dec	cx
	jnz	wcstrcpy_loop
    wcstrcpy_end:
	mov	BYTE PTR es:[di],0
	invoke	strtrim,cp
	pop	ds
	ret
wcstrcpy ENDP

	END
