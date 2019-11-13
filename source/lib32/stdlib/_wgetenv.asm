; _WGETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

_wgetenv proc uses esi edi enval:LPWSTR

    .return .if !wcslen(enval)

    mov edi,eax
    mov esi,_wenviron
    lodsd

    .while eax

        .if !_wcsnicmp(eax, enval, edi)

            mov eax,[esi-4]
            lea eax,[edi*2+eax]

            .return( &[eax+2] ) .if word ptr [eax] == '='
        .endif
        lodsd
    .endw
    ret

_wgetenv endp

    END
