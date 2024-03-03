; _TSYSTEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
ifndef __UNIX__
include process.inc
include string.inc
include malloc.inc
include winbase.inc
include wincon.inc
endif
include tchar.inc

externdef errorlevel:int_t

    .code

_tsystem proc uses rdi rsi rbx string:LPTSTR
ifdef __UNIX__
    int 3
else
  local ProcessInfo     : PROCESS_INFORMATION,
        StartUpInfo     : STARTUPINFO,
        lpCommand       : LPTSTR,
        ConsoleMode     : uint_t,
        cmd[_MAX_PATH]  : TCHAR,
        delim           : TCHAR

    ldr rdi,string
ifdef _WIN64
    mov eax,0x10000
    _chkstk proto
    _chkstk()
endif
    mov rbx,_tcscpy( alloca( 0x8000*TCHAR ), "cmd.exe" )

    .if !GetEnvironmentVariable( "Comspec", rbx, 0x8000 )

        SearchPath( rax, "cmd.exe", rax, 0x8000, rbx, rax )
    .endif
    _tcscat( rbx, " /C " )

    mov edx,' '
    .if ( TCHAR ptr [rdi] == '"' )
        add rdi,TCHAR
        mov dl,'"'
    .endif
    mov delim,_tdl

    mov rsi,_tcschr( rdi, edx )
    .if rax
        mov TCHAR ptr [rax],0
    .endif
    _tcsncpy( &cmd, rdi, _MAX_PATH - 1 )

    .if rsi
        mov [rsi],delim
        .if _tal == '"'
            inc rsi
        .endif
    .else
        mov rsi,string
        add rsi,_tcslen(rsi)
ifdef _UNICODE
        add rsi,rax
endif
    .endif
    mov rdi,rsi
    lea rsi,cmd
    .if _tcschr( rsi, ' ' )
        _tcscat( _tcscat( _tcscat( rbx, "\"" ), rsi ), "\"" )
    .else
        _tcscat( rbx, rsi )
    .endif

    mov lpCommand,_tcscat( rbx, rdi )

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

endif
    ret

_tsystem endp

    end
