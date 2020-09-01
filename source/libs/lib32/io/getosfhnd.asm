; GETOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

.code

getosfhnd proc handle:SINT
    mov eax,-1
    mov ecx,handle
    .if ecx < _nfile
        .if _osfile[ecx] & FH_OPEN
            mov eax,handle
            mov eax,_osfhnd[eax*4]
        .endif
    .endif
    ret
getosfhnd endp

    end
