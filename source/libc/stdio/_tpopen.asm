; _TPOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE *_popen(char *cmdstring, char *type);
; FILE *_wpopen(wchar_t *cmdstring, wchar_t *type);
;

include stdio.inc
include stdlib.inc
include errno.inc
ifdef __UNIX__
include io.inc
include unistd.inc
include sys/wait.inc
include tchar.inc

define MAX_POPEN_STREAMS 16

.template POPEN_SLOT
    fp      LPFILE ?
    pid     pid_t ?
   .ends

.data
 popen_slots POPEN_SLOT MAX_POPEN_STREAMS dup(<NULL, 0>)

else

include malloc.inc
include process.inc
include io.inc
include fcntl.inc
include string.inc
include winbase.inc
include tchar.inc

define PISIZE       1024
define STDIN        0
define STDOUT       1
define SLASH        <"\\">
define SLASHCHAR    BSLASH
define XSLASHCHAR   '/'
define DELIMITER    <";">

.template IDpair
    stream  LPFILE ?
    prochnd intptr_t ?
   .ends

idtab proto private :LPFILE

.data
ifndef _UNICODE
__idtabsiz dd 0
else
externdef __idtabsiz:dword
endif
ifndef _UNICODE
__idpairs ptr IDpair NULL
else
externdef __idpairs:ptr IDpair
endif

endif

.code

_tpopen proc uses rsi rdi rbx cmdstring:tstring_t, type:tstring_t
ifdef __UNIX__
   .new pipefd[2]:int_t
   .new is_write:int_t
   .new parent_fd:int_t
   .new child_fd:int_t
   .new target_std:int_t
   .new pid:pid_t
   .new argv[4]:LPSTR = { "/bin/sh", "-c", NULL, NULL }

    ldr rdi,cmdstring
    ldr rsi,type
    .if ( !rsi || !rdi )
        _set_errno( EINVAL )
        .return( NULL )
    .endif
    mov argv[LPSTR*2],rdi
    mov al,[rsi]
    .if ( al == 'r' )
        mov is_write,0
    .elseif ( al == 'w' )
        mov is_write,1
    .else
        _set_errno( EINVAL )
        .return( NULL )
    .endif
    .for ( rbx = &popen_slots, ecx = 0 : ecx < MAX_POPEN_STREAMS : ecx++, rbx+=POPEN_SLOT )
        .break .if ( [rbx].POPEN_SLOT.fp == NULL )
    .endf
    .if ( ecx >= MAX_POPEN_STREAMS )
        _set_errno( EMFILE )
        .return( NULL )
    .endif
    .ifsd ( pipe(&pipefd) < 0 )
        .return( NULL )
    .endif
    .if ( is_write )
        mov child_fd,pipefd[0]      ; Child reads from stdin
        mov parent_fd,pipefd[4]     ; Parent writes to stdout
        mov target_std,0
    .else
        mov child_fd,pipefd[4]      ; Child writes to stdout
        mov parent_fd,pipefd[0]     ; Parent reads from stdin
        mov target_std,1
    .endif
    mov pid,fork()
    .ifs ( eax < 0 )
        close(pipefd[0])
        close(pipefd[4])
       .return( NULL )
    .endif
    .if ( eax == 0 )
        ; --- Child Process ---
        mov eax,child_fd
        .if ( eax != target_std )
            _dup2(eax, target_std)
        .endif
        close(pipefd[0])
        close(pipefd[4])
        execve("/bin/sh", &argv, _environ)
        _exit(127)
    .endif
   ; --- Parent Process ---
    close(child_fd)
    .if !_fdopen(parent_fd, type)
        close(parent_fd)
        waitpid(pid, NULL, 0)
       .return( NULL )
    .endif
    mov [rbx].POPEN_SLOT.fp,rax
    mov ecx,pid
    mov [rbx].POPEN_SLOT.pid,ecx

