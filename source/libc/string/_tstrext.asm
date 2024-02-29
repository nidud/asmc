; _TSTREXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc
include tchar.inc

    .code

_tstrext proc uses rbx string:LPTSTR

    ldr rcx,string
    mov rbx,_tstrfn( rcx )
    .if _tcsrchr( rbx, '.' )
        .if ( rax == rbx )
            xor eax,eax
        .endif
    .endif
    ret

_tstrext endp

    end
