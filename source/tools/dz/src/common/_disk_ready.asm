include direct.inc
include string.inc
include errno.inc
include winbase.inc
include dzlib.inc

    .code

_disk_ready proc disk

  local MaximumComponentLength:dword,
	FileSystemFlags:dword,
	RootPathName[2]:dword,
	FileSystemNameBuffer[32]:word

    mov eax,disk
    inc eax
    .if validdrive(eax)
	mov eax,'\: '
	mov al,byte ptr disk
	add al,'A' - 1
	mov RootPathName,eax
	GetVolumeInformation(
	    &RootPathName,
	    0,
	    0,
	    0,
	    &MaximumComponentLength,
	    &FileSystemFlags,
	    &FileSystemNameBuffer,
	    32)
	test eax,eax
    .endif
    ret

_disk_ready endp

    END
