; _EXIT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdlib.inc

; worker routine prototype
doexit proto :int_t, :int_t, :int_t

    .code

_exit proc retval:int_t

    ldr ecx,retval
    doexit( ecx, 1, 0 ) ; quick term, kill process

ifdef _CRT_APP
    ;
    ; The use of __fastfail here is a temporary workaround to ensure that
    ; _exit() does not return. We cannot exit properly because there is no
    ; operating system API available to end execution. The __fastfail will
    ; raise a second-chance exception, causing the process to end execution,
    ; and invoking WER.
    ;
    __fastfail(FAST_FAIL_FATAL_APP_EXIT)
endif
_exit endp

    end
