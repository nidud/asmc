; _TSPAWNVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; intptr_t _spawnve(int mode, char *cmdname, char **argv, char **envp);
; intptr_t _wspawnve(int mode, wchar_t *cmdname, wchar_t **argv, wchar_t **envp);
;
include process.inc
include string.inc
include errno.inc
include io.inc
ifdef __UNIX__
include sys/syscall.inc
include sys/wait.inc
include unistd.inc
else
include winbase.inc
include wincon.inc
endif
include tchar.inc

if not defined(_UNICODE) and not defined(__UNIX__)
undef spawnve
ALIAS <spawnve>=<_spawnve>
endif

.code

_tspawnve proc uses rsi rdi rbx mode:int_t, name:tstring_t, argv:tarray_t, envp:tarray_t

   .new syncexec:char_t = 0
   .new asyncresult:char_t = 0
   .new background:char_t = 0
   .new retval:intptr_t
   .new exitcode:int_t
ifdef __UNIX__
   .new pid:pid_t
else
   .new cmd:tstring_t
   .new env:tstring_t = 0
   .new StartupInfo:STARTUPINFO
   .new ProcessInformation:PROCESS_INFORMATION
   .new CreateProcessStatus:BOOL
   .new dosretval:ULONG
ifdef _UNICODE
   .new fdwCreate:DWORD = CREATE_UNICODE_ENVIRONMENT
else
   .new fdwCreate:DWORD = 0
endif
   .new nh:int_t
   .new env_size:int_t = 0
   .new cmd_size:int_t
   .new hnd_size:int_t
   .new ConsoleMode:uint_t
endif
    ldr ecx,mode
    ldr rbx,argv

    .switch ecx
    .case _P_WAIT
        mov syncexec,1
       .endc
    .case _P_OVERLAY
    .case _P_NOWAITO
       .endc
    .case _P_NOWAIT
        mov asyncresult,1
       .endc
    .case _P_DETACH
        mov background,1
       .endc
    .default
        .return( _set_errno(EINVAL) )
    .endsw
    .if ( !rbx || tarray_t ptr [rbx] == 0 )
        .return( _set_errno(EINVAL) )
    .endif

ifndef __UNIX__
    .for ( rsi = rbx, edi = 1 : tarray_t ptr [rsi] : rsi+=tarray_t )
        lea rdi,[rdi+_tcslen([rsi])+1]
    .endf
    lea rax,[rdi*TCHAR+15]
    and eax,-16
    mov cmd_size,eax
    mov rsi,envp
    .if ( rsi )
        .for ( edi = 2 : tarray_t ptr [rsi] : rsi+=tarray_t )
            lea rdi,[rdi+_tcslen([rsi])+1]
        .endf
        lea rax,[rdi*TCHAR+15]
        and eax,-16
        mov env_size,eax
    .endif
    .for ( rsi = __pioinfo, ecx = 0 : ecx < _nfile && [rsi].ioinfo.osfile : ecx++, rsi += ioinfo )
    .endf

    mov     nh,ecx
    imul    ecx,ecx,1 + intptr_t
    add     ecx,4 + 15
    and     ecx,-16
    mov     hnd_size,ecx
    add     ecx,env_size
    add     ecx,cmd_size

    .if ( malloc(ecx) == NULL )

        dec rax
       .return
    .endif
    mov cmd,rax

    mov rsi,_tcscpy(rax, [rbx])
    .for ( rbx+=tarray_t : tarray_t ptr [rbx] : rbx+=tarray_t )

        _tcscat(rsi, " ")
        _tcscat(rsi, [rbx])
    .endf

    mov rbx,envp
    .if ( rbx )

        mov eax,cmd_size
        add rax,cmd
        mov env,rax
        .for ( rdi = rax : tarray_t ptr [rbx] : rbx += tarray_t )

            mov rsi,[rbx]
            .repeat
                _tlodsb
                _tstosb
            .until !_tal
        .endf
        _tstosb
    .endif

    lea     rdi,StartupInfo
    xor     eax,eax
    mov     ecx,sizeof(StartupInfo)
    rep     stosb
    mov     StartupInfo.cb,sizeof(StartupInfo)
    mov     ecx,nh
    imul    eax,ecx,1 + intptr_t
    add     eax,4
    mov     StartupInfo.cbReserved2,ax
    mov     eax,cmd_size
    add     eax,env_size
    add     rax,cmd
    mov     StartupInfo.lpReserved2,rax
    mov     [rax],ecx
    lea     rdi,[rax+4]
    lea     rsi,[rdi+rcx]

    .for ( rbx = __pioinfo, ecx = 0 : ecx < nh : ecx++, rdi++, rsi+=intptr_t, rbx+=ioinfo )

        .if ( [rbx].ioinfo.osfile & FNOINHERIT || ( background && ecx < 3 ) )

            mov byte ptr [rdi],0
            mov intptr_t ptr [rsi],INVALID_HANDLE_VALUE
        .else
            mov [rdi],[rbx].ioinfo.osfile
            mov [rsi],[rbx].ioinfo.osfhnd
        .endif
    .endf

    .if ( background )

        or fdwCreate,DETACHED_PROCESS
    .endif

    SetErrorMode(_ermode)
    mov rbx,GetStdHandle(STD_INPUT_HANDLE)
    GetConsoleMode(rbx, &ConsoleMode)
    _set_doserrno(0)
    mov CreateProcessStatus,CreateProcess(name, cmd, NULL, NULL, TRUE, fdwCreate, env, NULL, &StartupInfo, &ProcessInformation)
    mov dosretval,GetLastError()
    free( cmd )
    SetConsoleMode( rbx, ConsoleMode )
    SetErrorMode( SEM_FAILCRITICALERRORS )

    .if ( !CreateProcessStatus )

       .return( _dosmaperr(dosretval) )
    .endif

endif

    .if ( mode == _P_OVERLAY )
ifdef __UNIX__
        .ifs ( sys_execve(name, argv, envp) < 0 )

            neg eax
            mov retval,_set_errno( eax )
        .else
            exit(EXIT_SUCCESS)
        .endif
else
        _exit( 0 )
endif
    .elseif ( mode == _P_WAIT )

ifdef __UNIX__
        mov pid,fork()
        .if ( pid == 0 )

            ; child process

            sys_execve(name, argv, envp)
            exit(EXIT_SUCCESS)

        .elseif ( pid > 0 )

            ; parent process

            waitpid(pid, &exitcode, 0)
            mov retval,exitcode
        .else
            mov retval,rax
        .endif
else
        WaitForSingleObject(ProcessInformation.hProcess, -1)
        GetExitCodeProcess(ProcessInformation.hProcess, &exitcode)
        mov retval,exitcode
        CloseHandle(ProcessInformation.hProcess)
endif
    .elseif ( mode == _P_DETACH )

ifdef __UNIX__
else
        CloseHandle(ProcessInformation.hProcess)
        mov retval,0
endif
    .else
ifdef __UNIX__
else
        mov retval,ProcessInformation.hProcess
endif
    .endif
ifndef __UNIX__
    CloseHandle(ProcessInformation.hThread)
endif
    mov rax,retval
    ret

_tspawnve endp

    end
