; OPERATOR.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include expreval.inc
include parser.inc
include reswords.inc
include memalloc.inc
include lqueue.inc
include types.inc
include operator.inc
include fastpass.inc

    .code

GetOperator proc token:token_t

    mov edx,token
    mov ecx,16
    mov eax,[edx].asm_tok.tokpos
    mov eax,[eax]
    .switch al
    .case '+'
        .return T_ADD .if ah != '+'
         add ecx,16
        .return T_INC
    .case '-'
        .return T_SUB .if ah != '-'
         add ecx,16
        .return T_DEC
    .case '='
        .return T_EQU .if ah != '='
         add ecx,16
        .return T_CMP
        .endc
    .case '&'
        .return T_AND .if ah != '~'
         add ecx,16
        .return T_ANDN
    .case '|' : .return T_OR
    .case '^' : .return T_XOR
    .case '*' : .return T_MUL
    .case '/' : .return T_DIV
    .case '<'
        .endc .if ah != '<'
        .return T_SHL
    .case '>'
        .endc .if ah != '>'
        .return T_SHR
    .case '~' : .return T_NOT
    .case '%' : .return T_MOD
    .endsw
    .return 0

GetOperator endp

GetOpType proc uses ebx oper:token_t, string:string_t

    mov ebx,oper
    .if ( GetOperator(ebx) == 0 )
        .return ERROR
    .endif
    add ebx,ecx
    GetResWName(eax, string)
   .return ebx

GetOpType endp

;
; param from .operator
;
; .operator + :byte, :word --> class_add_byte_word
;

    assume ebx:token_t

OperatorParam proc uses esi edi ebx tokenarray:ptr asm_tok, param:string_t

    mov ebx,tokenarray
    mov edi,strcat( param, "_" )
    add edi,strlen(edi)

    .while ( [ebx].token == T_BINARY_OPERATOR && [ebx].tokval == T_PTR )

        GetResWName(T_PTR, edi)
        add edi,strlen(edi)
        add ebx,16
    .endw
    .if ( [ebx].token == T_STYPE )

        GetResWName([ebx].tokval, edi)
       .return
    .endif
    .return .if ( [ebx].token != T_ID )

    mov ecx,[ebx].string_ptr
    mov eax,[ecx]
    or  eax,0x202020
    .if ( eax == 'sba' )

        strcat(edi, "abs")
       .return
    .endif

   .new i:int_t = 0
   .new ti:qualified_type = {0}
   .return .if ( GetQualifiedType( &i, ebx, &ti ) == ERROR )

    .if ( ti.mem_type == MT_PTR )

        .while ( ti.is_ptr )

            GetResWName(T_PTR, edi)
            add edi,strlen(edi)
            dec ti.is_ptr
        .endw
    .endif

    mov esi,ti.symtype
    .if ( esi && [esi].asym.state == SYM_TYPE )
        strcat(edi, [esi].asym.name)
    .endif
    ret

OperatorParam endp

GetArgs proc private uses esi ebx tokenarray:ptr asm_tok

    mov esi,ebx
    .for ( : [ebx].token != T_FINAL : ebx += 16 )

        .if ( [ebx].token == T_OP_BRACKET )
            .for ( ebx += 16, edx = 1 : [ebx].token != T_FINAL : ebx += 16 )
                .if ( [ebx].token == T_OP_BRACKET )
                    inc edx
                .elseif ( [ebx].token == T_CL_BRACKET )
                    dec edx
                    .break .ifz
                .endif
            .endf
        .endif
        .if ( [ebx].token == T_OP_SQ_BRACKET )
            .for ( ebx += 16, edx = 1 : [ebx].token != T_FINAL : ebx += 16 )
                .if ( [ebx].token == T_OP_SQ_BRACKET )
                    inc edx
                .elseif ( [ebx].token == T_CL_SQ_BRACKET )
                    dec edx
                    .break .ifz
                .endif
            .endf
        .endif
        .break .if ( GetOperator( ebx ) )
    .endf
    mov eax,ebx
    sub eax,esi
    shr eax,4
    ret

GetArgs endp

