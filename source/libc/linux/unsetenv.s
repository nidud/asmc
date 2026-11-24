; UNSETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include processenv.inc
include errhandlingapi.inc

.code

 unsetenv proc name:string_t
    .ifd SetEnvironmentVariableA(ldr(name), NULL)
        .return( 0 )
    .endif
    .return( _dosmaperr(GetLastError()) )
    endp

    end
