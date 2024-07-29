; GETOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

    .code

_get_osfhandle proc handle:int_t
ifdef __UNIX__
    ldr eax,handle
else
    ldr ecx,handle
    mov rdx,_pioinfo(ecx)
    mov rax,-1

    .if ( ecx < _nfile )

        .if ( [rdx].ioinfo.osfile & FOPEN )

            mov rax,[rdx].ioinfo.osfhnd
        .endif
    .endif
endif
    ret

_get_osfhandle endp

    end
