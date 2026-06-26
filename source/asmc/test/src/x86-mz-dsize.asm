
;--- v2.16: use memory model's default distance for pointers to data 

	.286
	.model compact
	.stack 500h
	.dosseg
	.386

	.data

stringptrs label ptr byte	; this pointer has size 4 in model compact
	dd s1, s2

s1	db "abc",0
s2	db "def",0

fstr db "bx=%X [%ls]",10,0

	.code

;	include printf16.inc

start:
	mov ax, @data
	mov ds, ax
if @DataSize
	lds bx, stringptrs
else
	mov bx, stringptrs
endif
;	invoke printf, addr fstr, bx, ds::bx
	mov ax,4C00h
	int 21h

	END start
