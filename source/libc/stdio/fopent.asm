; FOPENT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; FILE * _fopent() - open a text buffer
;
; This produce formatted output to a buffer which grows in size
; as appose being flushed to a file.
;
include stdio.inc

    .code

_fopent proc

    .if _getst()

        mov [rax].FILE._file,1 ; dummy handle..
        mov [rax].FILE._flag,_IOWRT or _IOMEMBUF
    .endif
    ret

_fopent endp

    end
