
;--- v2.19: in pass one, don't assume a (near) jmp to (or call) a label in another segment 
;--- is an error - it might be "fixed" by a GROUP directive.

	.286
	.dosseg
	option casemap:none

STACK segment para stack 'STACK'
	org 100h
STACK ends

_TEXT1 segment word public 'CODE'
	jmp lbl1
lbl2:
	ret
start:
	mov ah,4Ch
	int 21h
_TEXT1 ends

_TEXT2 segment word public 'CODE'
lbl1:
	jmp lbl2
_TEXT2 ends

CODE group _TEXT1, _TEXT2

	END start
