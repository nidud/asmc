; SETFTIME.ASM--
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

setftime proc uses rbx fd:int_t, ftime:uint_t

  local FileTime:FILETIME

    ldr ecx,fd
ifdef __UNIX__
    mov eax,-1
else
    .ifd ( _get_osfhandle(ecx) != -1 )

        mov rbx,rax
        .ifd !SetFileTime(rbx, 0, 0, TimeToFileTime(ftime, &FileTime))

            _dosmaperr( GetLastError() )
        .else
            xor eax,eax
        .endif
    .endif
endif
    ret

setftime endp

    end
