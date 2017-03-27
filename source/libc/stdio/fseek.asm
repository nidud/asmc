include stdio.inc
include errno.inc
include winbase.inc

	.code

	ASSUME	ebx: LPFILE

fseek proc uses ebx fp:LPFILE, off:ULONG, whence:SIZE_T

	mov ebx,fp
	mov eax,whence
	.if eax != SEEK_SET && eax != SEEK_CUR && eax != SEEK_END

		jmp error
	.endif

	mov edx,eax
	mov eax,[ebx]._flag
	.if !( eax & _IOREAD or _IOWRT or _IORW )

		jmp error
	.endif

	and eax,not _IOEOF
	mov [ebx]._flag,eax
	.if edx == SEEK_CUR

		add off,ftell(ebx)
		mov whence,SEEK_SET
	.endif

	fflush(ebx)

	mov eax,[ebx]._flag
	.if eax & _IORW

		and eax,not (_IOWRT or _IOREAD)
		mov [ebx]._flag,eax
	.elseif eax & _IOREAD && eax & _IOMYBUF && !( eax & _IOSETVBUF )

		mov [ebx]._bufsiz,_MINIOBUF
	.endif

	mov eax,[ebx]._file
	mov eax,_osfhnd[eax*4]
	.if SetFilePointer( eax, off, 0, whence ) == -1

		osmaperr()
		jmp toend
	.endif
	xor eax,eax
toend:
	ret
error:
	mov errno,EINVAL
	mov eax,-1
	jmp toend
fseek	ENDP

	END
