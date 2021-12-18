; STRFN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strfn(char *path);
;
; EXIT: file part of path if /\ is found, else path
;

include crtl.inc

    .code

strfn proc path:LPSTR

    mov ecx,path

    .for ( eax=ecx, dl=[ecx] : dl : ecx++, dl=[ecx] )

        .if ( dl == '\' || dl == '/' )

            .if ( byte ptr [ecx+1] )

                lea eax,[ecx+1]
            .endif
        .endif
    .endf
    ret

strfn endp

    end
