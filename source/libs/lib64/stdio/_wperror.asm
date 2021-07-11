; PERROR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include stdio.inc
include string.inc
include syserr.inc
include io.inc

    .code

_wperror proc message:wstring_t

  local buffer[512]:char_t

    .if rcx

        xor r8d,r8d
        movzx eax,word ptr [rcx]
        .while eax && r8d < 512
            mov buffer[r8],al
            add rcx,2
            add r8d,1
            mov al,[rcx]
        .endw
        .if eax
            dec r8d
            xor eax,eax
        .endif
        mov buffer[r8],al
        perror(&buffer)
    .endif
    ret

_wperror endp

    end
