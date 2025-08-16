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
include malloc.inc
include process.inc
include io.inc
include fcntl.inc
include errno.inc
include string.inc
include winbase.inc
include tchar.inc

; size for pipe buffer

define PISIZE       1024

define STDIN        0
define STDOUT       1

define SLASH        <"\\">
define SLASHCHAR    '\'
define XSLASHCHAR   '/'
define DELIMITER    <";">

.template IDpair
    stream  LPFILE ?
    prochnd intptr_t ?
   .ends


; function to find specified table entries. also, creates and maintains the table.

idtab proto private :LPFILE

.data

; number of entries in idpairs table

ifndef _UNICODE
__idtabsiz dd 0
else
externdef __idtabsiz:dword
endif

; pointer to first table entry

ifndef _UNICODE
__idpairs ptr IDpair NULL
else
externdef __idpairs:ptr IDpair
endif

.code

_tpopen proc uses rsi rdi rbx cmdstring:tstring_t, type:tstring_t

ifndef __UNIX__

   .new phdls[2]:int_t              ; I/O handles for pipe
   .new ph_open[2]:int_t            ; flags, set if correspond phdls is open
   .new i1:int_t                    ; index into phdls[]
   .new i2:int_t                    ; index into phdls[]
   .new mode:int_t                  ; flag indicating text or binary mode
   .new stdhdl:int_t                ; either STDIN or STDOUT
   .new newhnd:HANDLE = NULL        ; ...in calls to DuplicateHandle API
   .new pstream:LPFILE = NULL       ; stream to be associated with pipe
   .new prochnd:HANDLE              ; handle for current process
   .new cmdexe:tstring_t            ; pathname for the command processor
   .new envbuf:tstring_t = NULL     ; buffer for the env variable
   .new childhnd:intptr_t           ; handle for child process (cmd.exe)
   .new locidpair:ptr IDpair        ; pointer to IDpair table entry
   .new buf:tstring_t = NULL
   .new pfin:tstring_t
   .new env:tstring_t
   .new CommandLine:tstring_t
   .new CommandLineSize:size_t = 0
   .new _type[3]:tchar_t = {0, 0, 0}

    ; Info for spawning the child.

   .new StartupInfo:STARTUPINFO     ; Info for spawning a child
   .new childstatus:BOOL = 0
   .new ProcessInfo:PROCESS_INFORMATION ; child process information

   .new save_errno:errno_t
   .new fh_lock_held:int_t = 0
   .new popen_lock_held:int_t = 0

    ; first check for errors in the arguments

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

    ; do the _pipe(). note that neither of the resulting handles will
    ; be inheritable.

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

    ; test _type[0] and set stdhdl, i1 and i2 accordingly.

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
    ; ASSERT LOCK FOR IDPAIRS HERE!!!!

    .ifd ( !_mtinitlocknum( _POPEN_LOCK ) )

        _close( phdls[0] )
        _close( phdls[4] )
        .return NULL
    .endif
    _mlock( _POPEN_LOCK )
