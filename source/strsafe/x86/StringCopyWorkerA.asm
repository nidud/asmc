; STRINGCOPYWORKERA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCopyWorkerA proc WINAPI uses esi edi ebx pszDest:STRSAFE_LPSTR, cchDest:size_t,
        pcchNewDestLength:ptr size_t, pszSrc:STRSAFE_PCNZCH, cchToCopy:size_t

    mov esi,pszSrc
    mov edi,pszDest
    mov ecx,cchToCopy
    mov edx,cchDest
    xor ebx,ebx

    mov al,[esi]
    .while (edx && ecx && al != 0)

        mov al,[esi+ebx]
        mov [edi+ebx],al
        dec edx
        dec ecx
        inc ebx
    .endw

    xor eax,eax
    .if (!edx)
        ;;
        ;; we are going to truncate pszDest
        ;;
        dec ebx
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .endif

    mov byte ptr [edi+ebx],0
    mov edx,pcchNewDestLength

    .if (edx)

        mov [edx],ebx
    .endif
    ret

StringCopyWorkerA endp

    end
