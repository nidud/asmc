; RCXCHG.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include consx.inc
include malloc.inc

    .code

    option cstack:on

rcxchg proc uses esi edi ebx ecx rc, wc:PVOID

  local y, col, row, tmp
  local bz:COORD, rect:SMALL_RECT, lbuf[TIMAXSCRLINE]:CHAR_INFO

    movzx   eax,rc.S_RECT.rc_col
    mov     col,eax
    mov     bz.x,ax
    mov     al,rc.S_RECT.rc_row
    mov     row,eax
    mov     bz.y,ax
    mov     al,rc.S_RECT.rc_x
    mov     rect.Left,ax
    add     eax,col
    dec     eax
    mov     rect.Right,ax
    movzx   eax,rc.S_RECT.rc_y
    mov     y,eax
    mov     rect.Top,ax
    add     eax,row
    dec     eax
    mov     rect.Bottom,ax
    mov     eax,row
    mul     col
    shl     eax,2
    mov     tmp,alloca(eax)

    .repeat

        .break .if !rcreadc(tmp, bz, &rect)

        lea edi,lbuf
        xor eax,eax
        mov ecx,col
        rep stosd
        mov esi,wc
        mov ebx,row
        mov bz.y,1

        .repeat

            lea edi,lbuf
            mov ecx,col
            .repeat
                mov ax,[esi]
                mov [edi],al
                mov [edi+2],ah
                add esi,2
                add edi,SIZE CHAR_INFO
            .untilcxz

            mov eax,y
            add eax,row
            sub eax,ebx
            mov rect.Top,ax
            mov rect.Bottom,ax
            .break .if !WriteConsoleOutput(hStdOutput, &lbuf, bz, 0, &rect)

            dec ebx
        .untilz

        mov esi,tmp
        mov edi,wc
        mov ebx,row
        .repeat
            mov ecx,col
            .repeat
                mov al,[esi]
                mov ah,[esi+2]
                mov [edi],ax
                add edi,2
                add esi,4
            .untilcxz
            dec ebx
        .untilz

        mov eax,ebx
        inc eax
    .until 1
    ret

rcxchg endp

    END
