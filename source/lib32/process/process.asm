include io.inc
include errno.inc
include process.inc
include string.inc
include crtl.inc
include conio.inc
include winbase.inc

    .data
    errorlevel dd 0

    .code

process proc uses esi edi lpProgram:LPSTR, lpCommand:LPSTR, CreationFlags:dword

local PI:PROCESS_INFORMATION, SINFO:STARTUPINFO, ConsoleMode:dword

    xor eax,eax
    mov errno,eax
    mov errorlevel,eax
    lea edi,PI
    mov esi,edi
    mov ecx,sizeof(PROCESS_INFORMATION)
    rep stosb
    lea edi,SINFO
    mov ecx,sizeof(STARTUPINFO)
    rep stosb
    lea edi,SINFO
    mov SINFO.cb,sizeof(STARTUPINFO)

    SetErrorMode(OldErrorMode)
    GetConsoleMode(hStdInput, &ConsoleMode)

    mov edx,CreationFlags
    and edx,CREATE_NEW_CONSOLE or DETACHED_PROCESS
    xor eax,eax
    CreateProcess(lpProgram, lpCommand, eax, eax, eax, edx, eax, eax, edi, esi)
    mov edi,eax
    mov esi,PI.hProcess
    osmaperr()

    .if edi
        .if !(CreationFlags & _P_NOWAIT)

            WaitForSingleObject(esi, INFINITE)
            GetExitCodeProcess(esi, &errorlevel)
        .endif
        CloseHandle(esi)
        CloseHandle(PI.hThread)
    .endif

    mov hStdOutput, GetStdHandle(STD_OUTPUT_HANDLE)
    mov hStdInput,  GetStdHandle(STD_INPUT_HANDLE)
    SetConsoleMode(eax, ConsoleMode)
    SetErrorMode(SEM_FAILCRITICALERRORS)
ifdef __DZ__
    mov byte ptr _diskflag,3
endif
    mov eax,edi
    ret
process endp

    END
