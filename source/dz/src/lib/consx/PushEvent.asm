include consx.inc

	.code

PushEvent PROC Event:DWORD

	mov eax,Event
	mov ecx,keybcount
	.if ecx < MAXKEYSTACK-1

		inc keybcount
		mov keybstack[ecx*4],eax
	.endif
	ret

PushEvent ENDP

PopEvent PROC

	mov eax,keyshift
	mov edx,[eax]

	xor eax,eax
	.if eax != keybcount

		dec keybcount
		mov eax,keybcount
		mov eax,keybstack[eax*4]
		test eax,eax
	.endif
	ret

PopEvent ENDP

	END
