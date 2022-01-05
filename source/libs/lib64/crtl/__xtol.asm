; __XTOL.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; long __xtol(const char *);
;
; Change history:
; 2009-11-03 - created
;

include crtl.inc

    .code

__xtol proc string:string_t

    xor eax,eax
    xor edx,edx

    .while 1

        mov dl,[rcx]
        inc rcx
        and dl,0xDF

        .break .if dl < 0x10
        .break .if dl > 'F'

        .if dl > 0x19

            .break .if dl < 'A'
            sub dl,'A' - 0x1A
        .endif

        sub dl,0x10
        shl eax,4
        add eax,edx

    .endw
    ret

__xtol endp

    end
