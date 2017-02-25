include string.inc

	.code

_mbspbrk PROC USES esi edi s1:LPSTR, s2:LPSTR

	xor	eax,eax
	mov	edi,s2
	or	ecx,-1
	repnz	scasb
	not	ecx
	dec	ecx
	.repeat
		.breakz
		.for esi = s1, al = [esi] : eax : esi++

			mov	edi,s2
			mov	edx,ecx
			repnz	scasb
			mov	ecx,edx
			.ifz
				mov eax,esi
				.break1
			.endif
			mov	al,[esi+1]
		.endf
		xor eax,eax
	.until	1
	ret

_mbspbrk ENDP

	END
