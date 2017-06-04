include direct.inc
include errno.inc
include string.inc
include alloc.inc
include winbase.inc

	.code

	option	cstack:on

_getdcwd PROC USES esi edi ebx drive:SINT, buffer:LPSTR, maxlen:SINT

	mov esi,maxlen
	mov edi,alloca(esi)
	mov ebx,drive
	.if !ebx
		GetCurrentDirectoryA(esi, edi)
	.else
		GetLogicalDrives()
		mov ecx,ebx
		dec ecx
		shr eax,cl
		sbb eax,eax
		and eax,1
		.if ZERO?
			mov oserrno,ERROR_INVALID_DRIVE
			mov errno,EACCES
			jmp toend
		.endif
		mov	al,'A' - 1
		add	al,bl
		add	eax,002E3A00h
		push	eax
		mov	ecx,esp
		push	eax
		mov	eax,esp
		GetFullPathNameA(ecx, esi, edi, eax)
	.endif
	.if eax > esi
		mov errno,ERANGE
		xor eax,eax
		jmp toend
	.elseif eax
		mov esi,buffer
		.if !esi
			mov esi,malloc(addr [eax+1])
			test eax,eax
			jz toend
		.endif
		strcpy(esi, edi)
	.endif
toend:
	mov esp,ebp
	ret
_getdcwd ENDP

	END
