include io.inc
include time.inc
include direct.inc
include errno.inc
include stat.inc
include string.inc
include stdlib.inc
include alloc.inc
include crtl.inc
include winbase.inc

A_D	equ 10h

	.code

_lk_getltime PROC PRIVATE ft

local	SystemTime:SYSTEMTIME
local	LocalFTime:FILETIME

	.if	FileTimeToLocalFileTime( ft, addr LocalFTime )
		.if	FileTimeToSystemTime( addr LocalFTime, addr SystemTime )

			_loctotime_t( SystemTime.wYear,
				      SystemTime.wMonth,
				      SystemTime.wDay,
				      SystemTime.wHour,
				      SystemTime.wMinute,
				      SystemTime.wSecond )

			test	eax,eax
		.endif
	.endif
	ret
_lk_getltime ENDP

_stat	PROC USES esi edi ebx fname:LPSTR, buf:PVOID

  local path, drive, ff:WIN32_FIND_DATA, pathbuf[_MAX_PATH]:BYTE

	mov	esi,fname
	mov	edi,buf
	strchr( esi, '?' )
	jnz	error_1
	strchr( esi, '*' )
	jnz	error_1
	mov	eax,[esi]
	.if	ah == ':'
		test	eax,00FF0000h
		jz	error_1
		or	al,20h
		sub	al,'a' - 1
		movzx	eax,al
	.else
		_getdrive()
	.endif
	mov	drive,eax
	.if	FindFirstFileA( esi, addr ff ) == -1
		.if	!strchr( esi, '.' )
			.if	!strchr( esi, '\' )
				strchr( esi, '/' )
				jz error_1
			.endif
		.endif

		free( _getcwd( addr pathbuf, _MAX_PATH ) )
		test	eax,eax
		jz	error_1
		mov	path,eax
		strlen( eax )
		cmp	eax,3
		jne	error_1
		GetDriveType( path )
		cmp	eax,1
		jna	error_1
		xor	eax,eax
		mov	ff.dwFileAttributes,A_D
		mov	ff.nFileSizeHigh,eax
		mov	ff.nFileSizeLow,eax
		mov	ff.cFileName,0
		_loctotime_t( 80, 1, 1, 0, 0, 0 )
		mov	[edi].S_STAT.st_mtime,eax
		mov	[edi].S_STAT.st_atime,eax
		mov	[edi].S_STAT.st_ctime,eax
	.else
		FindClose( eax )
		_lk_getltime( addr ff.ftLastWriteTime )
		jz	error_2
		mov	[edi].S_STAT.st_mtime,eax
		_lk_getltime( addr ff.ftLastAccessTime )
		.if	ZERO?
			mov eax,[edi].S_STAT.st_mtime
		.endif
		mov	[edi].S_STAT.st_atime,eax
		_lk_getltime( addr ff.ftCreationTime )
		.if	ZERO?
			mov eax,[edi].S_STAT.st_mtime
		.endif
		mov	[edi].S_STAT.st_ctime,eax
	.endif

	mov	eax,[esi]
	mov	edx,ff.dwFileAttributes
	mov	ecx,S_IFDIR or S_IEXEC
	mov	ebx,S_IREAD

	.if	ah == ':'
		add esi,2
		shr eax,16
	.endif
	.if	al && !( dl & A_D )
		.if	ah || al != '\' && al != '/'
			mov ecx,S_IFREG
		.endif
	.endif
	.if	!( dl & A_D )
		mov ebx,S_IREAD or S_IWRITE
	.endif
	or	ebx,ecx
	.if	__isexec( esi )
		or ebx,S_IEXEC
	.endif
	mov	ecx,ebx
	and	ecx,01C0h
	mov	eax,ecx
	shr	ecx,3
	or	ebx,ecx
	shr	eax,6
	or	eax,ebx
	mov	[edi].S_STAT.st_mode,ax
	mov	[edi].S_STAT.st_nlink,1
	mov	eax,ff.nFileSizeLow
	mov	[edi].S_STAT.st_size,eax
	xor	eax,eax
	mov	[edi].S_STAT.st_uid,ax
	mov	[edi].S_STAT.st_ino,ax
	mov	[edi].S_STAT.st_gid,eax
	mov	eax,drive
	dec	eax
	mov	[edi].S_STAT.st_dev,eax
	mov	[edi].S_STAT.st_rdev,eax
	xor	eax,eax
toend:
	ret
error_1:
	mov	errno,ENOENT
	mov	oserrno,ERROR_PATH_NOT_FOUND
	mov	eax,-1
	jmp	toend
error_2:
	call	osmaperr
	mov	eax,-1
	jmp	toend
_stat	ENDP

	END
