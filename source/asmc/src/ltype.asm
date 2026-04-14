; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc

    .data
     DEFINE_LTYPE _ltype

    .code

exchange proc fastcall private a:ptr, b:ptr, size:int_t
    mov     rax,[rcx]
    xchg    rax,[rdx]
    mov     [rcx],rax
    cmp     ldr(size),size_t
    je      .0
    mov     rax,[rcx+size_t]
    xchg    rax,[rdx+size_t]
    mov     [rcx+size_t],rax
.0:
    ret
    endp


define STKSIZ   (8*size_t - 2)
define swap     <exchange>

ifdef _WIN64
tqsort proc __ccall uses rsi rdi rbx r12 r13 r14 p:ptr, n:int_t, w:int_t, compare:PQSORTCMD
    define lo    <rsi>
    define hi    <rdi>
    define loguy <r12>
    define higuy <r13>
    define stkptr <r14d>
    xor r14d,r14d
else
tqsort proc __ccall uses esi edi ebx p:ptr, n:int_t, w:int_t, compare:PQSORTCMD
    define lo <esi>
    define hi <edi>
   .new loguy:ptr
   .new higuy:ptr
   .new stkptr:int_t = 0
endif
   .new lostk[STKSIZ]:ptr
   .new histk[STKSIZ]:ptr

    ldr rcx,p
    ldr edx,n

    .if ( edx > 1 )
        lea eax,[rdx-1]
        mul w
        mov lo,rcx
        lea rax,[rcx+rax]
        mov hi,rax
        .while 1
            mov ecx,w
            mov rax,hi
            add rax,rcx ; middle from (hi - lo) / 2
            sub rax,lo
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif
            mov rbx,lo
            add rbx,rax
            .ifsd compare(lo, rbx) > 0
                swap(lo, rbx, w)
            .endif
            .ifsd compare(lo, hi) > 0
                swap(lo, hi, w)
            .endif
            .ifsd compare(rbx, hi) > 0
                swap(rbx, hi, w)
            .endif
            mov loguy,lo
            mov higuy,hi
            .while 1
                mov ecx,w
                add loguy,rcx
                .if loguy < hi
                    .continue .ifsd compare(loguy, rbx) <= 0
                .endif
                .while 1
                    mov ecx,w
                    sub higuy,rcx
                    .break .if higuy <= rbx
                    .break .ifsd compare(higuy, rbx) <= 0
                .endw
                mov rcx,higuy
                mov rax,loguy
                .if rcx < rax
                    .break
                .endif
                .if rbx == rcx
                    mov rbx,rax
                .endif
                swap(rcx, rax, w)
            .endw
            mov eax,w
            add higuy,rax
            .if ( rbx < higuy )
                .while 1
                    mov eax,w
                    sub higuy,rax
                    .break .if higuy <= rbx
                    .break .ifd compare(higuy, rbx)
                .endw
            .endif
            .if ( rbx >= higuy )
                .while 1
                    mov eax,w
                    sub higuy,rax
                    .break .if higuy <= lo
                    .break .ifd compare(higuy, rbx)
                .endw
            .endif
            mov rdx,loguy
            mov rax,higuy
            sub rax,lo
            mov rcx,hi
            sub rcx,rdx
            .if rax < rcx
                .if rdx < hi
                    mov ecx,stkptr
                    mov lostk[rcx*size_t],rdx
                    mov histk[rcx*size_t],hi
                    inc stkptr
                .endif
                mov rax,higuy
                .if lo < rax
                    mov hi,rax
                   .continue
                .endif
            .else
                mov rax,higuy
                .if lo < rax
                    mov ecx,stkptr
                    mov histk[rcx*size_t],rax
                    mov lostk[rcx*size_t],lo
                    inc stkptr
                .endif
                .if rdx < hi
                    mov lo,rdx
                   .continue
                .endif
            .endif
            .break .if !stkptr
            dec stkptr
            mov ecx,stkptr
            mov lo,lostk[rcx*size_t]
            mov hi,histk[rcx*size_t]
        .endw
    .endif
    ret
    endp


tstrupr proc fastcall string:string_t
    mov rdx,rcx
    .repeat
        .if ( isllower( [rcx] ) )
            and byte ptr [rcx],not 0x20
        .endif
        inc rcx
    .until !eax
    .return( rdx )
    endp


