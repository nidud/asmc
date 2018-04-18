include stdio.inc

    .code

.classdef XPush :UINT

    base    QWORD ?
    buffer  OWORD 8 dup(?)

    .ends

    assume rcx:LPXPUSH

    option win64:rsp nosave noauto

XPush::Release proc

    movaps xmm0,[rcx].buffer[0x00]
    movaps xmm1,[rcx].buffer[0x10]
    movaps xmm2,[rcx].buffer[0x20]
    movaps xmm3,[rcx].buffer[0x30]
    movaps xmm4,[rcx].buffer[0x40]
    movaps xmm5,[rcx].buffer[0x50]
    movaps xmm6,[rcx].buffer[0x60]
    movaps xmm7,[rcx].buffer[0x70]
    mov rax,[rsp]
    mov rsp,[rcx].base
    jmp rax

XPush::Release endp

XPush::XPush proc ReservedStack:UINT

    .repeat

        .if !rcx

            mov r8,rsp
            lea rax,[r8+rdx]        ; stack base
            lea rcx,[rdx+8*16+16]   ; alloc size
            sub rax,rcx
            and al,-16
            test [rax],al           ; probe..
            mov rcx,[r8]            ; return addr
            mov rsp,rax             ; new stack
            mov [rax],rcx
            and dl,-16              ; shadow space
            lea rcx,[rax+rdx+16]
            add r8,8
            mov [rcx].base,r8
        .endif

        movaps [rcx].buffer[0x00],xmm0
        movaps [rcx].buffer[0x10],xmm1
        movaps [rcx].buffer[0x20],xmm2
        movaps [rcx].buffer[0x30],xmm3
        movaps [rcx].buffer[0x40],xmm4
        movaps [rcx].buffer[0x50],xmm5
        movaps [rcx].buffer[0x60],xmm6
        movaps [rcx].buffer[0x70],xmm7

        lea rdx,[rax+0x80]
        mov [rcx],rdx
        lea rax,XPush@Release
        mov [rdx],rax
        mov rax,rcx
    .until 1
    ret

XPush::XPush endp

    option win64:rbp auto

main proc

  local p:LPXPUSH

    printf("RSP: %p\n", rsp)
    mov p,XPush::XPush( NULL, @ReservedStack )
    printf("RSP: %p\n", rsp)
    p.Release()
    printf("RSP: %p\n", rsp)
    ret

main endp

    end main

