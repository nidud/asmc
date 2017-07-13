include string.inc

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

	.code

memxchg PROC dst:LPSTR, src:LPSTR, count:SIZE_T

	mov	r9,rcx
loop_1:
	test	r8,r8
	jz	toend
	test	r8b,7
	jz	loop_8
	test	r8b,3
	jz	loop_4

	sub	r8,1
	mov	al,[rcx+r8]
	mov	r10b,[rdx+r8]
	mov	[rcx+r8],r10b
	mov	[rdx+r8],al
	jmp	loop_1
loop_4:
	sub	r8,4
	mov	eax,[rcx+r8]
	mov	r10d,[rdx+r8]
	mov	[rcx+r8],r10d
	mov	[rdx+r8],eax
	jz	toend
loop_8:
	sub	r8,8
	mov	rax,[rcx+r8]
	mov	r10,[rdx+r8]
	mov	[rcx+r8],r10
	mov	[rdx+r8],rax
	jnz	loop_8
toend:
	mov	rax,r9
	ret

memxchg ENDP

	END
