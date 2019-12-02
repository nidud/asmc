include direct.inc
include winbase.inc

    .code

GetVolumeID proc lpRootPathName:LPSTR, lpVolumeNameBuffer:LPSTR
local MaximumComponentLength, FileSystemFlags
    GetVolumeInformation(
	lpRootPathName,
	lpVolumeNameBuffer,
	64, ; length of lpVolumeNameBuffer
	0,  ; address of volume serial number
	addr MaximumComponentLength,
	addr FileSystemFlags,
	0,  ; address of name of file system
	0 ) ; length of lpFileSystemNameBuffer
    ret
GetVolumeID endp

    END
