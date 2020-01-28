; TWINOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include malloc.inc
include twindow.inc

    .data
    AttributesTransparent label byte
        db 0x07,0x07,0x0F,0x07,0x08,0x07,0x07,0x07,0x08,0x0F,0x0A,0x0B,0x0F,0x0B,0x0B,0x0B
        db 0x00,0x00,0x00,0x10,0x30,0x10,0x10,0x00,0x10,0x10,0x00,0x00,0x00,0x00,0x07,0x07

    .code

    assume rcx:window_t
    assume rbx:window_t

TWindow::Open proc uses rsi rdi rbx rcx rc:TRect, flags:uint_t

    mov rbx,rcx
    mov edi,edx
    mov esi,r8d

    .return .if !malloc(TWindow)

    mov r8d,edi
    mov rdx,rax
    mov rdi,rax
    mov ecx,TWindow/8
    xor eax,eax
    rep stosq

    mov rcx,rdx
    mov [rcx].lpVtbl,[rbx].lpVtbl
    mov [rcx].Class,[rbx].Class
    mov [rcx].Color,[rbx].Color
    mov [rcx].rc,r8d
    mov [rcx].Flags,esi
    mov [rcx].Prev,rbx

    .if ( [rcx].Flags & W_TRANSPARENT )

        lea rax,AttributesTransparent
        mov [rcx].Color,rax
    .endif

    .return rcx .if ( [rcx].Flags & W_CHILD )

    mov     rbx,rcx
    movzx   eax,[rcx].rc.col
    movzx   edx,[rcx].rc.row
    mov     r8d,eax
    mul     dl
    lea     rax,[rax*4]

    .if [rcx].Flags & W_SHADE

        lea rdx,[r8+rdx*2-2]
        lea rax,[rax+rdx*4]
    .endif

    .if malloc(eax)

        mov [rbx].Window,rax
        or  [rbx].Flags,W_ISOPEN

        .if ( [rbx].Flags & W_TRANSPARENT )

            [rbx].Read(&[rbx].rc, rax)
            [rbx].Clear(0x00080000)
        .endif
        mov rax,rbx
    .else
        free(rbx)
    .endif
    ret

TWindow::Open endp

    end
