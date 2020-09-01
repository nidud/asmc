; WCSNCMP.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsncmp proc uses esi edi edx s1:LPWSTR, s2:LPWSTR, count:SIZE_T

    mov ecx,count
    .if ecx

        mov edx,ecx
        mov edi,s1
        mov esi,edi
        sub eax,eax
        repne scasw

        neg ecx
        add ecx,edx
        mov edi,esi
        mov esi,s2
        repe cmpsw

        mov ax,[esi-2]
        sub ecx,ecx
        .if ax > [edi-2]

            not ecx
        .elseif !ZERO?

            sub ecx,2
            not ecx
        .endif
    .endif
    mov eax,ecx
    ret

wcsncmp endp

    end
