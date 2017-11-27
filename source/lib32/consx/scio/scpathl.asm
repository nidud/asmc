include consx.inc
include string.inc

    .code

scpathl proc uses esi edi edx ecx x, y, l, string:LPSTR

  local pcx:dword
  local lbuf[TIMAXSCRLINE]:byte

    movzx esi,byte ptr l
    mov al,' '
    lea edi,lbuf
    mov edx,edi
    mov ecx,esi
    rep stosb
    mov edi,string

    .if strlen(edi) > esi
        mov ecx,[edi]
        add edi,eax
        sub edi,esi
        add edi,4
        .if ch == ':'
            mov [edx],cl
            mov [edx+1],ch
            add edi,2
            add edx,2
        .endif
        mov ax,'.\'
        mov [edx],al
        mov [edx+1],ah
        mov [edx+2],ah
        mov [edx+3],al
        add edx,4
    .endif

    .while 1

        mov al,[edi]
        .break .if !al
        mov [edx],al
        inc edi
        inc edx
    .endw

    movzx eax,byte ptr x
    movzx edx,byte ptr y
    shl   edx,16
    mov   dx,ax

    WriteConsoleOutputCharacter(hStdOutput, &lbuf, esi, edx, &pcx)
    mov eax,pcx
    ret

scpathl endp

    END
