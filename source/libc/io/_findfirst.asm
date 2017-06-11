include crtl.inc
include io.inc
include time.inc
include winbase.inc

	.code

_findnext proc uses esi edi handle:HANDLE, ff:ptr _finddata_t

local	FindFileData:WIN32_FIND_DATAA

	mov edi,ff
	lea esi,FindFileData

	.if FindNextFileA(handle, esi)

		copyblock()
		xor eax,eax
	.else
		osmaperr()
	.endif
	ret

_findnext endp

_findfirst proc uses esi edi ebx lpFileName:LPSTR, ff:ptr _finddata_t

local	FindFileData:WIN32_FIND_DATAW,
	result:DWORD

	mov edi,ff
	lea esi,FindFileData
	;
	; single file fails in FindFirstFileW
	;
	mov eax,lpFileName
	.if BYTE PTR [eax+1] == ':'

		.if	FindFirstFileW( __allocwpath( eax ), esi ) != -1

			lea	edi,FindFileData.cFileName
			mov	esi,edi
			.repeat
				lodsw
				stosb
			.until	!al
			mov	edi,ff
			lea	esi,FindFileData
		.endif
	.else

		FindFirstFileA( eax, esi )
	.endif

	mov result,eax
	.if eax != -1

		copyblock()
	.else
		osmaperr()
	.endif
	mov eax,result
	ret

_findfirst endp

	ASSUME	esi:ptr WIN32_FIND_DATAA
	ASSUME	edi:ptr _finddata_t

copyblock:
	mov	eax,[esi].dwFileAttributes
	mov	[edi].attrib,eax
	mov	eax,[esi].nFileSizeLow
	mov	[edi]._size,eax
	mov	[edi].time_create,__FTToTime( addr [esi].ftCreationTime )
	mov	[edi].time_access,__FTToTime( addr [esi].ftLastAccessTime )
	mov	[edi].time_write, __FTToTime( addr [esi].ftLastWriteTime )
	lea	esi,[esi].cFileName
	lea	edi,[edi]._name
	mov	ecx,260/4
	rep	movsd
	ret

	END
