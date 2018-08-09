include stdio.inc

    .code

.classdef XPush :UINT

    base    QWORD ?
    buffer  OWORD 8 dup(?)

    .ends

    option win64:rsp nosave noauto

    assume rcx:LPXPUSH

XPush::Release proc

    movaps  xmm0,[rcx].buffer[0x00]
    movaps  xmm1,[rcx].buffer[0x10]
    movaps  xmm2,[rcx].buffer[0x20]
    movaps  xmm3,[rcx].buffer[0x30]
    movaps  xmm4,[rcx].buffer[0x40]
    movaps  xmm5,[rcx].buffer[0x50]
    movaps  xmm6,[rcx].buffer[0x60]
    movaps  xmm7,[rcx].buffer[0x70]
    mov     r11,[rsp]
    mov     rsp,[rcx].base
    jmp     r11

XPush::Release endp

XPush::XPush proc ReservedStack:UINT

    mov     r11,rcx             ; *this
    mov     r10,rsp
    lea     rax,[r10+rdx]       ; stack base
    lea     rcx,[rdx+8*16+16]   ; alloc size
    sub     rax,rcx
    test    [rax],al            ; probe..
    mov     rcx,[r10]           ; return addr
    mov     rsp,rax             ; new stack
    mov     [rax],rcx
    lea     rcx,[rax+rdx+8]     ; shadow space
    add     r10,8
    mov     [rcx].base,r10

    movaps  [rcx].buffer[0x00],xmm0
    movaps  [rcx].buffer[0x10],xmm1
    movaps  [rcx].buffer[0x20],xmm2
    movaps  [rcx].buffer[0x30],xmm3
    movaps  [rcx].buffer[0x40],xmm4
    movaps  [rcx].buffer[0x50],xmm5
    movaps  [rcx].buffer[0x60],xmm6
    movaps  [rcx].buffer[0x70],xmm7

    lea     rdx,[rax+0x80]
    mov     [rcx],rdx
    lea     rax,XPush_Release
    mov     [rdx],rax
    mov     rax,rcx
    .if r11

        mov [r11],rax
    .endif
    ret

XPush::XPush endp

    option win64:rbp auto

main proc

  local p:LPXPUSH

    printf("RSP: %p\n", rsp)
    XPush::XPush( &p, @ReservedStack )
    printf("RSP: %p - 0x90 byte\n", rsp)
    p.Release()
    printf("RSP: %p + 0x90 byte\n", rsp)
    ret

main endp

    end main

