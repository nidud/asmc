; _ucmpo() - Unsigned Compare
;
; Subtracts destination value from source without saving results.
; Updates flags based on the subtraction.
;
; Modifies flags: ZF CF (OF,SF,PF,AF undefined)
;
include intn.inc

.code

_ucmpo proc fastcall a:ptr, b:ptr

    mov eax,[ecx+12]
    .if eax == [edx+12]
        mov eax,[ecx+8]
        .if eax == [edx+8]
            mov eax,[ecx+4]
            .if eax == [edx+4]
                mov eax,[ecx]
                cmp eax,[edx]
            .endif
        .endif
    .endif
    ret

_ucmpo endp

    end
