
;--- test jwasm -mz option
;--- segments _DATA1, _DATA3, _BSS and STACK in a group
;--- bug until jwasm v2.12

	.286

_TEXT segment word public 'CODE'
_TEXT ends
_DATA1 segment para public 'DATA'
ditem1 db 16 dup ('1')
_DATA1 ends
_DATA2 segment para public 'DATA'
ditem2 db 16 dup ('2')
_DATA2 ends
_DATA3 segment para public 'DATA'
ditem3 db 16 dup ('3')
_DATA3 ends
_DATA4 segment para public 'DATA'
ditem4 db 16 dup ('4')
_DATA4 ends
_BSS   segment para public 'BSS'
ditem5 db 16 dup (?)
_BSS   ends

GROUP1 group _DATA1, _DATA3, _BSS, STACK

_TEXT segment

	dw seg ditem1, seg ditem2, seg ditem3, seg ditem4, seg ditem5
start:
	mov ax,GROUP1
	mov ds,ax
	mov ax,offset ditem1
	mov ax,offset ditem2
	mov ax,offset ditem3
	mov ax,offset ditem4
	mov ax,offset ditem5
	push ds
	pop ss
	mov sp,offset stackbottom
	mov ax,4c00h
	int 21h

_TEXT ends

STACK segment para stack 'STACK'
	db 100h dup (?)
stackbottom label near
STACK ends

	end start
