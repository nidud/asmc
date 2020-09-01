; WCSNCAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsncat PROC USES esi edi s1:LPWSTR, s2:LPWSTR, max:SIZE_T

    xor eax,eax
    mov edi,s1
    mov esi,s2
    mov ecx,-1
    repne scasw
    sub edi,2
    mov ecx,max

    .repeat

        .if !ecx

            mov [edi],cx
            .break
        .endif
        mov ax,[esi]
        mov [edi],ax
        add edi,2
        add esi,2
        sub ecx,1

    .until !eax

    mov eax,s1
    ret

wcsncat endp

    end
