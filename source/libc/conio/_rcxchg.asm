; _RCXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include conio.inc
include malloc.inc

    .code

_rcxchg proc uses rsi rdi rbx rc:TRECT, p:PCHAR_INFO

    ldr     ebx,rc
    ldr     rsi,p

    mov     rcx,_cbeginpaint()
    movzx   eax,[rcx].TCONSOLE.rc.col
    mul     bh
    movzx   edx,bl
    add     eax,edx
    shl     eax,2
    add     rax,[rcx].TCONSOLE.buffer
    mov     rdi,rax
    mov     eax,ebx
    shr     ebx,16
    mov     dh,[rcx].TCONSOLE.rc.col
    add     dl,bl

    .if ( dl > dh )

        mov bl,dh
        sub bl,al
    .endif

    mov al,bh
    add al,ah
    .if ( al > [rcx].TCONSOLE.rc.row )

        mov al,[rcx].TCONSOLE.rc.row
        mov bh,al
        sub bh,ah
    .endif

    .for ( dl = 0 : dl < bh : dl++ )

        shl edx,16
        mov rcx,rdi
        .for ( dl = 0 : dl < bl : dl++ )

            mov eax,[rdi]
            movsd
            mov [rsi-4],eax
        .endf
        shr edx,16
        movzx eax,dh
        lea rdi,[rcx+rax*4]
    .endf
    _cendpaint()
    mov eax,1
    ret

_rcxchg endp

    end
