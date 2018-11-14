; STRNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

strncpy PROC USES edi esi edx dst:LPSTR, src:LPSTR, count:SIZE_T
	mov	edi,dst
	mov	esi,src
	mov	ecx,count
	test	ecx,ecx		; filler..
	jz	toend
	cmp	ecx,4
	jb	tail
	mov	eax,[esi]
	lea	edx,[eax-01010101h]
	not	eax
	and	edx,eax
	and	edx,80808080h
	jnz	tail
	mov	eax,edi		; align 4
	neg	eax
	and	eax,11B
	mov	edx,[esi]	; copy the first 4 bytes
	mov	[edi],edx
	add	edi,eax		; add leading bytes
	add	esi,eax		;
	sub	ecx,eax
	jmp	start
	ALIGN	16
lupe:
	sub	ecx,4
	mov	eax,[esi]	; copy 4 bytes
	mov	[edi],eax
	add	edi,4
	add	esi,4
start:
	cmp	ecx,4
	jb	tail
	mov	eax,[esi]
	lea	edx,[eax-01010101h]
	not	eax
	and	edx,eax
	and	edx,80808080h
	jz	lupe
	ALIGN	8
tail:
	test	ecx,ecx
	jz	toend
@@:
	mov	al,[esi]
	mov	[edi],al
	dec	ecx
	jz	toend
	inc	edi
	inc	esi
	test	al,al
	jnz	@B
	rep	stosb
toend:
	mov	eax,dst
	ret
strncpy ENDP

	END
