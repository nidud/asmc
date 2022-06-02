; DOEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc
include linux/kernel.inc

_initterm proto __cdecl :ptr _PVFV, :ptr _PIFV

;;
;; pointers to initialization sections
;;
externdef __fini_array_start:ptr
externdef __fini_array_end:ptr
externdef _exitflag:byte

    .data
;;
;; flag indicating if C runtime termination has been done. set if exit,
;; _exit, _cexit or _c_exit has been called. checked when _CRTDLL_INIT
;; is called with DLL_PROCESS_DETACH.
;;
_C_Termination_Done int_t FALSE
_C_Exit_Done        int_t FALSE

    .code

doexit proc code:int_t, quick:int_t, retcaller:int_t

    .if ( _C_Exit_Done != TRUE )

        mov _C_Termination_Done,TRUE

        ; save callable exit flag (for use by terminators)
        mov _exitflag,dl ; 0 = term, !0 = callable exit
ifndef CRTDLL
        ;
        ; do terminators
        ;
        push rdi
        push rdx

        _initterm(&__fini_array_start, &__fini_array_end)

        pop rdx
        pop rdi
endif
    .endif

    ; return to OS or to caller

    .return .if ( retcaller )

    mov _C_Exit_Done,TRUE
    sys_exit(edi)
    ret

doexit endp

    end
