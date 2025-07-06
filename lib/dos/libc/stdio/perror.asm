; PERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include string.inc
include syserr.inc
include io.inc

    .code

perror proc uses bx message:string_t

    lesl bx,message

    .if ( bx )

        .if ( byte ptr esl[bx] )

            _write( 2, message, strlen( message ) )
            _write( 2, ": ", 2 )
        .endif
        mov message,_get_sys_err_msg( errno )
        _write( 2, message, strlen( message ) )
        _write( 2, "\n", 1 )
    .endif
    ret

perror endp

    end
