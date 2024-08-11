; FSTAT64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
include errno.inc
include sys/stat.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif

    .code

ifdef __UNIX__

_fstat64 proc fd:int_t, buf:PSTAT64
ifdef _WIN64
    .ifs ( sys_newfstat(edi, rsi) < 0 )
else
    .ifs ( sys_newfstat64(fd, buf) < 0 )
endif
        neg eax
        _set_errno( eax )
    .endif
    ret

_fstat64 endp

else

_lk_getltime proc private ft:LPFILETIME

  local SystemTime:SYSTEMTIME
  local LocalFTime:FILETIME

    ldr rcx,ft

    .if FileTimeToLocalFileTime(rcx, &LocalFTime)
        .if FileTimeToSystemTime(&LocalFTime, &SystemTime)
            _loctotime_t(
                SystemTime.wYear,
                SystemTime.wMonth,
                SystemTime.wDay,
                SystemTime.wHour,
                SystemTime.wMinute,
                SystemTime.wSecond )
        .endif
    .endif
    ret

_lk_getltime endp

    assume rdi:PSTAT64

_fstat64 proc uses rsi rdi rbx fd:int_t, buf:PSTAT64

   .new ulAvail:uint_t
   .new bhfi:BY_HANDLE_FILE_INFORMATION
   .new LocalFTime:FILETIME
   .new SystemTime:SYSTEMTIME
   .new osfhnd:HANDLE

    ldr esi,fd
    ldr rdx,buf

    .if ( rdx == NULL )

        .return( _set_errno( EINVAL ) )
    .endif

    mov rdi,rdx
    xor eax,eax
    mov ecx,_stati64
    rep stosb
    mov rdi,rdx

    .ifs ( esi < 0 || esi >= _nfile )

        .return( _set_errno( EBADF ) )
    .endif

    mov rcx,_pioinfo(esi)
    mov osfhnd,[rcx].ioinfo.osfhnd

    .if !( [rcx].ioinfo.osfile & FOPEN )

        .return( _set_errno( EBADF ) )
    .endif

    ; Find out what kind of handle underlies filedes

    GetFileType(osfhnd)
    and eax,not FILE_TYPE_REMOTE

    .if ( eax != FILE_TYPE_DISK )

        ; not a disk file. probably a device or pipe

        .if ( eax == FILE_TYPE_CHAR || eax == FILE_TYPE_PIPE )

            ; treat pipes and devices similarly. no further info is
            ; available from any API, so set the fields as reasonably
            ; as possible and return.

            .if ( eax == FILE_TYPE_CHAR )
                mov [rdi].st_mode,_S_IFCHR
            .else
                mov [rdi].st_mode,_S_IFIFO
            .endif
            mov [rdi].st_rdev,esi
            mov [rdi].st_dev,esi
            mov [rdi].st_nlink,1

            .if ( eax != FILE_TYPE_CHAR )

                .ifd PeekNamedPipe(osfhnd, NULL, 0, NULL, &ulAvail, NULL)

                    mov uint_t ptr [rdi].st_size,ulAvail
                .endif
            .endif
            .return( 0 )

        .elseif ( eax == FILE_TYPE_UNKNOWN )

            .return( _set_errno( EBADF ) )

        .else

            ; according to the documentation, this cannot happen, but
            ; play it safe anyway.

            .return( _dosmaperr( GetLastError() ) )
        .endif
    .endif

    ; set the common fields

    mov [rdi].st_nlink,1
    mov [rdi].st_mode,_S_IFREG

    ; use the file handle to get basic info about the file

    .if ( !GetFileInformationByHandle(osfhnd, &bhfi) )

        .return( _dosmaperr( GetLastError() ) )
    .endif
    .if ( bhfi.dwFileAttributes & FILE_ATTRIBUTE_READONLY )
        mov eax,(_S_IREAD + (_S_IREAD shr 3) + (_S_IREAD shr 6))
    .else
        mov eax,((_S_IREAD or _S_IWRITE) + ((_S_IREAD or _S_IWRITE) shr 3) + ((_S_IREAD or _S_IWRITE) shr 6))
    .endif
    or  [rdi].st_mode,ax

    ; set file date and size fields

    mov rbx,_lk_getltime(&bhfi.ftLastWriteTime)
    mov rsi,_lk_getltime(&bhfi.ftLastAccessTime)
    mov rcx,_lk_getltime(&bhfi.ftCreationTime)
    mov dword ptr [rdi].st_size[4],bhfi.nFileSizeHigh
    mov dword ptr [rdi].st_size[0],bhfi.nFileSizeLow
    xor eax,eax
ifdef _WIN64
    mov [rdi].st_mtime,rbx
    mov [rdi].st_atime,rsi
    mov [rdi].st_ctime,rcx
else
    mov dword ptr [rdi].st_mtime[0],ebx
    mov dword ptr [rdi].st_mtime[4],eax
    mov dword ptr [rdi].st_atime[0],esi
    mov dword ptr [rdi].st_atime[4],eax
    mov dword ptr [rdi].st_ctime[0],ecx
    mov dword ptr [rdi].st_ctime[4],eax
endif
    ret

_fstat64 endp
endif

    end
