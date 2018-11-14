; _SARND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _sarnd() - Shift Arithmetic Right
;
; Shifts the destination right by "count" bits with
; the current sign bit replicated in the leftmost bit.
;
include intn.inc

option win64:rsp nosave noauto

.code

_sarnd proc o:ptr, i:dword, n:dword

    .if r8d > 1
        .while edx >= 64
            mov r10,[rcx+r8*8-8]
            .for r9d=0: r9d < r8d: r9d++
                mov rax,[rcx+r9*8+8]
                mov [rcx+r9*8],rax
            .endf
            sar r10,63
            mov [rcx+r8*8-8],r10
            sub edx,64
            dec r8d
        .endw
    .endif

    .if edx
        mov r11d,r8d
        .repeat
            xor r9d,r9d
            mov r10,[rcx+r8*8-8]
            .repeat
                mov eax,[rcx+r8*8-8]
                shr r9d,1
                rcr eax,1
                sbb r9d,r9d
                mov [rcx+r8*8-8],eax
                dec r8d
            .untilz
            mov r8d,r11d
            sar r10,1
            mov [rcx+r8*8-8],r10
            dec edx
        .untilz
    .endif
    ret

_sarnd endp

    end
