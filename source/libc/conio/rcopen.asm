; RCOPEN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include tchar.inc

.code

rcopen proc rc:TRECT, flag:uint_t, color:uint_t, attrib:uint_t, title:string_t, p:ptr

    ldr eax,flag
    .if !( eax & W_MYBUF )

        or eax,W_UNICODE
        .if !_rcalloc(rc, eax)
            .return
        .endif
        mov p,rax
    .endif
    _rcread(rc, p)

    mov edx,color
    and edx,_D_CLEAR or _D_BACKG or _D_FOREG
    .ifnz

        movzx eax,rc.row
        mul rc.col
        mov ecx,attrib

        .switch edx
          .case _D_CLEAR : wcputw (p, eax, ' ') : .endc
          .case _D_COLOR : wcputa (p, eax, ecx) : .endc
          .case _D_BACKG : wcputbg(p, eax, ecx) : .endc
          .case _D_FOREG : wcputfg(p, eax, ecx) : .endc
          .default
            shl ecx,16
            mov cl,' '
            wcputw(p, eax, ecx)
        .endsw

        mov rax,title
        .if rax

            movzx ecx,rc.col
            wctitle(p, ecx, rax)
        .endif
    .endif
    mov rax,p
    ret

rcopen endp

    end
