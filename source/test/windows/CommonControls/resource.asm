; RESOURCE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include windows.inc
include wininet.inc
include stdio.inc
include tchar.inc

.code

GetResourceFile proc name:ptr wchar_t

  local wsaData             : WSADATA,
        hINet               : HINTERNET,
        hFile               : HANDLE,
        BytesRead           : uint_t,
        hr                  : HRESULT,
        fp                  : ptr FILE,
        file[64]            : wchar_t,
        link[512]           : wchar_t,
        buffer[1024]        : char_t

    wcscpy(&file, ".\\res\\")
    wcscat(&file, name)

    .ifd ( GetFileAttributes(&file) != -1 )
        .return S_OK
    .endif
    .ifd ( WSAStartup(2, &wsaData) != S_OK )
        .return E_FAIL
    .endif
    .if ( InternetOpen("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0) == FALSE )
        .return E_FAIL
    .endif

    mov hINet,rax
    mov hr,S_OK

    wcscpy(&link,
        "https://raw.githubusercontent.com/microsoftarchive/msdn-code-gallery-microsoft/"
        "411c271e537727d737a53fa2cbe99eaecac00cc0/OneCodeTeam/"
        "Windows%20common%20controls%20demo%20(CppWindowsCommonControls)/"
        "%5BC%2B%2B%5D-Windows%20common%20controls%20demo%20(CppWindowsCommonControls)/"
        "C%2B%2B/CppWindowsCommonControls/res/")
    wcscat(&link, name)

    wprintf("Downloading %s ", name)

    .if InternetOpenUrl(hINet, &link, NULL, 0, 0, 0 )

        mov hFile,rax
        .if _wfopen(&file, "wb")

            mov fp,rax
            .while 1
                InternetReadFile(hFile, &buffer, 1024, &BytesRead)
                .break .if !BytesRead
                fwrite(&buffer, BytesRead, 1, fp)
            .endw
            fclose(fp)
        .else
            mov hr,E_FAIL
        .endif
    .endif
    .if ( hr == S_OK )
        wprintf("OK\n")
    .else
        _wperror(name)
    .endif

    InternetCloseHandle(hINet)
    WSACleanup()
   .return hr

GetResourceFile endp

wmain proc uses rbx

  .new files[11]:wstring_t = {
        "error.ico",
        "Gear.ico",
        "info.ico",
        "Likely_unavail.ico",
        "New.ico",
        "preferences.ico",
        "share_overlay.ico",
        "Shortcut.ico",
        "UAC_shield.ico",
        "warning.ico",
        "upload.avi"
        }

    .for ( ebx = 0 : ebx < ARRAYSIZE(files) : ebx++ )

        .break .ifd GetResourceFile(files[rbx*wstring_t])
    .endf
    ret

wmain endp

    end _tstart
