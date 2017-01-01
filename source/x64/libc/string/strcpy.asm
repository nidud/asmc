include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strcpy	PROC dst:LPSTR, src:LPSTR
if 1
	mov	r8,rsi
	mov	r9,rdi
	mov	r10,rcx
	xor	rax,rax
	mov	rcx,-1
	mov	rdi,rdx
	repnz	scasb
	mov	rdi,r10
	mov	rsi,rdx
	mov	rax,rdi
	not	rcx
	rep	movsb
	mov	rsi,r8
	mov	rdi,r9
else
	mov	r9,rcx
	mov	r10,8080808080808080h
	mov	r11,0101010101010101h
	jmp	start
loop_8:
	mov	[rcx],rax
	add	rcx,8
start:
	mov	rax,[rdx]
	add	rdx,8
	mov	r8,rax
	sub	r8,r11
	not	rax
	and	r8,rax
	and	r8,r10
	jz	loop_8
	not	rax
loop_2:
	mov	[rcx],al
	test	al,al
	jz	toend
	mov	[rcx+1],ah
	test	ah,ah
	jz	toend
	shr	rax,16
	add	rcx,2
	jmp	loop_2
toend:
	mov	rax,r9
endif
	ret
strcpy	ENDP

	END
