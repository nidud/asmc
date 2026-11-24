; SETENV.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include processenv.inc
include errhandlingapi.inc

.code

 setenv proc name:string_t, value:string_t, overwrite:int_t
    .if ( ldr(overwrite) == 0 )
        .if getenv( ldr(name) )
            .return( 0 )
        .endif
    .endif
    .ifd SetEnvironmentVariableA( name, value )
        .return( 0 )
    .endif
    .return( _dosmaperr(GetLastError()) )
    endp

    end
