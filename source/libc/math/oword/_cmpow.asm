; _cmpow() - Signed Compare
;
; Subtracts destination value from source without saving results.
; Updates flags based on the subtraction.
;
; Modifies flags: OF SF ZF CF (PF,AF undefined)
;
include intn.inc

.code

_cmpow proc fastcall a:ptr, b:ptr

    mov eax,[ecx]
    sub eax,[edx]
    jnz @1
    mov eax,[ecx+4]
    sub eax,[edx+4]
    jnz @2
    mov eax,[ecx+8]
    sub eax,[edx+8]
    jnz @3
    mov eax,[ecx+12]
    sbb eax,[edx+12]
    jmp toend
@4:
    jc  toend
    mov eax,80000000h
    sub eax,7FFFFFFFh
    jmp toend
@1:
    mov eax,[ecx+4]
    sbb eax,[edx+4]
@2:
    mov eax,[ecx+8]
    sbb eax,[edx+8]
@3:
    mov eax,[ecx+12]
    sbb eax,[edx+12]
    jnz toend
    jo  @4
    inc eax
toend:
    ret

_cmpow endp

    end
