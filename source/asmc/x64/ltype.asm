; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc

    .data
     DEFINE_LTYPE _ltype

    .code

    option dotname
    option win64:rsp noauto nosave

tstrupr proc fastcall string:string_t

    mov     rax,rcx
.0:
    mov     dl,[rcx]
    test    dl,dl
    jz      .1
    inc     rcx
    cmp     dl,'a'
    jb      .0
    cmp     dl,'z'
    ja      .0
    and     byte ptr [rcx-1],not 0x20
    jmp     .0
.1:
    ret

tstrupr endp

tstrstart proc watcall string:string_t

    movzx   ecx,byte ptr [rax]
    lea     rdx,_ltype
.0:
    test    byte ptr [rdx+rcx+1],_SPACE
    jz      .1
    inc     rax
    mov     cl,[rax]
    jmp     .0
.1:
    ret

tstrstart endp

tstrstartr proc watcall string:string_t

    movzx   ecx,byte ptr [rax]
    lea     rdx,_ltype
.0:
    test    byte ptr[rdx+rcx+1],_SPACE
    jz      .1
    dec     rax
    mov     cl,[rax]
    jmp     .0
.1:
    ret

tstrstartr endp

tmemcpy proc fastcall uses rdi dst:ptr, src:ptr, z:uint_t

    mov     rax,rcx ; -- return value
    xchg    rsi,rdx
    mov     ecx,r8d
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

tmemcpy endp

tmemmove proc fastcall uses rsi rdi dst:ptr, src:ptr, z:uint_t

    mov     rax,rcx ; -- return value
    mov     rsi,rdx
    mov     ecx,r8d
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
    mov     ecx,r8d
    mov     r8,rdi
    rep     stosb
    mov     rax,r8
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
    mov     dh,[rcx]
    test    dh,dh
    jz      .1
    cmp     dh,dl
    cmovz   rax,rcx
    lea     rcx,[rcx+1]
    jnz     .0
.1:
    ret

tstrchr endp

tstrrchr proc fastcall string:string_t, char:int_t

    xor     eax,eax
.0:
    mov     dh,[rcx]
    test    dh,dh
    jz      .1
    cmp     dh,dl
    cmovz   rax,rcx
    add     rcx,1
    jmp     .0
.1:
    ret

tstrrchr endp

tstrcpy proc fastcall dst:string_t, src:string_t

    mov     r9,rcx
    mov     al,[rdx]
    mov     [rcx],al
    test    al,al
    jz      .2

    mov     al,[rdx+1]
    mov     [rcx+1],al
    test    al,al
    jz      .2

    mov     al,[rdx+2]
    mov     [rcx+2],al
    test    al,al
    jz      .2

    mov     al,[rdx+3]
    mov     [rcx+3],al
    test    al,al
    jz      .2

    mov     al,[rdx+4]
    mov     [rcx+4],al
    test    al,al
    jz      .2

    mov     al,[rdx+5]
    mov     [rcx+5],al
    test    al,al
    jz      .2

    mov     al,[rdx+6]
    mov     [rcx+6],al
    test    al,al
    jz      .2

    mov     al,[rdx+7]
    mov     [rcx+7],al
    test    al,al
    jz      .2

    add     rdx,8
    add     rcx,8
    mov     r10,0x8080808080808080
    mov     r11,0x0101010101010101
.0:
    mov     rax,[rdx]
    mov     r8,rax
    sub     r8,r11
    not     rax
    and     r8,rax
    not     rax
    and     r8,r10
    jnz     .1
    mov     [rcx],rax
    add     rcx,8
    add     rdx,8
    jmp     .0
.1:
    mov     [rcx],al
    test    al,al
    jz      .2

    mov     [rcx+1],ah
    test    ah,ah
    jz      .2

    shr     rax,16
    mov     [rcx+2],al
    test    al,al
    jz      .2

    mov     [rcx+3],ah
    test    ah,ah
    jz      .2

    shr     rax,16
    add     rcx,4
    jmp     .1
.2:
    mov     rax,r9
    ret

tstrcpy endp

tstrncpy proc fastcall dst:string_t, src:string_t, count:int_t

    mov     r10,rdi
    mov     rdi,rcx
    mov     r11,rcx
    mov     ecx,r8d
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
    mov     rdi,r10
    mov     rax,r11
    ret

tstrncpy endp

tstrcat proc fastcall dst:string_t, src:string_t

    mov     r8,rcx
    xor     eax,eax
.0:
    cmp     al,[rcx]
    je      .1
    add     rcx,1
    jmp     .0
.1:
    cmp     ah,[rdx]
    je      .2
    mov     al,[rdx]
    mov     [rcx],al
    add     rdx,1
    add     rcx,1
    jmp     .1
.2:
    mov     [rcx],ah
    mov     rax,r8
    ret

tstrcat endp

tstrcmp proc fastcall a:string_t, b:string_t

    mov     eax,1
.0:
    test    al,al
    jz      .1
    mov     al,[rcx]
    inc     rdx
    inc     rcx
    cmp     al,[rdx-1]
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.1:
    ret

