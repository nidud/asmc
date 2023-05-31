; _GETST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rcx:LPFILE

_getst proc

    .for ( rcx = stdin,
           rdx = &[rcx+(_NSTREAM_ * sizeof(_iobuf))],
           eax = 0 : rcx < rdx : rcx += sizeof(_iobuf) )

        .if ( !( [rcx]._flag & _IOREAD or _IOWRT or _IORW ) )

            mov [rcx]._cnt,eax
            mov [rcx]._flag,eax
            mov [rcx]._ptr,rax
            mov [rcx]._base,rax
            dec eax
            mov [rcx]._file,eax
            mov rax,rcx
           .break
        .endif
    .endf
    ret

_getst endp

    end
