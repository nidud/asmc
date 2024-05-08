; _UTFSLEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Return Wide char count (EAX) of UTF8 string.
;
include stdlib.inc

    .code

_utfslen proc uses rbx utf:string_t

    ldr rcx,utf

    .for ( rdx = &_lookuptrailbytes,
           ebx = 0, eax = 0 : byte ptr [rcx] : eax++ )

        mov bl,[rcx]
        mov bl,[rdx+rbx]
        lea rcx,[rcx+rbx+1]
    .endf
    ret

_utfslen endp

    end
