; _TPGMPTR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include tchar.inc

.data
_tpgmptr tstring_t 0

.code

_get_tpgmptr proc pgmptr:tarray_t
    ldr rcx,pgmptr
    mov rax,_tpgmptr
    .if ( rcx )
        mov [rcx],rax
    .endif
    ret
    endp

__initpgmptr proc private
    mov rcx,__targv
    mov rax,[rcx]
    mov _tpgmptr,rax
    ret
    endp

.pragma init(__initpgmptr, 5)

    end
