; _TCSDOS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strdos(char *);
; wchar_t *_wstrdos(wchar_t *);
;
; Converts a UNIX path to DOS ('/' --> '\')
;
include string.inc
include tchar.inc

.code

_tcsdos proc string:LPTSTR

    ldr rax,string

    .for ( : TCHAR ptr [rax] : rax+=TCHAR )

        .if ( TCHAR ptr [rax] == '/' )

            mov TCHAR ptr [rax],'\'
        .endif
    .endf
    ldr rax,string
    ret

_tcsdos endp

    end
