.xlist

cmprm	macro	src
local	@@
	cmp	dx,word ptr src+2
	jne	@@
	cmp	ax,word ptr src
	@@:
	endm

cmpmm	macro	des,src
ifdef __3__
	mov	eax,des
	cmp	eax,src
else
	lodm	des
	cmprm	src
endif
	endm

movmm	macro m1,m2
	lodm m2
	stom m1
	endm

movmw	macro m1,m2
	mov ax,word ptr m2
	mov word ptr m1,ax
	endm

incm	macro	src
ifndef __16__
	inc	dword ptr src
else
	add	word ptr src,1
	adc	word ptr src+2,0
endif
	endm

decm	macro	src
ifdef __3__
	dec	dword ptr src
else
	sub	word ptr src,1
	sbb	word ptr src+2,0
endif
	endm

.list
