;
; https://msdn.microsoft.com/en-us/library/windows/desktop/ms724340(v=vs.85).aspx
;
include windows.inc
include stdio.inc
include tchar.inc

.code

main proc

    local s:SYSTEM_INFO
    local ns:SYSTEM_INFO

    GetSystemInfo(&s)
    GetNativeSystemInfo(&ns)

    printf(
        "lpMaximumApplicationAddress:\n"
        "  7FFEFFFF: 32-bit Windows 2GB minus 64KB\n"
        "  BFFFFFFF: 32-bit Windows 3GB\n"
        "  BB3EFFFF: 32-bit Windows 2995 MB\n"
        "  FFFEFFFF: 64-bit Windows 2GB minus 64KB/4GB minus 64KB\n"
        "wProcessorArchitecture:\n"
        "  0: x86\n"
        "  9: x64 (AMD or Intel)\n\n"
        "GetSystemInfo():\n"
        "wProcessorArchitecture      %d\n"
        "lpMaximumApplicationAddress %08X\n"
        "\nGetNativeSystemInfo():\n"
        "wProcessorArchitecture      %d\n"
        "lpMaximumApplicationAddress %08X\n",
        s.wProcessorArchitecture,
        s.lpMaximumApplicationAddress,
        ns.wProcessorArchitecture,
        ns.lpMaximumApplicationAddress )

    xor eax,eax
    ret

main endp

    end _tstart
