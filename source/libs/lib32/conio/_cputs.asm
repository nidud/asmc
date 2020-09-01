; _CPUTS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc

    .code

_cputs proc uses ebx string:LPSTR

  local num_written:ULONG
    ;
    ; write string to console file handle
    ;
    mov ebx,-1
    .if hStdOutput != ebx

        mov edx,strlen(string)
        .if !WriteConsole(hStdOutput, string, edx, &num_written, NULL)
            xor ebx,ebx
        .endif
    .endif
    mov eax,ebx
    ret

_cputs endp

    END
