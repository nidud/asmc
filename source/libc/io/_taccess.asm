; _TACCESS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
include tchar.inc
ifdef __UNIX__
include sys/syscall.inc
endif

.code

_taccess proc file:LPTSTR, mode:SINT
ifdef __UNIX__
    .ifsd ( sys_access( ldr(file), ldr(mode) ) < 0 )

        neg eax
        _set_errno( eax )
    .endif
else
    .ifd ( _tgetfattr( ldr(file) ) != -1 )

        .if ( mode == 2 && eax & _A_RDONLY )
            mov eax,-1
        .else
            xor eax,eax
        .endif
    .endif
endif
    ret

_taccess endp

    end