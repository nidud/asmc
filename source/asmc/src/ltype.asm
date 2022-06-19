; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc

    .data
     DEFINE_LTYPE _ltype

    .code

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
    mov     ecx,count
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

tmemcpy endp


tmemmove proc fastcall uses rsi rdi dst:ptr, src:ptr, count:uint_t

    mov     rax,rcx ; -- return value
    mov     rsi,rdx
    mov     ecx,count
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
    mov     ecx,count
    rep     stosb
    mov     rax,rdx
    ret

tmemset endp


tstrlen proc fastcall uses rdi string:string_t

    mov     rdi,rcx
    mov     ecx,-1
    xor     eax,eax
    repnz   scasb
    not     ecx
    dec     ecx
    mov     eax,ecx
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


tstrcpy proc fastcall uses rbx dst:string_t, src:string_t

    xor     ebx,ebx
.0:
    mov     al,[rdx+rbx]
    mov     [rcx+rbx],al
    inc     rbx
    test    al,al
    jnz     .0
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


tstrcat proc fastcall uses rbx dst:string_t, src:string_t

    mov     rbx,rcx
    xor     eax,eax
.0:
    cmp     al,[rbx]
    je      .1
    inc     rbx
    jmp     .0
.1:
    mov     al,[rdx]
    mov     [rbx],al
    inc     rbx
    inc     rdx
    test    al,al
    jnz     .1
.2:
    mov     rax,rcx
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

    end