ProcessOperator proc uses esi edi ebx tokenarray:ptr asm_tok

   .new class:ptr asym
   .new name:string_t
   .new isptr:byte = 0
   .new vector:int_t = 0
   .new type:int_t

    .if StoreState == FALSE
        .return NOT_ERROR
    .endif
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif

    mov ebx,tokenarray
    mov name,[ebx].string_ptr

    .if ( SymFind( eax ) )
        .if ( [eax].asym.mem_type == MT_TYPE )
            mov eax,[eax].asym.type
        .endif
        .if ( [eax].asym.mem_type == MT_PTR )
            inc isptr
            mov eax,[eax].asym.target_type
        .endif
    .endif

    .if ( eax && [eax].asym.flag2 & S_CLASS && [eax].asym.flag2 & S_OPERATOR )

        mov class,eax
        movzx edx,[eax].asym.regist[2]
        movzx eax,[eax].asym.regist
        .if ( eax == 0 )
            mov eax,T_EAX
            .if ( ModuleInfo.Ofssize == USE64 )
                mov eax,T_RAX
            .endif
        .endif
        .if ( edx == 0 )
            mov edx,T_DWORD
            .if ( ModuleInfo.Ofssize == USE64 )
                mov edx,T_QWORD
            .endif
        .else
            inc isptr
        .endif
        mov vector,eax
        mov type,edx
    .else
        .return asmerr( 2008, name )
    .endif
    add ebx,16

    .while 1

       .new func[128]:char_t
        lea edi,func

        mov ecx,class
        strcpy( edi, [ecx].asym.name )
        strcat( edi, "_" )
        add edi,strlen( edi )

       .break .if ( GetOpType( ebx, edi ) == ERROR )
        mov ebx,eax

       .new args[128]:char_t
        lea esi,args
        mov byte ptr [esi],0

        .if ( isptr == 0 )
            strcpy( esi, "addr " )
        .endif
        .if ( name )
            strcat( esi, name )
        .else
            strlen(esi)
            add eax,esi
            tsprintf(eax, "%r", vector)
        .endif
        .if ( vector )
            mov name,NULL
        .endif

        .if ( GetArgs( ebx ) )

           .new n:int_t
           .new i:int_t
            mov ecx,ebx
            sub ecx,tokenarray
            shr ecx,4
            mov i,ecx
            add eax,ecx
            mov n,eax
            strcat( esi, ", " )
            mov edi,esi
            mov esi,[ebx].tokpos
            imul ebx,n,16
            add ebx,tokenarray
            add edi,strlen( edi )
            mov ecx,[ebx].tokpos
            sub ecx,esi
            rep movsb
            mov byte ptr [edi],0
            lea edi,func

            .while ( i < n )

               .new opnd:expr
               .new isaddr:int_t = 0

                strcat( edi, "_" )
                imul ecx,i,16
                add ecx,tokenarray
                mov eax,[ecx].asm_tok.string_ptr
                .if ( eax )
                    mov eax,[eax]
                .endif
                .if ( ax == 'L' && [ecx+16].asm_tok.token == T_STRING )
                    strcat( edi, "ptrword" )
                    add i,2
                .elseif ( [ecx].asm_tok.hll_flags & T_HLL_PROC )
                    .if ( ModuleInfo.Ofssize == USE64 )
                        strcat( edi, "qword" )
                    .else
                        strcat( edi, "dword" )
                    .endif
                    mov i,n
                .else

                    .if ( [ecx].asm_tok.token == T_RES_ID &&
                          [ecx].asm_tok.tokval == T_ADDR )
                        inc i
                        inc isaddr
                    .endif
                    .return .if ( EvalOperand( &i, tokenarray, n, &opnd, 0 ) == ERROR )

                    .if ( opnd.kind == EXPR_CONST )

                        mov ecx,opnd.quoted_string
                        .if ( ecx && [ecx].asm_tok.token == T_STRING )
                            .if ( ModuleInfo.xflag & OPT_WSTRING )
                                strcat( edi, "ptrword" )
                            .else
                                strcat( edi, "ptrsbyte" )
                            .endif
                        .else
                            strcat( edi, "abs" )
                        .endif
                    .else
                        GetType( edi, &opnd, edi, isaddr )
                    .endif
                .endif
                imul ecx,i,16
                add ecx,tokenarray
                .if ( [ecx].asm_tok.token == T_COMMA )
                    inc i
                .endif
            .endw
            AddLineQueueX( "%s(%s)", &func, &args )
        .endif
    .endw
    .if ( ModuleInfo.line_queue.head )
        InsertLineQueue()
    .endif
    .return NOT_ERROR

ProcessOperator endp

    assume esi:expr_t
    assume ebx:ptr opinfo

EvalOperator proc uses esi edi ebx opnd1:expr_t, opnd2:expr_t, oper:token_t

    ;
    ; first argument has to be class::operator
    ;
    mov edx,ModuleInfo.tokenarray
    .if ( [edx].asm_tok.token != T_ID ||
          [edx+16].asm_tok.token != T_DIRECTIVE ||
          [edx+16].asm_tok.tokval != T_EQU )
        .return ERROR
    .endif
    .if ( SymFind( [edx].asm_tok.string_ptr ) == NULL )
        .return ERROR
    .endif
    .if ( [eax].asym.mem_type == MT_TYPE )
        mov eax,[eax].asym.type
    .endif
    .if ( [eax].asym.mem_type == MT_PTR )
        mov eax,[eax].asym.target_type
    .endif
    .if ( !eax || !( [eax].asym.flag2 & S_OPERATOR ) )
        .return ERROR
    .endif


    mov esi,opnd1
    mov ecx,[esi].type
    mov eax,[esi].sym

    .if ( !ecx && eax )
        .if ( [eax].asym.mem_type == MT_TYPE )
            mov eax,[eax].asym.type
        .endif
        .if ( [eax].asym.mem_type == MT_PTR )
            mov eax,[eax].asym.target_type
        .endif
        mov ecx,eax
    .endif
    .if ( !ecx || !( [ecx].asym.flag2 & S_OPERATOR ) )
        .if ( [esi].kind != EXPR_REG )
            .return ERROR
        .endif
    .endif
    mov [esi].type,ecx
    mov ebx,LclAlloc( opinfo )
   .return ERROR .if ( eax == NULL )

    mov [ebx].next,NULL
    mov [ebx].type,GetOperator(oper)
   .return ERROR .if ( eax == 0 )

    mov edx,opnd2
    mov eax,[edx].expr.op
    .if ( eax && [esi].op == NULL )

        mov [esi].op,eax
        mov [edx].expr.op,NULL
    .endif

    lea edi,[ebx].op1
    mov ecx,expr
    rep movsb
    mov esi,edx
    mov ecx,expr
    rep movsb
    mov esi,opnd1
    mov eax,ebx
    .if ( [esi].op )
        mov ebx,[esi].op
        .while ( [ebx].next )
            mov ebx,[ebx].next
        .endw
        mov [ebx].next,eax
    .else
        mov [esi].op,eax
    .endif
    .return NOT_ERROR

