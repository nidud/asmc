include string.inc

	.code

strins	PROC USES ebx s1:LPSTR, s2:LPSTR
	strlen( s2 )
	mov	ebx,eax
	strlen( s1 )
	mov	ecx,ebx
	add	ecx,s1
	inc	eax
	memmove( ecx, s1, eax )
	memcpy( s1, s2, ebx )
	ret
strins	ENDP

	END
