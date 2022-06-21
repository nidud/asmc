; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc

    .data
     DEFINE_LTYPE _ltype

    .code

memxchg proc fastcall uses rdi rbx a:ptr, b:ptr, size:int_t

.32 mov     ebx,size
.64 mov     ebx,r8d
.0:
    mov     rax,[rcx]
    mov     rdi,[rdx]
    mov     [rdx],rax
    mov     [rcx],rdi
    sub     ebx,size_t
    cmp     ebx,size_t
    jae     .0
    ret

memxchg endp


tqsort proc __ccall uses rsi rdi rbx p:ptr, n:int_t, w:int_t, compare:PQSORTCMD

    .32 mov ecx,p
    .32 mov edx,n

    .if ( edx > 1 )

        lea eax,[rdx-1]
        mul w
        mov rsi,rcx
        lea rdi,[rsi+rax]

        .new level:int_t = 0

        .while 1

            mov ecx,w
            lea rax,[rdi+rcx]   ; middle from (hi - lo) / 2
            sub rax,rsi
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif

            .64 sub rsp,0x20
            lea rbx,[rsi+rax]

            .ifsd compare(rsi, rbx) > 0
                memxchg(rsi, rbx, w)
            .endif
            .ifsd compare(rsi, rdi) > 0
                memxchg(rsi, rdi, w)
            .endif
            .ifsd compare(rbx, rdi) > 0
                memxchg(rbx, rdi, w)
            .endif

            .new _si:ptr = rsi
            .new _di:ptr = rdi

            .while 1

                mov ecx,w
                add _si,rcx
                .if _si < rdi

                    .continue .ifsd compare(_si, rbx) <= 0
                .endif

                .while 1

                    mov ecx,w
                    sub _di,rcx

                    .break .if _di <= rbx
                    .break .ifsd compare(_di, rbx) <= 0
                .endw

                mov rcx,_di
                mov rax,_si
                .break .if rcx < rax
                memxchg(rcx, rax, w)

                .if rbx == _di

                    mov rbx,_si
                .endif
            .endw

            mov ecx,w
            add _di,rcx

            .while 1

                mov ecx,w
                sub _di,rcx

                .break .if _di <= rsi
                .break .ifd compare(_di, rbx)
            .endw

            .64 add rsp,0x20

            mov rdx,_si
            mov rax,_di
            sub rax,rsi
            mov rcx,rdi
            sub rcx,rdx

            .ifs rax < rcx

                mov rcx,_di

                .if rdx < rdi

                    push rdx
                    push rdi
                    inc level
                .endif

                .if rsi < rcx

                    mov rdi,rcx
                    .continue
                .endif
            .else
                mov rcx,_di

                .if rsi < rcx

                    push rsi
                    push rcx
                    inc level
                .endif

                .if rdx < rdi

                    mov rsi,rdx
                    .continue
                .endif
            .endif

            .break .if !level

            dec level
            pop rdi
            pop rsi
        .endw
    .endif
    ret

tqsort endp

    option win64:rsp noauto

tstrupr proc fastcall string:string_t

    mov rdx,rcx
    .repeat

        .if ( isllower( [rcx] ) )
            and byte ptr [rcx],not 0x20
        .endif
        inc rcx
    .until !eax
    .return( rdx )

tstrupr endp


tstrstart proc fastcall string:string_t

    ltokstart( rcx )
    ret

tstrstart endp


tmemcpy proc fastcall uses rdi dst:ptr, src:ptr, count:uint_t

    mov     rax,rcx ; -- return value
    xchg    rsi,rdx
.32 mov     ecx,count
.64 mov     ecx,r8d
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

tmemcpy endp


tmemmove proc fastcall uses rsi rdi dst:ptr, src:ptr, count:uint_t

    mov     rax,rcx ; -- return value
    mov     rsi,rdx
.32 mov     ecx,count
.64 mov     ecx,r8d
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

tmemmove endp


tmemset proc fastcall uses rdi dst:ptr, char:int_t, count:uint_t

    mov     rdi,rcx
    mov     al,dl
    mov     rdx,rcx
.32 mov     ecx,count
.64 mov     ecx,r8d
    rep     stosb
    mov     rax,rdx
    ret

tmemset endp

tstrlen proc fastcall uses rdi string:string_t

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
    ret

tstrlen endp


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

tstrchr endp


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

tstrrchr endp


tstrcpy proc fastcall uses rsi rdi dst:string_t, src:string_t

    mov     rdi,rcx
    mov     rsi,rdx
    jmp     .1
.0:
    mov     [rdi],eax
    add     rdi,4
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
    mov     [rdi],al
    jc      .2
    bt      edx,15
    mov     [rdi+1],ah
    jc      .2
    shr     eax,16
    bt      edx,23
    mov     [rdi+2],al
    jc      .2
    mov     [rdi+3],ah
.2:
    mov     rax,rcx
    ret

tstrcpy endp


tstrncpy proc fastcall uses rsi rdi dst:string_t, src:string_t, count:int_t

    mov     rdi,rcx
    mov     rsi,rcx
.32 mov     ecx,count
.64 mov     ecx,r8d
.0:
    test    ecx,ecx
    jz      .2
    dec     ecx
    mov     al,[rdx]
    mov     [rdi],al
    add     rdx,1
    add     rdi,1
    test    al,al
    jnz     .0
.1:
    rep     stosb
.2:
    mov     rax,rsi
    ret

tstrncpy endp


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
    mov     [rdi],eax
    mov     rax,rbx
    ret

tstrcat endp


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

tstrcmp endp


tmemcmp proc fastcall uses rsi rdi dst:ptr, src:ptr, size:uint_t

    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,size
    xor     eax,eax
    repe    cmpsb
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.0:
    ret

tmemcmp endp


tmemicmp proc fastcall uses rbx dst:ptr, src:ptr, size:uint_t

.32 mov     ebx,size
.64 mov     ebx,r8d

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

tmemicmp endp


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

tstricmp endp


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

tstrstr endp


    end

