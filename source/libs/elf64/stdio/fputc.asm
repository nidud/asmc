; FPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

fputc proc char:SINT, fp:LPFILE

    dec [rsi]._iobuf._cnt
    jl	flush
    mov rcx,[rsi]._iobuf._ptr
    inc [rsi]._iobuf._ptr
    mov eax,edi
    mov [rcx],al
toend:
    ret
flush:
    _flsbuf(edi, rsi)
    jmp toend
fputc endp

    END
