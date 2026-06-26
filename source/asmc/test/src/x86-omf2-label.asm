
;--- v2.19: for assembly time variables that define a label
;---        a wrong fixup was created if segment wasn't the
;---        first in a group. Now all special handling in omffixup.c
;---        for such labels has been removed.

	.286
	.dosseg

DGROUP group _DATA,CONST,STACK

_DATA segment word public 'DATA'
	db 1,2,3,4
_DATA ends
CONST segment word public 'DATA'
optlist = $             ;wrong fixup for jwasm < v2.19
;optlist equ $          ;ok
;optlist label word     ;ok
	dw 1,2,3
CONST ends
STACK segment para stack 'STACK'
	org 200h
STACK ends

_TEXT segment word public 'CODE'

start:
	mov ax,DGROUP
    mov ds,ax
;    mov bx,offset DGROUP:optlist
    mov bx,offset optlist
    mov ax,4c00h
    int 21h

_TEXT ends

	END start

