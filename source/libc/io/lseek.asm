; LSEEK.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifdef __UNIX__
include sys/syscall.inc
endif

    .code

_lseek proc fd:int_t, offs:size_t, pos:uint_t

ifdef __UNIX__

    .ifs ( sys_lseek(ldr(fd), ldr(offs), ldr(pos)) < 0 )

        neg eax
        _set_errno(eax)
    .endif
ifndef _WIN64
    cdq
endif

else

    ldr ecx,fd
    ldr rax,offs
    ldr edx,pos

ifdef _WIN64
    .if ( edx == SEEK_SET )
        mov eax,eax
    .endif
    _lseeki64( ecx, rax, edx )
else
    cmp edx,SEEK_SET
    cdq
    .ifz
        xor edx,edx
    .endif
    _lseeki64( ecx, edx::eax, pos )
endif
endif
    ret

_lseek endp

    end
