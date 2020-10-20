; STRINGLENGTHWORKERW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringLengthWorkerW proc psz:STRSAFE_PCNZWCH, cchMax:size_t, pcchLength:ptr size_t

    mov ecx,psz
    mov edx,cchMax

    .while (edx && (word ptr [ecx] != 0))

        add ecx,2
        dec edx
    .endw

    xor eax,eax
    .if (!edx)
        ;;
        ;; the string is longer than cchMax
        ;;
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif

    mov ecx,pcchLength
    .if (ecx)

        .ifs (SUCCEEDED(eax))

            mov eax,cchMax
            sub eax,edx
            mov [ecx],eax
            mov eax,S_OK

        .else

            mov dword ptr [ecx],0
        .endif
    .endif
    ret

StringLengthWorkerW endp

    end
