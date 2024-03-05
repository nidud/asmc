; _FINDCLOSE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc
ifdef __UNIX__
include malloc.inc
else
include errno.inc
include winbase.inc
endif

.code

ifdef __UNIX__

_findclose proc uses rbx handle:ptr

ifdef _WIN64
    mov rbx,rdi
    .while rbx
        mov rdi,rbx
        mov rbx,[rbx] ; .DNODE.next
        free(rdi)
    .endw
    mov rax,rbx
else
    mov eax,-1
endif
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
