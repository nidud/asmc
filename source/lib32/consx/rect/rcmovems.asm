; RCMOVEMS.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include string.inc
include malloc.inc
include strlib.inc

    .code

rcmoveup proc uses esi edi ebx rc, wp:PVOID, flag

  local x,l,lp

    movzx eax,rc.S_RECT.rc_y
    .if eax > 1

        movzx   esi,rc.S_RECT.rc_row
        dec     eax
        add     esi,eax
        mov     edi,eax
        mov     al,rc.S_RECT.rc_x
        mov     x,eax
        mov     al,rc.S_RECT.rc_col
        mov     l,eax

        .if rcalloc(rc, 0)

            mov ebx,eax
            rcread(rc, eax)
            scgetws(x, edi, l)
            mov lp,eax
            dec rc.S_RECT.rc_y
            rcwrite(rc, ebx)
            free(ebx)
            mov ebx,l
            add ebx,ebx
            movzx eax,rc.S_RECT.rc_row
            dec eax
            push eax
            mul ebx
            mov edi,wp
            add edi,eax
            memxchg(lp, edi, ebx)
            scputws(x, esi, l, eax)
            mov edx,edi
            sub edx,ebx
            pop esi
            .while esi
                memxchg(edx, edi, ebx)
                sub edi,ebx
                sub edx,ebx
                dec esi
            .endw
        .endif
    .endif
    mov eax,rc
    ret

rcmoveup endp

rcmovedn proc uses esi edi ebx rc, wp:PVOID, flag

  local x,l,lp

    movzx eax,rc.S_RECT.rc_y
    movzx edx,rc.S_RECT.rc_row
    mov   esi,eax
    add   eax,edx

    .if _scrrow >= eax

        mov edi,eax
        mov al,rc.S_RECT.rc_x
        mov x,eax
        mov al,rc.S_RECT.rc_col
        mov l,eax

        .if rcalloc( rc, 0 )

            mov ebx,eax
            rcread(rc, eax)
            mov lp,scgetws(x, edi, l)
            inc rc.S_RECT.rc_y
            rcwrite(rc, ebx)
            free(ebx)
            mov ebx,l
            add ebx,ebx
            memxchg( lp, wp, ebx )
            scputws( x, esi, l, eax )
            movzx esi,rc.S_RECT.rc_row
            dec esi
            mov edi,wp

            .while esi

                memxchg(edi, &[edi+ebx], ebx)
                add edi,ebx
                dec esi
            .endw
        .endif
    .endif
    mov eax,rc
    ret

rcmovedn endp

rcmoveright proc uses esi edi ebx rc, wp:PVOID, flag

  local x,y,l,lp

    movzx eax,rc.S_RECT.rc_x
    movzx edx,rc.S_RECT.rc_col
    mov   esi,eax
    add   eax,edx

    .if _scrcol > eax

        mov edi,eax
        mov al,rc.S_RECT.rc_x
        mov x,eax
        mov al,rc.S_RECT.rc_y
        mov y,eax
        mov al,rc.S_RECT.rc_row
        not eax
        mov l,eax

        .if rcalloc(rc, 0)

            mov ebx,eax
            rcread(rc, eax)
            mov lp,scgetws(edi, y, l)
            inc rc.S_RECT.rc_x
            rcwrite(rc, ebx)
            free(ebx)

            movzx ebx,rc.S_RECT.rc_col
            dec   ebx
            movzx edx,rc.S_RECT.rc_row
            mov   esi,wp
            mov   edi,lp

            .repeat
                mov  ax,[esi]
                push [edi]
                mov  [edi],ax
                mov  ecx,ebx
                push edi
                mov  edi,esi
                add  esi,2
                rep  movsw
                pop  edi
                pop  eax
                mov  [esi-2],ax
                add  edi,2
                dec  edx
            .until !edx
            scputws(x, y, l, lp)
        .endif
    .endif
    mov eax,rc
    ret

rcmoveright endp

rcmoveleft proc uses esi edi ebx rc, wp:PVOID, flag

  local x,y,l,lw,lp

    .if rc.S_RECT.rc_x

        movzx eax,rc.S_RECT.rc_x
        mov   edi,eax
        dec   edi
        mov   x,eax
        mov   al,rc.S_RECT.rc_y
        mov   y,eax
        mov   al,rc.S_RECT.rc_row
        mov   esi,eax
        not   eax
        mov   l,eax

        .if rcalloc(rc, 0)

            mov ebx,eax
            rcread(rc, eax)
            scgetws(edi, y, l)
            mov lp,eax
            dec rc.S_RECT.rc_x
            rcwrite(rc, ebx)
            free(ebx)

            movzx eax,rc.S_RECT.rc_col
            mov   edx,eax
            dec   eax
            mov   ebx,eax
            shl   edx,2
            mov   lw,edx
            mov   edx,esi
            add   eax,eax
            mov   esi,wp
            add   esi,eax
            mov   edi,lp
            std

            .repeat
                mov  ax,[esi]
                push [edi]
                mov  [edi],ax
                mov  ecx,ebx
                push edi
                mov  edi,esi
                sub  esi,2
                rep  movsw
                pop  edi
                pop  eax
                mov  [esi+2],ax
                add  esi,lw
                add  edi,2
                dec  edx
            .until !edx
            cld
            movzx eax,rc.S_RECT.rc_col
            add eax,x
            dec eax
            scputws(eax, y, l, lp)
        .endif
    .endif
    mov eax,rc
    ret
rcmoveleft endp

    END
