; GETFILETIME.ASM--
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

 GetFileTime proc WINAPI fh:HANDLE, cTime:LPFILETIME, aTime:LPFILETIME, mTime:LPFILETIME
   .new q:_sstat
    ldr rcx,fh
    .ifd _xstat(ecx, &q)
        .return ( FALSE )
    .endif
    mov rdx,cTime
    .if ( rdx )
        __timespec_to_ft(&q.st_ctime, rdx)
    .endif
    mov rdx,aTime
    .if ( rdx )
        __timespec_to_ft(&q.st_atime, rdx)
    .endif
    mov rdx,mTime
    .if ( rdx )
        __timespec_to_ft(&q.st_mtime, rdx)
    .endif
    .return( TRUE )
    endp

    end
