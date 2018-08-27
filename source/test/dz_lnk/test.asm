include windows.inc
include shlobj.inc
include stdio.inc

ROOT equ <"C:\\Asmc">

.code

wmain proc

  local link:ptr IShellLinkW
  local file:ptr IPersistFile

    CoInitialize(NULL)
    .ifd CoCreateInstance(&CLSID_ShellLink, NULL,
            CLSCTX_INPROC_SERVER, &IID_IShellLink, &link) == S_OK

        link.QueryInterface(&IID_IPersistFile, &file)

        link.SetDescription("Doszip Commander")
        link.SetPath(ROOT "\\bin\\dz.exe")
        link.SetWorkingDirectory(ROOT)
        link.SetIconLocation(ROOT "\\bin\\dz.exe", 0)

        file.Save("dz.lnk", TRUE)
    .endif
    xor eax,eax
    ret

wmain endp

    end
