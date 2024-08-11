; LSEEKI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include stdlib.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif

    .code

_lseeki64 proc fd:int_t, offs:uint64_t, pos:uint_t

if defined(__UNIX__) and defined(_WIN64)

    .ifs ( sys_lseek(edi, rsi, edx) < 0 )

        neg eax
        _set_errno(eax)
    .endif

else

    .new new_offs:uint64_t

ifdef __UNIX__

    lea eax,new_offs
    .ifs ( sys_llseek(fd, uint_t ptr offs, uint_t ptr offs[4], eax, pos) < 0 )

        neg eax
        _set_errno(eax)
    .endif

else
    .ifd ( _get_osfhandle( fd ) != -1 )

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
endif
endif
    ret

_lseeki64 endp

    end
