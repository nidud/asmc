; STRINGCCHLENGTH.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

StringCchLength proc uses rbx psz:LPTSTR, cchMax:size_t, pcchLength:ptr size_t

    ldr rbx,pcchLength
    ldr rax,cchMax
    ldr rcx,psz

    .if ( rcx == NULL || rax > STRSAFE_MAX_CCH )
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .else
        StringLengthWorker(rcx, rax, rbx)
    .endif

    .if ( FAILED(eax) && rbx )

        xor edx,edx
        mov [rbx],rdx
    .endif
    ret
    endp

    end
