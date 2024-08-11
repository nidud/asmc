; ALLOCOSFHND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include io.inc

.code

_alloc_osfhnd proc

    assume rcx:pioinfo

    .for ( rcx = __pioinfo, eax = 0: [rcx].osfile & FOPEN: rcx += ioinfo )

        inc eax
        .if ( eax == _nfile  )

            .return(-1)
        .endif
    .endf

    mov [rcx].osfile,0
ifndef __UNIX__
    ;mov [rcx].osfhnd,-1
    mov [rcx].pipech,10
    ;mov [rcx].textmode,0
    ;mov [rcx].unicode,0
    mov [rcx].pipech2[0],10
    mov [rcx].pipech2[1],10
    ;mov [rcx].dbcsBuffer,0
    ;mov [rcx].startpos,0
    ;mov [rcx].utf8translations,0
    ;mov [rcx].dbcsBufferUsed,0
endif
    ret

_alloc_osfhnd endp

    end
