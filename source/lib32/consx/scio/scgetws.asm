include consx.inc
include malloc.inc

    .code

scgetws proc uses esi edi ebx ecx edx x, y, l

  local rect:SMALL_RECT
  local lbuf[TIMAXSCRLINE]:CHAR_INFO
  local buf:dword

    movzx eax,byte ptr x
    movzx edx,byte ptr y
    mov   rect.Left,ax
    mov   rect.Top,dx
    mov   ebx,l

    .ifs ebx < 0
        not ebx
        mov l,ebx
        add edx,ebx
        dec edx
        shl ebx,16
        mov bx,1
    .else
        add eax,ebx
        add ebx,10000h
    .endif

    mov rect.Right,ax
    mov rect.Bottom,dx
    mov eax,l
    shl eax,1

    .if malloc(eax)

        mov buf,eax
        .if ReadConsoleOutput(hStdOutput, &lbuf, ebx, 0, &rect)

            lea esi,lbuf
            mov edi,buf
            mov ecx,l
            .repeat
                lodsw
                stosb
                lodsw
                stosb
            .untilcxz
            inc ecx
            mov eax,1
        .endif
        mov eax,buf
    .endif
    ret

scgetws endp

    END
