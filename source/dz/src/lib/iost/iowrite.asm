include iost.inc

    .code

    assume ebx:ptr S_IOST

iowrite proc uses esi edi ebx iost:ptr S_IOST, buf:PVOID, len

    mov esi,buf
    mov ebx,iost
    .repeat
        mov ecx,len
        mov edi,[ebx].ios_i
        mov eax,[ebx].ios_size
        sub eax,edi
        add edi,[ebx].ios_bp
        .if eax < ecx
            add [ebx].ios_i,eax
            sub len,eax
            mov ecx,eax
            rep movsb
            ioflush(ebx)
            .continue(0) .ifnz
            .break
        .endif
        add [ebx].ios_i,ecx
        rep movsb
    .until 1
    mov eax,esi
    ret

iowrite endp

    END
