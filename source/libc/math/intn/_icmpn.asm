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

.code

_icmpn proc uses esi edi ebx a:ptr, b:ptr, n:dword
    mov esi,a
    mov edi,b
    mov ecx,n
    xor edx,edx
    .repeat
        mov eax,[esi+edx*4]
        sub eax,[edi+edx*4]
        jnz break
        inc edx
    .untilcxz
toend:
    ret
break:
    sbb ebx,ebx
    dec ecx
    .ifnz
        inc edx
        .if ecx > 1
            dec ecx
            .repeat
                shr ebx,1
                mov eax,[esi+edx*4]
                sbb eax,[edi+edx*4]
                sbb ebx,ebx
                inc edx
            .untilcxz
        .endif
        shr ebx,1
        mov eax,[esi+edx*4]
        sbb eax,[edi+edx*4]
        jnz toend
        .ifo
            jc  toend
            mov eax,80000000h
            sub eax,7FFFFFFFh
            jmp toend
        .endif
        inc eax
        jmp toend
    .endif
    mov eax,[esi+edx*4]
    sub eax,[edi+edx*4]
    jmp toend

_icmpn endp

    end
