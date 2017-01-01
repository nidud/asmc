include consx.inc

	.code

	OPTION	PROLOGUE:NONE, EPILOGUE:NONE

PushEvent PROC Event:DWORD

	mov eax,Event
	mov ecx,keybcount
	.if ecx < MAXKEYSTACK-1

		inc keybcount
		lea r8,keybstack
		mov [r8+rcx*4],eax
	.endif
	ret

PushEvent ENDP

PopEvent PROC
	mov	rax,keyshift
	mov	edx,[rax]
	xor	eax,eax
	cmp	eax,keybcount
	je	@F
	dec	keybcount
	mov	eax,keybcount
	lea	r8,keybstack
	mov	eax,[r8+rax*4]
	test	eax,eax
@@:
	ret
PopEvent ENDP

	END
