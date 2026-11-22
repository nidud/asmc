; READFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include errno.inc
include sys/syscall.inc

.code

 ReadFile proc WINAPI hFile:HANDLE, lpBuffer:LPVOID, nNumberOfBytesToRead:DWORD,
        lpNumberOfBytesRead:LPDWORD, lpOverlapped:LPOVERLAPPED
    .ifsd ( sys_read( ldr(hFile), lpBuffer, ldr(nNumberOfBytesToRead) ) < 0 )
        .return( _sys_maperr(eax) )
    .endif
    mov rcx,lpNumberOfBytesRead
    .if ( rcx )
        mov [rcx],eax
    .endif
    ret
    endp

    end
