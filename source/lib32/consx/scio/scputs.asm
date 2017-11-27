include consx.inc

    .code

scputs proc uses esi edi edx ecx x, y, a, l, string:LPSTR

  local bz:COORD
  local rect:SMALL_RECT
  local lbuf[TIMAXSCRLINE]:CHAR_INFO

    mov   edx,_scrcol
    movzx ecx,byte ptr l
    movzx eax,byte ptr x

    .repeat

        .if eax > edx

            xor eax,eax
            .break
        .endif

        .if !ecx || ecx > edx
            mov ecx,edx
            sub ecx,eax
        .endif

        add eax,ecx
        .if eax > edx

            xor eax,eax
            .break
        .endif

        mov esi,ecx
        movzx eax,byte ptr a

        .if !eax

            getxya(x, y)
        .endif

        mov a,eax
        shl eax,16
        mov al,' '
        lea edi,lbuf
        mov ecx,esi
        rep stosd
        mov ecx,esi
        mov esi,string
        lea edi,lbuf

        .repeat

            mov al,[esi]
            .break .if !al

            .if al == 9
                add edi,32
                and edi,-32
                inc esi
                .continue(0)
            .endif

            .if al == 10
                lea eax,[esi+1]
                mov ecx,y
                inc ecx
                scputs(x, ecx, a, l, eax)
                .break
            .endif

            inc esi
            mov [edi],al
            add edi,SIZE CHAR_INFO
        .untilcxz

        sub esi,string
        .ifz
            xor eax,eax
            .break
        .endif

        mov   bz.x,si
        mov   bz.y,1
        movzx eax,byte ptr x
        mov   rect.Left,ax
        add   eax,esi
        dec   eax
        mov   rect.Right,ax
        movzx eax,byte ptr y
        mov   rect.Top,ax
        mov   rect.Bottom,ax

        WriteConsoleOutput(hStdOutput, &lbuf, bz, 0, &rect)
        mov eax,esi
    .until 1
    ret

scputs endp

    END
