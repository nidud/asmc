; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_strrev proc string:string_t

ifndef _WIN64
    mov ecx,string
endif
    .for ( rdx = rcx : byte ptr [rdx] : rdx++ )
    .endf

    .for ( rdx-- : rdx > rcx : rdx--, rcx++ )

        mov al,[rcx]
        mov ah,[rdx]
        mov [rcx],ah
        mov [rdx],al
    .endf
    .return( string )

_strrev endp

    end