tstrstart proc fastcall string:string_t
    ltokstart( rcx )
    ret
    endp


tmemcpy proc fastcall uses rdi dst:ptr, src:ptr, count:uint_t
    mov     rax,rcx ; -- return value
    xchg    rsi,rdx
ifdef _WIN64
    mov     ecx,r8d
else
    mov     ecx,count
endif
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret
    endp


tmemmove proc fastcall uses rsi rdi dst:ptr, src:ptr, count:uint_t
    mov     rax,rcx ; -- return value
    mov     rsi,rdx
ifdef _WIN64
    mov     ecx,r8d
else
    mov     ecx,count
endif
    mov     rdi,rax
    cmp     rax,rsi
    ja      .0
    rep     movsb
    jmp     .1
.0:
    lea     rsi,[rsi+rcx-1]
    lea     rdi,[rdi+rcx-1]
    std
    rep     movsb
    cld
.1:
    ret
    endp


tmemset proc fastcall uses rdi dst:ptr, char:int_t, count:uint_t
    mov     rdi,rcx
    mov     al,dl
    mov     rdx,rcx
ifdef _WIN64
    mov     ecx,r8d
else
    mov     ecx,count
endif
    rep     stosb
    mov     rax,rdx
    ret
    endp


tstrlen proc fastcall string:string_t
ifdef _WIN64
    mov         r8,rcx
    mov         rax,rcx         ; align back to avoid reading ahead
ifdef __AVX__
    and         rax,-32
    and         ecx,32-1
    mov         edx,-1          ; mask string part
    shl         edx,cl
    vxorps      ymm0,ymm0,ymm0
    vpcmpeqb    ymm1,ymm0,[rax]
    add         rax,32
    vpmovmskb   ecx,ymm1
    and         ecx,edx
    jnz         .1
.0:
    vpcmpeqb    ymm1,ymm0,[rax]
    vpmovmskb   ecx,ymm1
    add         rax,32
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-32]
else
    and         rax,-16
    and         ecx,16-1
    or          edx,-1
    shl         edx,cl
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,[rax]
    add         rax,16
    pmovmskb    ecx,xmm0
    xorps       xmm0,xmm0
    and         ecx,edx
    jnz         .1
.0:
    movaps      xmm1,[rax]
    pcmpeqb     xmm1,xmm0
    pmovmskb    ecx,xmm1
    add         rax,16
    test        ecx,ecx
    jz          .0
.1:
    bsf         ecx,ecx
    lea         rax,[rax+rcx-16]
endif
    sub         rax,r8
else
    push    rdi
    mov     rdi,rcx
    mov     rax,rcx
    and     ecx,3
    jz      .1
    sub     rax,rcx
    shl     ecx,3
    mov     edx,-1
    shl     edx,cl
    not     edx
    or      edx,[rax]
    lea     ecx,[rdx-0x01010101]
    not     edx
    and     ecx,edx
    and     ecx,0x80808080
    jnz     .2
.0:
    add     rax,4
.1:
    mov     edx,[rax]
    lea     ecx,[rdx-0x01010101]
    not     edx
    and     ecx,edx
    and     ecx,0x80808080
    jz      .0
.2:
    bsf     ecx,ecx
    shr     ecx,3
    add     rax,rcx
    sub     rax,rdi
    pop     rdi
endif
    ret
    endp


tstrchr proc fastcall string:string_t, char:int_t
    xor     eax,eax
.0:
    cmp     al,[rcx]
    jz      .2
    cmp     dl,[rcx]
    jz      .1
    inc     rcx
    jmp     .0
.1:
    mov     rax,rcx
.2:
    ret
    endp


tstrrchr proc fastcall string:string_t, char:int_t
    xor     eax,eax
.0:
    cmp     byte ptr [rcx],0
    jz      .2
    cmp     dl,[rcx]
    jz      .1
    inc     rcx
    jmp     .0
.1:
    mov     rax,rcx
    inc     rcx
    jmp     .0
.2:
    ret
    endp


tstrcpy proc fastcall dst:string_t, src:string_t
ifdef _WIN64
    mov         rax,rcx
    mov         r10,rdx
    and         r10,-16
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,[r10]
    pmovmskb    r9d,xmm0
    add         r10,16
    mov         cl,dl
    and         cl,16-1
    shr         r9d,cl
    test        r9d,r9d
    jz          .0
    bsf         ecx,r9d
    mov         r9,rax
    jmp         .4
