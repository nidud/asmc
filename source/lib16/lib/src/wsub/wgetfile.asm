; WGETFILE.ASM--
; Copyright (C) 2015 Doszip Developers

include wsub.inc
include string.inc
include dos.inc
include io.inc
include iost.inc
include conio.inc

externdef configpath:BYTE
externdef IDD_DirectoryNotFound:DWORD

.code

MakeDirectory PROC _CType PUBLIC USES si di directory:DWORD
	.if filexist(directory) != 2
	    .if rsopen(IDD_DirectoryNotFound)
		mov si,dx
		mov di,ax
		invoke dlshow,dx::ax
		mov ax,es:[bx+4]
		add ax,0204h
		mov dl,ah
		invoke scpath,ax,dx,22,directory
		.if dlmodal(si::di)
		    invoke wsmkdir,directory
		    inc ax
		.endif
	    .endif
	.endif
	ret
MakeDirectory ENDP


wgetfile PROC _CType PUBLIC USES si fmask:PTR BYTE, flag:size_t
local	path[WMAXPATH]:BYTE
	mov	si,WORD PTR fmask
	add	si,2
	invoke	strfcat,addr path,addr configpath,ds::si
	invoke	MakeDirectory,dx::ax
	test	ax,ax
	jz	@F
	invoke	wdlgopen,addr path,fmask,flag
	jz	@F
	mov	si,ax
	.if flag & 1
	    invoke openfile,dx::ax,M_RDONLY,A_OPEN
	.else
	    invoke ogetouth,dx::ax
	.endif
	inc	ax
	jz	@F
	dec	ax
     @@:
	mov	dx,si
	ret
wgetfile ENDP

	END
