; _LTYPE.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc

    .data
     DEFINE_LTYPE _ltype

    .code

exchange proc fastcall a:ptr, b:ptr, size:int_t
    mov     rax,[rcx]
    xchg    rax,[rdx]
    mov     [rcx],rax
ifdef _WIN64
    cmp     r8d,8
else
    cmp     size,4
endif
    je      .0
    mov     rax,[rcx+size_t]
    xchg    rax,[rdx+size_t]
    mov     [rcx+size_t],rax
.0:
    ret

exchange endp


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

tqsort endp


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
ifdef _WIN64
    mov     ecx,r8d
else
    mov     ecx,count
endif
    mov     rdi,rax
    rep     movsb
    mov     rsi,rdx
    ret

tmemcpy endp


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

tmemmove endp


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

