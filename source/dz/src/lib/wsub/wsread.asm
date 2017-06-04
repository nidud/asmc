include io.inc
include time.inc
include string.inc
include consx.inc
include wsub.inc

_A_STDFILES equ _A_ARCH or _A_RDONLY or _A_SYSTEM or _A_SUBDIR or _A_NORMAL
_A_ALLFILES equ _A_STDFILES or _A_HIDDEN ;or 7F00h

	.code

wsreadwf PROC PRIVATE USES esi edi ebx wsub:PTR S_WSUB, attrib

  local path[WMAXPATH]:byte,
	wf:WIN32_FIND_DATA,
	fsize:qword

	lea edi,wf
	mov ebx,wsub

	.if wsfindfirst(
		strfcat(
			addr path,
			[ebx].S_WSUB.ws_path,
			addr cp_stdmask ),
		edi,
		attrib ) != -1

		mov esi,eax
		xor eax,eax
		mov edx,'.'

		.while	byte ptr [edi] & _A_VOLID || \
			word ptr [edi].WIN32_FIND_DATA.cFileName == dx || \
			word ptr [edi].WIN32_FIND_DATA.cFileName[1] == dx
			.break .if wsfindnext(edi, esi)
			mov edx,'.'
		.endw

		.while	!eax

			inc eax
			.if !(byte ptr [edi] & _A_SUBDIR)

				cmpwarg(addr [edi].WIN32_FIND_DATA.cFileName, [ebx].S_WSUB.ws_mask)
			.endif

			.if eax
				mov eax,[edi].WIN32_FIND_DATA.nFileSizeLow
				mov dword ptr fsize,eax
				mov eax,[edi].WIN32_FIND_DATA.nFileSizeHigh
				mov dword ptr fsize[4],eax
				mov ecx,[edi].WIN32_FIND_DATA.dwFileAttributes
				lea eax,[edi].WIN32_FIND_DATA.ftLastWriteTime
				.if ecx & _A_SUBDIR
					lea eax,[edi].WIN32_FIND_DATA.ftCreationTime
				.endif
				__FTToTime(eax)
				and ecx,_A_FATTRIB
				lea edx,[edi].WIN32_FIND_DATA.cFileName
				.if !([ebx].S_WSUB.ws_flag & _W_LONGNAME) && \
					console & CON_IOSFN && [edi].WIN32_FIND_DATA.cAlternateFileName
					lea edx,[edi].WIN32_FIND_DATA.cAlternateFileName
				.endif
				.break .if !fballoc(edx, eax, fsize, ecx)
				mov ecx,[ebx].S_WSUB.ws_count
				mov edx,[ebx].S_WSUB.ws_fcb
				mov [edx+ecx*4],eax
				inc ecx
				mov [ebx].S_WSUB.ws_count,ecx
				.if ecx >= [ebx].S_WSUB.ws_maxfb
				    .break .if !wsextend(ebx)
				.endif
			.endif
			wsfindnext(edi, esi)
		.endw
		wscloseff(esi)
	.endif
	mov eax,[ebx].S_WSUB.ws_count
	ret
wsreadwf ENDP

wsread	PROC USES ebx wsub:PTR S_WSUB

	mov ebx,wsub
	wsfree(ebx)
	mov eax,[ebx].S_WSUB.ws_path
	movzx eax,word ptr [eax+2]
	mov edx,_FB_ROOTDIR
	.if al && eax != '\' && eax != '/'
		xor edx,edx
	.endif
	.if fbupdir(edx)
		inc [ebx].S_WSUB.ws_count
		mov edx,[ebx].S_WSUB.ws_fcb
		mov [edx],eax
		mov edx,[ebx].S_WSUB.ws_mask
		mov eax,'*'
		.if [edx] == ah
			mov [edx+2],ax
			mov [edx],al
			mov byte ptr [edx][1],'.'
		.endif
		mov edx,[ebx].S_WSUB.ws_flag
		mov eax,_A_ALLFILES
		.if !(edx & _W_HIDDEN)
			mov eax,_A_STDFILES
		.endif
		wsreadwf(ebx, eax)
	.endif
	mov eax,[ebx].S_WSUB.ws_count
	ret

wsread	ENDP

	END
