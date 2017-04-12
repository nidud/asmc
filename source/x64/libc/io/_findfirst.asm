include io.inc
include crtl.inc
include time.inc
include winbase.inc

	.code

_findnext PROC USES rsi rdi handle: HANDLE, ff: ptr _finddata_t

	local	wf:WIN32_FIND_DATA

	mov	rdi,ff
	lea	rsi,wf

	.if	FindNextFile( rcx, rsi )

		call	copyblock
		xor	eax,eax
	.else

		call	osmaperr
	.endif
	ret

_findnext ENDP

_findfirst PROC USES rsi rdi rbx lpFileName:LPSTR, ff:PTR _finddata_t
local	FindFileData:	WIN32_FIND_DATAW,
	result:		DWORD

	mov	rdi,ff
	lea	rsi,FindFileData
	;
	; single file fails in FindFirstFileW
	;
	mov	rax,lpFileName
	.if	BYTE PTR [rax+1] == ':'

		.if	FindFirstFileW( __allocwpath( rax ), rsi ) != -1

			lea	rdi,FindFileData.cFileName
			mov	rsi,rdi
			.repeat
				lodsw
				stosb
			.until	!al
			mov	rdi,ff
			lea	rsi,FindFileData
		.endif
	.else

		FindFirstFileA( rax, rsi )
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

	.if !FindClose( rcx )

		osmaperr()
	.else

		xor eax,eax
	.endif
	ret

_findclose ENDP

	ASSUME	rsi:ptr WIN32_FIND_DATA
	ASSUME	rdi:ptr _finddata_t

copyblock proc private
	mov	eax,[rsi].dwFileAttributes
	mov	[rdi].ff_attrib,eax
	mov	eax,[rsi].nFileSizeLow
	mov	edx,[rsi].nFileSizeHigh
	mov	DWORD PTR [rdi].ff_size,eax
	mov	DWORD PTR [rdi].ff_size[4],edx
	__FTToTime( addr [rsi].ftCreationTime )
	mov	[rdi].ff_time_create,eax
	__FTToTime( addr [rsi].ftLastAccessTime )
	mov	[rdi].ff_time_access,eax
	__FTToTime( addr [rsi].ftLastWriteTime )
	mov	[rdi].ff_time_write,eax
	lea	rsi,[rsi].cFileName
	lea	rdi,[rdi].ff_name
	mov	rcx,260/4
	rep	movsd
	ret
copyblock endp

	END
