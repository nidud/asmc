include stdlib.inc
include string.inc
include alloc.inc
include winbase.inc

	.code

__setenvp PROC USES esi edi ebx envp:LPSTR

	mov edi,GetEnvironmentStringsA()

	mov esi,eax			; save start of block in ESI
	xor eax,eax
	xor ebx,ebx
	mov ecx,-1

	.while	BYTE PTR [edi]		; size up the environment

		.if BYTE PTR [edi] != '='

			mov edx,edi	; save offset of string
			sub edx,esi
			push edx
			inc ebx		; increase count
		.endif
		repnz scasb		; next string..
	.endw

	inc ebx				; count strings plus NULL
	sub edi,esi			; EDI to size
	lea eax,[edi+ebx*4]		; pointers plus size of environment
	malloc(eax)
	mov ecx,envp			; return result
	mov [ecx],eax

	.if eax

		lea eax,[eax+ebx*4] ; new adderss of block
		memcpy(eax, esi, edi)
		xchg eax,esi		; ESI to block
		FreeEnvironmentStrings(eax)
		lea edi,[esi-4]		; EDI to end of pointers array

		std			; move backwards
		xor eax,eax		; set last pointer to NULL
		stosd
		dec ebx
		.while	ebx
			pop eax		; pop offset in reverse
			add eax,esi	; add address of block
			stosd
			dec ebx
		.endw
		cld
		inc ebx			; remove ZERO flag
		mov eax,envp		; return address of new _environ
		mov eax,[eax]
;	.else
;		mov esp,ebp		; case no mem...
	.endif
	ret

__setenvp ENDP

	END
