; _DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include stdio.inc
include malloc.inc

    .code

_dlopen proc uses rbx rc:TRECT, count:uint_t, flags:uint_t, size:uint_t

   .new     hwnd:THWND
   .new     rsize:int_t
   .new     dsize:int_t
   .new     tsize:int_t

    ldr     eax,flags
    ldr     ecx,rc
    or      eax,W_UNICODE
    mov     rsize,_rcmemsize(ecx, eax)
    mov     eax,count
    inc     eax
    imul    eax,eax,TDIALOG
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
    lea     rax,[rbx+TDIALOG]
    cmp     ecx,count
    cmovz   rax,rcx
    mov     [rbx].object,rax
    mov     eax,W_PARENT
    cmovz   eax,ecx
    or      eax,flags
    or      eax,W_ISOPEN or W_CURSOR
    mov     [rbx].flags,ax
    mov     [rbx].rc,rc
    mov     [rbx].count,count

    _getcursor(&[rbx].cursor)
    .if ( flags & W_TRANSPARENT )
        _rcread(rc, [rbx].window)
        _rcclear(rc, [rbx].window, 0x00080000)
    .else
        _at BG_MENU,FG_MENU,' '
        _rcclear(rc, [rbx].window, eax)
    .endif
    .for ( rdx = rbx, rbx = [rbx].object, ecx = 0 : ecx < count : ecx++, rbx+=TDIALOG )

        lea eax,[rcx+1]
        mov [rbx].flags,W_CHILD
        mov [rbx].prev,rdx
        mov [rbx].oindex,al

        .if ( eax < count )

            lea rax,[rbx+TDIALOG]
            mov [rbx].next,rax
        .endif
    .endf
    .return( _conslink(hwnd) )

_dlopen endp

    end
