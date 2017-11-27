include stdlib.inc

	.data
	A dd 9,8,7,6,5,4,3,2,1,0
	B dd 0,1,2,3,4,5,6,7,8,9
	.code

compare PROC PRIVATE a, b

	mov	eax,a
	mov	edx,b
	mov	eax,[eax]
	mov	edx,[edx]

	.if	eax > edx

		mov	eax,1
	.elseif eax < edx

		mov	eax,-1
	.else

		xor	eax,eax
	.endif
	ret

compare ENDP


main	proc c

	qsort ( addr A, 10, 4, compare )

	xor	eax,eax
	lea	esi,A
	lea	edi,B
	mov	ecx,10
	repe	cmpsd
	setnz	al
	ret

main	endp

	end
