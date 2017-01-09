include io.inc
include string.inc
include alloc.inc
include consx.inc
include wsub.inc

WMAXPATH		equ 2048
ERROR_NO_MORE_FILES	equ 18
MAXFINDHANDLES		equ 20

	.data
	_attrib dd MAXFINDHANDLES dup(0)

	.code

wfindnext PROC ff:PTR S_WFBLK, handle:HANDLE
	.while	FindNextFile( handle, ff )
		mov	ecx,ff
		mov	eax,dword ptr [ecx].S_WFBLK.wf_size[4]
		mov	edx,dword ptr [ecx].S_WFBLK.wf_size
		mov	dword ptr [ecx].S_WFBLK.wf_size,eax
		mov	dword ptr [ecx].S_WFBLK.wf_size[4],edx
		xor	eax,eax
		mov	al,[ecx]
		mov	ecx,_attrib
		not	cl
		and	eax,ecx
		jz	toend
	.endw
	call	osmaperr
toend:
	ret
wfindnext ENDP

wfindfirst PROC USES esi edi ebx fmask:LPSTR, fblk:PTR S_WFBLK, attrib:SIZE_T
	;
	; @v3.31 - single file fails in FindFirstFileW
	;
	xor	ebx,ebx
	mov	eax,fmask
	mov	ax,[eax]
	cmp	ah,':'
ifdef __W95__
	jne	@F
	test	console,CON_WIN95
endif
	jz	unicode
@@:
	FindFirstFile( fmask, fblk )
	jmp	done

unicode:
	inc	ebx
	alloca( WMAXPATH + sizeof( S_WFBLKW ) )
	mov	edx,eax
	mov	edi,eax
	mov	ecx,esi
	mov	esi,fmask
	mov	eax,'\'
	stosw
	stosw
	mov	al,'?'
	stosw
	mov	al,'\'
	stosw
	.repeat
		lodsb
		stosw
	.until	!al
	lea	esi,[edx+WMAXPATH]
	FindFirstFileW( edx, esi )
done:
	.if	eax != -1
		push	eax
		.if	ebx
			mov	edi,fblk
			mov	ecx,S_WFBLK.wf_name / 4
			rep	movsd
			lea	ecx,[edi+260]
			lea	edx,[esi+520]
			.repeat
				lodsw
				stosb
			.until	!al
			mov	edi,ecx
			mov	esi,edx
			.repeat
				lodsw
				stosb
			.until	!al
		.endif
		mov	ecx,fblk
		mov	eax,dword ptr [ecx].S_WFBLK.wf_size[4]
		mov	edx,dword ptr [ecx].S_WFBLK.wf_size
		mov	dword ptr [ecx].S_WFBLK.wf_size,eax
		mov	dword ptr [ecx].S_WFBLK.wf_size[4],edx
		memmove( addr _attrib + 4, addr _attrib, 4 * ( MAXFINDHANDLES - 1 ) )
		mov	eax,attrib
		mov	_attrib,eax
		pop	eax
	.else
		call	osmaperr
	.endif
	mov	esp,ebp
	ret
wfindfirst ENDP

wcloseff PROC handle:HANDLE
	memcpy( addr _attrib, addr _attrib + 4, 4 * ( MAXFINDHANDLES - 1 ) )
	.if	FindClose( handle )
		xor	eax,eax
	.else
		call	osmaperr
	.endif
	ret
wcloseff ENDP

	END
