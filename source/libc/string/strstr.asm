; STRSTR.ASM--
; char *strstr(s1, s2) - search for s2 in s1
;
; returns:
;  - a pointer to the first occurrence of s2 in s1
;  - NULL if s2 does not occur in s1
;
; uses: eax ecx
;
include string.inc

	.code

	option	stackbase:esp

strstr	PROC USES esi edi ebx edx dst:LPSTR, src:LPSTR

	mov esi,src

	.repeat
		mov	edi,esi
		or	ecx,-1
		xor	eax,eax
		repnz	scasb	; strlen(src)
		not	ecx
		dec	ecx
		.break .ifz
		lea	ebx,[ecx-1]
		mov	edi,dst
		or	ecx,-1
		repnz	scasb	; strlen(dst)
		not	ecx
		dec	ecx
		.break .ifz
		mov	edi,dst

		.while	1

			mov	al,[esi]
			repne	scasb
			.break .ifnz

			.if	ebx

				.break .if ecx < ebx
				mov	edx,ebx

				.repeat
					mov al,[esi+edx]
					.continue(1) .if al != [edi+edx-1]
				.untildxz
			.endif
			mov	eax,edi
			dec	eax
			.break( 1 )
		.endw
		xor	eax,eax
	.until	1
	ret
strstr	ENDP

	END
