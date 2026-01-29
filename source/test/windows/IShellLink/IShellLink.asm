include shlobj.inc

    .data
    root TCHAR @CatStr(<!">, @Environ(ASMCDIR),<!">),0
    dz   TCHAR @CatStr(<!">, @Environ(ASMCDIR),<!">),"\bin\dz.exe",0

    .code

wmain proc

  local pShellLink:ptr IShellLink
  local pPersistFile:ptr IPersistFile

    .ifd CoInitialize(NULL) == S_OK

        .ifd CoCreateInstance(
                &CLSID_ShellLink,
                NULL,
                CLSCTX_INPROC_SERVER,
                &IID_IShellLink,
                &pShellLink ) == S_OK

            pShellLink.QueryInterface(
                &IID_IPersistFile,
                &pPersistFile )

            pShellLink.SetDescription("Doszip Commander")
            pShellLink.SetPath(&dz)
            pShellLink.SetWorkingDirectory(&root)
            pShellLink.SetIconLocation(&dz, 0)

            pPersistFile.Save("dz.lnk", TRUE)

        .endif
        CoUninitialize()
    .endif

    .return 0

wmain endp

    end
