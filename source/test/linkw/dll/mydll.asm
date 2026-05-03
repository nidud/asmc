include windows.inc
ifdef __DLL__
.pragma comment(linker, "/entry:DllMain")
endif

    .code

DllProc proc WINAPI _CRTIMP string:LPSTR

    MessageBox(NULL, string, "DllProc", MB_OK)
    ret

DllProc endp

DllMain proc WINAPI hinstDLL:HANDLE, fdwReason:DWORD, lpvReserved:ptr

    mov eax,TRUE
    ret

DllMain endp

    end
