; GETST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

.code

_getst proc
    .for ( eax = 0, rcx = stdin, edx = 0 : edx < _nstream : edx++, rcx+=FILE )
        .if ( !( [rcx].FILE._flag & _IOREAD or _IOWRT or _IORW ) )
            mov [rcx].FILE._cnt,eax
            mov [rcx].FILE._flag,eax
            mov [rcx].FILE._bitcnt,eax
            mov [rcx].FILE._ptr,rax
            mov [rcx].FILE._base,rax
            dec eax
            mov [rcx].FILE._file,eax
ifdef STDZIP
            mov [rcx].FILE._crc32,eax
endif
            mov rax,rcx
           .break
        .endif
    .endf
    ret
    endp

    end
