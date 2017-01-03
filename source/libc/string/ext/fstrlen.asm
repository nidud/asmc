include string.inc

	.code

fstrlen PROC FASTCALL string
	mov	eax,string
	push	eax
	mov	ecx,eax
	and	ecx,3
	jz	start

	and	eax,-4
	shl	ecx,3
	mov	edx,-1
	shl	edx,cl
	not	edx
	or	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jnz	done

	ALIGN	4
lupe:
	add	eax,4
start:
	mov	edx,[eax]
	lea	ecx,[edx-01010101h]
	not	edx
	and	ecx,edx
	and	ecx,80808080h
	jz	lupe
done:
	pop	edx
	bsf	ecx,ecx
	shr	ecx,3
	sub	eax,edx
	add	eax,ecx
	ret
fstrlen ENDP

	END
