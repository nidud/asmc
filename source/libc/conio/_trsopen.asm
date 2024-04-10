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
    assume rsi:THWND

_rsopen proc uses rsi rdi rbx res:PTRES

   .new     hwnd:THWND
   .new     rsize:int_t
   .new     dsize:int_t
   .new     tsize:int_t
   .new     xsize:int_t
   .new     count:int_t
   .new     olist:int_t = 0
   .new     rdata:string_t

    ldr     rbx,res
    movzx   ecx,word ptr [rbx]
    mov     hwnd,malloc(ecx)
    .return .if !rax

    mov     rsi,rax
    mov     rdi,rax
    xor     eax,eax
    movzx   ecx,word ptr [rbx]
    add     rbx,2
    rep     stosb
    movzx   eax,[rbx].flag
    and     eax,W_RESBITS
    mov     [rsi].flags,eax
    mov     [rsi].type,T_WINDOW
    mov     [rsi].rc,[rbx].rc
    mov     [rsi].index,[rbx].index
    mov     [rsi].count,[rbx].count

    movzx   eax,[rbx].count
    mov     count,eax
    inc     eax
    imul    edx,eax,TCLASS
    mov     dsize,edx
    add     rdx,rsi
    mov     [rsi].window,rdx
    imul    edx,eax,ROBJ
    add     rdx,rbx
    mov     rdata,rdx
    lea     rax,[rsi+TCLASS]
    cmp     cl,[rbx].count
    cmovz   rax,rcx
    mov     [rsi].object,rax
    mov     eax,O_CHILD
    cmovz   eax,ecx
    or      eax,W_ISOPEN
    or      [rsi].flags,eax

    .for ( rdi = rsi, ecx = 0 : ecx < count : ecx++ )

        add rsi,TCLASS
        add rbx,ROBJ

        movzx eax,[rbx].flag
        mov edx,eax
        and eax,O_RESBITS
        and edx,0xF

        mov [rsi].flags,eax
        mov [rsi].type,dl
        and eax,O_LIST
        or  olist,eax
        mov [rsi].rc,[rbx].rc
        mov [rsi].syskey,[rbx].index
        mov [rsi].count,[rbx].count
        mov [rsi].index,cl
        mov [rsi].prev,rdi
        mov [rsi].next,0

        lea eax,[rcx+1]
        .if ( eax < count )

            lea rax,[rsi+TCLASS]
            mov [rsi].next,rax
        .endif
    .endf

    assume rbx:THWND
    mov rbx,rdi
    _rcunzip([rbx].rc, [rbx].window, rdata, [rbx].flags)
    .if ( [rbx].flags & W_RESAT )
        _rcunzipat([rbx].rc, [rbx].window)
    .endif

    xor edx,edx
    test [rbx].flags,W_SHADE
    setnz dl
    mov rsize,_rcmemsize([rbx].rc, edx)

    xor eax,eax
    .if ( olist )

        add eax,TLIST
        or  [rbx].flags,W_LIST
    .endif

    .for ( rsi = [rbx].object : rsi : rsi = [rsi].next )

        movzx edx,[rsi].count
        shl edx,3+TCHAR
        .if ( [rsi].type == T_EDIT )
            .if ( [rsi].flags & O_MYBUF )
                mov edx,TEDIT
            .else
                add edx,TEDIT
            .endif
        .endif
        add eax,edx
    .endf

    xor     ecx,ecx
    mov     xsize,eax
    mov     eax,dsize
    add     eax,rsize
    add     rax,rbx
    cmp     ecx,xsize
    cmovz   rax,rcx
    lea     rdx,[rax+TLIST]
    mov     [rbx].context.llist,rax
    test    [rbx].flags,W_LIST
    cmovnz  rax,rdx
    mov     [rbx].buffer,rax

    .for ( rsi = [rbx].object : rsi : rsi = [rsi].next )

        movzx   eax,[rbx].rc.col
        mul     [rsi].rc.y
        movzx   ecx,[rsi].rc.x
        add     eax,ecx
        shl     eax,2
        add     rax,[rbx].window
        mov     [rsi].window,rax

        lea     rcx,_tiproc
        lea     rax,_defwinproc
        cmp     [rsi].type,T_EDIT
        cmovz   rax,rcx
        mov     [rsi].winproc,rax

        .if ( [rsi].count )

            .if ( [rsi].type == T_EDIT )

                mov [rsi].context.tedit,[rbx].buffer
                add [rbx].buffer,TEDIT

                .if !( [rsi].flags & O_MYBUF )

                    movzx   ecx,[rsi].count
                    shl     ecx,3+TCHAR
                    add     [rbx].buffer,rcx
                .endif

                mov     rcx,rax
                assume  rcx:PTEDIT
                movzx   eax,[rsi].count
                shl     eax,4
                mov     [rcx].bcols,eax
                lea     rax,[rcx+TEDIT]
                mov     [rcx].base,rax
                mov     [rsi].buffer,rax
                mov     rax,[rsi].window
                mov     eax,[rax]
                mov     ax,U_MIDDLE_DOT
                mov     [rcx].clrattrib,eax
                movzx   eax,[rbx].rc.y
                add     al,[rsi].rc.y
                mov     [rcx].ypos,eax
                mov     al,[rbx].rc.x
                add     al,[rsi].rc.x
                mov     [rcx].xpos,eax
                mov     [rcx].flags,[rsi].flags
                mov     [rcx].scols,[rsi].rc.col
            .else
                mov     [rsi].buffer,[rbx].buffer
                movzx   ecx,[rsi].count
                shl     ecx,4
                add     [rbx].buffer,rcx
            .endif
        .endif
    .endf
    .if ( [rbx].flags & O_CURSOR )
        _getcursor(&[rbx].cursor)
    .endif
    _conslink(rbx)
    ret

_rsopen endp

    end
