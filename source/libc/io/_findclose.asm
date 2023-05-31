; _FINDCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
include errno.inc
ifndef __UNIX__
include winbase.inc
endif

    .code

_findclose proc handle:intptr_t
ifdef __UNIX__
    _set_errno( ENOSYS )
    mov rax,-1
else
    .if !FindClose( handle )

        _dosmaperr( GetLastError() )
    .else
        xor eax,eax
    .endif
endif
    ret

_findclose endp

    end
