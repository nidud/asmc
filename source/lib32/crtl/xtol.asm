; XTOL.ASM--
;
; long xtol(const char *);
;
; Change history:
; 2009-11-03 - created
;
include stdlib.inc

    .code

xtol proc string:LPSTR

    mov edx,string
    xor eax,eax
    xor ecx,ecx

    .while 1

        mov cl,[edx]
        add edx,1
        and cl,0xDF

        .break .if cl < 0x10
        .break .if cl > 'F'

        .if cl > 0x19

            .break .if cl < 'A'
            sub cl,'A' - 0x1A
        .endif
        sub cl,0x10
        shl eax,4
        add eax,ecx
    .endw
    ret

xtol endp

    end
