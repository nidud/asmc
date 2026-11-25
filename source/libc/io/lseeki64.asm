; LSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
include winbase.inc

.code

_lseeki64 proc fd:int_t, offs:uint64_t, pos:uint_t
    .new new_offs:uint64_t
    .ifd ( _get_osfhandle( ldr(fd) ) != -1 )
        mov rcx,rax
        .ifd !SetFilePointerEx( rcx, offs, &new_offs, pos )
            _dosmaperr( GetLastError() )
ifdef _WIN64
        .else
            mov rax,new_offs
else
            cdq
        .else
            mov eax,uint_t ptr new_offs
            mov edx,uint_t ptr new_offs[4]
endif
        .endif
    .endif
    ret
    endp

    end
