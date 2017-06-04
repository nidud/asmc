include direct.inc
include string.inc
include errno.inc
include winbase.inc
include dzlib.inc

	.code

_disk_ready PROC disk

  local MaximumComponentLength: DWORD,
	FileSystemFlags:	DWORD,
	RootPathName[2]:	DWORD,
	FileSystemNameBuffer[32]:WORD

	mov eax,disk
	inc eax
	.if validdrive( eax )
		mov eax,'\: '
		mov al,BYTE PTR disk
		add al,'A' - 1
		mov RootPathName,eax
		GetVolumeInformation(
			addr RootPathName,
			0,
			0,
			0,
			addr MaximumComponentLength,
			addr FileSystemFlags,
			addr FileSystemNameBuffer,
			32 )
		test eax,eax
	.endif
	ret

_disk_ready ENDP

	END
