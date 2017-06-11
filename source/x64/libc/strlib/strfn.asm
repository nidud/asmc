; char *strfn(char *path);
;
; EXIT: file part of path if /\ is found, else path
;
include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strfn	PROC	path:LPSTR
	push	rdi
	mov	rdi,rcx
	strlen( rdi )
	lea	rax,[rdi+rax-1]
@@:
	cmp	byte ptr [rax],'\'
	je	@F
	cmp	byte ptr [rax],'/'
	je	@F
	dec	rax
	cmp	rax,rdi
	ja	@B
	lea	rax,[rdi-1]
@@:
	inc	rax
	pop	rdi
	ret
strfn	ENDP

	END
