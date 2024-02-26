; STRINGCOPYWORKER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc
include tmacro.inc

    .code

StringCopyWorker proc uses rsi rdi rbx pszDest:LPTSTR, cchDest:size_t, pcchNewDestLength:ptr size_t,
    pszSrc:LPTSTR, cchToCopy:size_t

    ldr rcx,pszDest
    ldr rdx,cchDest
    mov rsi,pszSrc

    xor ebx,ebx
    mov rdi,cchToCopy

    mov __a,[rsi]
    .while ( rdx && rdi && __a )

        mov __a,[rsi+rbx*TCHAR]
        mov [rcx+rbx*TCHAR],__a
        dec rdx
        dec rdi
        inc rbx
    .endw

    xor eax,eax
    .if ( !rdx )
        ;
        ; we are going to truncate pszDest
        ;
        dec rbx
        mov eax,STRSAFE_E_INSUFFICIENT_BUFFER
    .endif

    mov TCHAR ptr [rcx+rbx*TCHAR],0
    mov rdi,pcchNewDestLength

    .if ( rdi )

        mov [rdi],rbx
    .endif
    ret

StringCopyWorker endp

    end
