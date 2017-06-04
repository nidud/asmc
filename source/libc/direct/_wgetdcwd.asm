include direct.inc
include errno.inc
include string.inc
include alloc.inc
include winbase.inc

	.code

	option	cstack:on

_wgetdcwd PROC USES esi edi ebx drive:SINT, buffer:LPWSTR, maxlen:SINT

	mov esi,maxlen
	mov edi,alloca(esi)
	mov ebx,drive
	.if !ebx
		GetCurrentDirectoryW(esi, edi)
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
		mov	eax,0x003A0000 + 'A' - 1
		add	al,bl
		push	0x0000002E
		push	eax
		mov	ecx,esp
		push	0x0000002E
		push	eax
		mov	eax,esp
		GetFullPathNameW(ecx, esi, edi, eax)
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
		wcscpy(esi, edi)
	.endif
toend:
	mov esp,ebp
	ret
_wgetdcwd ENDP

	END
