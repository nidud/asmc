; PROCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include process.inc
include string.inc
include conio.inc
include crtl.inc

    public errorlevel  ; Exit Code from GetExitCodeProcess

    .data
    errorlevel dd 0

    .code

process proc uses rsi rdi program:LPSTR, command:LPSTR, CreationFlags:DWORD

  local PI:PROCESS_INFORMATION, SINFO:STARTUPINFO, ConsoleMode:dword

    _set_errno(0)
    mov errorlevel,0

    lea rdi,PI
    mov rsi,rdi
    mov ecx,sizeof(PROCESS_INFORMATION)
    rep stosb

    lea rdi,SINFO
    mov ecx,sizeof(STARTUPINFO)
    rep stosb

    lea rdi,SINFO
    mov SINFO.cb,sizeof(STARTUPINFO)

    SetErrorMode(OldErrorMode)
    GetConsoleMode(hStdInput, &ConsoleMode)

    mov r10d,CreationFlags
    and r10d,CREATE_NEW_CONSOLE or DETACHED_PROCESS
    xor eax,eax
    mov rdi,CreateProcess(program, command, rax, rax, eax, r10d, rax, rax, rdi, rsi)
    mov rsi,PI.hProcess
    _dosmaperr(GetLastError())

    .if rdi

        .if !( CreationFlags & _P_NOWAIT )

            WaitForSingleObject(rsi, INFINITE)
            GetExitCodeProcess(rsi, &errorlevel)
        .endif

        CloseHandle(rsi)
        CloseHandle(PI.hThread)
    .endif


    mov hStdOutput,GetStdHandle(STD_OUTPUT_HANDLE)
    mov hStdInput,GetStdHandle(STD_INPUT_HANDLE)
    SetConsoleMode(rax, ConsoleMode)
    SetErrorMode(SEM_FAILCRITICALERRORS)

    mov eax,edi
    ret

process endp

    end
