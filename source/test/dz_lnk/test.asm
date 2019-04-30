include shlobj.inc

    .data
    root TCHAR @CatStr(<!">, @Environ(ASMCDIR),<!">),0
    dz   TCHAR @CatStr(<!">, @Environ(ASMCDIR),<!">),"\bin\dz.exe",0

    .code

wmain proc

  local link:ptr IShellLinkW
  local file:ptr IPersistFile

    CoInitialize(NULL)
    .ifd CoCreateInstance(&CLSID_ShellLink, NULL,
            CLSCTX_INPROC_SERVER, &IID_IShellLink, &link) == S_OK

        link.QueryInterface(&IID_IPersistFile, &file)
        link.SetDescription("Doszip Commander")
        link.SetPath(&dz)
        link.SetWorkingDirectory(&root)
        link.SetIconLocation(&dz, 0)
        file.Save("dz.lnk", TRUE)
    .endif
    CoUninitialize()
    xor eax,eax
    ret

wmain endp

    end
