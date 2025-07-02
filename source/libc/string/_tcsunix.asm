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

_tcsunix proc string:tstring_t

    ldr rax,string

    .for ( : tchar_t ptr [rax] : rax+=tchar_t )

        .if ( tchar_t ptr [rax] == '\' )

            mov tchar_t ptr [rax],'/'
        .endif
    .endf
    ldr rax,string
    ret

_tcsunix endp

    end
