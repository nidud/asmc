; STRFN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include crtl.inc

    .code

strfn proc path:string_t

    .for ( rax=rcx, dl=[rcx] : dl : rcx++, dl=[rcx] )

        .if ( dl == '\' || dl == '/' )

            .if ( byte ptr [rcx+1] )

                lea rax,[rcx+1]
            .endif
        .endif
    .endf
    ret

strfn endp

    end
