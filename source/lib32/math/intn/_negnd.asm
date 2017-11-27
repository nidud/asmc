; _negnd() - Negation
;
include intn.inc

.code

_negnd proc p:ptr, n:dword

    mov eax,p
    mov ecx,n
    neg dword ptr [eax+ecx*4-4]
    .if ecx > 1
        dec ecx
        .repeat
            neg dword ptr [eax+ecx*4-4]
            sbb dword ptr [eax+ecx*4],0
        .untilcxz
    .endif
    ret

_negnd endp

    end