EvalOperator endp


GetArgs2 proc private uses esi opnd:ptr expr

    mov esi,opnd
    .switch ( [esi].expr.kind )
    .case EXPR_FLOAT
        .endc
    .case EXPR_CONST
        tsprintf(edi, "%d", [esi].expr.value)
        .endc
    .case EXPR_ADDR
        mov ecx,[esi].expr.sym
        .if ( ecx )
            strcpy(edi, [ecx].asym.name)
        .endif
        .endc
    .case EXPR_REG
        mov edx,[esi].expr.base_reg
        tsprintf(edi, "%r", [edx].asm_tok.tokval)
        .endc
    .endsw
    ret

GetArgs2 endp

ParseOperator proc uses esi edi ebx tokenarray:token_t, op:ptr opinfo

   .new buffer[256]:char_t
   .new level:int_t = 0
   .new name:string_t
   .new vector:int_t
   .new type:int_t

    mov ebx,op
    .while ( [ebx].next )
        mov ebx,[ebx].next
    .endw
    mov level,eax
    mov ecx,[ebx].op1.type
    mov name,[ecx].asym.name

    movzx eax,[ecx].asym.regist
    movzx edx,[ecx].asym.regist[2]
    .if ( eax == 0 )
        mov eax,T_EAX
        .if ( ModuleInfo.Ofssize == USE64 )
            mov eax,T_RAX
        .endif
    .endif
    .if ( edx == 0 )
        mov edx,T_DWORD
        .if ( ModuleInfo.Ofssize == USE64 )
            mov edx,T_QWORD
        .endif
    .endif
    mov vector,eax
    mov type,edx

    .for ( ebx = op : ebx : ebx = [ebx].next, level++ )

        lea edi,buffer
        tsprintf( edi, "%s_%r_", name, [ebx].type )

        .switch ( [ebx].op2.kind )
        .case EXPR_FLOAT
        .case EXPR_CONST
            mov ecx,[ebx].op2.quoted_string
            .if ( ecx && [ecx].asm_tok.token == T_STRING )
                .if ( ModuleInfo.xflag & OPT_WSTRING )
                    strcat( edi, "ptrword" )
                .else
                    strcat( edi, "ptrsbyte" )
                .endif
            .else
                strcat( edi, "abs" )
            .endif
            .endc
        .default
            GetType( edi, &[ebx].op2, edi, 0 )
            .endc
        .endsw
        strcat( edi, "(" )
        add edi,strlen(edi)

        mov ecx,[ebx].op1.label_tok
        .if ( ecx == NULL )
            mov ecx,[ebx].op1.base_reg
        .endif
        mov edx,[ebx].op2.label_tok
        .if ( edx == NULL )
            mov edx,[ebx].op2.base_reg
        .endif
        .if ( ecx && [ecx].asm_tok.hll_flags & T_EXPR )

            .if ( edx )
                or [edx].asm_tok.hll_flags,T_EXPR
            .endif
            add edi,tsprintf( edi, "%r, ", vector )
            GetArgs2( &[ebx].op2 )

        .elseif ( edx && [edx].asm_tok.hll_flags & T_EXPR )

            .if ( ecx )
                or [ecx].asm_tok.hll_flags,T_EXPR
            .endif
            GetArgs2( &[ebx].op1 )
            add edi,strlen( edi )
            tsprintf( edi, ", %r", vector )

        .else

            .if ( edx )
                or [edx].asm_tok.hll_flags,T_EXPR
            .endif
            .if ( ecx )
                or [ecx].asm_tok.hll_flags,T_EXPR
            .endif

            GetArgs2(&[ebx].op1)
            strcat( edi, ", " )
            add edi,strlen(edi)
            GetArgs2(&[ebx].op2)
        .endif
        strcat( edi, ")" )
        AddLineQueue( &buffer )
    .endf
    .if ( ModuleInfo.line_queue.head )
        RunLineQueue()
    .endif
    .return NOT_ERROR

ParseOperator endp

    end

