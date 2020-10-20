; STRINGLENGTHWORKERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringLengthWorkerA proc psz:STRSAFE_PCNZCH, cchMax:size_t, pcchLength:ptr size_t

    mov ecx,psz
    mov edx,cchMax

    .while (edx && (byte ptr [ecx] != 0))

        inc ecx
        dec edx
    .endw

    xor eax,eax
    .if (!edx)
        ;;
        ;; the string is longer than cchMax
        ;;
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif

    .if (pcchLength)

        .ifs (SUCCEEDED(eax))

            mov ecx,cchMax
            sub ecx,edx
            mov edx,pcchLength
            mov [edx],ecx

        .else

            mov edx,pcchLength
            mov dword ptr [edx],0

        .endif
    .endif
    ret

StringLengthWorkerA endp

    end
