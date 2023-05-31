; STRFN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strfn(char *path);
;
; EXIT: file part of path if /\ is found, else path
;

include string.inc

    .code

strfn proc path:string_t

    ldr rcx,path
    .for ( rax = rcx, dl = [rcx] : dl : rcx++, dl = [rcx] )
ifdef __UNIX__
        .if ( dl == '/' )
else
        .if ( dl == '\' || dl == '/' )
endif

            .if ( byte ptr [rcx+1] )

                lea rax,[rcx+1]
            .endif
        .endif
    .endf
    ret

strfn endp

    end
