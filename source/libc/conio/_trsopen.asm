; _TRSOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include stdio.inc
include malloc.inc

    .code

    assume rbx:PIDD
    assume rsi:THWND

_rsopen proc uses rsi rdi rbx res:PIDD

   .new hwnd:THWND
   .new size:int_t
   .new rsize:int_t
   .new dsize:int_t
   .new tsize:int_t
   .new xsize:int_t
   .new olist:int_t = 0
   .new count:int_t
   .new rdata:string_t

    ldr     rbx,res

    movzx   eax,[rbx].flags
    or      eax,W_UNICODE
    mov     rsize,_rcmemsize([rbx].rc, eax)
    movzx   eax,[rbx].count
    mov     count,eax
    inc     eax
    imul    eax,eax,TDIALOG
    mov     dsize,eax
    lea     rdi,[rbx+RIDD]

    .for ( ecx = 0, edx = 0 : dl < [rbx].count : edx++, rdi+=ROBJ )

        movzx eax,[rdi].ROBJ.flags
        .if ( eax & O_LIST )

            mov olist,TLIST
        .endif
        and eax,O_TYPEMASK
        cmp eax,O_TEDIT
        mov al,[rdi].ROBJ.count
        .ifz

            add ecx,TEDIT
ifdef _UNICODE
            add eax,eax
endif
        .endif
        shl eax,4
        add ecx,eax
    .endf

    add     ecx,olist
    mov     xsize,ecx
    add     ecx,dsize
    add     ecx,rsize
    mov     size,ecx
    mov     hwnd,malloc(ecx)
    .return .if !rax

    mov     rsi,rax
    mov     rdi,rax
    xor     eax,eax
    mov     ecx,size
    rep     stosb

    mov     [rsi].rc,[rbx].rc
    mov     [rsi].index,[rbx].index
    mov     [rsi].count,[rbx].count

    mov     eax,count
    inc     eax
    imul    edx,eax,TDIALOG
    mov     dsize,edx
    add     rdx,rsi
    mov     [rsi].window,rdx
    imul    edx,eax,ROBJ
    add     rdx,rbx
    mov     rdata,rdx

    lea     rax,[rsi+TDIALOG]
    cmp     cl,[rbx].count
    cmovz   rax,rcx
    mov     [rsi].object,rax
    mov     edx,W_PARENT
    cmovz   edx,ecx
    movzx   eax,[rbx].flags
    and     eax,W_RESBITS
    or      eax,W_ISOPEN
    or      eax,edx
    mov     [rsi].flags,ax

    .for ( rdi = rsi : ecx < count : ecx++ )

        add     rsi,TDIALOG
        add     rbx,ROBJ

        movzx   eax,[rbx].flags
        and     eax,O_RESBITS
        mov     [rsi].flags,ax
        mov     [rsi].rc,[rbx].rc
        mov     [rsi].syskey,[rbx].index
        mov     [rsi].count,[rbx].count
        mov     [rsi].index,cl
        mov     [rsi].prev,rdi
        lea     rax,[rsi+TDIALOG]
        mov     [rsi].next,rax
    .endf
    mov     [rsi].next,NULL

    assume  rbx:THWND
    mov     rbx,rdi
    invoke  _rcunzip([rbx].rc, [rbx].window, rdata, [rbx].flags)

    mov     edi,dsize
    add     edi,rsize
    add     rdi,rbx
    mov     [rbx].buffer,rdi
    mov     eax,olist
    mov     rcx,rdi
    test    eax,eax
    cmovz   rcx,rax
    mov     [rbx].llist,rcx
    add     rdi,rax

    .for ( rsi = [rbx].object : rsi : rsi = [rsi].next )

        movzx   eax,[rbx].rc.col
        mul     [rsi].rc.y
        movzx   ecx,[rsi].rc.x
        add     eax,ecx
        shl     eax,2
        add     rax,[rbx].window
        mov     [rsi].window,rax
        movzx   edx,[rbx].flags
        and     edx,O_TYPEMASK

        lea     rcx,_tiproc
        lea     rax,_defwinproc
        cmp     edx,O_TEDIT
        cmovz   rax,rcx
        mov     [rsi].winproc,rax

        .if ( [rsi].count )

            .if ( edx == O_TEDIT)

                mov     [rsi].tedit,rdi
                mov     rcx,rdi
                assume  rcx:PTEDIT
                add     rdi,TEDIT
                movzx   eax,[rsi].count
                shl     eax,4
                mov     [rcx].bcols,eax
ifdef _UNICODE
                add     eax,eax
endif
                add     rdi,rax
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
                mov     [rsi].buffer,rdi
                movzx   ecx,[rsi].count
                shl     ecx,4
                add     rdi,rcx
            .endif
        .endif
    .endf

    .if ( [rbx].flags & W_CURSOR )
        _getcursor(&[rbx].cursor)
    .endif
    _conslink(rbx)
    ret

_rsopen endp

    end
