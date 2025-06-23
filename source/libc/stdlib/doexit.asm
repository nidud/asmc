; DOEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
ifdef __UNIX__
include sys/syscall.inc
else
include winbase.inc
endif

externdef _CRTFINI_S:ptr
externdef _CRTFINI_E:ptr
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
        _initterm(&_CRTFINI_S, &_CRTFINI_E)
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
