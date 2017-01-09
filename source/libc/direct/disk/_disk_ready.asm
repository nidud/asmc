include direct.inc
include string.inc
include errno.inc

	.code

_disk_ready PROC disk
  local MaximumComponentLength,
	FileSystemFlags,
	RootPathName,
	FileSystemNameBuffer[32]:BYTE
	mov	eax,disk
	inc	eax
	validdrive( eax )
	jz	toend
	mov	eax,'\: '
	mov	al,BYTE PTR disk
	add	al,'A' - 1
	mov	RootPathName,eax
	GetVolumeInformation( addr RootPathName, 0, 0, 0, addr MaximumComponentLength,
		addr FileSystemFlags, addr FileSystemNameBuffer, 32 )
	test	eax,eax
toend:
	ret
_disk_ready ENDP

	END
