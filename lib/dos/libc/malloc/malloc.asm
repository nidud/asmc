; MALLOC.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.

include malloc.inc
include errno.inc
include dos.inc

mb      struct
size    dw ?
used    dw ?
mb      ends

.code

getmaxblock proc private uses si di bx

    xor     cx,cx           ; max size of block
    mov     ax,_heapbase    ; segment of block
    mov     dx,ax
    mov     bx,cx
    mov     si,ax           ; segment of last block
.0:
    mov     es,ax
    mov     di,es:[bx].mb.size
    test    di,di
    jz      .3
    mov     si,ax
    cmp     es:[bx].mb.used,bx
    jne     .2
    add     ax,di
    mov     es,ax
    cmp     es:[bx].mb.used,bx
    jne     .1
    mov     ax,es:[bx].mb.size
    test    ax,ax
    jz      .1
    add     di,ax
    mov     ax,si
    mov     es,ax
    mov     es:[bx].mb.size,di
    jmp     .0
.1:
    mov     ax,si
    cmp     di,cx
    jb      .2
    mov     cx,di
    mov     dx,ax
.2:
    add     ax,di
    jmp     .0
.3:
    mov     ax,si           ; last block
    test    cx,cx
    jz      .4
    mov     _heapfree,dx
.4:
    ret

getmaxblock endp


free proc uses bx maddr:ptr

if @DataSize
    mov ax,word ptr maddr+2
else
    mov bx,word ptr maddr
    mov ax,ss:[bx-2]
endif
    mov cx,_brklvl

    .if ( ax >= _heapbase && ax < cx )

        mov es,ax
        xor bx,bx
        add ax,es:[bx].mb.size
        mov es:[bx].mb.used,bx

        .if ( ax == cx )

            getmaxblock()
            mov es,ax
            mov es:[bx].mb.size,bx
            mov es:[bx].mb.used,1
            mov _brklvl,ax
            inc ax
            mov bx,ax
            mov ax,_psp
            sub bx,ax
            mov es,ax
            mov ah,0x4A
            int 0x21
        .else
            mov ax,es
            mov _heapfree,ax
        .endif
if (@DataSize eq 0)
        mov ax,ds
        mov es,ax
endif
    .else
        xor ax,ax
    .endif
    ret

free endp


malloc proc uses bx msize:size_t

    mov ax,msize
    add ax,4
    .ifc
        mov ax,0x1001
    .else
        mov dl,al
        shr ax,4
        .if dl & 15
            inc ax
        .endif
    .endif

    test    ax,ax
    jz      .6

    mov     cx,ax
    mov     ax,_heapfree
    test    ax,ax
    jz      .3

    mov     es,ax
    mov     dx,ax
    xor     bx,bx
    cmp     es:[bx].mb.used,bx
    mov     ax,es:[bx].mb.size
    je      .1
.0:
    push    cx
    call    getmaxblock
    mov     ax,cx
    pop     cx
    jz      .4
    cmp     ax,cx
    jb      .4
    mov     es,dx
.1:
    cmp     ax,cx
    jb      .0
    mov     es:[bx].mb.used,1
    je      .2
    mov     es:[bx].mb.size,cx
    sub     ax,cx
    add     cx,dx
    mov     es,cx
    mov     es:[bx].mb.size,ax
    mov     es:[bx].mb.used,bx
    mov     es,dx
.2:
    mov     ax,es:[bx].mb.size
    add     ax,dx
    mov     _heapfree,ax
    jmp     .5
.3:
    mov     ax,_heapbase ; create heap
    inc     ax
    cmp     ax,_heaptop
    ja      .6
    mov     bx,ax
    mov     ax,_psp
    sub     bx,ax
    mov     es,ax
    mov     ah,0x4A
    int     0x21
    jc      .6
    mov     ax,_heapbase
    mov     _brklvl,ax
    mov     _heapfree,ax
    mov     es,ax
    mov     ax,1
    xor     bx,bx
    mov     es:[bx].mb.size,bx
    mov     es:[bx].mb.used,ax
.4:
    mov     ax,_brklvl  ; extend heap
    inc     ax
    add     ax,cx
    cmp     ax,_heaptop
    ja      .6
    mov     bx,ax
    mov     ax,_psp
    sub     bx,ax
    mov     es,ax
    mov     ah,0x4A
    int     0x21
    jc      .6
    mov     ax,_brklvl
    mov     es,ax
    xor     bx,bx
    mov     es:[bx].mb.size,cx
    mov     dx,ax
    add     ax,cx
    mov     _brklvl,ax
    mov     es,ax
    mov     ax,1
    mov     es:[bx].mb.size,bx
    mov     es:[bx].mb.used,ax
.5:
if @DataSize
    mov     ax,4    ; seg:[4]
else
    mov     es,dx   ; ds:[offset]
    mov     es:[bx].mb.used,dx
    mov     ax,ds
    mov     es,ax
    xchg    ax,dx
    sub     ax,dx
    test    ah,0xF0
    jnz     .6
    shl     ax,4
    add     ax,4
endif
    jmp     .7
.6:
    mov     errno,ENOMEM
    xor     ax,ax
    cwd
.7:
    ret

malloc endp

    end
