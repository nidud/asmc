; _RSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc
include malloc.inc

    .code

    assume rbx:PTRES
    assume r12:THWND
    assume r13:THWND

_rsopen proc uses rbx r12 r13 r14 rs:PTRES

   .new hwnd:THWND
   .new rsize:int_t
   .new dsize:int_t
   .new xsize:int_t
   .new count:int_t

    mov     rbx,rdi
    xor     edx,edx
    test    [rbx].flags,W_SHADE
    setnz   dl
    mov     rsize,_rcmemsize([rbx].rc, edx)
    movzx   eax,[rbx].count
    inc     eax
    imul    eax,eax,TCLASS
    mov     dsize,eax
    xor     eax,eax

    .for ( r12=&[rbx+TOBJ], ecx = 0 : cl < [rbx].count : ecx++, r12+=TOBJ )

        movzx edx,[r12].count
        shl edx,4
        .if ( [r12].type == T_EDIT )
            add edx,TEDIT
        .endif
        add eax,edx
    .endf

    mov     xsize,eax
    mov     r13d,eax
    add     r13d,rsize
    add     r13d,dsize
    mov     hwnd,malloc(r13d)

    .return .if !( rax )

    mov     ecx,r13d
    mov     rdi,rax
    mov     r13,rax
    xor     eax,eax
    rep     stosb

    mov     eax,dsize
    add     eax,rsize
    add     rax,r13
    cmp     xsize,ecx
    cmovz   rax,rcx
    mov     [r13].buffer,rax

    mov     eax,dsize
    add     rax,r13
    mov     [r13].window,rax
    lea     rax,[r13+TCLASS]
    cmp     [rbx].count,cl
    cmovz   rax,rcx
    mov     [r13].object,rax

    mov     rdi,r13
    mov     rsi,rbx
    mov     ecx,TOBJ
    rep     movsb
    or      [r13].flags,W_ISOPEN

    _getcursor(&[r13].cursor)

    mov     rdx,[r13].window
    movzx   eax,[rbx].count
    mov     count,eax

    .for ( r12=[r13].object, ecx = 0 : ecx < count : ecx++, r12+=TCLASS )

        mov [r12].prev,r13
        mov [r12].window,rdx

        lea eax,[rcx+1]
        .if ( eax < count )

            lea rax,[r12+TCLASS]
            mov [r12].next,rax
        .endif
    .endf

    mov r13,[r13].object
    lea r12,[rbx+TOBJ]
    .for ( : count : count--, r13+=TCLASS )

        .if ( [r12].flags & W_WNDPROC )
            mov [r13].winproc,&_defwinproc
        .endif

        mov rsi,r12
        mov rdi,r13
        mov ecx,TOBJ
        rep movsb
        mov r12,rsi

        mov [r13].window,_rcbprc([rbx].rc, [r13].rc, [r13].window)
    .endf

    mov r13,hwnd
    _rcunzip([rbx].rc, [r13].window, r12)
   .return( _conslink(r13) )

_rsopen endp

    end
