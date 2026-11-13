; SETFTIME_CREATE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include time.inc
include winbase.inc
include errno.inc

.code

setftime_create proc uses rbx fd:int_t, ftime:uint_t
  local FileTime:FILETIME
    ldr ecx,fd
ifdef __UNIX__
    mov eax,-1
else
    .ifd ( _get_osfhandle(ecx) != -1 )
        mov rbx,rax
        .ifd !SetFileTime(rbx, __timet_to_ft(ftime, &FileTime), 0, 0)
            _dosmaperr( GetLastError() )
        .else
            xor eax,eax
        .endif
    .endif
endif
    ret
    endp

    end
