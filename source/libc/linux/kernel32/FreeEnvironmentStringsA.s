; FREEENVIRONMENTSTRINGSA.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include processenv.inc

.code

 FreeEnvironmentStringsA proc WINAPI penv:LPSTR
    ldr rcx,penv
    .if ( rcx )
        free(rcx)
    .endif
    .return( 1 )
    endp

    end
