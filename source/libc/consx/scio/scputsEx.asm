include consx.inc

    .code

scputsEx proc uses esi edi ebx x, y, a, l, string:LPSTR

    mov edi,string
    mov esi,x
    mov ebx,l
    mov ah,byte ptr a

    .repeat
        mov al,byte ptr [edi]
        inc edi
        .switch al
          .case 9
            add esi,16
            and esi,0xFFF0
            .endc
          .case 10
            mov esi,x
            inc y
            .endc
          .case 0
            mov bl,al
            .endc
          .case '&'
            .if bh
                mov  al,bh
                push ecx
                lea  ecx,[esi-1]
                scputa(ecx, y, 1, eax)
                pop  ecx
                .endc
            .endif
          .default
            scputw(esi, y, 1, eax)
            inc esi
            dec bl
        .endsw
    .until !bl
    mov eax,edi
    sub eax,string
    dec eax
    ret

scputsEx endp

    END
