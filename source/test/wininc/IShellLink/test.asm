;
; https://blogs.msdn.microsoft.com/oldnewthing/20180509-00/?p=98715
;
include windows.inc
include ole2.inc
include shlobj.inc
include stdio.inc

.data

CLSID_ShellLink         IID _CLSID_ShellLink
IID_IShellLink          IID _IID_IShellLinkW
IID_IPersistFile        IID _IID_IPersistFile
IID_IShellFolderViewCB  IID _IID_IShellFolderViewCB

.code

wmain proc

  local link:ptr IShellLinkW
  local file:ptr IPersistFile

    CoInitialize(NULL)
    .ifd CoCreateInstance(&CLSID_ShellLink, NULL,
            CLSCTX_INPROC_SERVER, &IID_IShellLink, &link) != S_OK

        wprintf("error: %x\n", eax)
    .else
        link.QueryInterface(&IID_IPersistFile, &file)
        link.SetPath("N:\\dir\\some file that doesn't exist.txt")
        file.Save("test.lnk", TRUE)
    .endif
    xor eax,eax
    ret

wmain endp

    end
