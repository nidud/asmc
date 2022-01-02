; TYPEID.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include expreval.inc
include parser.inc
include reswords.inc
include lqueue.inc

    .code

    assume rbx:ptr expr

GetType proc fastcall uses rsi rdi rbx buffer:string_t, opnd:ptr expr,
        string:string_t, is_addr:int_t

    mov rdi,rcx
    mov rbx,rdx

    .if ( r8 )
        .if ( rdi != r8 )
            strcpy(rdi, r8)
        .endif
        add rdi,tstrlen(rdi)
    .else
        mov byte ptr [rdi],0
    .endif


    mov eax,[rbx].kind
    .if ( eax == EXPR_CONST || eax == EXPR_FLOAT )

        lea rdx,@CStr("flt")
        .if ( eax == EXPR_CONST )
            lea rdx,@CStr("imm")
        .endif
        strcpy( rdi, rdx )
       .return 1
    .endif

    .if ( eax == EXPR_REG && !( [rbx].flags & E_INDIRECT ) )

        mov rcx,[rbx].base_reg
        SizeFromRegister( [rcx].asm_tok.tokval )
        xor ecx,ecx
        .switch pascal eax
        .case  1: mov ecx,T_BYTE
        .case  2: mov ecx,T_WORD
        .case  4: mov ecx,T_DWORD
        .case  8: mov ecx,T_QWORD
        .case 16: mov ecx,T_OWORD
        .case 32: mov ecx,T_YWORD
        .case 64: mov ecx,T_ZWORD
        .endsw
         GetResWName(ecx, rdi)
        .return 1
    .endif

    .if ( is_addr )

        GetResWName(T_PTR, rdi)
        add rdi,3
    .elseif ( eax != EXPR_ADDR && eax != EXPR_REG )
        .return 0
    .endif

    mov rdx,[rbx].sym
    mov rsi,[rbx].type
    .if [rbx].mbr
        mov rdx,[rbx].mbr
    .endif
    .if ( !rdx || [rdx].asym.state == SYM_UNDEFINED )

        GetResWName(T_PTR, rdi)
       .return 1
    .endif
    assume rbx:ptr asym
    mov rbx,rdx

    .if ( [rbx].mem_type == MT_TYPE && [rbx].type )
        mov rbx,[rbx].type
    .endif
    .if ( [rbx].target_type && \
          ( [rbx].mem_type == MT_PTR || [rbx].ptr_memtype == MT_TYPE ) )

        .if ( [rbx].mem_type == MT_PTR )

            GetResWName(T_PTR, rdi)
            add rdi,3
            .if ( [rbx].is_ptr == 2 )
                GetResWName(T_PTR, rdi)
                add rdi,3
            .endif
        .endif
        mov rbx,[rbx].asym.target_type
    .endif

    .if ( [rbx].state == SYM_TYPE && [rbx].typekind == TYPE_STRUCT )

        strcpy(rdi, [rbx].name )
       .return 1
    .endif

    .if ( rsi )
        .if ( [rsi].asym.state == SYM_TYPE && [rsi].asym.typekind == TYPE_STRUCT )

            strcpy(rdi, [rsi].asym.name)
           .return 1
        .endif
    .endif

    .if ( [rbx].state == SYM_INTERNAL || \
          [rbx].state == SYM_STACK || \
          [rbx].state == SYM_STRUCT_FIELD || \
          [rbx].state == SYM_TYPE )

        mov cl,[rbx].mem_type
        .switch pascal cl
        .case MT_BYTE    : mov eax,T_BYTE
        .case MT_SBYTE   : mov eax,T_SBYTE
        .case MT_WORD    : mov eax,T_WORD
        .case MT_SWORD   : mov eax,T_SWORD
        .case MT_REAL2   : mov eax,T_REAL2
        .case MT_DWORD   : mov eax,T_DWORD
        .case MT_SDWORD  : mov eax,T_SDWORD
        .case MT_REAL4   : mov eax,T_REAL4
        .case MT_FWORD   : mov eax,T_FWORD
        .case MT_QWORD   : mov eax,T_QWORD
        .case MT_SQWORD  : mov eax,T_SQWORD
        .case MT_REAL8   : mov eax,T_REAL8
        .case MT_TBYTE   : mov eax,T_TBYTE
        .case MT_REAL10  : mov eax,T_REAL10
        .case MT_OWORD   : mov eax,T_OWORD
        .case MT_REAL16  : mov eax,T_REAL16
        .case MT_YWORD   : mov eax,T_YWORD
        .case MT_ZWORD   : mov eax,T_ZWORD
        .case MT_PROC    : mov eax,T_PROC
        .case MT_NEAR    : mov eax,T_NEAR
        .case MT_FAR     : mov eax,T_FAR
        .case MT_PTR
            GetResWName(T_PTR, rdi)
            add rdi,3
            mov cl,[rbx].mem_type
            .if ( [rbx].is_ptr == 1 && cl != [rbx].ptr_memtype )
                .if ( [rbx].ptr_memtype != MT_EMPTY )
                    mov cl,[rbx].ptr_memtype
                    .gotosw
                .endif
            .elseif ( [rbx].is_ptr == 2 )
                GetResWName(T_PTR, rdi)
            .endif
            .return 1
        .default
            .return 1
        .endsw
        GetResWName(eax, rdi)
       .return 1
    .endif
    .return 0

GetType endp

    assume rbx:ptr asm_tok

GetTypeId proc fastcall uses rsi rdi rbx buffer:string_t, tokenarray:token_t

  local i:int_t
  local opnd:expr
  local id[256]:char_t

    mov rbx,rdx

    ; find first instance of macro in line

    .while [rbx].token != T_FINAL
        .if [rbx].token == T_ID
            .ifd !tstricmp([rbx].string_ptr, "typeid")

                mov rax,[rbx].string_ptr
                mov byte ptr [rax],'?'
                .break
            .endif
        .endif
        add rbx,asm_tok
    .endw
    .if [rbx].token == T_FINAL && [rbx+asm_tok].token == T_OP_BRACKET
        add rbx,asm_tok
    .elseif [rbx].token != T_FINAL
        add rbx,asm_tok
    .else
        mov rbx,tokenarray
    .endif
    .return 0 .if [rbx].token != T_OP_BRACKET

    add rbx,asm_tok
    mov id,0
    .if [rbx+asm_tok].token == T_COMMA
        strcpy( &id, [rbx].string_ptr )
        add rbx,2*asm_tok
    .endif

    xor esi,esi
    .if [rbx].token == T_RES_ID && [rbx].tokval == T_ADDR
        add rbx,asm_tok
        inc esi
    .endif

    mov rax,rbx
    sub rax,tokenarray
    mov ecx,asm_tok
    xor edx,edx
    div ecx
    mov ecx,eax
    mov i,eax

    .for edx = 1 : [rbx].token != T_FINAL : rbx += asm_tok, ecx++
        .switch [rbx].token
        .case T_OP_BRACKET
            inc edx
            .endc
        .case T_CL_BRACKET
            dec edx
            .endc .ifnz
            .break
        .endsw
    .endf
    .return 0 .ifd ( EvalOperand( &i, tokenarray, ecx, &opnd, 0 ) == ERROR )

    xor ecx,ecx
    .if ( id )
        lea rcx,id
    .endif
    GetType(buffer, &opnd, rcx, esi)
    ret

GetTypeId endp

    end
