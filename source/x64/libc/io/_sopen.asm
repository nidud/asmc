include io.inc
include share.inc
include stdio.inc
include fcntl.inc
include stat.inc
include errno.inc

extrn	_fmode:DWORD
extrn	_umaskval:DWORD

	.code

	OPTION	WIN64:3, STACKBASE:rsp

_sopen	PROC USES rsi rdi rbx path:LPSTR, oflag:UINT, shflag:UINT, args:VARARG

	local sa:SECURITY_ATTRIBUTES
	local fileflags:BYTE

	xor	rax,rax
	mov	sa.nLength,sizeof(SECURITY_ATTRIBUTES)
	mov	sa.bInheritHandle,eax
	mov	sa.lpSecurityDescriptor,rax
	mov	fileflags,al
	mov	eax,edx
	.if	eax & O_NOINHERIT
		mov fileflags,FH_NOINHERIT
	.else
		inc sa.bInheritHandle
	.endif
	;
	; figure out binary/text mode
	;
	.if	!( eax & O_BINARY )
		.if	eax & O_TEXT
			or fileflags,FH_TEXT
		.elseif _fmode != O_BINARY	; check default mode
			or fileflags,FH_TEXT
		.endif
	.endif

	;
	; decode the access flags
	;
	and	eax,O_RDONLY or O_WRONLY or O_RDWR
	mov	edi,GENERIC_READ		; read access
	.if	eax != O_RDONLY
		mov	edi,GENERIC_WRITE	; write access
		.if	eax != O_WRONLY
			mov	edi,GENERIC_READ or GENERIC_WRITE
			.if	eax != O_RDWR
				jmp error_inval
			.endif
		.endif
	.endif
	;
	; decode sharing flags
	;
	mov	eax,r8d;shflag
	.switch eax
	  .case SH_DENYNO			; share read and write access
		mov	ebx,SHARE_READ or SHARE_WRITE
		.endc
	  .case SH_DENYWR
		mov	ebx,SHARE_READ		; share read access
		.endc
	  .case SH_DENYRD
		mov	ebx,SHARE_WRITE		; share write access
		.endc
	  .default
		xor	ebx,ebx			; exclusive access
		.if	eax != SH_DENYRW
			jmp error_inval
		.endif
	.endsw
	;
	; decode open/create method flags
	;
	mov	eax,edx
	and	eax,O_CREAT or O_EXCL or O_TRUNC
	.switch eax
	  .case 0
	  .case O_EXCL
		mov	eax,OPEN_EXISTING
		.endc
	  .case O_CREAT
		mov	eax,OPEN_ALWAYS
		.endc
	  .case O_CREAT or O_EXCL
	  .case O_CREAT or O_EXCL or O_TRUNC
		mov	eax,CREATE_NEW
		.endc
	  .case O_CREAT or O_TRUNC
		mov	eax,CREATE_ALWAYS
		.endc
	  .case O_TRUNC
	  .case O_TRUNC or O_EXCL
		mov	eax,TRUNCATE_EXISTING
		.endc
	  .default
		jmp	error_inval
	.endsw

	mov	r10d,FILE_ATTRIBUTE_NORMAL
	.if	edx & O_CREAT

		lea	rsi,args
		mov	esi,[rsi]	; fopen(0284h)
		mov	r11d,_umaskval	; 0
		not	r11d		; -1
		and	esi,r11d	; 0284h
		and	esi,S_IWRITE	; 0080h

		.if	ZERO?
			mov	r10d,FILE_ATTRIBUTE_READONLY
		.endif
	.endif

	.if	edx & O_TEMPORARY
		or	r10d,FILE_FLAG_DELETE_ON_CLOSE
		or	edi,M_DELETE
	.endif
	.if	edx & O_SHORT_LIVED
		or	r10d,FILE_ATTRIBUTE_TEMPORARY
	.endif
	.if	edx & O_SEQUENTIAL
		or	r10d,FILE_FLAG_SEQUENTIAL_SCAN
	.elseif edx & O_RANDOM
		or	r10d,FILE_FLAG_RANDOM_ACCESS
	.endif

	.if	_osopen( rcx, edi, ebx, addr sa, eax, r10d ) != -1

		mov	rsi,rax
		mov	bl,fileflags
		.if	GetFileType( rdx ) == FILE_TYPE_UNKNOWN
			jmp	error
		.elseif eax == FILE_TYPE_CHAR
			or	bl,FH_DEVICE
		.elseif eax == FILE_TYPE_PIPE
			or	bl,FH_PIPE
		.endif
		lea	rax,_osfile
		or	[rax+rsi],bl
		.if	!( bl & FH_DEVICE or FH_PIPE ) && bl & FH_TEXT && oflag & O_RDWR
			.if	_lseek( esi, -1, SEEK_END ) != -1
				mov	rbx,rax
				xor	eax,eax
				push	rax
				mov	rax,rsp
				osread( esi, rax, 1 )
				pop	rdx
				.if	!eax && dl == 26
					.if	_chsize( esi, rbx ) == -1
						jmp error
					.endif
				.endif
				.if	_lseek( esi, 0, SEEK_SET ) == -1
					jmp error
				.endif
			.elseif oserrno != ERROR_NEGATIVE_SEEK
				jmp	error
			.endif
		.endif
		lea	rax,_osfile
		add	rax,rsi
		.if	!(BYTE PTR [rax] & FH_DEVICE or FH_PIPE) && oflag & O_APPEND
			or	BYTE PTR [rax],FH_APPEND
		.endif
		mov	rax,rsi
	.endif
toend:
	ret
error:
	_close( esi )
	mov	eax,-1
	jmp	toend
error_inval:
	mov	errno,EINVAL
	xor	rax,rax
	mov	oserrno,eax
	dec	rax
	jmp	toend
_sopen	ENDP

	END
