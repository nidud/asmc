; _STRREV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include string.inc

    .code

_wcsrev proc string:wstring_t

    .for ( rax=rcx, rdx=rcx : word ptr [rdx] : rdx += 2 )

    .endf

    .for ( rdx -= 2 : rdx > rcx : rdx -= 2, rcx += 2 )

        mov r8w,[rcx]
        mov r9w,[rdx]
        mov [rcx],r9w
        mov [rdx],r8w
    .endf
    ret

_wcsrev endp

    end
