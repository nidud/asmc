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

    .for ( esi = a, edi = b, ecx = n, edx = 0: ecx: ecx--, edx++ )

        mov eax,[esi+edx*4]
        sub eax,[edi+edx*4]
        .ifnz
            sbb ebx,ebx
            dec ecx
            .ifnz
                inc edx
                .if ecx > 1
                    dec ecx
                    .repeat
                        bt  ebx,0
                        mov eax,[esi+edx*4]
                        sbb eax,[edi+edx*4]
                        sbb ebx,ebx
                        inc edx
                    .untilcxz
                .endif
                bt  ebx,0
                mov eax,[esi+edx*4]
                sbb eax,[edi+edx*4]
                .break .ifnz
                .ifo
                    .break .ifc
                    mov eax,0x80000000
                    sub eax,0x7FFFFFFF
                    .break
                .endif
                inc eax
                .break
            .endif
            mov eax,[esi+edx*4]
            sub eax,[edi+edx*4]
            .break
        .endif
    .endf
    ret

_icmpn endp

    end
