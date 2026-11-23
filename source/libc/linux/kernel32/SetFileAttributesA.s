; SETFILEATTRIBUTESA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include sys/syscall.inc
include errno.inc
include winbase.inc

.code

 SetFileAttributesA proc WINAPI lpFileName:LPCSTR, dwFileAttributes:DWORD
    ldr rcx,lpFileName
    .if ( !rcx || byte ptr [rcx] == 0 )
        .return( SetLastError( ERROR_INVALID_PARAMETER ) )
    .endif
    ldr eax,dwFileAttributes
    and eax,07777o ; keep permission & special bits (rwx + suid/sgid/sticky)
    .ifsd ( sys_chmod( rcx, eax ) < 0 )
        .return( _sys_maperr(eax) )
    .endif
    .return( 1 )
    endp

    end
