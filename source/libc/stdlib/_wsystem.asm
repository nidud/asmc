; _WSYSTEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include process.inc
include string.inc
include malloc.inc
include winbase.inc
include wincon.inc
include crtl.inc

externdef errorlevel:int_t

    .code

_wsystem proc uses rdi rsi rbx string:wstring_t

  local ProcessInfo     : PROCESS_INFORMATION,
        StartUpInfo     : STARTUPINFOW,
        lpCommand       : wstring_t,
        ConsoleMode     : uint_t,
        cmd[_MAX_PATH]  : wchar_t,
        delim           : wchar_t

    ldr rdi,string
ifdef _WIN64
    mov eax,0x10000
    _chkstk proto
    _chkstk()
endif
    mov rbx,wcscpy( alloca( 0x8000*2 ), L"cmd.exe" )

    .if !GetEnvironmentVariableW( L"Comspec", rbx, 0x8000 )

        SearchPathW( rax, L"cmd.exe", rax, 0x8000, rbx, rax )
    .endif
    wcscat( rbx, L" /C " )

    mov edx,' '
    .if ( wchar_t ptr [rdi] == '"' )
        add rdi,wchar_t
        mov dl,'"'
    .endif
    mov delim,dx

    mov rsi,wcschr( rdi, dx )
    .if rax
        mov wchar_t ptr [rax],0
    .endif
    wcsncpy( &cmd, rdi, _MAX_PATH - 1 )

    .if rsi
        mov [rsi],delim
        .if ax == '"'
            inc rsi
        .endif
    .else
        wcslen(string)
        add rax,rax
        add rax,string
        mov rsi,rax
    .endif
    mov rdi,rsi
    lea rsi,cmd
    .if wcschr( rsi, ' ' )
        wcscat( wcscat( wcscat( rbx, L"\"" ), rsi ), L"\"" )
    .else
        wcscat( rbx, rsi )
    .endif

    mov lpCommand,wcscat( rbx, rdi )

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
    mov StartUpInfo.cb,STARTUPINFOW

    SetErrorMode(_ermode)
    mov rbx,GetStdHandle(STD_INPUT_HANDLE)
    GetConsoleMode(rbx, &ConsoleMode)

    xor ecx,ecx
    mov rdi,CreateProcessW( rcx, lpCommand, rcx, rcx, ecx, ecx, rcx, rcx, rdi, rsi )
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
   .return( edi )

_wsystem endp

    end
