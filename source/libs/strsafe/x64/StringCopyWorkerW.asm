; STRINGCOPYWORKERW.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

    option win64:rsp noauto nosave

StringCopyWorkerW proc pszDest:STRSAFE_LPWSTR, cchDest:size_t, pcchNewDestLength:ptr size_t,
    pszSrc:STRSAFE_PCNZWCH, cchToCopy:size_t

    xor r10d,r10d
    mov r11,cchToCopy
    mov ax,[r9]
    .while (rdx && r11 && ax != 0)

        mov ax,[r9+r10*2]
        mov [rcx+r10*2],ax
        dec rdx
        dec r11
        inc r10
    .endw

    xor eax,eax
    .if (!rdx)
        ;;
        ;; we are going to truncate pszDest
        ;;
        dec r10
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .endif

    mov word ptr [rcx+r10*2],0

    .if (r8)

        mov [r8],r10
    .endif
    ret

StringCopyWorkerW endp

    end
