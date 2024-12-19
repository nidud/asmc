; _CRC32.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc

    .data?
     crctable dd 256 dup(?)

    .code

_crc32 proc uses rsi rdi crc:uint_t, p:ptr, len:uint_t

    ldr eax,crc
    ldr ecx,len
    ldr rsi,p

    .for ( rdi = &crctable, edx = 0 : ecx : ecx--, rsi++ )

        mov dl,al
        xor dl,[rsi]
        shr eax,8
        xor eax,[rdi+rdx*4]
    .endf
    ret

_crc32 endp


__initcrc proc uses rbx

    .for ( ecx = 0 : ecx < 256 : ecx++ )

        .for ( edx = 0, eax = ecx : edx < 8 : edx++ )

            mov     ebx,eax
            and     ebx,1
            imul    ebx,ebx,0xEDB88320
            shr     eax,1
            xor     eax,ebx
        .endf
        lea rdx,crctable
        mov [rdx+rcx*4],eax
    .endf
    ret

__initcrc endp

.pragma init(__initcrc, 50)

    end
