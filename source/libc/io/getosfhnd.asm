; GETOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

getosfhnd proc handle:SINT

    mov ecx,handle
    mov rax,-1

    .if ( ecx < _nfile )

        lea rdx,_osfile
        .if ( byte ptr [rdx+rcx] & FH_OPEN )

            lea rax,_osfhnd
            mov rax,[rax+rcx*size_t]
        .endif
    .endif
    ret

getosfhnd endp

    end
