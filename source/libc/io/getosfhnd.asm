; GETOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

.code

ifndef __UNIX__
_get_osfhandle proc handle:int_t
    ldr ecx,handle
    mov rdx,_pioinfo(ecx)
    mov rax,-1
    .if ( ecx < _nfile )
        .if ( [rdx].ioinfo.osfile & FOPEN )
            mov rax,[rdx].ioinfo.osfhnd
        .endif
    .endif
    ret
    endp
endif
    end
