; _DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include stdio.inc
include malloc.inc

    .code

_dlopen proc uses rbx rc:TRECT, count:UINT, flags:UINT, size:UINT

   .new     hwnd:THWND
   .new     rsize:int_t
   .new     dsize:int_t
   .new     tsize:int_t

    xor     edx,edx
    test    flags,W_SHADE
    setnz   dl
    mov     rsize,_rcmemsize(rc, edx)
    mov     eax,count
    inc     eax
    imul    eax,eax,TCLASS
    mov     dsize,eax
    add     eax,size
    add     eax,rsize
    mov     tsize,eax
    mov     hwnd,malloc(eax)

    .return .if !( rax )

    mov     rdx,rdi
    mov     rbx,rax
    mov     rdi,rax
    mov     ecx,tsize
    xor     eax,eax
    rep     stosb
    mov     rdi,rdx
    assume  rbx:THWND

    mov     eax,dsize
    add     eax,rsize
    add     rax,rbx
    cmp     size,ecx
    cmovz   rax,rcx
    mov     [rbx].buffer,rax

    mov     eax,dsize
    add     rax,rbx
    mov     [rbx].window,rax
    lea     rax,[rbx+TCLASS]
    cmp     count,ecx
    cmovz   rax,rcx
    mov     [rbx].object,rax
    mov     eax,O_CHILD
    cmovz   eax,ecx
    or      eax,flags
    mov     [rbx].flags,eax
    or      [rbx].flags,W_ISOPEN or O_CURSOR
    mov     [rbx].rc,rc
    mov     [rbx].count,count

    _getcursor(&[rbx].cursor)
    .if ( flags & W_TRANSPARENT )
        _rcread(rc, [rbx].window)
        _rcclear(rc, [rbx].window, 0x00080000)
    .else
        _rcclear(rc, [rbx].window, _getattrib(BG_MENU, FG_MENU))
    .endif
    .for ( rdx=rbx, rbx=[rbx].object, ecx=0 : ecx < count : ecx++, rbx+=TCLASS )

        lea eax,[rcx+1]
        mov [rbx].flags,W_CHILD
        mov [rbx].prev,rdx
        mov [rbx].index,al

        .if ( eax < count )

            lea rax,[rbx+TCLASS]
            mov [rbx].next,rax
        .endif
    .endf
    .return( _conslink(hwnd) )

_dlopen endp

    end
