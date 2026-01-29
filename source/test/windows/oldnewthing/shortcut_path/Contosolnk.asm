;
; https://devblogs.microsoft.com/oldnewthing/20230208-00/?p=107807
;
; The 64-bit code that creates the shortcut (Contoso.lnk)
;
include windows.inc
include shlobj.inc
include stdio.inc
include tchar.inc

ifdef _MSVCRT
.data
 CLSID_ShellLink        GUID _CLSID_ShellLink
 IID_IShellLink         GUID _IID_IShellLinkW
 IID_IPersistFile       GUID _IID_IPersistFile
endif

.code

wmain proc

    .new hr:HRESULT = CoInitialize(NULL)

    .if (SUCCEEDED(hr))

       .new pShellLink:ptr IShellLinkW = NULL
        mov hr,CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, &IID_IShellLink, &pShellLink )

        .if (SUCCEEDED(hr))

           .new pPersistFile:ptr IPersistFile = NULL
            mov hr,pShellLink.QueryInterface(&IID_IPersistFile, &pPersistFile)
        .endif

        .if (SUCCEEDED(hr))

            pShellLink.SetPath("%ProgramFiles%\\Contoso\\Contoso.exe")
            mov hr,pPersistFile.Save("Contoso.lnk", TRUE)

        .endif

        .if (FAILED(hr))

           .new szMessage:ptr wchar_t
            mov edx,hr
            .if (HRESULT_FACILITY(edx) == FACILITY_WINDOWS)

                mov hr,HRESULT_CODE(edx)
            .endif

            FormatMessage(
                FORMAT_MESSAGE_ALLOCATE_BUFFER or \
                FORMAT_MESSAGE_FROM_SYSTEM or \
                FORMAT_MESSAGE_IGNORE_INSERTS,
                NULL,
                hr,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                &szMessage,
                0,
                NULL)

            wprintf("Error code: %08X\n\n%s", hr, szMessage)
            LocalFree(szMessage)
        .endif
        CoUninitialize()
    .endif
    .return( 0 )

wmain endp

    end _tstart
