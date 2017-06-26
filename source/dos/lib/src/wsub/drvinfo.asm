; DRVINFO.ASM--
; Copyright (C) 2015 Doszip Developers

include dir.inc
include dos.inc
include fblk.inc
include wsub.inc

	PUBLIC	drvinfo

	.data

drvinfo S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'A:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'B:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'C:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'D:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'E:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'F:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'G:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'H:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'I:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'J:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'K:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'L:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'M:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'N:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'O:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'P:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'Q:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'R:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'S:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'T:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'U:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'V:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'W:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'X:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'Y:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'Z:'>
	S_DISK <_A_VOLID or _A_ROOTDIR,0,0,0,'[:'>

	.code

Init20: call	dostime
	push	bx
	xor	cx,cx
	mov	bx,offset drvinfo
      @@:
	stom	[bx].S_DISK.di_time
	mov	WORD PTR [bx].S_DISK.di_sizeax,cx
	add	bx,SIZE S_DISK
	inc	cx
	cmp	cx,MAXDRIVES
	jb	@B
	pop	bx
	ret

pragma_init Init20, 11

	END
