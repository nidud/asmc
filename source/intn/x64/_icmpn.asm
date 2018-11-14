; _ICMPN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _icmpn() - Signed Compare
;
; Subtracts destination value from source without saving results.
; Updates flags based on the subtraction.
;
; Modifies flags: OF SF ZF CF (PF,AF undefined)
;
; Note: Using invoke with C call will ADD ESP,12 and thus destroy
;       the flags. See OPTION EPILOGUE:FLAGS in _divdn.asm.
;
include intn.inc

option win64:rsp nosave noauto

.code

_icmpn proc a:ptr, b:ptr, n:dword
    xor r9d,r9d
    .repeat
        mov rax,[rcx+r9*8]
        sub rax,[rdx+r9*8]
        jnz break
        inc r9d
        dec r8d
    .untilz
toend:
    ret
break:
    sbb r10d,r10d
    dec r8d
    .ifnz
        inc r9d
        .if r8d > 1
            dec r8d
            .repeat
                shr r10d,1
                mov rax,[rcx+r9*8]
                sbb rax,[rdx+r9*8]
                sbb r10d,r10d
                inc r9d
                dec r8d
            .untilz
        .endif
        shr r10d,1
        mov rax,[rcx+r9*8]
        sbb rax,[rdx+r9*8]
        jnz toend
        .ifo
            jc  toend
            mov eax,0x80000000
            sub eax,0x7FFFFFFF
            jmp toend
        .endif
        inc eax
        jmp toend
    .endif
    mov rax,[rcx+r9*8]
    sub rax,[rdx+r9*8]
    jmp toend

_icmpn endp

    end
