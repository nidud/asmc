; STRINGCCHLENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchLength proc psz:LPTSTR, cchMax:size_t, pcchLength:ptr size_t

    ldr rcx,psz
    ldr rax,cchMax

    .if ( rcx == NULL || rax > STRSAFE_MAX_CCH )
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorker(rcx, rax, pcchLength)
    .endif

    .if ( FAILED(eax) && pcchLength )

        mov rcx,pcchLength
        xor edx,edx
        mov [rcx],rdx
    .endif
    ret

StringCchLength endp

    end
