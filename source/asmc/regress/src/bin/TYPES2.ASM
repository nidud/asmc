
;--- test TYPEOF with type coercions

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

	mov ax,typeof vd1
	mov ax,typeof (WORD ptr vd1)
	mov ax,typeof vd2
	mov ax,typeof (WORD ptr vd2)
	mov ax,typeof vd3
	mov ax,typeof (WORD ptr vd3)
	mov ax,typeof vd4
	mov ax,typeof (WORD ptr vd4)
	mov ax,typeof vd5
	mov ax,typeof (WORD ptr vd5)
	mov ax,typeof DWORD
	mov ax,typeof (WORD ptr DWORD)
	mov ax,typeof UINT
	mov ax,typeof (WORD ptr UINT)
	mov ax,typeof S1
	mov ax,typeof (WORD ptr S1)
	mov ax,typeof U1
	mov ax,typeof (WORD ptr U1)
	mov ax,typeof R1
	mov ax,typeof (WORD ptr R1)

	assume bx:ptr WORD
	mov ax,typeof [bx]
	assume bx:ptr UINT
	mov ax,typeof [bx]
	assume bx:ptr S1
	mov ax,typeof [bx]

	end
