;
; Clean up the shortcut and COM registration.
;
include windows.inc
include winreg.inc
include shlobj.inc
include pathcch.inc
include tchar.inc

.data
 DECLARE_GUID(FOLDERID_RoamingAppData)

.code
_tmain proc
    .new appData:PWSTR
    .new hr:HRESULT = SHGetKnownFolderPath(&FOLDERID_RoamingAppData, 0, NULL, &appData)
    .if (SUCCEEDED(hr))
       .new shortcutPath[MAX_PATH]:wchar_t
        mov hr,PathCchCombine(&shortcutPath, ARRAYSIZE(shortcutPath),
                appData, "Microsoft\\Windows\\Start Menu\\Programs\\Desktop Toasts App.lnk")
        .if (SUCCEEDED(hr))
            DeleteFileW(&shortcutPath)
        .endif
    .endif
    RegDeleteTree(HKEY_CURRENT_USER, "SOFTWARE\\Classes\\CLSID\\{23A5B06E-20BB-4E7E-A0AC-6982ED6A6041}")
    .return( 0 )
    endp
    end _tstart
