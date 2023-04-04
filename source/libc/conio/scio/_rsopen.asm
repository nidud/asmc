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
   .new xsize:int_t
   .new count:int_t

    mov     rbx,rs
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
    mov     esi,eax
    add     esi,rsize
    add     esi,dsize
    mov     hwnd,malloc(esi)

    .return .if !( rax )

    mov     ecx,esi
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
    mov     rdx,rsi
    mov     rsi,rbx
    mov     ecx,TOBJ
    rep     movsb
    mov     rsi,rdx
    or      [rsi].flags,W_ISOPEN

    .if ( [rsi].flags & O_CURSOR )
        _getcursor(&[rsi].cursor)
    .endif

    assume  rdi:THWND
    mov     rdx,[rsi].window
    mov     rdi,rsi
    movzx   eax,[rbx].count
    mov     count,eax

    .for ( rsi = [rsi].object, ecx = 0 : ecx < count : ecx++, rsi += TCLASS )

        mov [rsi].prev,rdi
        mov [rsi].window,rdx

        lea eax,[rcx+1]
        .if ( eax < count )

            lea rax,[rsi+TCLASS]
            mov [rsi].next,rax
        .endif
    .endf

    mov rdi,[rdi].object
    lea rsi,[rbx+TOBJ]
    .for ( : count : count--, rdi += TCLASS )

        .if ( [rsi].flags & W_WNDPROC )
            mov [rdi].winproc,&_defwinproc
        .endif
        mov rax,rdi
        mov ecx,TOBJ
        rep movsb
        mov rdi,rax
        mov [rdi].window,_rcbprc([rbx].rc, [rdi].rc, [rdi].window)
    .endf

    mov rdi,hwnd
    _rcunzip([rbx].rc, [rdi].window, rsi)
   .return( _conslink(rdi) )

_rsopen endp

    end
