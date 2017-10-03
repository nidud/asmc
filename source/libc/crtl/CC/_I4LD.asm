include math.inc

.code
    ;
    ; long [eax] to long double[edx]
    ;
_I4LD proc
    test eax,eax
    .ifs
        push ebx
        mov  ebx,edx
        neg  eax
        mov  edx,0xBFFF
        jmp  @F
    .endif
_I4LD endp
    ;
    ; DWORD [eax] to long double[edx]
    ;
_U4LD proc

    push ebx
    mov  ebx,edx
    mov  edx,0x3FFF

_U4LD endp

@@:
    push ecx
    .if eax
        bsr ecx,eax
        mov ch,cl
        mov cl,31
        sub cl,ch
        shl eax,cl
        mov cl,ch
        movzx ecx,ch
        add ecx,edx
        mov edx,eax
    .else
        xor edx,edx
        xor ecx,ecx
    .endif
    xor eax,eax
    mov [ebx],eax
    mov [ebx+4],edx
    mov [ebx+8],cx
    pop ecx
    pop ebx
    ret

    END
