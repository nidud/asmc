include io.inc
include string.inc
include alloc.inc
include consx.inc
include wsub.inc
include winbase.inc

WMAXPATH		equ 2048
ERROR_NO_MORE_FILES	equ 18
MAXFINDHANDLES		equ 20

	.data
	_attrib dd MAXFINDHANDLES dup(0)

	.code

wsfindnext PROC ff:ptr, handle:HANDLE
	.while FindNextFileA(handle, ff)
		mov ecx,ff
		xor eax,eax
		mov al,[ecx]
		mov ecx,_attrib
		not cl
		and eax,ecx
		jz toend
	.endw
	osmaperr()
toend:
	ret
wsfindnext ENDP

wsfindfirst PROC USES esi edi ebx fmask:LPSTR, fblk:ptr, attrib:SIZE_T
	;
	; @v3.31 - single file fails in FindFirstFileW
	;
	xor ebx,ebx
	mov eax,fmask
	mov ax,[eax]
	cmp ah,':'
ifdef _WIN95
	jne @F
	test console,CON_WIN95
endif
	jz unicode
@@:
	FindFirstFileA(fmask, fblk)
	jmp done

unicode:
	inc ebx
	mov edx,alloca(WMAXPATH + sizeof(WIN32_FIND_DATAW))
	mov edi,eax
	mov ecx,esi
	mov esi,fmask
	mov eax,'\'
	stosw
	stosw
	mov al,'?'
	stosw
	mov al,'\'
	stosw
	.repeat
		lodsb
		stosw
	.until	!al
	lea esi,[edx+WMAXPATH]
	mov [esi].WIN32_FIND_DATAW.cFileName,ax
	mov [esi].WIN32_FIND_DATAW.cAlternateFileName,ax
	FindFirstFileW(edx, esi)
done:
	.if eax != -1
		push eax
		.if ebx
			mov edi,fblk
			mov ecx,WIN32_FIND_DATA.cFileName / 4
			rep movsd
			lea ecx,[edi+260]
			lea edx,[esi+520]
			.repeat
				lodsw
				stosb
			.until	!al
			mov edi,ecx
			mov esi,edx
			.repeat
				lodsw
				stosb
			.until	!al
		.endif
		mov ecx,fblk
		memmove(addr _attrib + 4, addr _attrib, 4 * (MAXFINDHANDLES - 1))
		mov eax,attrib
		mov _attrib,eax
		pop eax
	.else
		osmaperr()
	.endif
	mov esp,ebp
	ret
wsfindfirst ENDP

wscloseff PROC handle:HANDLE
	memcpy( addr _attrib, addr _attrib + 4, 4 * ( MAXFINDHANDLES - 1 ) )
	.if FindClose(handle)
		xor eax,eax
	.else
		osmaperr()
	.endif
	ret
wscloseff ENDP

	END
