; char *strfn(char *path);
;
; EXIT: file part of path if /\ is found, else path
;
include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strfn	PROC	path:LPSTR
	push	edi
	push	ecx
	mov	edi,[esp+4+8]
	strlen( edi )
	lea	eax,[edi+eax-1]
@@:
	cmp	byte ptr [eax],'\'
	je	@F
	cmp	byte ptr [eax],'/'
	je	@F
	dec	eax
	cmp	eax,edi
	ja	@B
	lea	eax,[edi-1]
@@:
	inc	eax
	pop	ecx
	pop	edi
	ret	4
strfn	ENDP

	END
