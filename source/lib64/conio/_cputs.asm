; _CPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_cputs proc frame string:string_t

  local num_written:ulong_t
    ;
    ; write string to console file handle
    ;
    .if WriteConsoleA(_confh, string, strlen(rcx), &num_written, NULL)

        mov rax,-1
    .endif
    ret

_cputs  ENDP

    END
