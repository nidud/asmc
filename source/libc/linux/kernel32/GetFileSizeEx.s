; GETFILESIZEEX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include sys/stat.inc

.code

GetFileSizeEx proc WINAPI fh:HANDLE, lpSize:PLARGE_INTEGER
   .new q:_stati64
    ldr rcx,fh
    .ifd _fstat64(ecx, &q)
        .return ( FALSE )
    .endif
    mov rcx,lpSize
    mov [rcx],q.st_size
    .return( TRUE )
    endp

    end
