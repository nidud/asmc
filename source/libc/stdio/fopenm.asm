; FOPENM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE * _fopenm() - open a memory buffer
;
; This duplicate a stream for output to a buffer.
;
include stdio.inc

    .code

_fopenm proc uses rbx fp:LPFILE

    ldr rbx,fp

    .if _getst()

        mov ecx,[rbx].FILE._file
        mov [rax].FILE._file,ecx ; duplicate handle..
        mov ecx,[rbx].FILE._flag
        and ecx,_IOREAD or _IOWRT
        or  ecx,_IOMEMBUF
        mov [rax].FILE._flag,ecx
    .endif
    ret

_fopenm endp

    end
