; SETARGV.ASM--
; Copyright (C) 2015 Doszip Developers

include stdlib.inc
include string.inc
include alloc.inc

	PUBLIC	_argc
	PUBLIC	_argv

	.data
	_argc	dw ?
	_argv	dd ?

	__setargv__ label WORD
	PUBLIC	__setargv__

	_ip	dw ?
	_si	dw ?
	_di	dw ?

	extrn	_psp:WORD
	extrn	envlen:WORD
	extrn	envseg:WORD
	extrn	C0_argc:WORD
	extrn	C0_argv:DWORD

	.code

setargv_abort:
	jmp	abort

setargv:
	pop	ax		; return adress - only 2 byte on stack!!
	mov	_ip,ax
	mov	_si,si		; save SI and DI
	mov	_di,di
	mov	bp,_psp		; command line at _psp[0080]
	mov	es,bp
	mov	si,0080h
	sub	bx,bx
	cld?
	mov	bl,es:[si]	; BX to length of command line + 1
	inc	bx
	inc	si
	mov	dx,si
	mov	si,envlen	; program name - _argv[0]
	add	si,2
	mov	es,envseg
	mov	di,si
	mov	cx,007Fh
	xor	ax,ax
	repnz	scasb
	test	cx,cx
	jz	setargv_abort
	xor	cl,7Fh
	push	ax		; set end of buffer to 0
	mov	ax,cx		; total size: command + program
	add	ax,bx
	inc	ax
	and	ax,not 1
	mov	di,sp		; create buffer
	sub	di,ax
	jb	setargv_abort
	mov	sp,di
	push	es		; DS to envseg
	pop	ds
	push	ss		; ES to SS
	pop	es
	dec	cx
	rep	movsb		; copy .EXE name to stack
	sub	ax,ax
	stosb			; parse command line to args..
	mov	ds,bp		; DS to _psp
	xchg	dx,si		; SI to 0081
	xchg	cx,bx		; CX to size command line, BX to 0
	mov	dx,ax		; DX to 0
	inc	bx		; BX (_argc) to 1
	dec	cx
	jz	setargv_end
    setargv_loop:
	lodsb			; find first char
	cmp	al,' '		; space ?
	je	setargv_loop
	cmp	al,9		; tab ?
	je	setargv_loop
	cmp	al,0Dh
	je	setargv_break
	dec	si
	inc	bx		; _argc++
	mov	ah,' '		; assume ' ' as arg seperator
	mov	dl,ah
	lodsb			; first char
	cmp	al,'"'		; quote ?
	jne	@F
	mov	ah,al
	mov	dl,ah		; assume '"' as arg seperator
	lodsb
      @@:
	cmp	al,0Dh
	je	setargv_break
	stosb			; save char
	dec	cx
	jz	setargv_break	; end of command line ?
	lodsb
	.if al == '"' && al != ah
	    mov ah,al		; -arg"quoted text in argument"
	    jmp @B		; continue using '"' as arg seperator
	.endif
	cmp	al,ah		; arg loop..
	jne	@B
	cmp	ah,dl		; al == '"' or ' '
	mov	ah,dl		; if '"' then continue using ' '
	jne	@B
      @@:
	mov	al,0		; break if 0?
	cmp	[si],al
	je	setargv_break
	stosb
	dec	cx
	jnz	setargv_loop	; next argument
    setargv_break:
	sub	al,al
	stosb			; terminate last arg
    setargv_end:
	mov	ax,sp
	mov	cx,di
	sub	cx,ax
	push	ss		; restore DS
	pop	ds
	mov	_argc,bx	; set _argc
	mov	C0_argc,bx	; set C0_argc
	inc	bx
	add	bx,bx
	add	bx,bx
	mov	si,ax
	mov	bp,ax
	sub	bp,bx
	jb	setargv_abort
	mov	sp,bp
	mov	WORD PTR _argv,bp
	mov	WORD PTR _argv+2,ss
	mov	WORD PTR C0_argv,bp
	mov	WORD PTR C0_argv+2,ss
    setargv_06:
	test	cx,cx
	jz	setargv_08
	mov	[bp],si
	mov	[bp+2],ss
	add	bp,4
    setargv_07:
	lodsb
	test	al,al
	loopnz	setargv_07
	jz	setargv_06
    setargv_08:
	xor	ax,ax
	mov	[bp],ax
	mov	[bp+2],ax
	mov	si,_si
	mov	di,_di
	jmp	_ip
pragma_init setargv, 3

	END
