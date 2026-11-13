; WRITEFILE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include fileapi.inc
include sys/syscall.inc

.code

 WriteFile proc WINAPI uses rbx hFile:HANDLE, lpBuffer:LPCVOID, nNumberOfBytesToWrite:DWORD,
        lpNumberOfBytesWritten:LPDWORD, lpOverlapped:LPOVERLAPPED
    ldr rbx,lpNumberOfBytesWritten
    ldr rcx,hFile
    .ifs ( sys_write( ecx, lpBuffer, ldr(nNumberOfBytesToWrite) ) < 0 )
        neg eax
        _set_errno( eax )
        .return( FALSE )
    .endif
    .if ( rbx )
        mov [rbx],eax
    .endif
    .return( TRUE )
    endp

    end
