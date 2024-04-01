; _TRSOPEN.ASM--
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

_rsopen proc uses rsi rdi rbx res:PTRES

   .new hwnd:THWND
   .new rsize:int_t
   .new dsize:int_t
   .new tsize:int_t
   .new xsize:int_t
   .new rdata:string_t

    ldr     rbx,res
    xor     edx,edx
    test    [rbx].flags,W_SHADE
    setnz   dl
    mov     rsize,_rcmemsize([rbx].rc, edx)
    movzx   eax,[rbx].count
    inc     eax
    imul    eax,eax,TCLASS
    mov     dsize,eax
    xor     eax,eax
    mov     ecx,TLIST
    test    [rbx].flags,O_LIST
    cmovnz  eax,ecx

    .for ( rdi = &[rbx+TOBJ], ecx = 0 : cl < [rbx].count : ecx++, rdi += TOBJ )

        movzx edx,[rdi].count
        shl edx,3+TCHAR
        .if ( [rdi].type == T_EDIT )
            .if ( [rdi].flags & O_MYBUF )
                mov edx,TEDIT
            .else
                add edx,TEDIT
            .endif
        .endif
        add eax,edx
    .endf

    mov     rdata,rdi
    mov     xsize,eax
    add     eax,rsize
    add     eax,dsize
    mov     tsize,eax

    .return .if !( malloc(eax) )

    mov     ecx,tsize
    mov     rdi,rax
    mov     rsi,rax
    xor     eax,eax
    rep     stosb

    mov     eax,dsize
    add     eax,rsize
    add     rax,rsi
    cmp     ecx,xsize
    cmovz   rax,rcx
    lea     rdx,[rax+TLIST]
    mov     [rsi].context.llist,rax
    test    [rbx].flags,O_LIST
    cmovnz  rax,rdx
    mov     [rsi].buffer,rax

    mov     eax,dsize
    add     rax,rsi
    mov     [rsi].window,rax
    lea     rax,[rsi+TCLASS]
    cmp     cl,[rbx].count
    cmovz   rax,rcx
    mov     [rsi].object,rax
    mov     eax,O_CHILD
    cmovz   eax,ecx
    or      eax,W_ISOPEN

    mov     rdi,rsi
    xchg    rsi,rbx
    mov     ecx,TOBJ
    rep     movsb
    assume  rbx:THWND
    assume  rdi:THWND
    or      [rbx].flags,eax
    mov     hwnd,rsi

    _rcunzip([rbx].rc, [rbx].window, rdata)
    .if ( [rbx].flags & W_RESAT )
        _rcunzipat([rbx].rc, [rbx].window)
    .endif

    .for ( rsi = hwnd, rdi = [rbx].object, edx = 0 : dl < [rbx].count : edx++, rdi+=TCLASS )

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
        lea     rcx,_tiproc
        lea     rax,_defwinproc
        cmp     [rdi].type,T_EDIT
        cmovz   rax,rcx
        mov     [rdi].winproc,rax

        .if ( [rdi].count )

            .if ( [rdi].type == T_EDIT )

                mov [rdi].context.tedit,[rbx].buffer
                add [rbx].buffer,TEDIT

                .if !( [rdi].flags & O_MYBUF )

                    movzx   ecx,[rdi].count
                    shl     ecx,3+TCHAR
                    add     [rbx].buffer,rcx
                .endif

                mov     rcx,rax
                assume  rcx:PTEDIT
                movzx   eax,[rdi].count
                shl     eax,4
                mov     [rcx].bcols,eax
                lea     rax,[rcx+TEDIT]
                mov     [rcx].base,rax
                mov     [rdi].buffer,rax
                mov     rax,[rdi].window
                mov     eax,[rax]
                mov     ax,U_MIDDLE_DOT
                mov     [rcx].clrattrib,eax
                movzx   eax,[rbx].rc.y
                add     al,[rdi].rc.y
                mov     [rcx].ypos,eax
                mov     al,[rbx].rc.x
                add     al,[rdi].rc.x
                mov     [rcx].xpos,eax
                mov     [rcx].flags,[rdi].flags
                mov     [rcx].scols,[rdi].rc.col
            .else
                mov     [rdi].buffer,[rbx].buffer
                movzx   ecx,[rdi].count
                shl     ecx,4
                add     [rbx].buffer,rcx
            .endif
        .endif

        lea eax,[rdx+1]
        .if ( al < [rbx].count )

            lea rax,[rdi+TCLASS]
            mov [rdi].next,rax
        .endif
    .endf
    .if ( [rbx].flags & O_CURSOR )
        _getcursor(&[rbx].cursor)
    .endif
    _conslink(rbx)
    ret

_rsopen endp

    end
