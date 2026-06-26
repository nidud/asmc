
;--- v2.19, MZ format: stack segment with class 'CODE' ( to locate it before _TEXT )
;--- was skipped previously.

    .286

STACK segment para stack 'CODE'
	org 100h
STACK ends

_TEXT segment word public 'CODE'
start:
	mov ax, 4c00h
	int 21h
_TEXT ends

    end start
