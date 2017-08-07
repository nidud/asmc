include ltype.inc
include fltintrn.inc

    .code

    assume esi: ptr S_STRFLT

_fltsetflags proc uses esi edi ebx fp:LPSTRFLT, string:LPSTR, flags:UINT

    mov esi,fp
    mov ebx,string
    mov edi,flags

    mov [esi].exponent,0
    .repeat
        movzx eax,byte ptr [ebx]
        inc ebx
        test al,al
        jz case_zero
    .until !(_ltype[eax+1] & _SPACE)
    dec ebx

    .if al == '+'
        inc ebx
        or  edi,_ST_SIGN
    .endif
    .if al == '-'
        inc ebx
        or  edi,_ST_SIGN or _ST_NEGNUM
    .endif
    mov ax,[ebx]
    inc ebx
    test al,al
    jz case_zero
    or  eax,2020h
    cmp al,'n'
    je  case_NaN
    cmp al,'i'
    je  case_INF
    .if ax == 'x0'
        or edi,_ST_ISHEX
        add ebx,2
    .endif
    dec ebx
toend:
    mov [esi].flags,edi
    mov [esi].string,ebx
    mov eax,edi
    ret

case_NaN:

    mov ax,[ebx]
    inc ebx
    test al,al
    jz case_zero

    or  ax,2020h
    cmp ax,'na'
    jne case_INVALID
    or  edi,_ST_ISNAN
    inc ebx
    movzx eax,BYTE PTR [ebx]

    .if al == '('
        lea edx,[ebx+1]
        movzx eax,BYTE PTR [edx]
        .while al == '_' || _ltype[eax+1] & _DIGIT or _UPPER or _LOWER
            inc edx
            mov al,[edx]
        .endw
        .if al == ')'
            lea ebx,[edx+1]
        .endif
    .endif

return_NAN:
    xor eax,eax
    mov ecx,80000000h
    jmp return_NANINF

case_INF:
    mov ax,[ebx]
    inc ebx
    or  ax,2020h
    cmp ax,'fn'
    jne case_INVALID
    or  edi,_ST_ISINF
    inc ebx
    xor eax,eax
    xor ecx,ecx

return_NANINF:
    mov edx,[esi].mantissa
    mov [edx],eax
    mov [edx+4],ecx
    mov ecx,7FFFh
    .if edi & _ST_NEGNUM
        or ecx,8000h
    .endif
    mov [edx+8],cx
    jmp toend

case_INVALID:
    dec ebx
    or  edi,_ST_INVALID
    jmp toend

case_zero:
    dec ebx
    or  edi,_ST_ISZERO
    xor eax,eax
    mov edx,[esi].mantissa
    mov [edx],eax
    mov [edx+4],eax
    mov [edx+8],ax
    jmp toend
_fltsetflags endp

    END
