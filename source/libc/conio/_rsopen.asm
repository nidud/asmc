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
    assume rdi:PTRES
    assume rsi:THWND

_rsopen proc uses rsi rdi rbx rs:PTRES

   .new hwnd:THWND
   .new rsize:int_t
   .new dsize:int_t
   .new tsize:int_t
   .new xsize:int_t

    ldr     rbx,rs
    xor     edx,edx
    test    [rbx].flags,W_SHADE
    setnz   dl
    mov     rsize,_rcmemsize([rbx].rc, edx)
    movzx   eax,[rbx].count
    inc     eax
    imul    eax,eax,TCLASS
    mov     dsize,eax
    xor     eax,eax

    .for ( rdi = &[rbx+TOBJ], ecx = 0 : cl < [rbx].count : ecx++, rdi += TOBJ )

        movzx edx,[rdi].count
        shl edx,4
        .if ( [rdi].type == T_EDIT )
            add edx,TEDIT
        .endif
        add eax,edx
    .endf

    mov     xsize,eax
    add     eax,rsize
    add     eax,dsize
    mov     tsize,eax
    mov     hwnd,malloc(eax)

    .return .if !( rax )

    mov     ecx,tsize
    mov     rdi,rax
    mov     rsi,rax
    xor     eax,eax
    rep     stosb

    mov     eax,dsize
    add     eax,rsize
    add     rax,rsi
    cmp     xsize,ecx
    cmovz   rax,rcx
    mov     [rsi].buffer,rax

    mov     eax,dsize
    add     rax,rsi
    mov     [rsi].window,rax
    lea     rax,[rsi+TCLASS]
    cmp     [rbx].count,cl
    cmovz   rax,rcx
    mov     [rsi].object,rax

    mov     rdi,rsi
    xchg    rsi,rbx
    mov     ecx,TOBJ
    rep     movsb
    assume  rbx:THWND
    assume  rdi:THWND
    or      [rbx].flags,W_ISOPEN
    mov     rdi,[rbx].object

    .for ( edx = 0 : dl < [rbx].count : edx++, rdi+=TCLASS )

        mov     ecx,TOBJ
        rep     movsb
        sub     rdi,TOBJ
        movzx   eax,[rbx].rc.col
        mul     [rdi].rc.y
        movzx   ecx,[rdi].rc.x
        add     eax,ecx
        shl     eax,2
        add     rax,[rbx].window
        mov     [rdi].window,rax
        mov     [rdi].prev,rbx
        mov     [rdi].winproc,&_defwinproc
        lea     eax,[rdx+1]

        .if ( al < [rbx].count )

            lea rax,[rdi+TCLASS]
            mov [rdi].next,rax
        .endif
    .endf
    .if ( [rbx].flags & O_CURSOR )
        _getcursor(&[rbx].cursor)
    .endif
    _rcunzip([rbx].rc, [rbx].window, rs)
    .return( _conslink(rbx) )

_rsopen endp

    end
