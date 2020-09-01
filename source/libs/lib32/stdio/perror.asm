; PERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include io.inc
include errno.inc
include string.inc

    .code

perror proc uses edi string:LPSTR

    mov eax,string
    .if eax

        mov edi,eax
        movzx eax,byte ptr [edi]
        .if eax

            _write(2, edi, strlen(edi))
            _write(2, ": ", 2)
            mov eax,errno
            mov edi,_sys_errlist[eax*4]
            _write(2, edi, strlen(edi))
            _write(2, "\n", 1)
        .endif
    .endif
    ret

perror endp

    END
