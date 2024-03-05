; _TSTAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
include direct.inc
include errno.inc
include sys/stat.inc
include string.inc
include stdlib.inc
include malloc.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif
include tchar.inc

    .code

ifdef __UNIX__

stat proc file:string_t, buf:PSTAT
ifdef _WIN64
    .ifs ( sys_newstat(rdi, rsi) < 0 )

        neg eax
        _set_errno( eax )
        .return( -1 )
    .endif
else
    _set_errno( ENOSYS )
    mov eax,-1
endif
    ret

stat endp

stat64 proc file:string_t, buf:PSTAT64
ifdef _WIN64
    .ifs ( sys_newstat(rdi, rsi) < 0 )

        neg eax
        _set_errno( eax )
        .return( -1 )
    .endif
else
    _set_errno( ENOSYS )
    mov eax,-1
endif
    ret

stat64 endp

else

define A_D 0x10

_lk_getltime proc private ft:PVOID

  local SystemTime:SYSTEMTIME
  local LocalFTime:FILETIME

    .if FileTimeToLocalFileTime(ft, &LocalFTime)
        .if FileTimeToSystemTime(&LocalFTime, &SystemTime)
            _loctotime_t(
                SystemTime.wYear,
                SystemTime.wMonth,
                SystemTime.wDay,
                SystemTime.wHour,
                SystemTime.wMinute,
                SystemTime.wSecond
            )
        .endif
    .endif
    ret

_lk_getltime endp

_lk_stat proc private file:LPTSTR, buf:PSTAT, b64:int_t

   .new path:LPTSTR
   .new drive:int_t
   .new ff:WIN32_FIND_DATA
   .new pathbuf[_MAX_PATH]:TCHAR
   .new m_time:uint_t
   .new a_time:uint_t
   .new c_time:uint_t

    ldr rsi,file
    ldr rdi,buf

    .repeat

        .break .if _tcschr( rsi, '?' )
        .break .if _tcschr( rsi, '*' )

        .if ( TCHAR ptr [rsi+TCHAR] == ':' )

            .break .if ( TCHAR ptr [rsi+TCHAR*2] == 0 )

            movzx eax,TCHAR ptr [rsi]
            or    al,0x20
            sub   al,'a' - 1
        .else
            _getdrive()
        .endif
        mov drive,eax

        .ifd ( FindFirstFile( rsi, &ff ) == -1 )

            .if !_tcschr( rsi, '.' )
                .if !_tcschr( rsi, '\' )
                    .break .if !_tcschr( rsi, '/' )
                .endif
            .endif

            .break .if !_tgetcwd( &pathbuf, _MAX_PATH )
            mov path,rax

            .break .ifd ( _tcslen( rax ) != 3 )
            .break .if ( GetDriveType( path ) < 2 )

            mov ff.dwFileAttributes,A_D
            mov ff.nFileSizeLow,0
            mov ff.cFileName,0

            _loctotime_t( 80, 1, 1, 0, 0, 0 )
            mov m_time,eax
            mov a_time,eax
            mov c_time,eax

        .else

            FindClose( rax )
            .ifd !_lk_getltime( &ff.ftLastWriteTime )
                .return _dosmaperr( GetLastError() )
            .endif
            mov m_time,eax
            .ifd !_lk_getltime( &ff.ftLastAccessTime )
                mov eax,m_time
            .endif
            mov a_time,eax
            .ifd !_lk_getltime( &ff.ftCreationTime )
                mov eax,m_time
            .endif
            mov c_time,eax
        .endif

        movzx eax,TCHAR ptr [rsi]
        mov edx,ff.dwFileAttributes
        mov ecx,_S_IFDIR or _S_IEXEC
        mov ebx,_S_IREAD

        .if ( TCHAR ptr [rsi+TCHAR] == ':' )
            add rsi,2*TCHAR
            movzx eax,TCHAR ptr [rsi]
        .endif

        .if ( eax && !( dl & A_D ) )
            .if ( TCHAR ptr [rsi+TCHAR] || eax != '\' && eax != '/' )
                mov ecx,_S_IFREG
            .endif
        .endif

        .if !( dl & A_D )
            mov ebx,_S_IREAD or _S_IWRITE
        .endif

        or  ebx,ecx
        .if _tisexec( rsi )
            or ebx,_S_IEXEC
        .endif

        mov ecx,ebx
        and ecx,0x01C0
        mov eax,ecx
        shr ecx,3
        or  ebx,ecx
        shr eax,6
        or  eax,ebx
        mov [rdi]._stat32.st_mode,ax
        mov eax,drive
        dec eax
        mov [rdi]._stat32.st_dev,eax
        mov [rdi]._stat32.st_rdev,eax
        mov [rdi]._stat32.st_nlink,1

        mov eax,ff.nFileSizeLow
ifdef _WIN64
        .if ( b64 == 0 )
endif
            mov [rdi]._stat32.st_size,eax
            mov [rdi]._stat32.st_atime,a_time
            mov [rdi]._stat32.st_mtime,m_time
            mov [rdi]._stat32.st_ctime,c_time
ifdef _WIN64
        .else
            mov edx,ff.nFileSizeHigh
            mov dword ptr [rdi]._stati64.st_size,eax
            mov dword ptr [rdi]._stati64.st_size[4],edx
            mov dword ptr [rdi]._stati64.st_atime,a_time
            mov dword ptr [rdi]._stati64.st_mtime,m_time
            mov dword ptr [rdi]._stati64.st_ctime,c_time
        .endif
endif
       .return( 0 )
    .until 1

    _set_errno( ENOENT )
    _set_doserrno( ERROR_PATH_NOT_FOUND )
    .return( -1 )

_lk_stat endp

_tstat proc uses rsi rdi rbx file:LPTSTR, buf:PSTAT

    ldr rcx,file
    ldr rdx,buf
    mov rbx,rcx
    mov rsi,rdx
    mov rdi,rdx
    xor eax,eax
    mov ecx,_stat32
    rep stosb
    _lk_stat(rbx, rsi, 0)
    ret

_tstat endp

ifdef _WIN64

_tstat64 proc uses rsi rdi rbx file:LPTSTR, buf:PSTAT64

    ldr rcx,file
    ldr rdx,buf
    mov rbx,rcx
    mov rsi,rdx
    mov rdi,rdx
    xor eax,eax
    mov ecx,_stati64
    rep stosb
    _lk_stat(rbx, rsi, 1)
    ret

_tstat64 endp

endif
endif
    end
