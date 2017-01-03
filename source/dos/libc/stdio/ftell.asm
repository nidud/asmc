; FTELL.ASM--
; Copyright (C) 2015 Doszip Developers

include stdio.inc
include io.inc
include errno.inc

	.code

ftell	PROC _CType PUBLIC USES bx si fp:DWORD
local	rdcnt:size_t, offs:size_t, p:DWORD, max:size_t
	les	bx,fp
	mov	si,es:[bx].S_FILE.iob_file
	sub	ax,ax
	cmp	es:[bx].S_FILE.iob_cnt,ax
	jge	ftell_00
	mov	es:[bx].S_FILE.iob_cnt,ax
    ftell_00:
	invoke	lseek,si,0,SEEK_CUR
	les	bx,fp
	cmp	dh,0
	jnl	ftell_02
    ftell_01:
	mov	ax,-1
	cwd
	jmp	ftell_END
    ftell_02:
	mov	cx,es:[bx].S_FILE.iob_flag
	test	cx,_IOMYBUF or _IOYOURBUF
	jnz	ftell_03
	sub	ax,es:[bx].S_FILE.iob_cnt
	jmp	ftell_END
    ftell_03:
	xor	dx,dx
	mov	ax,WORD PTR es:[bx].S_FILE.iob_bp
	sub	ax,WORD PTR es:[bx].S_FILE.iob_base
	stom	offs
	test	cx,_IOWRT or _IOREAD
	jnz	ftell_04
	test	cx,_IORW
	jnz	ftell_04
	mov	errno,EINVAL
	jmp	ftell_01
    ftell_04:
	mov	si,ax
	or	si,dx
	jnz	ftell_05
	lodm	offs
	jmp	ftell_END
    ftell_05:
	test	cx,_IOREAD
	jz	ftell_07
	cmp	es:[bx].S_FILE.iob_cnt,0
	jne	ftell_06
	sub	ax,ax
	mov	dx,ax
	jmp	ftell_07
    ftell_06:
	mov	si,ax
	mov	ax,WORD PTR es:[bx].S_FILE.iob_bp
	sub	ax,WORD PTR es:[bx].S_FILE.iob_base
	add	ax,es:[bx].S_FILE.iob_cnt
	xchg	ax,si
	sub	ax,si
	sbb	dx,0
    ftell_07:
	add	ax,WORD PTR offs
	adc	dx,WORD PTR offs+2
    ftell_END:
	ret
ftell	ENDP

	END
