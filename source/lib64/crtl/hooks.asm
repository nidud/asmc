; HOOKS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stddef.inc
include stdlib.inc
include excpt.inc

include windows.inc
include mtdll.inc
include eh.inc
include ehhooks.inc
include ehassert.inc
include internal.inc

.data

__pInconsistency _inconsistency_function 0 ;; not a valid state

.code

_initp_eh_hooks proc frame enull:ptr_t

    mov __pInconsistency,EncodePointer(&terminate)
    ret

_initp_eh_hooks endp

__except:; (EXCEPTION_EXECUTE_HANDLER) {
    ;;
    ;; Intercept ANY exception from the terminate handler
    ;;
    ;; Deliberately do nothing
    ;; }
    ret

terminate proc frame:__except

  local pTerminate:terminate_function

    mov rax,__pTerminate
    mov pTerminate,rax

    .if ( rax )
        ;;
        ;; Note: If the user's terminate handler crashes, we cannot allow an EH to propagate
        ;; as we may be in the middle of exception processing, so we abort instead.
        ;;

            ;;
            ;; Let the user wrap things up their way.
            ;;
            pTerminate()

    .endif

    ;;
    ;; If the terminate handler returned, faulted, or otherwise failed to
    ;; halt the process/thread, we'll do it.
    ;;
    abort()
    ret

terminate endp

unexpected proc

    mov rax,__pUnexpected

    .if ( rax != NULL )

        ;;
        ;; Let the user wrap things up their way.
        ;;
        rax();
    .endif

    ;;
    ;; If the unexpected handler returned, we'll give the terminate handler a chance.
    ;;
    terminate()
    ret

unexpected endp

_inconsistency proc frame:__except

    ;;
    ;; Let the user wrap things up their way.
    ;;

    .if DecodePointer(__pInconsistency)
        ;;
        ;; Note: If the user's terminate handler crashes, we cannot allow an EH to propagate
        ;; as we may be in the middle of exception processing, so we abort instead.
        ;;
        rax();
    .endif

    ;;
    ;; If the inconsistency handler returned, faulted, or otherwise
    ;; failed to halt the process/thread, we'll do it.
    ;;
    terminate()
    ret

_inconsistency endp

    end
