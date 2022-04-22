; DOEXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include internal.inc
include linux/kernel.inc

_initterm proto __cdecl :ptr _PVFV, :ptr _PIFV

;;
;; pointers to initialization sections
;;
externdef __xi_a:_PIFV
externdef __xi_z:_PIFV
externdef __xt_a:_PVFV
externdef __xt_z:_PVFV

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
        push rsi
        push rdx

        _initterm(&__xt_a, &__xt_z)

        pop rdx
        pop rsi
endif
    .endif

    ; return to OS or to caller

    .return .if ( retcaller )

    mov _C_Exit_Done,TRUE
    sys_exit(edi)
    ret

doexit endp

    end
