; _SHLND.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; _shlnd() - Shift Left
;
; Shifts the destination left by "count" bits with zeroes shifted
; in on right.
;
include intn.inc

option win64:rsp nosave noauto

.code

_shlnd proc o:ptr, i:dword, n:dword

    .if r8d > 1
        .while edx >= 64
            .for r9d=r8d: r9d: r9d--
                mov rax,[rcx+r9*8-16]
                mov [rcx+r9*8-8],rax
            .endf
            xor rax,rax
            mov [rcx],rax
            sub edx,64
        .endw
    .endif

    .if edx
        mov r10d,r8d
        .repeat
            xor r8d,r8d
            xor r9d,r9d
            .repeat
                mov rax,[rcx+r8*8]
                shr r9d,1
                rcl rax,1
                mov [rcx+r8*8],rax
                sbb r9d,r9d
                add r8d,1
            .until r8d == r10d
            dec edx
        .untilz
    .endif
    ret

_shlnd endp

    end
