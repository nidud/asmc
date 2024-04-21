; _TWCSTRCPY.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include string.inc
include tchar.inc

    .code

wcstrcpy proc uses rsi rdi rbx cp:LPTSTR, wc:PCHAR_INFO, count:int_t

    ldr rdi,cp
    ldr rsi,wc
    ldr ecx,count

    mov bl,[rsi+2]
    and bl,0x0F

    .repeat

        .break .if !ecx
         dec ecx
         lodsd
        .continue( 0 ) .if ax <= ' '
        .continue( 0 ) .if ax > 176
         sub rsi,4
        .break .if !ecx
        .repeat

            lodsd
            .break( 1 ) .if ax > 176

            mov dl,[rsi-4+2]
            and dl,0x0F
            .if dl != bl

                mov dx,ax
                mov ax,'&'
                _tstosb
                mov ax,dx
            .endif
            _tstosb
        .untilcxz
    .until 1
    mov TCHAR ptr [rdi],0
    _tstrtrim(cp)
    ret

wcstrcpy endp

    end
