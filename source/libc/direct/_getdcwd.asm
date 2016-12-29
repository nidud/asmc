include direct.inc
include errno.inc
include string.inc
include alloc.inc

	.code

	option	cstack:on

_getdcwd PROC USES esi edi ebx drive:SINT, buffer:LPSTR, maxlen:SINT

	mov	esi,maxlen
	alloca( esi )
	mov	edi,eax

	mov	ebx,drive
	.if	!ebx

		GetCurrentDirectory( esi, edi )
	.else
		GetLogicalDrives()
		mov	ecx,ebx
		dec	ecx
		shr	eax,cl
		sbb	eax,eax
		and	eax,1
		.if	ZERO?
			mov	oserrno,ERROR_INVALID_DRIVE
			mov	errno,EACCES
			jmp	toend
		.endif
ifdef _UNICODE
		mov	eax,0x003A0000 + 'A' - 1
		add	al,bl
		push	0x0000002E
		push	eax
		mov	ecx,esp
		push	0x0000002E
		push	eax
		mov	eax,esp
else
		mov	al,'A' - 1
		add	al,bl
		add	eax,002E3A00h
		push	eax
		mov	ecx,esp
		push	eax
		mov	eax,esp
endif
		GetFullPathName( ecx, esi, edi, eax )
	.endif
	.if	eax > esi

		mov	errno,ERANGE
		xor	eax,eax
		jmp	toend

	.elseif eax

		mov	esi,buffer
		.if	!esi
			inc	eax
			malloc( eax )
			mov	esi,eax
			jz	toend
		.endif
		lstrcpy( esi, edi )
	.endif
toend:
	mov	esp,ebp
	ret
_getdcwd ENDP

	END
