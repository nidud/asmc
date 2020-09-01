; _CHKSTK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc

	.code

_chkstk::
_alloca_probe::

	push	ecx
	lea	ecx,[esp+4]
	sub	ecx,eax
	sbb	eax,eax
	not	eax
	and	ecx,eax
	mov	eax,esp
	and	eax,not (_PAGESIZE_ - 1)
cs10:
	cmp	ecx,eax
	jb	cs20
	mov	eax,ecx
	pop	ecx
	xchg	esp,eax
	mov	eax,[eax]
	mov	[esp],eax
	ret
cs20:
	sub	eax,_PAGESIZE_
	test	[eax],eax
	jmp	cs10

	end
