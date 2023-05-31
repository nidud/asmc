; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_strrev proc uses rbx string:string_t

    ldr rcx,string
    mov rbx,rcx

    .for ( rdx = rcx : byte ptr [rdx] : rdx++ )
    .endf

    .for ( rdx-- : rdx > rcx : rdx--, rcx++ )

        mov al,[rcx]
        mov ah,[rdx]
        mov [rcx],ah
        mov [rdx],al
    .endf
    .return( rbx )

_strrev endp

    end
