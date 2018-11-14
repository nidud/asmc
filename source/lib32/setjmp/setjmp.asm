; SETJMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include setjmp.inc

	.code

	option stackbase:esp

	ASSUME	eax: PTR S_JMPBUF

setjmp PROC C JMPBUF:PTR S_JMPBUF
setjmp ENDP

_setjmp3 PROC JMPBUF:PTR S_JMPBUF
_setjmp3 ENDP

_setjmp PROC C JMPBUF:PTR S_JMPBUF
	mov	eax,[esp+4]
	mov	[eax].J_EBP,ebp
	mov	[eax].J_EBX,ebx
	mov	[eax].J_EDI,edi
	mov	[eax].J_ESI,esi
	mov	[eax].J_ESP,esp
	mov	[eax].J_EDX,edx
	mov	[eax].J_ECX,ecx
	mov	ecx,[esp]
	mov	[eax].J_EIP,ecx
	mov	ecx,[eax].J_ECX
	xor	eax,eax
	ret
_setjmp ENDP

	ASSUME	edx: PTR S_JMPBUF

longjmp PROC C JMPBUF:PTR S_JMPBUF, retval:DWORD
	mov	edx,[esp+4]
	mov	eax,[esp+8]
	mov	ebp,[edx].J_EBP
	mov	ebx,[edx].J_EBX
	mov	edi,[edx].J_EDI
	mov	esi,[edx].J_ESI
	mov	esp,[edx].J_ESP
	mov	ecx,[edx].J_EIP
	mov	[esp],ecx
	mov	ecx,[edx].J_ECX
	mov	edx,[edx].J_EDX
	ret
longjmp ENDP

	END
