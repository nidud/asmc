; STUB.ASM--
; Copyright (c) 2016 Doszip Developers

	.186
	.model	small
	.stack	128

include version.inc

	.code

start:
	call	print

	db	10
	db	"Doszip Macro Assembler Version ", ASMC_VERSSTR
%	db	" &@Date",13,10
	db	"This is a Windows NT character-mode executable",13,10,'$'

print:
	mov	ax,cs
	mov	ds,ax
	mov	ah,9
	pop	dx
	int	21h
	mov	ax,4C00h
	int	21h
	end	start
