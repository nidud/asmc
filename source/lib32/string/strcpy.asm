; STRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

	.code

	option stackbase:esp

strcpy	proc uses edi edx dst:LPSTR, src:LPSTR
	mov	ecx,src
	mov	edi,dst
	jmp	start
dword_loop:
	mov	[edi],eax
	add	edi,4
start:
	mov	eax,[ecx]
	add	ecx,4
	lea	edx,[eax-01010101h]
	not	eax
	and	edx,eax
	not	eax
	and	edx,80808080h
	jz	dword_loop
	mov	[edi],al
	test	al,al
	jz	toend
	mov	[edi+1],ah
	test	ah,ah
	jz	toend
	shr	eax,16
	mov	[edi+2],al
	test	al,al
	jz	toend
	mov	[edi+3],ah
toend:
	mov	eax,dst
	ret
strcpy	ENDP

	END
