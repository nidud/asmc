; PUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc

    .code

puts proc string:string_t

    mov rsi,rdi
    mov ecx,-1
    xor eax,eax
    repz scasb
    not ecx
    dec ecx
    _write(stdout._file, rsi, ecx)
    ret

puts endp

    END