endif
    ; set flags to indicate pipe handles are open. note, these are only
    ; used for error recovery.

    mov ph_open[0],1
    mov ph_open[4],1

    ; get the process handle, it will be needed in some API calls

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

    ; associate a stream with phdls[i2]. note that if there are no
    ; errors, pstream is the return value to the caller.

    mov ecx,i2
    .if ( _tfdopen( phdls[rcx*4], &_type ) == NULL )
        jmp error2
    .endif
    mov pstream,rax

    ; next, set locidpair to a free entry in the idpairs table.

    mov locidpair,idtab( NULL )
    .if ( rax == NULL )
        jmp error3
    .endif

    ; Find what to use. command.com or cmd.exe

    .if ( getenv("COMSPEC") == NULL )
        lea rax,@CStr("cmd.exe")
    .else
        mov envbuf,_strdup(rax)
    .endif
    mov cmdexe,rax

    ; Initialise the variable for passing to CreateProcess

    memset(&StartupInfo, 0, sizeof(StartupInfo))
    mov StartupInfo.cb,sizeof(StartupInfo)

    ; Used by os for duplicating the Handles.

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

    ; Check if cmdexe can be accessed. If yes CreateProcess else try
    ; searching path.

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

            ; check that the final path will be of legal size. if so,
            ; build it. otherwise, return to the caller (return value
            ; and errno rename set from initial call to _spawnve()).

            mov ebx,_tcslen(buf)
            add ebx,_tcslen(cmdexe)

            .if ( ebx < _MAX_PATH )
                _tcscat_s(buf, _MAX_PATH, cmdexe)
            .else
                .break
            .endif

            ; Check if buf can be accessed. If yes CreateProcess else try
            ; again.

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

    ; check if the CreateProcess was sucessful.

    .if ( childstatus )
        mov childhnd,ProcessInfo.hProcess
    .else
        jmp error4
    .endif

    mov rbx,locidpair
    mov [rbx].IDpair.prochnd,childhnd
    mov [rbx].IDpair.stream,pstream

    ; success, return the stream to the caller

    jmp done

    ; error handling code. all detected errors end up here, entering
    ; via a goto one of the labels. note that the logic is currently
    ; a straight fall-thru scheme (e.g., if entered at error4, the
    ; code for error4, error3,...,error1 is all executed).


error4: ; make sure locidpair is reusable

    mov rbx,locidpair
    mov [rbx].IDpair.stream,NULL

error3: ; close pstream (also, clear ph_open[i2] since the stream
        ; close will also close the pipe handle)

    fclose( pstream )
    mov ecx,i2
    mov ph_open[rcx*4],0
    mov pstream,NULL

error2: ; close handles on pipe (if they are still open)

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
else
    _set_errno( ENOSYS )
    xor eax,eax
endif
    ret

_tpopen endp


ifndef _UNICODE

_pclose proc uses rbx pstream:LPFILE

   .new locidpair:ptr IDpair    ; pointer to entry in idpairs table
   .new termstat:int_t          ; termination status word
   .new retval:int_t = -1       ; return value (to caller)
   .new save_errno:errno_t

    ldr rbx,pstream

    .if ( rbx == NULL )

        .return( _set_errno(EINVAL) )
    .endif
    fclose(rbx)

    ; wait on the child (copy of the command processor) and all of its
    ; children.

    _get_errno( &save_errno )
    _set_errno( 0 )

    .if ( idtab(rbx) == NULL )

        ; invalid pstream, exit with retval == -1

        .return( _set_errno(EBADF) )
    .endif

    mov rbx,rax
    .ifd ( _cwait(&termstat, [rbx].IDpair.prochnd, _WAIT_GRANDCHILD) != -1 )
        mov retval,termstat
    .elseifd ( errno == EINTR )
        mov retval,termstat
    .endif
    _set_errno(save_errno)

    ; Mark the IDpairtable entry as free (note: prochnd was closed by the
    ; preceding call to _cwait).

    mov [rbx].IDpair.stream,NULL
    mov [rbx].IDpair.prochnd,0

   .return( retval )

_pclose endp

endif

idtab proc private pstream:LPFILE

    ldr rcx,pstream

    ; search the table. if table is empty, appropriate action should
    ; fall out automatically.

    imul edx,__idtabsiz,IDpair
    .for ( rax = __idpairs, rdx += rax : rax < rdx : rax += IDpair )
        .break .if ( [rax].IDpair.stream == rcx )
    .endf

    ; if we found an entry, return it.

    .return .if ( rax < rdx )

    ; did not find an entry in the table.  if pstream was NULL, then try
    ; creating/expanding the table. otherwise, return NULL. note that
    ; when the table is created or expanded, exactly one new entry is
    ; produced. this must not be changed unless code is added to mark
    ; the extra entries as being free (i.e., set their stream fields to
    ; to NULL).

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

idtab endp

    end