else

   .new phdls[2]:int_t
   .new ph_open[2]:int_t
   .new i1:int_t
   .new i2:int_t
   .new mode:int_t
   .new stdhdl:int_t
   .new newhnd:HANDLE = NULL
   .new pstream:LPFILE = NULL
   .new prochnd:HANDLE
   .new cmdexe:tstring_t
   .new envbuf:tstring_t = NULL
   .new childhnd:intptr_t
   .new locidpair:ptr IDpair
   .new buf:tstring_t = NULL
   .new pfin:tstring_t
   .new env:tstring_t
   .new CommandLine:tstring_t
   .new CommandLineSize:size_t = 0
   .new _type[3]:tchar_t = {0, 0, 0}
   .new StartupInfo:STARTUPINFO
   .new childstatus:BOOL = 0
   .new ProcessInfo:PROCESS_INFORMATION
   .new save_errno:errno_t
   .new fh_lock_held:int_t = 0
   .new popen_lock_held:int_t = 0

    ldr rcx,cmdstring
    ldr rdx,type
    .if ( rcx == NULL || rdx == NULL )
        _set_errno(EINVAL)
        .return( NULL )
    .endif
    .while ( tchar_t ptr [rdx] == ' ' )
        add rdx,tchar_t
    .endw
    movzx eax,tchar_t ptr [rdx]
    .if ( eax != 'r' && eax != 'w' )
        _set_errno(EINVAL)
        .return( NULL )
    .endif
    add rdx,tchar_t
    mov _type[0],_tal
    .while ( tchar_t ptr [rdx] == ' ' )
        add rdx,tchar_t
    .endw
    movzx eax,tchar_t ptr [rdx]
    .if ( eax != 't' && eax != 'b' && eax != 0 )
        _set_errno(EINVAL)
        .return( NULL )
    .endif
    mov _type[tchar_t],_tal
    xor ecx,ecx
    .if ( _tal == 't' )
        mov ecx,_O_TEXT
    .elseif ( _tal == 'b' )
        mov ecx,_O_BINARY
    .endif
    or ecx,_O_NOINHERIT
    mov mode,ecx
    .ifd ( _pipe( &phdls, PISIZE, ecx ) == -1 )
        jmp error1
    .endif
    .if ( _type[0] == 'w' )
        mov stdhdl,STDIN
        mov i1,0
        mov i2,1
    .else
        mov stdhdl,STDOUT
        mov i1,1
        mov i2,0
    .endif
if 0
    .ifd ( !_mtinitlocknum( _POPEN_LOCK ) )
        _close( phdls[0] )
        _close( phdls[4] )
        .return NULL
    .endif
    _mlock( _POPEN_LOCK )
