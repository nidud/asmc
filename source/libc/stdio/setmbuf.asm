; SETMBYF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; void setmbuf() - toggles memory buffer
;
include stdio.inc

    .code

setmbuf proc fp:ptr FILE, mbuf:int_t

    ldr rcx,fp

    .if ( ldr(mbuf) )
        or [rcx].FILE._flag,_IOMEMBUF
    .else
        and [rcx].FILE._flag,not _IOMEMBUF
    .endif
    ret

setmbuf endp

    end
