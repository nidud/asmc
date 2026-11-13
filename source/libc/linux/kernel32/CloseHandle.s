; CLOSEHANDLE.S--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include handleapi.inc
include errno.inc
include sys/syscall.inc

.code

 CloseHandle proc WINAPI hFile:HANDLE
    ldr rcx,hFile
    .ifsd ( sys_close(ecx) < 0 )
        neg eax
        _set_errno( eax )
        .return( 0 )
    .endif
    .return( TRUE )
    endp

    end
