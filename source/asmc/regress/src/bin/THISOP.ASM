
;--- .THIS operator

	.286
	.model small
	option casemap:none

S1 struct
	dw ?
f1  equ THIS byte ;is accepted, but creates a text macro only
f2  equ THIS word
	db ?
S1 ends

if 0
;--- using .THIS outside of a segment block is invalid!
wb	equ THIS byte
ww	equ THIS word
wd	equ THIS dword
wn	equ THIS near
endif

	.data

S2 struct
	dw ?
f3  equ THIS byte ;is accepted, but creates a text macro only
f4  equ THIS word
	db ?
S2 ends

xb	equ THIS byte
	db 1,2,3
xw	equ THIS word
	db 1,2,3
xd	equ THIS dword
	db 1,2,3
xn	equ THIS near

	.code

vb	equ THIS byte
	db 5,6,7
vw	equ THIS word
	db 5,6,7
vd	equ THIS dword
	db 5,6,7
vn	equ THIS near

	mov al,xb
	mov ax,xw
	mov ax,xn
	mov ax,THIS word
	mov bx,THIS word
	mov bx,THIS near

	end
