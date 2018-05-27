;
; https://msdn.microsoft.com/en-us/library/windows/desktop/bb762114(v=vs.85).aspx
;
include windows.inc
include shlobj.inc
include shlwapi.inc
include stdio.inc
include tchar.inc

.data
IID_IShellFolder	GUID _IID_IShellFolder
IID_IShellFolderViewCB	GUID _IID_IShellFolderViewCB

.code

main proc

  local psfParent:LPIShellFolder
  local pidlRelative:ptr PCUITEMID_CHILD
  local pidlItem:PIDLIST_ABSOLUTE
  local szDisplayName[MAX_PATH]:TCHAR
  local strret:STRRET

    mov pidlItem,ILCreateFromPath("C:\\")
    .ifd !SHBindToParent(pidlItem, &IID_IShellFolder, &psfParent, &pidlRelative)

	psfParent.GetDisplayNameOf(pidlRelative, SHGDN_NORMAL, &strret)
	psfParent.Release()
	StrRetToBuf(&strret, pidlRelative, &szDisplayName, MAX_PATH)
	printf("%s\n", &szDisplayName)
    .endif

    ILFree(pidlItem)
    xor eax,eax
    ret

main endp

    end _tstart
