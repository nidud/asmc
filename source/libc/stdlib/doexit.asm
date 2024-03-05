; DOEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
ifdef __UNIX__
include sys/syscall.inc
externdef __fini_array_start:ptr
externdef __fini_array_end:ptr
else
include winbase.inc
externdef __xt_a:ptr
externdef __xt_z:ptr
endif
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
ifdef __UNIX__
        _initterm(&__fini_array_start, &__fini_array_end)
else
        _initterm(&__xt_a, &__xt_z)
endif
    .endif

    .if ( !retcaller )

        mov _C_Exit_Done,TRUE
ifdef __UNIX__
        sys_exit(code)
else
        ExitProcess(code)
endif
    .endif
    ret

doexit endp

    end
