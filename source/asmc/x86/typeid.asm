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

    assume ebx:ptr expr

GetType proc uses esi edi ebx buffer:string_t, opnd:ptr expr,
        string:string_t, is_addr:int_t

    mov edi,buffer
    .if ( string )
        .if ( edi != string )
            strcpy(edi, string)
        .endif
        add edi,strlen(edi)
    .else
        mov byte ptr [edi],0
    .endif

    mov ebx,opnd
    mov eax,[ebx].kind

    .if ( eax == EXPR_CONST || eax == EXPR_FLOAT )

        lea edx,@CStr("flt")
        .if ( eax == EXPR_CONST )
            lea edx,@CStr("imm")
        .endif
        strcpy( edi, edx )
       .return 1
    .endif

    .if ( eax == EXPR_REG && !( [ebx].flags & E_INDIRECT ) )

        mov ecx,[ebx].base_reg
        SizeFromRegister( [ecx].asm_tok.tokval )
        xor ecx,ecx
        .if ( eax >= 16 )
            .switch pascal eax
            .case 16: mov ecx,T_OWORD
            .case 32: mov ecx,T_YWORD
            .case 64: mov ecx,T_ZWORD
            .endsw
        .elseif ( [rbx].mem_type != MT_EMPTY && [rbx].mem_type & MT_SIGNED )
            .switch pascal eax
            .case  1: mov ecx,T_SBYTE
            .case  2: mov ecx,T_SWORD
            .case  4: mov ecx,T_SDWORD
            .case  8: mov ecx,T_SQWORD
            .endsw
        .else
            .switch pascal eax
            .case  1: mov ecx,T_BYTE
            .case  2: mov ecx,T_WORD
            .case  4: mov ecx,T_DWORD
            .case  8: mov ecx,T_QWORD
            .endsw
        .endif
         GetResWName(ecx, edi)
        .return 1
    .endif

    .if ( is_addr )

        GetResWName(T_PTR, edi)
        add edi,3
    .elseif ( eax != EXPR_ADDR && eax != EXPR_REG )
        .return 0
    .endif

    mov edx,[ebx].sym
    mov esi,[ebx].type
    .if [ebx].mbr
        mov edx,[ebx].mbr
    .endif
    .if ( !edx || [edx].asym.state == SYM_UNDEFINED )

        GetResWName(T_PTR, edi)
       .return 1
    .endif
    assume ebx:ptr asym
    mov ebx,edx

    .if ( [ebx].mem_type == MT_TYPE && [ebx].type )
        mov ebx,[ebx].type
    .endif
    .if ( [ebx].target_type &&
          ( [ebx].mem_type == MT_PTR || [ebx].ptr_memtype == MT_TYPE ) )

        .if ( [ebx].mem_type == MT_PTR )

            GetResWName(T_PTR, edi)
            add edi,3
            .if ( [ebx].is_ptr == 2 )
                GetResWName(T_PTR, edi)
                add edi,3
            .endif
        .endif
        mov ebx,[ebx].asym.target_type
    .endif

    .if ( [ebx].state == SYM_TYPE && [ebx].typekind == TYPE_STRUCT )

        strcpy(edi, [ebx].name )
       .return 1
    .endif

    .if ( esi )
        .if ( [esi].asym.state == SYM_TYPE && [esi].asym.typekind == TYPE_STRUCT )

            strcpy(edi, [esi].asym.name)
           .return 1
        .endif
    .endif
    mov al,[ebx].state
    .if ( al == SYM_INTERNAL ||
          al == SYM_EXTERNAL ||
          al == SYM_STACK ||
          al == SYM_STRUCT_FIELD ||
          al == SYM_TYPE )

        mov cl,[ebx].mem_type
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
            GetResWName(T_PTR, edi)
            add edi,3
            mov cl,[ebx].mem_type
            .if ( [ebx].is_ptr == 1 && cl != [ebx].ptr_memtype )
                .if ( [ebx].ptr_memtype != MT_EMPTY )
                    mov cl,[ebx].ptr_memtype
                    .gotosw
                .endif
            .elseif ( [ebx].is_ptr == 2 )
                GetResWName(T_PTR, edi)
            .endif
            .return 1
        .default
            .return 1
        .endsw
        GetResWName(eax, edi)
       .return 1
    .endif
    .return 0

GetType endp

    assume ebx:ptr asm_tok

GetTypeId proc uses esi edi ebx buffer:string_t, tokenarray:token_t

  local i:int_t
  local opnd:expr
  local id[256]:char_t

    mov ebx,tokenarray

    ; find first instance of macro in line

    .while [ebx].token != T_FINAL
        .if [ebx].token == T_ID
            .if !tstricmp([ebx].string_ptr, "typeid")

                mov eax,[ebx].string_ptr
                mov byte ptr [eax],'?'
                .break
            .endif
        .endif
        add ebx,16
    .endw
    .if [ebx].token == T_FINAL && [ebx+16].token == T_OP_BRACKET
        add ebx,16
    .elseif [ebx].token != T_FINAL
        add ebx,16
    .else
        mov ebx,tokenarray
    .endif
    .return 0 .if [ebx].token != T_OP_BRACKET

    add ebx,16
    mov id,0
    .if [ebx+16].token == T_COMMA
        strcpy( &id, [ebx].string_ptr )
        add ebx,32
    .endif

    xor esi,esi
    .if [ebx].token == T_RES_ID && [ebx].tokval == T_ADDR
        add ebx,16
        inc esi
    .endif

    mov eax,ebx
    sub eax,tokenarray
    shr eax,4
    mov ecx,eax
    mov i,eax

    .for ( eax = 0, edx = 1 : [ebx].token != T_FINAL : ebx += 16, ecx++ )
        .switch [ebx].token
        .case T_OP_BRACKET
            inc edx
            .if ( eax == 0 && [rbx-asm_tok].token == T_ID )
                mov eax,ecx
            .endif
            .endc
        .case T_CL_BRACKET
            dec edx
            .endc .ifnz
            .break
        .endsw
    .endf
    mov edi,ecx
    .if ( eax )
        mov ecx,eax
        .return 0 .ifd ( EvalOperand( &i, tokenarray, ecx, &opnd, 0 ) == ERROR )
        xor eax,eax
        .if ( opnd.mem_type == MT_NEAR )
            inc eax
        .endif
    .endif
    .if ( !eax )
        .return 0 .ifd ( EvalOperand( &i, tokenarray, edi, &opnd, 0 ) == ERROR )
    .endif
    xor ecx,ecx
    .if ( id )
        lea ecx,id
    .endif
    GetType(buffer, &opnd, ecx, esi)
    ret

GetTypeId endp

    end
