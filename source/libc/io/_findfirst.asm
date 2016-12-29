include crtl.inc
include io.inc
include time.inc

	.code

_findnext PROC USES esi edi handle:HANDLE, ff:PTR _finddata_t

local	FindFileData:WIN32_FIND_DATA

	mov	edi,ff
	lea	esi,FindFileData

	.if	FindNextFileA( handle, esi )

		copyblock()
		xor	eax,eax
	.else

		osmaperr()
	.endif
	ret

_findnext ENDP

_findfirst PROC USES esi edi ebx lpFileName:LPSTR, ff:PTR _finddata_t

local	FindFileData:	WIN32_FIND_DATAW,
	result:		DWORD

	mov	edi,ff
	lea	esi,FindFileData
	;
	; single file fails in FindFirstFileW
	;
	mov	eax,lpFileName
	.if	BYTE PTR [eax+1] == ':'

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

	mov	result,eax
	.if	eax != -1

		copyblock()
	.else

		osmaperr()
	.endif
	mov	eax,result
	ret

_findfirst ENDP

_findclose PROC h:HANDLE

	.if	!FindClose( h )

		osmaperr()
	.else

		xor eax,eax
	.endif
	ret

_findclose ENDP

	ASSUME	esi:ptr WIN32_FIND_DATA
	ASSUME	edi:ptr _finddata_t

copyblock:
	mov	eax,[esi].dwFileAttributes
	mov	[edi].ff_attrib,eax
	mov	eax,[esi].nFileSizeLow
	mov	edx,[esi].nFileSizeHigh
	mov	DWORD PTR [edi].ff_size,eax
	mov	DWORD PTR [edi].ff_size[4],edx
	mov	[edi].ff_time_create,__FTToTime( addr [esi].ftCreationTime )
	mov	[edi].ff_time_access,__FTToTime( addr [esi].ftLastAccessTime )
	mov	[edi].ff_time_write, __FTToTime( addr [esi].ftLastWriteTime )
	lea	esi,[esi].cFileName
	lea	edi,[edi].ff_name
	mov	ecx,260/4
	rep	movsd
	ret

	END
