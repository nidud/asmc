; _RSSAVE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include stdio.inc
include conio.inc
include malloc.inc
include string.inc

    .code

    assume rbx:THWND
    assume rcx:THWND

_rssave proc uses rbx hwnd:THWND, file:LPSTR

   .new     o:ROBJ
   .new     size:int_t
   .new     flags:int_t
   .new     wp:ptr
   .new     fp:LPFILE = fopen(file, "wb")
   .return .if ( rax == NULL )

    mov     rbx,hwnd
    mov     o.rc,[rbx].rc
    mov     o.index,[rbx].index
    mov     o.count,[rbx].count
    mov     eax,[rbx].flags
    and     eax,W_RESBITS
    mov     flags,eax
    mov     o.flag,ax
    xor     edx,edx
    test    [rbx].flags,_D_SHADE
    setnz   dl
    mov     size,_rcmemsize([rbx].rc, edx)
    movzx   eax,[rbx].count
    inc     eax
    imul    eax,eax,TCLASS
    add     size,eax
    xor     eax,eax
    mov     ecx,TLIST
    test    [rbx].flags,O_LIST
    cmovnz  eax,ecx

    .for ( rcx = [rbx].object : rcx : rcx = [rcx].next )

        movzx edx,[rcx].count
        shl edx,3+TCHAR
        .if ( [rcx].type == T_EDIT )
            .if ( [rcx].flags & O_MYBUF )
                mov edx,TEDIT
            .else
                add edx,TEDIT
            .endif
        .endif
        add eax,edx
    .endf
    add size,eax
    fwrite(&size, 1, 2, fp)
    fwrite(&o, 1, ROBJ, fp)

    .for ( rbx = [rbx].object : rbx : rbx = [rbx].next )

        mov o.rc,[rbx].rc
        mov o.index,[rbx].index
        mov o.count,[rbx].count
        movzx eax,[rbx].type
        dec eax
        mov ecx,[rbx].flags
        and ecx,O_RESBITS
        or  eax,ecx
        mov o.flag,ax
        fwrite(&o, 1, ROBJ, fp)
    .endf

    mov rbx,hwnd
    movzx eax,[rbx].rc.col
    mul [rbx].rc.row
    shl eax,4
    mov wp,malloc(eax)
    mov size,_rczip([rbx].rc, rax, [rbx].window, flags)

    fwrite(wp, 1, size, fp)
    free(wp)
    fclose(fp)
   .return( 1 )

_rssave endp

    end
