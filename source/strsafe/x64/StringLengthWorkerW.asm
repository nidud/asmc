
include strsafe.inc

    .code

    option win64:rsp nosave noauto

StringLengthWorkerW proc psz:STRSAFE_PCNZWCH, cchMax:size_t, pcchLength:ptr size_t

    mov r9,rdx

    .while (rdx && (word ptr [rcx] != 0))

        add rcx,2
        dec rdx
    .endw

    xor eax,eax
    .if (!rdx)
        ;;
        ;; the string is longer than cchMax
        ;;
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif

    .if (r8)

        .ifs (SUCCEEDED(eax))

            sub r9,rdx
            mov [r8],r9

        .else

            xor r9d,r9d
            mov [r8],r9

        .endif
    .endif
    ret

StringLengthWorkerW endp

    end
