; STRINGLENGTHWORKER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include strsafe.inc

    .code

StringLengthWorker proc _CRTIMP psz:LPTSTR, cchMax:size_t, pcchLength:ptr size_t

    ldr rcx,psz
    ldr rdx,cchMax

    .while ( rdx && ( TCHAR ptr [rcx] != 0 ) )

        add rcx,TCHAR
        dec rdx
    .endw

    xor eax,eax
    .if ( !rdx )
        ;
        ; the string is longer than cchMax
        ;
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif

    mov rcx,pcchLength
    .if ( rcx )

        .ifs (SUCCEEDED(eax))

            sub cchMax,rdx
            mov rdx,cchMax
        .else
            xor edx,edx
        .endif
        mov [rcx],rdx
    .endif
    ret

StringLengthWorker endp

    end
