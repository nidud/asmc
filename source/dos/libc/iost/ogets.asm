; OGETS.ASM--
; Copyright (C) 2015 Doszip Developers

include iost.inc
include io.inc
include stdio.inc

	.code

ogetl	PROC _CType PUBLIC filename:DWORD, buffer:DWORD, bsize:size_t
	mov WORD PTR STDI.ios_bp+2,ds
	mov WORD PTR STDI.ios_bp,offset _bufin
	mov STDI.ios_size,1000h
	mov STDI.ios_flag,IO_STRINGB
	mov ax,bsize
	mov STDI.ios_l,ax
	mov STDI.ios_c,0
	mov STDI.ios_i,0
	movmx STDI.ios_bb,buffer
	.if osopen(filename,0,M_RDONLY,A_OPEN) != -1
	    mov STDI.ios_file,ax
	.else
	    sub ax,ax
	.endif
	test ax,ax
	ret
ogetl	ENDP

ogets	PROC _CType PUBLIC
local	p:DWORD
	movmx	p,STDI.ios_bb
	mov	cx,STDI.ios_l
	sub	cx,2
	call	ogetc
	jz	ogets_end
      @@:
	cmp	al,0Dh
	je	ogets_0Dh
	cmp	al,0Ah
	je	ogets_eol
	test	al,al
	jz	ogets_end
	les	bx,p
	mov	es:[bx],al
	inc	WORD PTR p
	dec	cx
	jz	ogets_eol
	call	ogetc
	jnz	@B
    ogets_eol:
	inc	al
	jmp	ogets_end
    ogets_0Dh:
	call	ogetc
    ogets_end:
	les bx,p
	mov BYTE PTR es:[bx],0
	.if !ZERO?
	    lodm STDI.ios_bb
	.else
	    sub ax,ax
	    cwd
	.endif
	ret
ogets	ENDP

	END


