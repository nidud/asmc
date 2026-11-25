; FLUSHFILEBUFFERS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include errno.inc
include sys/syscall.inc
include winbase.inc

.code

 FlushFileBuffers proc WINAPI hFile:HANDLE

    ldr rcx,hFile
    .ifs ( ecx < 0 )
        .return( SetLastError( ERROR_INVALID_HANDLE ) )
    .endif
    .ifsd ( sys_fsync(ecx) < 0 )
        mov ecx,eax
        neg eax
        .if ( eax == EINVAL )
            ; Pipes, sockets, FIFOs, and TTYs return EINVAL on Linux fsync
            .return( 1 )
        .endif
        .if ( eax == EBADF )
            .return( SetLastError( ERROR_INVALID_HANDLE ) )
        .endif
        .return( _sys_maperr(ecx) )
    .endif
    .return( 1 )
    endp

    end
