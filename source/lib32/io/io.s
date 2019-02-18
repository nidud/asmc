include io.inc
include stdio.inc
include string.inc
include fcntl.inc
include stat.inc

	.data
	buf db 4096 dup(?)
	.code

main	proc c

	.assert _creat("test.fil",S_IREAD or S_IWRITE) != -1
	.assert !_close(eax)
	.assert _open("test.fil",O_RDWR) == 3
	mov	esi,eax
	.assert !_chsize(esi,0)
	.assert !_filelength(esi)
	mov	ebx,8192
	.assert !_chsize(esi,ebx)
	.assert _filelength(esi) == 8192
	.repeat
		.assert _read(esi,addr buf,1) == 1
		.assert buf == 0
		dec	ebx
	.until	!ebx
	.assert _eof(esi) == 1
	.assert _filelength(esi) == 8192
	.assert _lseek(esi,16384,SEEK_SET) == 16384
	.assert _tell(esi) == 16384
	.assert _write(esi,"!",1) == 1
	.assert _lseek(esi,8192,SEEK_SET) == 8192
	sub	ebx,ebx
	.repeat
		.assert _read(esi,addr buf,1) == 1
		.assert buf == 0
		inc	ebx
	.until	ebx == 8192
	.assert _read(esi,addr buf,1) == 1
	.assert buf == '!'
	.assert !_close(esi)
	.assert !remove("test.fil")

	ret
main	endp

	end
