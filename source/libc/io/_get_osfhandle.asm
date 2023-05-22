; GETOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_get_osfhandle proc handle:int_t

    ldr ecx,handle
    mov rax,-1

    .if ( ecx < _nfile )

        lea rdx,_osfile
        .if ( byte ptr [rdx+rcx] & FOPEN )

            lea rax,_osfhnd
            mov rax,[rax+rcx*size_t]
        .endif
    .endif
    ret

_get_osfhandle endp

    end
