; _TCSUNIX.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strunix(char *);
; wchar_t *_wstrunix(wchar_t *);
;
; Converts a DOS path to UNIX ('\' --> '/')
;
include string.inc
include tchar.inc

.code

_tcsunix proc string:LPTSTR

    ldr rax,string

    .for ( : TCHAR ptr [rax] : rax+=TCHAR )

        .if ( TCHAR ptr [rax] == '\' )

            mov TCHAR ptr [rax],'/'
        .endif
    .endf
    ldr rax,string
    ret

_tcsunix endp

    end
