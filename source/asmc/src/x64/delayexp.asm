include libc.inc
include asmc.inc

    .code

    assume rcx:ptr asmtok
B   equ <SBYTE PTR>

DelayExpand proc tokenarray

        xor     eax,eax
        test    [rcx].hll_flags,T_HLL_DELAY
        jz      toend
        test    ModuleInfo.aflag,_AF_ON
        jz      toend
        cmp     Parse_Pass,PASS_1
        jne     toend
        cmp     eax,NoLineStore
        jne     toend

        xor     edx,edx

find_macro:
        cmp     eax,ModuleInfo.token_count
        jge     delayed
        test    [rcx+rdx].hll_flags,T_HLL_MACRO
        lea     edx,[edx+16]
        lea     eax,[eax+1]
        jz      find_macro
        cmp     [rcx+rdx].token,T_OP_BRACKET
        jne     find_macro

        mov     r8d,1   ; one open bracket found

macro_loop:

        lea     edx,[edx+16]
        lea     eax,[eax+1]
        cmp     eax,ModuleInfo.token_count
        jge     delayed

        .switch [rcx+rdx].token
          .case T_OP_BRACKET
                add     r8d,1
                jmp     macro_loop
          .case T_CL_BRACKET
                sub     r8d,1
                jz      find_macro
                jmp     macro_loop
          .case T_STRING
                mov rax,[rcx+rdx].string_ptr
                .if B[rax] != '<'
                        mov rax,[rcx+rdx].tokpos
                        .if B[rax] == '<'
                                asmerr( 7008, rax )
                                jmp nodelay
                        .endif
                .endif
                mov     eax,edx
                shr     eax,4
                jmp     macro_loop
        .endsw
        jmp     macro_loop

delayed:
        or      [rcx].hll_flags,T_HLL_DELAYED
        mov     eax,1
        ret
nodelay:
        xor     eax,eax
toend:
        ret
DelayExpand ENDP

        END
