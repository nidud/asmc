include io.inc
include stdio.inc
include string.inc
include fcntl.inc
include stat.inc

	.code

main	proc

local	buf[4096]:byte

	.assert _creat("test.fil",S_IREAD or S_IWRITE) != -1
	.assert _close(eax) == 0
	.assert _open("test.fil",O_RDWR) == 3
	mov	esi,eax
	.assert _chsize(esi,0) == 0
	.assert filelength(esi) == 0
	mov	rbx,8192
	.assert _chsize(esi,rbx) == 0
	.assert filelength(esi) == 8192
	.repeat
		.assert _read(esi,addr buf,1) == 1
		.assert buf == 0
		dec	ebx
	.until	!ebx
	.assert _eof(esi) == 1
	.assert filelength(esi) == 8192
	.assert _lseek(esi,16384,SEEK_SET) == 16384
	.assert _tell(esi) == 16384
	.assert _write(esi,"!",1) == 1
	.assert _lseek(esi,8192,SEEK_SET) == 8192
	xor	ebx,ebx
	.repeat
		.assert _read(esi,addr buf,1) == 1
		.assert buf == 0
		inc	ebx
	.until	ebx == 8192
	.assert _read(esi,addr buf,1) == 1
	.assert buf == '!'
	.assert _close(esi) == 0
	.assert remove("test.fil") == 0
	xor	eax,eax
	ret

main	endp

	end
