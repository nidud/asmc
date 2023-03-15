; _GETST.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

_getst proc uses rsi rdi

    .for ( rsi = stdin,
           rdi = &[rsi+(_NSTREAM_ * sizeof(_iobuf))],
           eax = 0 : rsi < rdi : rsi += sizeof(_iobuf) )

        .if ( !( [rsi]._iobuf._flag & _IOREAD or _IOWRT or _IORW ) )

            mov [rsi]._iobuf._cnt,eax
            mov [rsi]._iobuf._flag,eax
            mov [rsi]._iobuf._ptr,rax
            mov [rsi]._iobuf._base,rax
            dec eax
            mov [rsi]._iobuf._file,eax
            mov rax,rsi
           .break
        .endif
    .endf
    ret

_getst endp

    end
