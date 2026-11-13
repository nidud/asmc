; GETFILESIZE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include fileapi.inc
include sys/stat.inc
ifdef _WIN64
define _xstat <_fstat64>
define _sstat <_stati64>
else
define _xstat <_fstat>
define _sstat <_stat32>
endif

.code

GetFileSize proc WINAPI fh:HANDLE, lpSize:LPDWORD
   .new q:_sstat
    ldr rcx,fh
    .ifd _xstat(ecx, &q)
        .return ( FALSE )
    .endif
    mov rcx,lpSize
    mov [rcx],dword ptr q.st_size
    .return( TRUE )
    endp

    end
