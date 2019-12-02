;
; '128'		- long
; '128 C:\file' - long
; '100h'	- hex
; 'f3 22'	- hex
;
include stdlib.inc
include crtl.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

strtolx PROC string:LPSTR
	mov	edx,[esp+4]	; string
	push	edx
	mov	ah,'9'
@@:
	mov	al,[edx]
	inc	edx
	test	al,al
	jz	@F
	cmp	al,' '
	je	@F
	cmp	al,ah
	jbe	@B
	call	__xtol
	ret	4
@@:
	call	atol
	ret	4
strtolx ENDP

	END
