; _TCSDOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strdos(char *);
; wchar_t *_wstrdos(wchar_t *);
;
; Converts a UNIX path to DOS ('/' --> BSLASH)
;
include string.inc
include tchar.inc

.code

_tcsdos proc string:tstring_t

    ldr rax,string

    .for ( : tchar_t ptr [rax] : rax+=tchar_t )

        .if ( tchar_t ptr [rax] == '/' )

            mov tchar_t ptr [rax],BSLASH
        .endif
    .endf
    ldr rax,string
    ret

_tcsdos endp

    end
