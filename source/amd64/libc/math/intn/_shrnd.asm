; _shrnd() - Shift Right
;
; Shifts the destination right by "count" bits with zeroes shifted
; in on the left.
;
include intn.inc

option win64:rsp nosave noauto

.code

_shrnd proc o:ptr, i:dword, n:dword

    .if r8d > 1
        .while edx >= 64
            .for r9d=0: r9d < r8d: r9d++
                mov rax,[rcx+r9*8+8]
                mov [rcx+r9*8],rax
            .endf
            mov qword ptr [rcx+r8*8-8],0
            sub edx,64
            dec r8d
        .endw
    .endif
    .if edx
        mov r10d,r8d
        .repeat
            mov r8d,r10d
            xor r9d,r9d
            .repeat
                mov rax,[rcx+r8*8-8]
                shr r9d,1
                rcr rax,1
                sbb r9d,r9d
                mov [rcx+r8*8-8],rax
                dec r8d
            .untilz
            dec edx
        .untilz
    .endif
    ret

_shrnd endp

    end
