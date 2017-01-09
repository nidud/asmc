include direct.inc
include io.inc
include string.inc
include time.inc
include crtl.inc
include wsub.inc

PUBLIC	drvinfo

	.data
	drvinfo S_DISK MAXDRIVES dup(<?>)

	.code

_disk_read PROC USES esi edi ebx

	mov	esi,clock()
	mov	edi,GetLogicalDrives()
	lea	ebx,drvinfo
	mov	ecx,1
l1:
	sub	eax,eax
	mov	[ebx].S_DISK.di_flag,eax
	shr	edi,1
	jnc	l4
	_disk_type( ecx )
	cmp	eax,1
	jna	l3
	mov	edx,_FB_ROOTDIR or _A_VOLID
	cmp	eax,DRIVE_CDROM
	jne	l2
	or	edx,_FB_CDROOM
l2:
	mov	[ebx].S_DISK.di_flag,edx
l3:
	mov	[ebx].S_DISK.di_time,esi
l4:
	add	ebx,SIZE S_DISK
	inc	ecx
	cmp	ecx,MAXDRIVES+1
	jne	l1
	ret
_disk_read ENDP

InitDisk:
	lea	edx,drvinfo
	mov	ecx,1
	mov	eax,':A'
@@:
	mov	DWORD PTR [edx].S_DISK.di_name,eax
	mov	DWORD PTR [edx].S_DISK.di_size,ecx
	inc	eax
	add	edx,SIZE S_DISK
	inc	ecx
	cmp	ecx,MAXDRIVES+1
	jne	@B
@@:
	call	_disk_read
	ret

pragma_init InitDisk, 11

	END
