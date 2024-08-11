; FINDCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
ifdef __UNIX__
include direct.inc
include malloc.inc
else
include errno.inc
include winbase.inc
endif

.code

ifdef __UNIX__

_findclose proc uses rbx handle:ptr

    ldr rbx,handle

    closedir( [rbx] )
    free(rbx)
    xor eax,eax
    ret

_findclose endp

else

_findclose proc handle:ptr

    .if !FindClose( handle )

        _dosmaperr( GetLastError() )
    .else
        xor eax,eax
    .endif
    ret

_findclose endp

endif

    end
