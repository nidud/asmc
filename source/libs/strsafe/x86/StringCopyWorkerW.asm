; STRINGCOPYWORKERW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringCopyWorkerW proc uses esi edi ebx pszDest:STRSAFE_LPWSTR, cchDest:size_t,
        pcchNewDestLength:ptr size_t, pszSrc:STRSAFE_PCNZWCH, cchToCopy:size_t

    xor ebx,ebx
    mov edi,pszDest
    mov esi,pszSrc
    mov ecx,cchToCopy
    mov edx,cchDest

    mov ax,[esi]
    .while (edx && ecx && ax != 0)

        mov ax,[esi+ebx*2]
        mov [edi+ebx*2],ax
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

    mov word ptr [edi+ebx*2],0
    mov edx,pcchNewDestLength
    .if (edx)

        mov [edx],ebx
    .endif
    ret

StringCopyWorkerW endp

    end
