; _TCSEXT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; char *strext(char *);
; wchar_t *_wstrext(wchar_t *);
;
include string.inc
include tchar.inc

    .code

_tcsext proc uses rbx string:tstring_t

    mov rbx,_tcsfn( ldr(string) )

    .if _tcsrchr( rbx, '.' )

        .if ( rax == rbx )

            xor eax,eax
        .endif
    .endif
    ret

_tcsext endp

    end
