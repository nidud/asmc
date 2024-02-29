; _TSTRFN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strfn(char *path);
;
; return file part of path if /\ is found, else path
;

include string.inc

    .code

_tstrfn proc path:LPTSTR

    ldr rcx,path
    movzx edx,TCHAR ptr [rcx]

    .for ( rax = rcx : edx : )
ifdef __UNIX__
        .if ( edx == '/' )
else
        .if ( edx == '\' || edx == '/' )
endif

            .if ( TCHAR ptr [rcx+TCHAR] )

                lea rax,[rcx+TCHAR]
            .endif
        .endif
        add rcx,TCHAR
        movzx edx,TCHAR ptr [rcx]
    .endf
    ret

_tstrfn endp

    end
