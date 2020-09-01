; WCSNCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

wcsncpy proc uses esi edi s1:LPWSTR, s2:LPWSTR, count:SIZE_T

    .for ( edi=s1, esi=s2, eax=0, ecx=count: ecx: edi+=2, esi+=2, ecx-- )

        mov ax,[esi]
        mov [edi],ax
        .break .if !eax
    .endf

    mov word ptr [edi-2],0
    mov eax,s1
    ret

wcsncpy endp

    END
