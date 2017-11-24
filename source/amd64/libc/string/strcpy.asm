include string.inc

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strcpy	PROC dst:LPSTR, src:LPSTR

	mov	r9,rcx
	mov	al,[rdx]
	mov	[rcx],al
	test	al,al
	jz	toend
	mov	al,[rdx+1]
	mov	[rcx+1],al
	test	al,al
	jz	toend
	mov	al,[rdx+2]
	mov	[rcx+2],al
	test	al,al
	jz	toend
	mov	al,[rdx+3]
	mov	[rcx+3],al
	test	al,al
	jz	toend
	mov	al,[rdx+4]
	mov	[rcx+4],al
	test	al,al
	jz	toend
	mov	al,[rdx+5]
	mov	[rcx+5],al
	test	al,al
	jz	toend
	mov	al,[rdx+6]
	mov	[rcx+6],al
	test	al,al
	jz	toend
	mov	al,[rdx+7]
	mov	[rcx+7],al
	test	al,al
	jz	toend
	lea	rdx,[rdx+8]
	lea	rcx,[rcx+8]
	;and	al,not 7
	;sub	rax,rdx
	;add	rdx,rax
	;add	rcx,rax
	mov	r10,0x8080808080808080
	mov	r11,0x0101010101010101
lupe:
	mov	rax,[rdx]
	mov	r8,rax
	sub	r8,r11
	not	rax
	and	r8,rax
	not	rax
	and	r8,r10
	jnz	@F
	mov	[rcx],rax
	add	rcx,8
	add	rdx,8
	jmp	lupe
@@:
	mov	[rcx],al
	test	al,al
	jz	toend
	mov	[rcx+1],ah
	test	ah,ah
	jz	toend
	shr	rax,16
	mov	[rcx+2],al
	test	al,al
	jz	toend
	mov	[rcx+3],ah
	test	ah,ah
	jz	toend
	shr	rax,16
	add	rcx,4
	jmp	@B
toend:
	mov	rax,r9
	ret

strcpy	ENDP

	END
