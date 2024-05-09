; GETFTIME_ACCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
ifdef __UNIX__
include sys/stat.inc
else
include winbase.inc
endif
include errno.inc

.code

getftime_access proc fd:int_t

  local FileTime:FILETIME

    ldr ecx,fd

ifdef __UNIX__
    mov eax,-1
else
    .ifd ( _get_osfhandle(ecx) != -1 )

        mov rcx,rax
        .ifd ( GetFileTime(rcx, 0, &FileTime, 0) == 0 )

            _dosmaperr( GetLastError() )
        .else
            FileTimeToTime(&FileTime)
        .endif
    .endif
endif
    ret

getftime_access endp

    end
