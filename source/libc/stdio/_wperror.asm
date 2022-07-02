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

ifndef _WIN64
    mov ecx,message
endif
    .if ( rcx )

        xor edx,edx
        movzx eax,wchar_t ptr [rcx]

        .while ( eax && edx < 512 )

            mov buffer[rdx],al
            add rcx,2
            add edx,1
            mov al,[rcx]
        .endw
        .if eax
            dec edx
            xor eax,eax
        .endif
        mov buffer[rdx],al
        perror(&buffer)
    .endif
    ret

_wperror endp

    end