.0:
    movaps      xmm1,[r10]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jz          .1
    bsf         ecx,ecx
    sub         r10,rdx
    add         ecx,r10d
    mov         r9,rax
    jmp         .4
.1:
    movups      xmm2,[rdx]
    lea         rcx,[r10+16]
    sub         rcx,rdx
    lea         rdx,[r10+16]
    lea         r9,[rax+rcx]
    movups      [r9-16],xmm1
.2:
    movaps      xmm1,[rdx]
    xorps       xmm0,xmm0
    pcmpeqb     xmm0,xmm1
    pmovmskb    ecx,xmm0
    test        ecx,ecx
    jnz         .3
    movups      [r9],xmm1
    add         rdx,16
    add         r9,16
    jmp         .2
.3:
    movups      [rax],xmm2
    bsf         ecx,ecx
.4:
    inc         ecx
    test        cl,11110000B
    jnz         .16_32
    test        cl,00001000B
    jnz         .08_16
    test        cl,00000100B
    jnz         .04_08
    test        cl,00000010B
    jnz         .02_04
    mov         cl,[rdx]
    mov         [r9],cl
    jmp         .5
.02_04:
    mov         r8w,[rdx]
    mov         dx,[rdx+rcx-2]
    mov         [r9+rcx-2],dx
    mov         [r9],r8w
    jmp         .5
.04_08:
    mov         r8d,[rdx]
    mov         edx,[rdx+rcx-4]
    mov         [r9+rcx-4],edx
    mov         [r9],r8d
    jmp         .5
.08_16:
    mov         r8,[rdx]
    mov         rdx,[rdx+rcx-8]
    mov         [r9],r8
    mov         [r9+rcx-8],rdx
    jmp         .5
.16_32:
    movups      xmm0,[rdx]
    movups      xmm1,[rdx+rcx-16]
    movups      [r9],xmm0
    movups      [r9+rcx-16],xmm1
.5:
else
    push    rsi
    push    rcx
    mov     rsi,rdx
    jmp     .1
.0:
    mov     [rcx],eax
    add     rcx,4
.1:
    mov     eax,[rsi]
    add     rsi,4
    lea     edx,[rax-0x01010101]
    not     eax
    and     edx,eax
    not     eax
    and     edx,0x80808080
    jz      .0
    bt      edx,7
    mov     [rcx],al
    jc      .2
    bt      edx,15
    mov     [rcx+1],ah
    jc      .2
    shr     eax,16
    bt      edx,23
    mov     [rcx+2],al
    jc      .2
    mov     [rcx+3],ah
.2:
    pop     rax
    pop     rsi
endif
    ret
    endp


tstrncpy proc fastcall uses rsi rdi dst:string_t, src:string_t, count:int_t
    mov     rdi,rcx
    mov     rsi,rcx
ifdef _WIN64
    mov     ecx,r8d
else
    mov     ecx,count
endif
.0:
    test    ecx,ecx
    jz      .1
    dec     ecx
    mov     al,[rdx]
    mov     [rdi],al
    add     rdx,1
    add     rdi,1
    test    al,al
    jnz     .0
    rep     stosb
.1:
    mov     rax,rsi
    ret
    endp


tstrcat proc fastcall uses rdi rbx dst:string_t, src:string_t
    mov     rdi,rcx
    mov     rbx,rcx
.0:
    mov     eax,[rdi]
    add     rdi,4
    lea     ecx,[rax-0x01010101]
    not     eax
    and     ecx,eax
    and     ecx,0x80808080
    jz      .0
    bsf     ecx,ecx
    shr     ecx,3
    lea     rdi,[rdi+rcx-4]
    mov     rcx,rdx
    jmp     .2
.1:
    mov     [rdi],eax
    add     rdi,4
.2:
    mov     eax,[rcx]
    add     rcx,4
    lea     edx,[rax-0x01010101]
    not     eax
    and     edx,eax
    not     eax
    and     edx,0x80808080
    jz      .1
    bt      edx,7
    mov     [rdi],al
    jc      .3
    bt      edx,15
    mov     [rdi+1],ah
    jc      .3
    shr     eax,16
    bt      edx,23
    mov     [rdi+2],al
    jc      .3
    mov     [rdi+3],ah
.3:
    mov     rax,rbx
    ret
    endp