tstrcmp endp

tmemcmp proc fastcall uses rsi rdi dst:ptr, src:ptr, size:uint_t

    mov     rdi,rcx
    mov     rsi,rdx
    mov     ecx,r8d
    xor     eax,eax
    repe    cmpsb
    je      .0
    sbb     eax,eax
    sbb     eax,-1
.0:
    ret

tmemcmp endp

tmemicmp proc fastcall dst:ptr, src:ptr, size:uint_t
.0:
    test    r8d,r8d
    jz      .1
    dec     r8d
    mov     al,[rcx+r8]
    cmp     al,[rdx+r8]
    je      .0
    mov     ah,al
    mov     al,[rdx+r8]
    or      eax,0x2020
    cmp     ah,al
    je      .0
    sbb     r8d,r8d
    sbb     r8d,-1
.1:
    mov     eax,r8d
    ret

tmemicmp endp

tstricmp proc fastcall a:string_t, b:string_t

    mov     eax,1
    xor     r8d,r8d
.0:
    test    al,al
    jz      .1
    mov     al,[rcx]
    cmp     al,[rdx]
    lea     rdx,[rdx+1]
    lea     rcx,[rcx+1]
    je      .0
    mov     ah,[rdx-1]
    or      eax,0x2020
    cmp     al,ah
    je      .0
    sbb     r8d,r8d
    sbb     r8d,-1
.1:
    mov     eax,r8d
    ret

tstricmp endp

tstrstr proc fastcall uses rsi rdi rbx dst:string_t, src:string_t

    mov rdi,rcx
    mov rbx,rdx

    .if tstrlen(rbx)

        mov rsi,rax
        .if tstrlen(rdi)

            mov rcx,rax
            xor eax,eax
            dec rsi

            .repeat
                mov al,[rbx]
                repne scasb
                mov al,0
                .break .ifnz
                .if rsi
                    .break .if rcx < rsi
                    mov rdx,rsi
                    .repeat
                        mov al,[rbx+rdx]
                        .continue(01) .if al != [rdi+rdx-1]
                        dec rdx
                    .untilz
                .endif
                lea rax,[rdi-1]
            .until 1
        .endif
    .endif
    ret

tstrstr endp

    option win64:rbp auto save

memxchg proto fastcall :ptr, :ptr, :int_t {

    .repeat
        mov rax,[rcx]
        mov r10,[rdx]
        mov [rdx],rax
        mov [rcx],r10
        sub r8d,8
    .until r8d < 8
    }

tqsort proc fastcall uses rsi rdi rbx r12 r13 r14 r15 p:ptr, n:int_t, w:int_t, compare:PQSORTCMD

    .if edx > 1

        lea eax,[rdx-1]
        mul r8d
        mov rsi,rcx
        lea rdi,[rsi+rax]
        xor r12,r12
        mov r13d,r8d

        .while 1

            mov ecx,r13d
            lea rax,[rdi+rcx]   ; middle from (hi - lo) / 2
            sub rax,rsi
            .ifnz
                xor rdx,rdx
                div rcx
                shr rax,1
                mul rcx
            .endif

            sub rsp,0x20

            lea rbx,[rsi+rax]

            .ifsd compare(rsi, rbx) > 0
                memxchg(rsi, rbx, r13d)
            .endif
            .ifsd compare(rsi, rdi) > 0
                memxchg(rsi, rdi, r13d)
            .endif
            .ifsd compare(rbx, rdi) > 0
                memxchg(rbx, rdi, r13d)
            .endif

            mov r14,rsi
            mov r15,rdi

            .while 1

                add r14,r13
                .if r14 < rdi

                    .continue .ifsd compare(r14, rbx) <= 0
                .endif

                .while 1

                    sub r15,r13

                    .break .if r15 <= rbx
                    .break .ifsd compare(r15, rbx) <= 0
                .endw

                mov rcx,r15
                mov rax,r14
                .break .if rcx < rax
                memxchg(rcx, rax, r13d)

                .if rbx == r15

                    mov rbx,r14
                .endif
            .endw

            add r15,r13

            .while 1

                sub r15,r13

                .break .if r15 <= rsi
                .break .ifd compare(r15, rbx)
            .endw

            add rsp,0x20

            mov rdx,r14
            mov rax,r15
            sub rax,rsi
            mov rcx,rdi
            sub rcx,rdx

            .ifs rax < rcx

                mov rcx,r15

                .if rdx < rdi

                    push rdx
                    push rdi
                    inc r12d
                .endif

                .if rsi < rcx

                    mov rdi,rcx
                    .continue
                .endif
            .else
                mov rcx,r15

                .if rsi < rcx

                    push rsi
                    push rcx
                    inc r12d
                .endif

                .if rdx < rdi

                    mov rsi,rdx
                    .continue
                .endif
            .endif

            .break .if !r12d

            dec r12d
            pop rdi
            pop rsi
        .endw
    .endif
    ret

tqsort endp

    end

