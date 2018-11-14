; _IDIVN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _idivn() - Signed Divide
;
; Signed binary division of dividend by source.
; Note: The quotient is stored in "dividend".
;
include intn.inc

.code

_idivn proc uses esi edi ebx dividend:ptr, divisor:ptr, reminder:ptr, n:dword

    mov esi,divisor
    mov edi,dividend
    mov ebx,n

    mov eax,[edi+ebx*4-4]
    .ifs eax < 0
        _negnd(edi, ebx)
        mov eax,[esi+ebx*4-4]
        .ifs eax < 0
            _negnd(esi, ebx)
            _divnd(edi, esi, reminder, ebx)
            _negnd(esi, ebx)
        .else
            _divnd(edi, esi, reminder, ebx)
            _negnd(edi, ebx)
        .endif
    .else
        mov eax,[esi+ebx*4-4]
        .ifs eax < 0
            _negnd(esi, ebx)
            _divnd(edi, esi, reminder, ebx)
            _negnd(esi, ebx)
            _negnd(edi, ebx)
        .else
            _divnd(edi, esi, reminder, ebx)
        .endif
    .endif
    ret

_idivn endp

    end
