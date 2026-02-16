;
; https://blogs.msdn.microsoft.com/oldnewthing/20180509-00/?p=98715
;
include windows.inc
include shlobj.inc
include stdio.inc
include tchar.inc

 ifdef _MSVCRT
    .data
     CLSID_ShellLink GUID _CLSID_ShellLink
     IID_IShellLink GUID _IID_IShellLinkW
     IID_IPersistFile GUID _IID_IPersistFile
     IID_IShellFolderViewCB GUID _IID_IShellFolderViewCB
 endif

.code

wmain proc

  local pShellLink:ptr IShellLinkW
  local pPersistFile:ptr IPersistFile

    CoInitialize(NULL)
    .ifd ( CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                &IID_IShellLink, &pShellLink) != S_OK )
        wprintf("error: %x\n", eax)
    .else
        pShellLink.QueryInterface(&IID_IPersistFile, &pPersistFile)
        pShellLink.SetPath("N:\\dir\\some file that doesn't exist.txt")
        pPersistFile.Save("test.lnk", TRUE)
    .endif
    .return 0
    endp

    end _tstart
