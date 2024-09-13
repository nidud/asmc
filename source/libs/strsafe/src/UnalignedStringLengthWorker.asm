; UNALIGNEDSTRINGLENGTHWORKER.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include strsafe.inc

.code

UnalignedStringLengthWorker proc _CRTIMP psz:LPTSTR, cchMax:size_t, pcchLength:ptr size_t

    ldr rcx,psz
    ldr rdx,cchMax

    .while ( rdx && TCHAR ptr [rcx] != 0 )

        add rcx,TCHAR
        dec rdx
    .endw

    mov eax,S_OK
    .if ( rdx == 0 )
        mov eax,STRSAFE_E_INVALID_PARAMETER
    .endif

    mov rcx,pcchLength
    .if ( rcx )

        .if (SUCCEEDED(eax))

            mov rax,cchMax
            sub rax,rdx
            mov [rcx],rax
            mov eax,S_OK
        .else
            xor edx,edx
            mov [rcx],rdx
        .endif
    .endif
    ret

UnalignedStringLengthWorker endp

    end
