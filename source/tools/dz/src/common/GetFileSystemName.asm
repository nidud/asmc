include direct.inc
include winbase.inc

    .code

GetFileSystemName proc lpRootPathName:LPSTR, lpFileSystemNameBuffer:LPSTR

local MaximumComponentLength, FileSystemFlags

    GetVolumeInformation(
	lpRootPathName,
	0,
	0,
	0,
	&MaximumComponentLength,
	&FileSystemFlags,
	lpFileSystemNameBuffer,
	32)
    ret

GetFileSystemName endp

    END
