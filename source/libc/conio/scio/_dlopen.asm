; _DLOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
include conio.inc
include stdio.inc
include malloc.inc

    .code

_dlopen proc uses rsi rdi rbx rc:TRECT, count:UINT, flags:UINT, size:UINT

   .new     hwnd:THWND
   .new     rsize:int_t
   .new     dsize:int_t

    xor     edx,edx
    test    flags,W_SHADE
    setnz   dl
    mov     rsize,_rcmemsize(rc, edx)
    mov     eax,count
    inc     eax
    imul    eax,eax,TCLASS
    mov     dsize,eax
    mov     esi,size
    add     esi,rsize
    add     esi,eax
    mov     hwnd,malloc(esi)

    .return .if !( rax )

    mov     rbx,rax
    mov     rdi,rax
    mov     ecx,esi
    xor     eax,eax
    rep     stosb

    assume  rbx:THWND

    mov     eax,dsize
    add     eax,rsize
    add     rax,rbx
    cmp     size,ecx
    cmovz   rax,rcx
    mov     .context.buffer,rax

    mov     eax,dsize
    add     rax,rbx
    mov     .window,rax
    lea     rax,[rbx+TCLASS]
    cmp     count,ecx
    cmovz   rax,rcx
    mov     .object,rax
    mov     eax,O_CHILD
    cmovz   eax,ecx
    or      eax,flags
    mov     .flags,eax
    or      .flags,W_ISOPEN
    mov     .rc,rc
    mov     .count,count

    _getcursor(&.cursor)

    .if ( flags & W_TRANSPARENT )
        _rcread(rc, .window)
        _rcclear(rc, .window, 0x00080000)
    .elseif ( flags & W_COLOR )
        _rcclear(rc, .window, _getattrib(FG_DIALOG, BG_DIALOG))
    .endif

    mov     rdx,.window
    assume  rsi:THWND

    .for ( rsi = [rbx].object, ecx = 0 : ecx < count : ecx++, rsi += TCLASS )

        mov .flags,  W_CHILD
        mov .prev,   rbx
        mov .window, rdx
        mov .index,  cl

        lea eax,[rcx+1]
        .if ( eax < count )

            lea rax,[rsi+TCLASS]
            mov .next,rax
        .endif
    .endf
    .return( _conslink(hwnd) )

_dlopen endp

    end
