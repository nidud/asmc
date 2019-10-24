include windows.inc
include stdio.inc
include winreg.inc
include locals.inc

    .code

wmain proc

  local hKey0:HKEY, hKey1:HKEY, hKey2:HKEY
  local Disposition:int_t, retval:int_t

    mov retval,1
    .ifd !RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Classes", 0, KEY_WRITE, &hKey0)

        .ifd !RegOpenKeyEx(hKey0, "CLSID", 0, KEY_ALL_ACCESS, &hKey1)

            .ifd !RegCreateKeyEx(hKey1, dll_clsid, 0, 0, REG_OPTION_NON_VOLATILE,
                        KEY_WRITE, 0, &hKey2, &Disposition)

                .ifd !RegDeleteKey(hKey2, "InprocServer32")

                    RegCloseKey(hKey2)
                    .ifd !RegDeleteKey(hKey1, dll_clsid)

                        mov retval,0
                        wprintf("Successfully removed IConfig.dll as a COM component.\n")
                    .endif
                .endif
            .endif
            RegCloseKey(hKey1)
        .endif
        RegCloseKey(hKey0)
    .endif

    .if retval

        wprintf("Failed to remove IConfig.dll as a COM component.\n")
    .endif

    exit(retval)
    ret

wmain endp

    end wmain
