include stdio.inc
include winbase.inc

    .code

DllProc proc WINAPI export

    printf( "DllProc() called\n" )
    ret

DllProc endp

DllMain proc WINAPI hinstDLL:HINSTANCE, fdwReason:DWORD, lpvReserved:LPVOID

    mov eax,TRUE
    ret

DllMain endp

    end DllMain