tstrcmp proc fastcall a:string_t, b:string_t
    dec     rcx
    dec     rdx
    mov     eax,1
.0:
    test    eax,eax
    jz      .1
    inc     rcx
    inc     rdx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.1:
    ret
    endp

tmemcmp proc fastcall dst:ptr, src:ptr, count:uint_t
ifndef _WIN64
    push    esi
    push    edi
    mov     esi,count
    define  r8 <esi>
    define  r9 <edi>
endif
    sub     rdx,rcx
    cmp     r8,size_t
    jb      .2
    test    cl,size_t-1
    jz      .1
    align   size_t*2
.0:
    mov     al,[rcx]
    cmp     al,[rcx+rdx]
    jne     .D
    inc     rcx
    dec     r8
    test    cl,size_t-1
    jne     .0
.1:
    mov     r9,r8
    shr     r9,size_t/4+1
    jnz     .5
.2:
    test    r8,r8
    jz      .4
.3:
    mov     al,[rcx]
    cmp     al,[rcx+rdx]
    jne     .D
    inc     rcx
    dec     r8
    jnz     .3
.4:
    xor     eax,eax
    jmp     .E
.5:
    shr     r9,2
    jz      .7
.6:
    mov     rax,[rcx]
    cmp     rax,[rcx+rdx]
    jne     .C
    mov     rax,[rcx+size_t]
    cmp     rax,[rcx+rdx+size_t]
    jne     .B
    mov     rax,[rcx+size_t*2]
    cmp     rax,[rcx+rdx+size_t*2]
    jne     .A
    mov     rax,[rcx+size_t*3]
    cmp     rax,[rcx+rdx+size_t*3]
    jne     .9
    add     rcx,size_t*4
    dec     r9
    jnz     .6
    and     r8,size_t*4-1
.7:
    mov     r9,r8
    shr     r9,size_t/4+1
    jz      .2
.8:
    mov     rax,[rcx]
    cmp     rax,[rcx+rdx]
    jne     .C
    add     rcx,size_t
    dec     r9
    jnz     .8
    and     r8,size_t-1
    jmp     .2
.9:
    add     rcx,size_t
.A:
    add     rcx,size_t
.B:
    add     rcx,size_t
.C:
    mov     rcx,[rdx+rcx]
    bswap   rax
    bswap   rcx
    cmp     rax,rcx
.D:
    sbb     rax,rax
    sbb     rax,-1
.E:
ifndef _WIN64
    pop     edi
    pop     esi
endif
    ret
    endp

tmemicmp proc fastcall uses rbx dst:ptr, src:ptr, count:uint_t
ifdef _WIN64
    mov     ebx,r8d
else
    mov     ebx,count
endif
.0:
    test    ebx,ebx
    jz      .1
    dec     ebx
    mov     al,[rcx+rbx]
    cmp     al,[rdx+rbx]
    je      .0
    xor     al,0x20
    cmp     al,[rdx+rbx]
    je      .0
    sbb     ebx,ebx
    sbb     ebx,-1
.1:
    mov     eax,ebx
    ret
    endp


tstricmp proc fastcall a:string_t, b:string_t
    dec     rcx
    dec     rdx
    mov     eax,1
.0:
    test    eax,eax
    jz      .1
    inc     rcx
    inc     rdx
    mov     al,[rcx]
    cmp     al,[rdx]
    je      .0
    xor     al,0x20
    cmp     al,[rdx]
    je      .0
    xor     al,0x20
    cmp     al,[rdx]
    sbb     eax,eax
    sbb     eax,-1
.1:
    ret
    endp


tstrstr proc fastcall uses rsi rdi rbx dst:string_t, src:string_t
    mov     rdi,rcx
    mov     rbx,rdx
    mov     esi,tstrlen(rbx)
    test    eax,eax
    jz      .3
    mov     ecx,tstrlen(rdi)
    test    eax,eax
    jz      .3
    xor     eax,eax
    dec     rsi
.0:
    mov     al,[rbx]
    repne   scasb
    mov     al,0
    jnz     .3
    test    esi,esi
    jz      .2
    cmp     ecx,esi
    jb      .3
    mov     edx,esi
.1:
    mov     al,[rbx+rdx]
    cmp     al,[rdi+rdx-1]
    jne     .0
    dec     edx
    jnz     .1
.2:
    lea     rax,[rdi-1]
.3:
    ret
    endp

    end
