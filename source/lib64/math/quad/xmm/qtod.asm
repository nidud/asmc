
include quadmath.inc

    .code

    option win64:rsp nosave noauto

qtod proc vectorcall Q:XQFLOAT

    movq    rax,xmm0
    movhlps xmm0,xmm0
    movq    rdx,xmm0
    shld    rcx,rdx,16
    shrd    rax,rdx,32
    shr     rdx,16
    mov     r10d,eax
    or      r10d,edx
    and     ecx,0xFFFF
    mov     r8d,ecx
    and     r8d,Q_EXPMASK
    mov     r9d,r8d
    neg     r8d
    rcr     edx,1
    rcr     eax,1
    mov     r8d,eax
    shl     r8d,22
    jnc     L1
    jnz     L2
    add     r8d,r8d
L2:
    add     eax,0x0800
    adc     edx,0
    jnc     L1
    mov     edx,0x80000000
    inc     cx
L1:
    and     eax,0xFFFFF800
    mov     r8d,ecx
    and     cx,0x7FFF
    add     cx,0x03FF-0x3FFF
    jz      L4
    cmp     cx,0x07FF
    jb      L5
    cmp     cx,0xC400
    jb      L7
    cmp     cx,-52
    jl      L8
    mov     r8d,0xFFFFF800
    sub     cx,12
    neg     cx
    cmp     cx,32
    jb      L9
    sub     cl,32
    mov     r8d,eax
    mov     eax,edx
    xor     edx,edx
L9:
    shrd    r8d,eax,cl
    shrd    eax,edx,cl
    shr     edx,cl
    add     r8d,r8d
    adc     eax,0
    adc     edx,0
    jmp     L3
L8:
    xor     eax,eax
    xor     edx,edx
    shl     r8d,17
    rcr     edx,1
    jmp     L3
L7:
    shrd    eax,edx,11
    shl     edx,1
    shr     edx,11
    shl     r8w, 1
    rcr     edx,1
    or      edx,0x7FF00000
    jmp     L3
L4:
    shrd    eax,edx,12
    shl     edx,1
    shr     edx,12
    jmp     L6
L5:
    shrd    eax,edx,11
    shl     edx,1
    shrd    edx,ecx,11
L6:
    shl     r8w,1
    rcr     edx,1
L3:
    xor     r8d,r8d
    cmp     r9d,0x3BCC
    jnb     L11
    or      r10d,r9d
    jz      L10
    xor     eax,eax
    xor     edx,edx
    mov     r8d,ERANGE
    jmp     L13
L11:
    cmp     r9d,0x3BCD
    jb      L12
    mov     r9d,edx
    and     r9d,0x7FF00000
    mov     r8d,ERANGE
    jz      L13
    cmp     r9d,0x7FF00000
    je      L13
    jmp     L10
L12:
    cmp     r9d,0x3BCC
    jb      L10
    mov     r9d,edx
    or      r9d,eax
    mov     r8d,ERANGE
    jz      L13
    mov     r9d,edx
    and     r9d,0x7FF00000
    jnz     L10
L13:
    mov     qerrno,r8d
L10:
    shl     rdx,32
    or      rax,rdx
    movq    xmm0,rax
    ret

qtod endp

    end
