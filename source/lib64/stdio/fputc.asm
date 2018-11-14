; FPUTC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .code

    option win64:rsp nosave

fputc proc char:SINT, fp: LPFILE

    dec [rdx]._iobuf._cnt
    jl	flush
    mov r8,[rdx]._iobuf._ptr
    inc [rdx]._iobuf._ptr
    mov eax,ecx
    mov [r8],al
toend:
    ret
flush:
    _flsbuf(ecx, rdx)
    jmp toend
fputc endp

    END
