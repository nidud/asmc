; _TCSFN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strfn(char *path);
; wchar_t *_wstrfn(wchar_t *path);
;
; return file part of path if /\ is found, else path
;

_tcsfn proc path:LPTSTR

    ldr rcx,path
    movzx edx,tchar_t ptr [rcx]

    .for ( rax = rcx : edx : )
ifdef __UNIX__
        .if ( edx == '/' )
else
        .if ( edx == '\' || edx == '/' )
endif
            .if ( tchar_t ptr [rcx+tchar_t] )

                lea rax,[rcx+tchar_t]
            .endif
        .endif
        add rcx,tchar_t
        movzx edx,tchar_t ptr [rcx]
    .endf
    ret

_tcsfn endp

