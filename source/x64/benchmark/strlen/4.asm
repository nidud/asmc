
	.x64
	.model	flat, fastcall

	.code

	OPTION PROLOGUE:NONE, EPILOGUE:NONE

strlen	PROC string:QWORD

	xor	rax,rax
	mov	r8,rcx
@@:
	cmp	[rcx],al
	jz	exit_0
	cmp	[rcx+1],al
	jz	exit_1
	cmp	[rcx+2],al
	jz	exit_2
	cmp	[rcx+3],al
	jz	exit_3
	cmp	[rcx+4],al
	jz	exit_4
	cmp	[rcx+5],al
	jz	exit_5
	cmp	[rcx+6],al
	jz	exit_6
	cmp	[rcx+7],al
	jz	exit_7

	mov	r10,8080808080808080h
	mov	r11,0101010101010101h
	and	rcx,-8
loop_8:
	add	rcx,8
	mov	rdx,[rcx]
	mov	rax,rdx
	sub	rax,r11
	not	rdx
	and	rax,rdx
	and	rax,r10
	jz	loop_8
L3:
	bsf	rax,rax
	shr	rax,3
	add	rax,rcx
	sub	rax,r8
	ret
exit_7:
	lea	rax,[rcx+7]
	sub	rax,r8
	ret
exit_6:
	lea	rax,[rcx+6]
	sub	rax,r8
	ret
exit_5:
	lea	rax,[rcx+5]
	sub	rax,r8
	ret
exit_4:
	lea	rax,[rcx+4]
	sub	rax,r8
	ret
exit_3:
	lea	rax,[rcx+3]
	sub	rax,r8
	ret
exit_2:
	lea	rax,[rcx+2]
	sub	rax,r8
	ret
exit_1:
	lea	rax,[rcx+1]
	sub	rax,r8
	ret
exit_0:
	sub	rcx,r8
	add	rax,rcx
	ret

strlen	ENDP

	END
