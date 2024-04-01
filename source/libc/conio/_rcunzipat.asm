; _RCUNZIPAT.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc

.code

_rcunzipat proc uses rsi rdi rbx rc:TRECT, pc:PCHAR_INFO

   .new count:int_t

    ldr ecx,rc
    shr ecx,16
    movzx eax,cl
    mul ch
    mov count,eax

    ldr rbx,pc
    lea rdi,at_foreground
    lea rsi,at_background

    .for ( ecx = 0 : ecx < count : ecx++ )

        mov     al,[rbx+rcx*4+2]
        mov     ah,al
        and     eax,0x0FF0
        shr     al,4
        movzx   edx,al
        mov     al,[rsi+rdx]
        mov     dl,ah
        or      al,[rdi+rdx]
        mov     [rbx+rcx*4+2],al
    .endf
    ret

_rcunzipat endp

    end
