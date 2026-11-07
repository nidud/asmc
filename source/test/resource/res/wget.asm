;
; download resources from ../msdn-code-gallery-microsoft/
;
include windows.inc
include wininet.inc
include stdio.inc
include tchar.inc

define URL1 <"https://raw.githubusercontent.com/microsoftarchive/msdn-code-gallery-microsoft/411c271e537727d737a53fa2cbe99eaecac00cc0/Official%20Windows%20Platform%20Sample/DPI%20Tutorial%20sample/[C%2B%2B]-DPI%20Tutorial%20sample/C%2B%2B/">
define URL2 <"https://raw.githubusercontent.com/microsoftarchive/msdn-code-gallery-microsoft/411c271e537727d737a53fa2cbe99eaecac00cc0/OneCodeTeam/Windows%20common%20controls%20demo%20(CppWindowsCommonControls)/%5BC%2B%2B%5D-Windows%20common%20controls%20demo%20(CppWindowsCommonControls)/C%2B%2B/CppWindowsCommonControls/res/">

.code

GetResource proc pUrl:LPWSTR, pFile:LPWSTR
  local wsaData     : WSADATA,
        hINet       : HINTERNET,
        hFile       : HANDLE,
        BytesRead   : uint_t,
        hr          : HRESULT,
        fp          : ptr FILE,
        file[64]    : wchar_t,
        link[512]   : wchar_t,
        buffer[1024]: char_t

    wcscpy(&file, ".\\res\\")
    wcscat(&file, pFile)
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
    wcscpy(&link, pUrl)
    wcscat(&link, pFile)
    wprintf("Downloading %s ", pFile)
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
        _wperror(pFile)
    .endif
    InternetCloseHandle(hINet)
    WSACleanup()
    .return hr
    endp

wmain proc uses rbx
    .new url1[5]:wstring_t = {
        "scaled100.bmp",
        "scaled125.bmp",
        "scaled150.bmp",
        "scaled200.bmp",
        "small.ico" }
    .new url2[11]:wstring_t = {
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
        "upload.avi" }
    .for ( ebx = 0 : ebx < ARRAYSIZE(url1) : ebx++ )
        .break .ifd GetResource(URL1, url1[rbx*wstring_t])
    .endf
    .for ( ebx = 0 : ebx < ARRAYSIZE(url2) : ebx++ )
        .break .ifd GetResource(URL2, url2[rbx*wstring_t])
    .endf
    ret
    endp

    end _tstart
