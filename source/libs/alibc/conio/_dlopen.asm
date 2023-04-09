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

   .new hwnd:THWND
   .new rsize:int_t
   .new dsize:int_t
   .new tsize:int_t

    test    edx,W_SHADE
    mov     edx,0
    setnz   dl
    mov     rsize,_rcmemsize(rc, edx)
    mov     eax,esi
    inc     eax
    imul    eax,eax,TCLASS
    mov     dsize,eax
    mov     edi,size
    add     edi,rsize
    add     edi,eax
    mov     tsize,edi
    mov     hwnd,malloc(edi)

    .return .if !( rax )

    mov     rbx,rax
    mov     rdi,rax
    mov     ecx,tsize
    xor     eax,eax
    rep     stosb

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

    mov rdx,[rbx].window

    assume rsi:THWND

    .for ( rsi = [rbx].object, ecx = 0 : ecx < count : ecx++, rsi += TCLASS )

        mov [rsi].flags,  W_CHILD
        mov [rsi].prev,   rbx
        mov [rsi].window, rdx
        mov [rsi].index,  cl

        lea eax,[rcx+1]
        .if ( eax < count )

            lea rax,[rsi+TCLASS]
            mov [rsi].next,rax
        .endif
    .endf
    .return( _conslink(hwnd) )

_dlopen endp

    end
