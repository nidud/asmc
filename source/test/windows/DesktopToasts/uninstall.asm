;
; Clean up the shortcut and COM registration.
;
include Windows.inc
include winreg.inc
include Shlobj.inc
include Pathcch.inc
include tchar.inc

.data
FOLDERID_RoamingAppData GUID {0x3EB685DB,0x65F9,0x4CF6,{0xA0,0x3A,0xE3,0xEF,0x65,0x72,0x9F,0x3D}}

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
   .return(0)

_tmain endp

end _tstart
