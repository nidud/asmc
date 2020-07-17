; SYSTEM.ASM--
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

public errorlevel

MAXCMDL equ 0x8000

    .data
    errorlevel dd 0

    .code

    option cstack:on

; CreationFlags: CREATE_NEW_CONSOLE, DETACHED_PROCESS

Process proc private uses esi edi ebx lpProgram:LPSTR, lpCommand:LPSTR, CreationFlags:dword

  local ProcessInfo : PROCESS_INFORMATION,
        StartUpInfo : STARTUPINFO,
        ConsoleMode : dword

    xor eax,eax
    mov errno,eax
    mov errorlevel,eax

    lea edi,ProcessInfo
    mov esi,edi
    mov ecx,sizeof(ProcessInfo)
    rep stosb

    lea edi,StartUpInfo
    mov ecx,sizeof(StartUpInfo)
    rep stosb
    lea edi,StartUpInfo
    mov StartUpInfo.cb,STARTUPINFO

    SetErrorMode(OldErrorMode)
    mov ebx,GetStdHandle(STD_INPUT_HANDLE)
    GetConsoleMode(ebx, &ConsoleMode)

    mov edx,CreationFlags
    and edx,CREATE_NEW_CONSOLE or DETACHED_PROCESS
    xor eax,eax
    mov edi,CreateProcess(lpProgram, lpCommand, eax, eax, eax, edx, eax, eax, edi, esi)
    mov esi,ProcessInfo.hProcess
    osmaperr()
    .if edi
        .if !(CreationFlags & _P_NOWAIT)

            WaitForSingleObject(esi, INFINITE)
            GetExitCodeProcess(esi, &errorlevel)
        .endif
        CloseHandle(esi)
        CloseHandle(ProcessInfo.hThread)
    .endif
    SetConsoleMode(ebx, ConsoleMode)
    SetErrorMode(SEM_FAILCRITICALERRORS)
    mov eax,edi
    ret

Process endp

system proc uses edi esi ebx string:LPSTR

  local cmd[_MAX_PATH]:sbyte

    mov ebx,strcpy( alloca( MAXCMDL ), "cmd.exe" )

    .if !GetEnvironmentVariable( "Comspec", ebx, MAXCMDL )

        SearchPath( eax, "cmd.exe", eax, MAXCMDL, ebx, eax )
    .endif
    strcat(ebx, " /C ")

    mov edi,string
    mov edx,' '
    .if byte ptr [edi] == '"'
        inc edi
        mov edx,'"'
    .endif

    xor esi,esi
    .if strchr( edi, edx )
        mov byte ptr [eax],0
        mov esi,eax
    .endif
    strncpy( &cmd, edi, _MAX_PATH-1 )
    .if esi
        mov [esi],dl
        .if dl == '"'
        inc esi
        .endif
    .else
        strlen( string )
        add eax,string
        mov esi,eax
    .endif
    mov edi,esi
    lea esi,cmd
    .if strchr( esi, ' ' )
        strcat( strcat( strcat( ebx, "\"" ), esi ), "\"" )
    .else
        strcat( ebx, esi )
    .endif
    Process( 0, strcat( ebx, edi ), 0 )
    ret

system endp

    END
