; DOEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include winbase.inc

_initterm proto __cdecl :ptr, :ptr

externdef __xt_a:ptr
externdef __xt_z:ptr
externdef _exitflag:char_t

    .data
     _C_Termination_Done int_t FALSE
     _C_Exit_Done        int_t FALSE

    .code

doexit proc code:int_t, quick:int_t, retcaller:int_t

    .if ( _C_Exit_Done != TRUE )

        mov _C_Termination_Done,TRUE

        ldr eax,retcaller
        mov _exitflag,al

        _initterm( &__xt_a, &__xt_z )
    .endif

    .if ( !retcaller )

        mov _C_Exit_Done,TRUE
        ExitProcess(code)
    .endif
    ret

doexit endp

    end
