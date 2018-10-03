
include strsafe.inc

    .code

    option win64:rsp noauto nosave

StringCopyWorkerA proc pszDest:STRSAFE_LPSTR, cchDest:size_t, pcchNewDestLength:ptr size_t,
    pszSrc:STRSAFE_PCNZCH, cchToCopy:size_t

    xor r10d,r10d
    mov r11,cchToCopy

    .while (rdx && r11 && (byte ptr [r9] != 0))

        mov al,[r9+r10]
        mov [rcx+r10],al
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

    mov byte ptr [rcx+r10],0

    .if (r8)

        mov [r8],r10
    .endif
    ret

StringCopyWorkerA endp

    end
