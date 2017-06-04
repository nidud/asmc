include string.inc

	.code

_mbspbrk PROC USES esi edi s1:LPSTR, s2:LPSTR

	mov	edi,s2
	or	ecx,-1
	xor	eax,eax
	repnz	scasb
	not	ecx
	dec	ecx

	.repeat
		.break .if ZERO?
		.for esi = s1, al = [esi] : eax : esi++
			mov   edi,s2
			mov   edx,ecx
			repnz scasb
			mov   ecx,edx
			.ifz
				mov eax,esi
				.break(1)
			.endif
			mov al,[esi+1]
		.endf
		xor eax,eax
	.until	1
	ret

_mbspbrk ENDP

	END
