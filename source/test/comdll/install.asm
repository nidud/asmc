include windows.inc
include stdio.inc
include winreg.inc
include locals.inc

    .code

wmain proc

    local hKey0:HKEY, hKey1:HKEY, hKey2:HKEY, hKey3:HKEY
    local Disposition:int_t, retval:int_t

    mov retval,1
    .if !RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Classes", 0, KEY_WRITE, &hKey0)
        .if !RegOpenKeyEx(hKey0, "CLSID", 0, KEY_ALL_ACCESS, &hKey1)
            .if !RegCreateKeyEx(hKey1, dll_clsid, 0, 0, REG_OPTION_NON_VOLATILE,
                    KEY_WRITE, 0, &hKey2, &Disposition)
                RegSetValueEx(hKey2, 0, 0, REG_SZ, "IConfig COM component", sizeof(DS0003))
                .if !RegCreateKeyEx(hKey2, "InprocServer32", 0, 0, REG_OPTION_NON_VOLATILE,
                        KEY_WRITE, 0, &hKey3, &Disposition)
                    .if !RegSetValueEx(hKey3, 0, 0, REG_SZ, dll_path, sizeof(DS0005) + TCHAR)
                        .if !RegSetValueEx(hKey3, "ThreadingModel", 0, REG_SZ,
                                "both", sizeof(DS0007))
                            mov retval,0
                            wprintf("Successfully registered IConfig.dll as a COM component.\n")
                        .endif
                    .endif
                    RegCloseKey(hKey3)
                .endif
                RegCloseKey(hKey2)
            .endif
            RegCloseKey(hKey1)
        .endif
        RegCloseKey(hKey0)
    .endif
    .if ( retval )
        wprintf("Failed to registered IConfig.dll as a COM component.\n")
        .if !RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Classes", 0, KEY_WRITE, &hKey0)
            .if !RegOpenKeyEx(hKey0, "CLSID", 0, KEY_ALL_ACCESS, &hKey1)
                .if !RegCreateKeyEx(hKey1, dll_clsid, 0, 0, REG_OPTION_NON_VOLATILE,
                        KEY_WRITE, 0, &hKey2, &Disposition)
                    RegDeleteKey(hKey2, "InprocServer32")
                    RegCloseKey(hKey2)
                    RegDeleteKey(hKey1, dll_clsid)
                .endif
                RegCloseKey(hKey1)
            .endif
            RegCloseKey(hKey0)
        .endif
    .endif
    exit(retval)
    ret

wmain endp

    end wmain
