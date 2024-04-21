; RSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

.code

rsopen proc uses rsi rdi rbx idd:PIDD

   .new     dlg:PDOBJ
   .new     flags:int_t
   .new     rc:TRECT

    ldr     rsi,idd
    mov     rc,[rsi].RIDD.rc
    movzx   eax,[rsi].RIDD.rc.col
    mul     [rsi].RIDD.rc.row
    shl     eax,2
    mov     edi,eax

    .if ( [rsi].RIDD.flag & W_SHADE )

        movzx   eax,[rsi].RIDD.rc.col
        movzx   edx,[rsi].RIDD.rc.row
        lea     eax,[rax+rdx*2-2]
        shl     eax,2
        add     edi,eax
    .endif

    .if !( [rsi].RIDD.flag & W_UTF16 )

        mov     eax,edi
        shr     eax,1
        sub     [rsi].RIDD.size,ax
        add     [rsi].RIDD.size,di
    .endif

    movzx   eax,[rsi].RIDD.size
    mov     dlg,malloc(eax)
    mov     ebx,edi
    mov     rdi,rax
    mov     rdx,rax
    movzx   ecx,[rsi].RIDD.size

    .if ( rax == NULL )

        .return
    .endif

    xor     eax,eax
    rep     stosb
    mov     rcx,rdx
    mov     rdi,rdx
    lodsw                   ; skip size

    ; -- copy dialog

    lodsw                   ; .flag
    or      eax,W_RCNEW or W_MYBUF or W_ISOPEN
    mov     flags,eax
    stosw                   ; .flag
    movsw                   ; .count + .index
    movsd                   ; .rect
    movzx   eax,byte ptr [rsi-6]
    inc     eax
    imul    eax,eax,TOBJ    ; * size of objects
    add     rax,rcx         ; + adress
    mov     [rdi],rax
    add     rdi,size_t
    xchg    rdx,rax
    add     rax,TOBJ        ; + dialog
    mov     [rdi],rax
    add     rdi,size_t

    ; -- copy objects

    add     rdx,rbx         ; end of wp = start of object alloc
    movzx   ebx,byte ptr [rsi-6]

    .while ebx

        movsd               ; copy 8 byte
        movsd               ; get alloc size of object
        movzx   eax,byte ptr [rsi-6]
        shl     eax,4

        .if eax

            xchg    rax,rdx ; offset of mem (.data)
            mov     [rdi],rax
            add     rdi,size_t
            add     rdx,rax
            xor     eax,eax
        .else
            mov     [rdi],rax
            add     rdi,size_t
        .endif
        add rdi,size_t
        dec ebx
    .endw
    mov rbx,rdi
    _rcunzip(rc, rdi, rsi, flags)
    mov rax,dlg
    ret

rsopen endp

    end
