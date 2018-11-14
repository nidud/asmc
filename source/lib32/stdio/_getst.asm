; _GETST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

lastiob equ (offset _iob + (_NSTREAM_ * (SIZE _iobuf)))

    .code

_getst proc
    lea edx,_iob
    .repeat
        xor eax,eax
        .if !([edx]._iobuf._flag & _IOREAD or _IOWRT or _IORW)
            mov [edx]._iobuf._cnt,eax
            mov [edx]._iobuf._flag,eax
            mov [edx]._iobuf._ptr,eax
            mov [edx]._iobuf._base,eax
            dec eax
            mov [edx]._iobuf._file,eax
            mov eax,edx
            .break
        .endif
        add edx,SIZE _iobuf
    .until  edx == lastiob
    ret
_getst endp

    END
