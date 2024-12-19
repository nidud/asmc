; GETST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    assume rcx:LPFILE

_getst proc

    .for ( eax = 0, rcx = stdin, edx = 0 : edx < _nstream : edx++, rcx+=FILE )

        .if ( !( [rcx]._flag & _IOREAD or _IOWRT or _IORW ) )

            mov [rcx]._cnt,eax
            mov [rcx]._flag,eax
            mov [rcx]._bitcnt,eax
            mov [rcx]._ptr,rax
            mov [rcx]._base,rax
            dec eax
            mov [rcx]._file,eax
ifndef NOSTDCRC
            mov [rcx]._crc32,eax
endif
            mov rax,rcx
           .break
        .endif
    .endf
    ret

_getst endp

    end
