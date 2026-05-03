; SHELLEXECUTEEX.ASM--
;
; https://learn.microsoft.com/en-us/windows/win32/shell/launch
;

include shlobj.inc
include shlwapi.inc
include objbase.inc
include tchar.inc

ifdef __PE__
.data
 IID_IShellFolder GUID _IID_IShellFolder
endif

.code

_tmain proc

   .new pidlWinFiles:LPITEMIDLIST = NULL
   .new pidlItems:LPITEMIDLIST = NULL
   .new psfWinFiles:ptr IShellFolder = NULL
   .new psfDeskTop:ptr IShellFolder = NULL
   .new ppenum:LPENUMIDLIST = NULL
   .new strDispName:STRRET
   .new pszParseName[MAX_PATH]:TCHAR
   .new celtFetched:ULONG
   .new ShExecInfo:SHELLEXECUTEINFO
   .new hr:HRESULT
   .new fBitmap:BOOL = FALSE

    SHGetFolderLocation(NULL, CSIDL_WINDOWS, NULL, NULL, &pidlWinFiles)
    SHGetDesktopFolder(&psfDeskTop)
    psfDeskTop.BindToObject(pidlWinFiles, NULL, &IID_IShellFolder, &psfWinFiles)
    psfDeskTop.Release()
    psfWinFiles.EnumObjects(NULL,SHCONTF_FOLDERS or SHCONTF_NONFOLDERS, &ppenum)
    .whiled ( ppenum.Next(1, &pidlItems, &celtFetched) == S_OK && celtFetched == 1 )
        psfWinFiles.GetDisplayNameOf(pidlItems, SHGDN_FORPARSING, &strDispName)
        StrRetToBuf(&strDispName, pidlItems, &pszParseName, MAX_PATH)
        CoTaskMemFree(pidlItems)
        .ifd ( StrCmpI(PathFindExtension(&pszParseName), ".bmp") == 0 )
            mov fBitmap,TRUE
           .break
        .endif
    .endw
    ppenum.Release()
    .if ( fBitmap )
        mov ShExecInfo.cbSize,sizeof(SHELLEXECUTEINFO)
        mov ShExecInfo.fMask,NULL
        mov ShExecInfo.hwnd,NULL
        mov ShExecInfo.lpVerb,NULL
        mov ShExecInfo.lpFile,&pszParseName
        mov ShExecInfo.lpParameters,NULL
        mov ShExecInfo.lpDirectory,NULL
        mov ShExecInfo.nShow,SW_MAXIMIZE
        mov ShExecInfo.hInstApp,NULL
        ShellExecuteEx(&ShExecInfo)
    .endif
    CoTaskMemFree(pidlWinFiles)
    psfWinFiles.Release()
    .return 0
    endp

    end _tstart
