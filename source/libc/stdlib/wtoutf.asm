; _WTOUTF.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Convert Wide char to UTF-8
;
; Input:  wc = 16-bit wchar_t (upper 16 bits 0), OR
;              32-bit packed (LowSurrogate << 16) | HighSurrogate
; Output: eax = little-endian UTF-8 bytes (1..4 bytes)
;         ecx = UTF-8 byte count (1..4)
;         edx = UTF-16 input bytes consumed (2 for single wchar_t, 4 for surrogate pair)
;

include stdlib.inc

.code

_wtoutf proc uses rsi rdi rbx wc:int_t

    ldr eax,wc
    mov edx,eax
    movzx eax,ax
    .if ( eax < 0x80 )
        mov ecx,1
        mov edx,2
       .return
    .endif
    mov esi,2
    ;
    ; Check for UTF-16 high surrogate (0xD800..0xDBFF)
    ;
    .if ( eax >= 0xD800 && eax <= 0xDBFF )
        shr edx,16
        .if ( edx >= 0xDC00 && edx <= 0xDFFF )
            sub eax,0xD800
            shl eax,10
            sub edx,0xDC00
            add eax,edx
            add eax,0x10000 ; Full Unicode code point (0x10000..0x10FFFF)
            mov esi,4
        .endif
    .endif
    mov ebx,eax
    xor edi,edi
    xor eax,eax
    mov edx,63
    mov ecx,128
    .while ( ebx > edx )
        mov al,bl
        and al,0x3F
        or  al,0x80
        shl eax,8
        shr ebx,6
        inc edi
        lea ecx,[rcx+rdx+1]
        shr edx,1
    .endw
    mov al,cl
    or  al,bl
    lea ecx,[rdi+1]
    mov edx,esi
    ret
    endp

    end
