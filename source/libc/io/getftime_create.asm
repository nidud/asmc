; GETFTIME_CREATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
include winbase.inc
include errno.inc

.code

getftime_create proc fd:int_t
  local FileTime:FILETIME
    ldr ecx,fd
    .ifd ( _get_osfhandle(ecx) != -1 )
        mov rcx,rax
        .ifd !GetFileTime(rcx, &FileTime, 0, 0)
            _dosmaperr( GetLastError() )
        .else
            __timet_from_ft(&FileTime)
        .endif
    .endif
    ret
    endp

    end
