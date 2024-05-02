
;--- test TYPE with type coercions

	.286
	.model tiny
	.dosseg

UINT typedef DWORD

S1 struct
	dd ?
S1 ends

U1 union
	db ?
	dw ?
	dd ?
U1 ends

R1 record reserved:31,bit0:1

	.data
vd1	dd ?
vd2	UINT ?
vd3 S1 <>
vd4 U1 <>
vd5 R1 <>
	.code

	mov ax,TYPE vd1
	mov ax,TYPE (WORD ptr vd1)
	mov ax,TYPE vd2
	mov ax,TYPE (WORD ptr vd2)
	mov ax,TYPE vd3
	mov ax,TYPE (WORD ptr vd3)
	mov ax,TYPE vd4
	mov ax,TYPE (WORD ptr vd4)
	mov ax,TYPE vd5
	mov ax,TYPE (WORD ptr vd5)
	mov ax,TYPE DWORD
	mov ax,TYPE (WORD ptr DWORD)
	mov ax,TYPE UINT
	mov ax,TYPE (WORD ptr UINT)
	mov ax,TYPE S1
	mov ax,TYPE (WORD ptr S1)
	mov ax,TYPE U1
	mov ax,TYPE (WORD ptr U1)
	mov ax,TYPE R1
	mov ax,TYPE (WORD ptr R1)

	assume bx:ptr WORD
	mov ax,TYPE [bx]
	assume bx:ptr UINT
	mov ax,TYPE [bx]
	assume bx:ptr S1
	mov ax,TYPE [bx]

	end
