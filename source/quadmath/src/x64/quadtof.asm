include quadmath.inc

DDFLT_MAX equ 0x7F7FFFFF
DDFLT_MIN equ 0x00800000

    .code

    option win64:rsp nosave noauto

quadtof proc d:ptr, q:ptr

    mov r9d,0xFFFFFF00  ; get mask of bits to keep
    mov eax,[rdx+10]    ; get top part
    mov r8w,[rdx+14]
    and r8d,Q_EXPMASK
    neg r8d
    rcr eax,1
    mov r8d,eax         ; duplicate it
    shl r8d,25          ; get rounding bit
    mov r8w,[rdx+14]    ; get exponent and sign
    .ifc                ; if have to round
        .ifz            ; - if half way between
            .if dword ptr [rdx+6] == 0
                shl r9d,1
            .endif
        .endif
        add eax,0x0100
        .ifc            ; - if exponent needs adjusting
            mov eax,0x80000000
            inc r8w
            ;
            ;  check for overflow
            ;
        .endif
    .endif
    and eax,r9d         ; mask off bottom bits
    mov r9d,r8d         ; save exponent and sign
    and r8w,0x7FFF      ; if number not 0
    .ifnz
        .if r8w == 0x7FFF
            shl eax,1   ; infinity or NaN
            shr eax,8
            or  eax,0xFF000000
            shl r9w,1
            rcr eax,1
        .else
            add r8w,0x07F-0x3FFF
            .ifs
                ;
                ; underflow
                ;
                xor eax,eax
                mov qerrno,ERANGE
            .else
                .ifs r8w >= 0x00FF
                    ;
                    ; overflow
                    ;
                    mov eax,0x7F800000 shl 1
                    shl r9w,1
                    rcr eax,1
                    mov qerrno,ERANGE
                .else
                    shl eax,1
                    shrd eax,r8d,8
                    shl r9w,1
                    rcr eax,1
                    .ifs !r8w && eax < DDFLT_MIN
                        mov qerrno,ERANGE
                    .endif
                .endif
            .endif
        .endif
    .endif
    mov [rcx],eax
    .if rcx == rdx
        xor eax,eax
        mov [rcx+4],eax
        mov [rcx+8],rax
    .endif
    mov rax,rcx
    ret

quadtof endp

    end
