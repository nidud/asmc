include direct.inc
include winbase.inc

	.code

GetFileSystemName PROC lpRootPathName:LPSTR, lpFileSystemNameBuffer:LPSTR

local	MaximumComponentLength,
	FileSystemFlags

	GetVolumeInformation(
		lpRootPathName,
		0,
		0,
		0,
		addr MaximumComponentLength,
		addr FileSystemFlags,
		lpFileSystemNameBuffer,
		32 )

	ret

GetFileSystemName ENDP

	END
