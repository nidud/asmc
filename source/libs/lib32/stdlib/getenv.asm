; GETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include string.inc

    .code

getenv proc uses esi edi enval:LPSTR

    .return .if !strlen(enval)

    mov edi,eax
    mov esi,_environ
    lodsd

    .while eax

        .if !_strnicmp(eax, enval, edi)

            mov eax,[esi-4]
            add eax,edi

            .return( &[eax+1] ) .if byte ptr [eax] == '='
        .endif
        lodsd
    .endw
    ret

getenv endp

    END