endif
    mov ph_open[0],1
    mov ph_open[4],1
    mov prochnd,GetCurrentProcess()
    mov ecx,i1
    mov ecx,phdls[rcx*4]
    mov rcx,_osfhnd(ecx)
    .ifd !DuplicateHandle( prochnd, rcx, prochnd, &newhnd, 0, TRUE, DUPLICATE_SAME_ACCESS )
        jmp error2
    .endif
    mov ecx,i1
    mov ph_open[rcx*4],0
    _close( phdls[rcx*4] )
    mov ecx,i2
    .if ( _tfdopen( phdls[rcx*4], &_type ) == NULL )
        jmp error2
    .endif
    mov pstream,rax
    mov locidpair,idtab( NULL )
    .if ( rax == NULL )
        jmp error3
    .endif
    .if ( getenv("COMSPEC") == NULL )
        lea rax,@CStr("cmd.exe")
    .else
        mov envbuf,_strdup(rax)
    .endif
    mov cmdexe,rax
    memset(&StartupInfo, 0, sizeof(StartupInfo))
    mov StartupInfo.cb,sizeof(StartupInfo)
    mov StartupInfo.dwFlags,STARTF_USESTDHANDLES
    mov rcx,__pioinfo
    mov rax,[rcx].ioinfo.osfhnd
    .if ( stdhdl == STDIN )
        mov rax,newhnd
    .endif
    mov StartupInfo.hStdInput,rax
    mov rax,[rcx+ioinfo].ioinfo.osfhnd
    .if ( stdhdl == STDOUT )
        mov rax,newhnd
    .endif
    mov StartupInfo.hStdOutput,rax
    mov rax,[rcx+ioinfo*2].ioinfo.osfhnd
    mov StartupInfo.hStdError,rax
    mov CommandLineSize,_tcslen(cmdexe)
    add CommandLineSize,_tcslen(cmdstring)
    add CommandLineSize,4+1
    mov CommandLine,calloc(CommandLineSize, tchar_t)
    test rax,rax
    jz error3
    _tcscpy_s(CommandLine, CommandLineSize, cmdexe)
    _tcscat_s(CommandLine, CommandLineSize, " /c ")
    _tcscat_s(CommandLine, CommandLineSize, cmdstring)
    memset(&ProcessInfo, 0, sizeof(ProcessInfo))
    _get_errno(&save_errno)
    .ifd ( _taccess(cmdexe, 0) == 0 )
        mov childstatus,CreateProcess(cmdexe, CommandLine, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
    .else
        .new envPath:tstring_t = NULL
        .new envPathSize:size_t = 0
        .if ( calloc(_MAX_PATH, tchar_t) == NULL )
            ;free(buf)
            free(CommandLine)
            free(envbuf)
            mov cmdexe,NULL
            _set_errno(save_errno)
            jmp error3
        .endif
        mov buf,rax
        .if ( getenv("PATH") )
            mov envPath,_strdup( rax )
        .endif
        .if ( rax == NULL )
            ;free(envPath)
            free(buf)
            free(CommandLine)
            free(envbuf)
            mov cmdexe,NULL
            _set_errno(save_errno)
            jmp error3
        .endif
        mov env,rax
        .while _tgetpath(env, buf, _MAX_PATH - 1 )
            mov env,rax
            mov rbx,buf
            .if ( tchar_t ptr [rbx] == 0 )
                .break
            .endif
            dec _tcslen(rbx)
ifdef _UNICODE
            add rax,rax
endif
            add rbx,rax
            .if ( tchar_t ptr [rbx] != SLASHCHAR && tchar_t ptr [rbx] != XSLASHCHAR )
                _tcscat_s(buf, _MAX_PATH, SLASH)
            .endif
            mov ebx,_tcslen(buf)
            add ebx,_tcslen(cmdexe)
            .if ( ebx < _MAX_PATH )
                _tcscat_s(buf, _MAX_PATH, cmdexe)
            .else
                .break
            .endif
            .ifd ( _taccess(buf, 0) == 0 )
                mov childstatus,CreateProcess(buf, CommandLine, NULL, NULL, TRUE, 0, NULL, NULL, &StartupInfo, &ProcessInfo)
               .break
            .endif
        .endw
        free(envPath)
        free(buf)
    .endif
    free(CommandLine)
    free(envbuf)
    mov cmdexe,NULL
    CloseHandle(newhnd)
    .if ( childstatus )
        CloseHandle(ProcessInfo.hThread)
    .endif
    _set_errno(save_errno)
    .if ( childstatus )
        mov childhnd,ProcessInfo.hProcess
    .else
        jmp error4
    .endif
    mov rbx,locidpair
    mov [rbx].IDpair.prochnd,childhnd
    mov [rbx].IDpair.stream,pstream
    jmp done
error4:
    mov rbx,locidpair
    mov [rbx].IDpair.stream,NULL
error3:
    fclose( pstream )
    mov ecx,i2
    mov ph_open[rcx*4],0
    mov pstream,NULL
error2:
    mov ecx,i1
    .if ( ph_open[rcx*4] )
        _close( phdls[rcx*4] )
    .endif
    mov ecx,i2
    .if ( ph_open[rcx*4] )
        _close( phdls[rcx*4] )
    .endif
done:
error1:
    mov rax,pstream
endif
    ret
    endp


ifndef _UNICODE
_pclose proc uses rbx pstream:LPFILE
ifdef __UNIX__
   .new pid:pid_t
   .new status:int_t
    ldr rax,pstream
    .if ( !rax )
        .return( _set_errno(EINVAL) )
    .endif
    .for ( rbx = &popen_slots, ecx = 0 : ecx < MAX_POPEN_STREAMS : ecx++, rbx+=POPEN_SLOT )
        .if ( rax == [rbx].POPEN_SLOT.fp )
            mov edx,[rbx].POPEN_SLOT.pid
            mov pid,edx
            mov [rbx].POPEN_SLOT.fp,NULL
            mov [rbx].POPEN_SLOT.pid,0
           .break
        .endif
    .endf
    .if ( ecx >= MAX_POPEN_STREAMS )
        .return( _set_errno(EINVAL) )
    .endif
    fclose(rax)
    mov status,0
    .while ( 1 )
        waitpid(pid, &status, 0)
        .break .ifs ( eax >= 0 )
        .if ( errno != EINTR )
            .return( -1 )
        .endif
    .endw
    .return( status )
else
   .new locidpair:ptr IDpair
   .new termstat:int_t
   .new retval:int_t = -1
   .new save_errno:errno_t
    ldr rbx,pstream
    .if ( rbx == NULL )
        .return( _set_errno(EINVAL) )
    .endif
    fclose(rbx)
    _get_errno( &save_errno )
    _set_errno( 0 )
    .if ( idtab(rbx) == NULL )
        .return( _set_errno(EBADF) )
    .endif
    mov rbx,rax
    .ifd ( _cwait(&termstat, [rbx].IDpair.prochnd, _WAIT_GRANDCHILD) != -1 )
        mov retval,termstat
    .elseifd ( errno == EINTR )
        mov retval,termstat
    .endif
    _set_errno(save_errno)
    mov [rbx].IDpair.stream,NULL
    mov [rbx].IDpair.prochnd,0
    .return( retval )
endif
    endp
endif

ifndef __UNIX__
idtab proc private pstream:LPFILE
    ldr rcx,pstream
    imul edx,__idtabsiz,IDpair
    .for ( rax = __idpairs, rdx += rax : rax < rdx : rax += IDpair )
        .break .if ( [rax].IDpair.stream == rcx )
    .endf
    .return .if ( rax < rdx )
    mov eax,__idtabsiz
    inc eax
    .if ( rcx != NULL || eax < __idtabsiz || eax >= (UINT_MAX / sizeof(IDpair)) )
        .return( NULL )
    .endif
    imul edx,eax,IDpair
    mov __idpairs,realloc(__idpairs, rdx)
    .if ( rax )
        imul edx,__idtabsiz,IDpair
        add rax,rdx
        inc __idtabsiz
    .endif
    ret
    endp
endif
    end
