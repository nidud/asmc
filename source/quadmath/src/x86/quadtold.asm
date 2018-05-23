include quadmath.inc

    .code

quadtold proc uses ebx ld:ptr, q:ptr

    mov eax,q
    movzx ecx,word ptr [eax+14]
    mov edx,[eax+10]
    mov ebx,ecx
    and ebx,LD_EXPMASK
    neg ebx
    mov eax,[eax+6]
    rcr edx,1
    rcr eax,1
    ;
    ; round result
    ;
    .ifc
        .if eax == -1 && edx == -1
            xor eax,eax
            mov edx,0x80000000
            inc cx
        .else
            add eax,1
            adc edx,0
        .endif
    .endif
    mov ebx,ld
    mov [ebx],eax
    mov [ebx+4],edx
    mov [ebx+8],cx
    mov eax,ebx
    ret

quadtold endp

    end
