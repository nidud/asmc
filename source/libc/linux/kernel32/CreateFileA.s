; CREATEFILEA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include share.inc
include errno.inc
include fcntl.inc
include sys/stat.inc
include sys/syscall.inc
include winbase.inc

.code

 CreateFileA proc WINAPI uses rsi rdi rbx lpFileName:LPCSTR, dwDesiredAccess:DWORD,
        dwShareMode:DWORD, lpSecurityAttributes:LPSECURITY_ATTRIBUTES,
        dwCreationDisposition:DWORD, dwFlagsAndAttributes:DWORD, hTemplateFile:HANDLE

    ldr rdi,lpFileName
    ldr eax,dwDesiredAccess
    mov edx,dwCreationDisposition
    mov ecx,dwFlagsAndAttributes
    .if ( !rdi || byte ptr [rdi] == 0 )
        SetLastError( ERROR_INVALID_PARAMETER )
       .return( INVALID_HANDLE_VALUE )
    .endif
    xor ebx,ebx
    mov esi,eax
    and esi,(GENERIC_READ or GENERIC_WRITE)
    .if ( esi == (GENERIC_READ or GENERIC_WRITE) )
        mov ebx,O_RDWR
    .elseif ( esi == GENERIC_WRITE )
        mov ebx,O_WRONLY
    .elseif ( eax & FILE_APPEND_DATA )
        or ebx,(O_WRONLY or O_APPEND)
    .endif
    .switch edx
    .case CREATE_NEW
        or ebx,(O_CREAT or O_EXCL)
       .endc
    .case CREATE_ALWAYS
        or ebx,(O_CREAT or O_TRUNC)
       .endc
    .case OPEN_EXISTING
       .endc
    .case OPEN_ALWAYS
        or ebx,O_CREAT
       .endc
    .case TRUNCATE_EXISTING
        or ebx,O_TRUNC
       .endc
    .default
        SetLastError( ERROR_INVALID_PARAMETER )
       .return( INVALID_HANDLE_VALUE )
    .endsw
    .if ( ecx & FILE_FLAG_WRITE_THROUGH )
        or ebx,O_SYNC
    .endif
    .if ( ecx & FILE_FLAG_NO_BUFFERING )
        or ebx,O_DIRECT
    .endif
    mov edx,0666o
    .if ( ecx & FILE_ATTRIBUTE_READONLY )
        mov edx,0444o
    .endif
    .ifsd ( sys_open(rdi, ebx, edx) < 0 )
        _sys_maperr( eax )
        .return( INVALID_HANDLE_VALUE )
    .endif
    mov ebx,eax
    mov ecx,dwFlagsAndAttributes
    .if ( ecx & FILE_FLAG_DELETE_ON_CLOSE )
        sys_unlink(lpFileName)
    .endif
    .return( rbx )
    endp

    end
