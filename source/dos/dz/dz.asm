; DZ.ASM--
; Copyright (C) 2016 Doszip Developers -- see LICENSE.TXT

	.186
	.model	small

include version.inc
include dz.inc

PROGRAMSIZE equ 1024

	.code

exec	label S_DZDS
start	PROC
	jmp	around
	db	10
copy	db	'The Doszip Commander Version ',VERSSTR,', '
	db	'Copyright (c) 1997-2016 Doszip Developers',13,10,13,10,'$'
errenv	db	'Environment invalid',13,10,'$'
around:
	mov	ax,cs
	mov	ds,ax
	ASSUME	DS:_TEXT
	mov	ah,9
	mov	dx,offset copy
	int	21h
	mov	si,offset exec
	mov	bx,002Ch
	mov	bp,es
	mov	ax,es:[bx]
	mov	exec.dz_envseg,ax
	mov	ax,3306h	; DOS 5+
	int	21h
	cmp	bl,7
	mov	bx,PROGRAMSIZE/16
	jne	@F
	add	bx,bx
     @@:
	mov	ah,4Ah
	int	21h
	mov	cl,4
	shl	bx,cl
	sub	bx,256
	mov	ax,cs
	mov	ss,ax
	mov	sp,bx
	mov	bx,exec.dz_envseg
	mov	es,bx
	xor	ax,ax
	mov	di,ax
	mov	cx,7FFFh
	cld
     @@:
	repnz	scasb
	test	cx,cx
	jz	errorlevel_10
	cmp	es:[di],al
	jne	@B
	or	ch,80h
	neg	cx
	jmp	init_vector
errorlevel_10:
	mov	dx,offset errenv
	mov	ah,9
	int	21h
	mov	ax,4C0Ah
	int	21h
init_vector:
	mov	ax,ds
	mov	vector+6,ax
	mov	vector+4,offset exec.dz_exeproc
	mov	exec.dz_fcb_0P[2],ax
	mov	exec.dz_fcb_1P[2],ax
	mov	exec.dz_fcb_0P,offset exec.dz_fcb_160
	mov	exec.dz_fcb_1P,offset exec.dz_fcb_161
	mov	exec.dz_command[2],ax
	mov	dx,ax
	mov	di,cx
	add	di,2
	mov	si,di
	mov	cx,-1
	xor	ax,ax
	repnz	scasb
	not	cx
	push	cx
	mov	es,dx
	mov	di,offset exec.dz_dzmain
	mov	ds,bx
	rep	movsb
	mov	ds,dx
	mov	es,dx
	mov	bx,di
	mov	di,offset exec.dz_fcb_160
	mov	si,offset exec.dz_dzmain
	mov	ax,2901h
	int	21h
	mov	ax,'OD'
	mov	[bx-4],ax
	mov	ax,'S'
	mov	[bx-2],ax
	mov	di,offset exec.dz_dzcommand
	mov	si,128
	mov	ds,bp
	mov	cx,128
	rep	movsb
	mov	ds,dx
	mov	ax,4300h
	mov	dx,offset exec.dz_dzmain
	int	21h
	pop	di
	jnc	file_found
file_not_found:
	mov	dx,offset cp_file_not_found
	mov	cx,15
	call	write
	mov	cx,di
	mov	dx,offset exec.dz_dzmain
	call	write
	mov	ax,2
	jmp	exit
write:	mov	ah,40h
	mov	bx,2
	int	21h
	ret
	db	13,10
%	db	'$Id: DZ.ASM &@Date',10
file_found:
	xor	ax,ax
	mov	vector+8,ax
	jmp	doszip
	db	13,10
	db	'DOS (errorlevel):',10
	db	' 2 '
cp_file_not_found label byte
	db	'File not found DZ.DOS',13,10
	db	' 5 Access',10
	db	' 8 Memory',10
	db	'10 Environment'
	org	SIZE S_DZDS - 14
	dw	0
	dw	0	; dz_errno
	dw	0	; dz_eflag
	dw	0	; dz_count
	dw	0A00h	; dz_exename
	dw	4F44h	; dz_oldintF1
	dw	3A53h
START	ENDP

doszip:
	mov	ax,35F1h
	int	21h
	mov	word ptr exec.dz_oldintF1,bx
	mov	word ptr exec.dz_oldintF1[2],es
	mov	ax,25F1h
	mov	dx,offset vector
	int	21h
	mov	exec.dz_exename,offset exec.dz_dzmain
	mov	exec.dz_command,offset exec.dz_dzcommand
execute:
	mov	ax,cs
	mov	es,ax
	mov	ds,ax
	mov	di,offset exec.dz_fcb_161
	mov	si,exec.dz_exename
	mov	ax,2901h
	int	21h
	mov	bx,offset exec.dz_envseg
	mov	dx,exec.dz_exename
	mov	ax,4B00h
	int	21h
	mov	dx,cs
	mov	ds,dx
	jc	execute_error
	xor	ax,ax
    execute_error:
	mov	si,ax
	mov	ax,4D00h
	int	21h
	mov	exec.dz_eflag,si
	mov	exec.dz_errno,ax
	cmp	exec.dz_exename,offset exec.dz_dzmain
	jne	doszip
	mov	di,ax
	mov	si,offset exec
	mov	ax,25F1h
	lds	dx,exec.dz_oldintF1
	int	21h
	mov	ax,cs
	mov	ds,ax
	mov	ax,di
	cmp	al,23
	jne	exit
	inc	exec.dz_count
	mov	exec.dz_exename,offset exec.dz_exeproc
	mov	exec.dz_command,offset exec.dz_execommand
	jmp	execute
exit:
	mov	ah,4Ch
	int	21h

vector	label word
	dd	495A440Ah
	dd	564A4A50h
	db	VERSSTR
	.stack	64
	end	start
