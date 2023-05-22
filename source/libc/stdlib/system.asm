; SYSTEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc
include malloc.inc
include winbase.inc
include wincon.inc
include crtl.inc

externdef errorlevel:int_t

    .code

system proc uses rdi rsi rbx string:string_t

  local ProcessInfo     : PROCESS_INFORMATION,
        StartUpInfo     : STARTUPINFO,
        lpCommand       : string_t,
        ConsoleMode     : uint_t,
        ErrorMode       : uint_t,
        cmd[_MAX_PATH]  : char_t,
        delim           : char_t

    ldr rdi,string
ifdef _WIN64
    mov eax,0x8000
    _chkstk proto
    _chkstk()
endif
    mov rbx,strcpy( alloca( 0x8000 ), "cmd.exe" )

    .if !GetEnvironmentVariable( "Comspec", rbx, 0x8000 )

        SearchPath( rax, "cmd.exe", rax, 0x8000, rbx, rax )
    .endif
    strcat( rbx, " /C " )

    mov edx,' '
    .if byte ptr [rdi] == '"'
        inc rdi
        mov dl,'"'
    .endif
    mov delim,dl

    mov rsi,strchr( rdi, edx )
    .if rax
        mov byte ptr [rax],0
    .endif
    strncpy( &cmd, rdi, _MAX_PATH - 1 )

    .if rsi
        mov [rsi],delim
        .if al == '"'
            inc rsi
        .endif
    .else
        strlen(string)
        add rax,string
        mov rsi,rax
    .endif
    mov rdi,rsi
    lea rsi,cmd
    .if strchr( rsi, ' ' )
        strcat( strcat( strcat( rbx, "\"" ), rsi ), "\"" )
    .else
        strcat( rbx, rsi )
    .endif

    mov lpCommand,strcat( rbx, rdi )

    _set_errno(0)
    xor eax,eax
    mov errorlevel,eax

    lea rdi,ProcessInfo
    mov rsi,rdi
    mov ecx,sizeof(ProcessInfo)
    rep stosb

    lea rdi,StartUpInfo
    mov ecx,sizeof(StartUpInfo)
    rep stosb

    lea rdi,StartUpInfo
    mov StartUpInfo.cb,STARTUPINFO

    SetErrorMode(_ermode)
    mov rbx,GetStdHandle(STD_INPUT_HANDLE)
    GetConsoleMode(rbx, &ConsoleMode)

    xor ecx,ecx
    mov rdi,CreateProcess( rcx, lpCommand, rcx, rcx, ecx, ecx, rcx, rcx, rdi, rsi )
    mov rsi,ProcessInfo.hProcess

    _dosmaperr(GetLastError())

    .if rdi

        WaitForSingleObject( rsi, INFINITE )
        GetExitCodeProcess( rsi, &errorlevel )
        CloseHandle( rsi )
        CloseHandle( ProcessInfo.hThread )
    .endif

    SetConsoleMode( rbx, ConsoleMode )
    SetErrorMode( SEM_FAILCRITICALERRORS )
    mov eax,edi
    ret

system endp

    end
