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

.code

_cmpnd proc uses esi a:ptr, b:ptr, n:dword

    mov esi,a
    mov edx,b
    mov ecx,n
    .repeat
        mov eax,[esi+ecx*4-4]
        sub eax,[edx+ecx*4-4]
        .break .ifnz
    .untilcxz
    ret

_cmpnd endp

    end
