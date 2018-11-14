; _CMPND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _cmpnd() - Unsigned Compare
;
; Subtracts destination value from source without saving results.
; Updates flags based on the subtraction.
;
; Modifies flags: ZF CF (OF,PF,SF,AF undefined)
;
; Note: Using invoke with C call will ADD ESP,12 and thus destroy
;       the flags. See OPTION EPILOGUE:FLAGS in _divdn.asm.
;
include intn.inc

option win64:rsp nosave noauto

.code

_cmpnd proc a:ptr, b:ptr, n:dword

    xchg rcx,r8
    .repeat
        mov rax,[r8+rcx*8-8]
        sub rax,[rdx+rcx*8-8]
        .break .ifnz
    .untilcxz
    ret

_cmpnd endp

    end
