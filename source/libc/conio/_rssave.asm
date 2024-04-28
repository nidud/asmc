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

   .new     d:RIDD
   .new     o:ROBJ
   .new     size:int_t
   .new     flags:int_t
   .new     wp:ptr
   .new     fp:LPFILE = fopen(file, "wb")
   .return .if ( rax == NULL )

    mov     rbx,hwnd
    mov     d.rc,[rbx].rc
    mov     d.index,[rbx].index
    mov     d.count,[rbx].count
    movzx   eax,[rbx].flags
    and     eax,W_RESBITS
    mov     flags,eax
    mov     d.flags,ax
    fwrite(&d, 1, RIDD, fp)

    .for ( rbx = [rbx].object : rbx : rbx = [rbx].next )

        mov ax,[rbx].flags
        and ax,O_RESBITS
        mov o.flags,ax
        mov o.count,[rbx].count
        mov o.syskey,[rbx].index
        mov o.rc,[rbx].rc
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
