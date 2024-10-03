include windows.inc

    .code

DllProc proc WINAPI string:LPSTR

    MessageBox(NULL, string, "DllProc", MB_OK)
    ret

DllProc endp

DllMain proc WINAPI hinstDLL:HANDLE, fdwReason:DWORD, lpvReserved:ptr

    mov eax,TRUE
    ret

DllMain endp

    end
