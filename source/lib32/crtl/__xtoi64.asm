; __XTOI64.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; long __xtoi64(const char *);
;
; Change history:
; 2017-10-18 - created
;
include crtl.inc

    .code

__xtoi64 proc uses ebx string:LPSTR

    mov ebx,string
    xor eax,eax
    xor ecx,ecx
    xor edx,edx

    .while 1

        mov cl,[ebx]
        add ebx,1
        and cl,0xDF

        .break .if cl < 0x10
        .break .if cl > 'F'

        .if cl > 0x19

            .break .if cl < 'A'
            sub cl,'A' - 0x1A
        .endif
        sub cl,0x10
        shld edx,eax,4
        shl eax,4
        add eax,ecx
        adc edx,0
    .endw
    ret

__xtoi64 endp

    end
