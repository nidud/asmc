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

GetOperator proc __ccall token:token_t

    ldr rdx,token
    mov ecx,asm_tok
    mov rax,[rdx].asm_tok.tokpos
    mov eax,[rax]
    .switch al
    .case '+'
        .return T_ADD .if ah != '+'
         add ecx,asm_tok
        .return T_INC
    .case '-'
        .return T_SUB .if ah != '-'
         add ecx,asm_tok
        .return T_DEC
    .case '='
        .return T_EQU .if ah != '='
         add ecx,asm_tok
        .return T_CMP
        .endc
    .case '&'
        .return T_AND .if ah != '~'
         add ecx,asm_tok
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


GetOpType proc __ccall uses rbx oper:token_t, string:string_t

    ldr rbx,oper
    .if ( GetOperator(rbx) == 0 )
        .return ERROR
    .endif
    add rbx,rcx
    GetResWName(eax, string)
   .return rbx

GetOpType endp


;
; param from .operator
;
; .operator + :byte, :word --> class_add_byte_word
;

    assume rbx:token_t

OperatorParam proc __ccall uses rsi rdi rbx tokenarray:ptr asm_tok, param:string_t

    ldr rbx,tokenarray
    mov rdi,tstrcat( param, "_" )
    add rdi,tstrlen(rdi)

    .while ( [rbx].token == T_BINARY_OPERATOR && [rbx].tokval == T_PTR )

        GetResWName( T_PTR, rdi )
        add rdi,tstrlen( rdi )
        add rbx,asm_tok
    .endw

    .if ( [rbx].token == T_STYPE )

        GetResWName( [rbx].tokval, rdi )
       .return
    .endif
    .return .if ( [rbx].token != T_ID )

    mov rcx,[rbx].string_ptr
    mov eax,[rcx]
    or  eax,0x202020
    .if ( eax == 'sba' )

        tstrcat(rdi, "abs")
       .return
    .endif

   .new i:int_t = 0
   .new ti:qualified_type = {0}

   .return .ifd ( GetQualifiedType( &i, rbx, &ti ) == ERROR )

    .if ( ti.mem_type == MT_PTR )

        .while ( ti.is_ptr )

            GetResWName(T_PTR, rdi)
            add rdi,tstrlen(rdi)
            dec ti.is_ptr
        .endw
    .endif

    mov rsi,ti.symtype
    .if ( rsi && [rsi].asym.state == SYM_TYPE )
        tstrcat(rdi, [rsi].asym.name)
    .endif
    ret

OperatorParam endp


GetArgs proc __ccall private uses rsi rbx tokenarray:ptr asm_tok

    mov rsi,rbx
    .for ( : [rbx].token != T_FINAL : rbx += asm_tok )

        .if ( [rbx].token == T_OP_BRACKET )
            .for ( rbx += asm_tok, edx = 1 : [rbx].token != T_FINAL : rbx += asm_tok )
                .if ( [rbx].token == T_OP_BRACKET )
                    inc edx
                .elseif ( [rbx].token == T_CL_BRACKET )
                    dec edx
                    .break .ifz
                .endif
            .endf
        .endif
        .if ( [rbx].token == T_OP_SQ_BRACKET )
            .for ( rbx += asm_tok, edx = 1 : [rbx].token != T_FINAL : rbx += asm_tok )
                .if ( [rbx].token == T_OP_SQ_BRACKET )
                    inc edx
                .elseif ( [rbx].token == T_CL_SQ_BRACKET )
                    dec edx
                    .break .ifz
                .endif
            .endf
        .endif
        .break .if ( GetOperator( rbx ) )
    .endf
    mov rax,rbx
    sub rax,rsi
    mov ecx,asm_tok
    xor edx,edx
    div ecx
    ret

GetArgs endp


ProcessOperator proc __ccall uses rsi rdi rbx tokenarray:ptr asm_tok

   .new class:ptr asym
   .new name:string_t
   .new isptr:byte = 0
   .new vector:int_t = 0
   .new type:int_t

    ldr rbx,tokenarray

    .if StoreState == FALSE
        .return NOT_ERROR
    .endif
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif

    mov name,[rbx].string_ptr

    .if ( SymFind( rax ) )
        .if ( [rax].asym.mem_type == MT_TYPE )
            mov rax,[rax].asym.type
        .endif
        .if ( [rax].asym.mem_type == MT_PTR )
            inc isptr
            mov rax,[rax].asym.target_type
        .endif
    .endif

    .if ( rax && [rax].asym.isclass && [rax].asym.operator )

        mov class,rax
        movzx edx,[rax].asym.regist[2]
        movzx eax,[rax].asym.regist
        .if ( eax == 0 )
            mov eax,MODULE.accumulator
        .endif
        .if ( edx == 0 )
            mov edx,T_DWORD
            .if ( MODULE.Ofssize == USE64 )
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
    add rbx,asm_tok

    .while 1

       .new func[128]:char_t
        lea rdi,func

        mov rcx,class
        tstrcpy( rdi, [rcx].asym.name )
        tstrcat( rdi, "_" )
        add rdi,tstrlen( rdi )

       .break .ifd ( GetOpType( rbx, rdi ) == ERROR )
        mov rbx,rax

       .new args[128]:char_t
        lea rsi,args
        mov byte ptr [rsi],0

        .if ( isptr == 0 )
            tstrcpy( rsi, "addr " )
        .endif
        .if ( name )
            tstrcat( rsi, name )
        .else
            tstrlen(rsi)
            add rax,rsi
            tsprintf(rax, "%r", vector)
        .endif
        .if ( vector )
            mov name,NULL
        .endif

        .if ( GetArgs( rbx ) )

           .new n:int_t
           .new i:int_t
            mov n,eax
            mov rax,rbx
            sub rax,tokenarray
            mov ecx,asm_tok
            xor edx,edx
            div ecx
            mov i,eax
            add n,eax
            tstrcat( rsi, ", " )
            mov rdi,rsi
            mov rsi,[rbx].tokpos
            imul ebx,n,asm_tok
            add rbx,tokenarray
            add rdi,tstrlen( rdi )
            mov rcx,[rbx].tokpos
            sub rcx,rsi
            rep movsb
            mov byte ptr [rdi],0
            lea rdi,func

            .while ( i < n )

               .new opnd:expr
               .new isaddr:int_t = 0

                tstrcat( rdi, "_" )
                imul ecx,i,asm_tok
                add rcx,tokenarray
                mov rax,[rcx].asm_tok.string_ptr
                .if ( rax )
                    mov eax,[rax]
                .endif
                .if ( ax == 'L' && [rcx+asm_tok].asm_tok.token == T_STRING )
                    tstrcat( rdi, "ptrword" )
                    add i,2
                .elseif ( [rcx].asm_tok.IsProc )
                    .if ( MODULE.Ofssize == USE64 )
                        tstrcat( rdi, "qword" )
                    .else
                        tstrcat( rdi, "dword" )
                    .endif
                    mov i,n
                .else

                    .if ( [rcx].asm_tok.token == T_RES_ID &&
                          [rcx].asm_tok.tokval == T_ADDR )
                        inc i
                        inc isaddr
                    .endif
                    .return .ifd ( EvalOperand( &i, tokenarray, n, &opnd, 0 ) == ERROR )

                    .if ( opnd.kind == EXPR_CONST )

                        mov rcx,opnd.quoted_string
                        .if ( rcx && [rcx].asm_tok.token == T_STRING )
                            .if ( MODULE.wstring )
                                tstrcat( rdi, "ptrword" )
                            .else
                                tstrcat( rdi, "ptrsbyte" )
                            .endif
                        .else
                            tstrcat( rdi, "abs" )
                        .endif
                    .else
                        GetType( rdi, &opnd, rdi, isaddr )
                    .endif
                .endif
                imul ecx,i,asm_tok
                add rcx,tokenarray
                .if ( [rcx].asm_tok.token == T_COMMA )
                    inc i
                .endif
            .endw
            AddLineQueueX( "%s(%s)", &func, &args )
        .endif
    .endw
    .if ( MODULE.line_queue.head )
        InsertLineQueue()
    .endif
    .return NOT_ERROR

ProcessOperator endp


    assume rsi:expr_t
    assume rbx:ptr opinfo

EvalOperator proc __ccall uses rsi rdi rbx opnd1:expr_t, opnd2:expr_t, oper:token_t

    ;
    ; first argument has to be class::operator
    ;
    mov rdx,TokenArray
    .if ( [rdx].asm_tok.token != T_ID ||
          [rdx+asm_tok].asm_tok.token != T_DIRECTIVE ||
          [rdx+asm_tok].asm_tok.tokval != T_EQU )
        .return ERROR
    .endif
    .if ( SymFind( [rdx].asm_tok.string_ptr ) == NULL )
        .return ERROR
    .endif
    .if ( [rax].asym.mem_type == MT_TYPE )
        mov rax,[rax].asym.type
    .endif
    .if ( [rax].asym.mem_type == MT_PTR )
        mov rax,[rax].asym.target_type
    .endif
    .if ( !rax || !( [rax].asym.operator ) )
        .return ERROR
    .endif


    mov rsi,opnd1
    mov rcx,[rsi].type
    mov rax,[rsi].sym

    .if ( !rcx && rax )
        .if ( [rax].asym.mem_type == MT_TYPE )
            mov rax,[rax].asym.type
        .endif
        .if ( [rax].asym.mem_type == MT_PTR )
            mov rax,[rax].asym.target_type
        .endif
        mov rcx,rax
    .endif
    .if ( !rcx || !( [rcx].asym.operator ) )
        .if ( [rsi].kind != EXPR_REG )
            .return ERROR
        .endif
    .endif
    mov [rsi].type,rcx
    mov rbx,LclAlloc( opinfo )
    mov [rbx].next,NULL
    mov [rbx].type,GetOperator(oper)
   .return ERROR .if ( rax == 0 )

    mov rdx,opnd2
    mov rax,[rdx].expr.op
    .if ( rax && [rsi].op == NULL )

        mov [rsi].op,rax
        mov [rdx].expr.op,NULL
    .endif

    lea rdi,[rbx].op1
    mov rcx,expr
    rep movsb
    mov rsi,rdx
    mov rcx,expr
    rep movsb
    mov rsi,opnd1
    mov rax,rbx
    .if ( [rsi].op )
        mov rbx,[rsi].op
        .while ( [rbx].next )
            mov rbx,[rbx].next
        .endw
        mov [rbx].next,rax
    .else
        mov [rsi].op,rax
    .endif
    .return NOT_ERROR

EvalOperator endp


GetArgs2 proc fastcall private uses rsi opnd:ptr expr

    mov rsi,rcx
    .switch ( [rsi].expr.kind )
    .case EXPR_FLOAT
        mov rcx,[rsi].expr.float_tok
        tstrcpy(rdi, [rcx].asm_tok.string_ptr )
        .endc
    .case EXPR_CONST
        tsprintf(rdi, "%d", [rsi].expr.value)
        .endc
    .case EXPR_ADDR
        mov rcx,[rsi].expr.sym
        .if ( rcx )
            tstrcpy(rdi, [rcx].asym.name)
        .endif
        .endc
    .case EXPR_REG
        mov rdx,[rsi].expr.base_reg
        tsprintf(rdi, "%r", [rdx].asm_tok.tokval)
        .endc
    .endsw
    ret

GetArgs2 endp


ParseOperator proc __ccall uses rsi rdi rbx tokenarray:token_t, op:ptr opinfo

   .new buffer[256]:char_t
   .new level:int_t = 0
   .new name:string_t
   .new vector:int_t
   .new type:int_t

    ldr rbx,op
    .while ( [rbx].next )
        mov rbx,[rbx].next
    .endw
    mov level,eax
    mov rcx,[rbx].op1.type
    mov name,[rcx].asym.name

    movzx eax,[rcx].asym.regist
    movzx edx,[rcx].asym.regist[2]
    .if ( eax == 0 )
        mov eax,MODULE.accumulator
    .endif
    .if ( edx == 0 )
        mov edx,T_DWORD
        .if ( MODULE.Ofssize == USE64 )
            mov edx,T_QWORD
        .endif
    .endif
    mov vector,eax
    mov type,edx

    .for ( rbx = op : rbx : rbx = [rbx].next, level++ )

        lea rdi,buffer
        tsprintf( rdi, "%s_%r_", name, [rbx].type )

        .switch ( [rbx].op2.kind )
        .case EXPR_FLOAT
        .case EXPR_CONST
            mov rcx,[rbx].op2.quoted_string
            .if ( rcx && [rcx].asm_tok.token == T_STRING )
                .if ( MODULE.wstring )
                    tstrcat( rdi, "ptrword" )
                .else
                    tstrcat( rdi, "ptrsbyte" )
                .endif
            .else
                tstrcat( rdi, "abs" )
            .endif
            .endc
        .default
            GetType( rdi, &[rbx].op2, rdi, 0 )
            .endc
        .endsw
        tstrcat( rdi, "(" )
        add rdi,tstrlen(rdi)

        mov rcx,[rbx].op1.label_tok
        .if ( rcx == NULL )
            mov rcx,[rbx].op1.base_reg
        .endif
        mov rdx,[rbx].op2.label_tok
        .if ( rdx == NULL )
            mov rdx,[rbx].op2.base_reg
        .endif
        .if ( rcx && [rcx].asm_tok.Operator )

            .if ( rdx )
                mov [rdx].asm_tok.Operator,1
            .endif
            add rdi,tsprintf( rdi, "%r, ", vector )
            GetArgs2( &[rbx].op2 )

        .elseif ( rdx && [rdx].asm_tok.Operator )

            .if ( rcx )
                mov [rcx].asm_tok.Operator,1
            .endif
            GetArgs2( &[rbx].op1 )
            add rdi,tstrlen( rdi )
            tsprintf( rdi, ", %r", vector )

        .else

            .if ( rdx )
                mov [rdx].asm_tok.Operator,1
            .endif
            .if ( rcx )
                mov [rcx].asm_tok.Operator,1
            .endif

            GetArgs2(&[rbx].op1)
            tstrcat( rdi, ", " )
            add rdi,tstrlen(rdi)
            GetArgs2(&[rbx].op2)
        .endif
        tstrcat( rdi, ")" )
        AddLineQueue( &buffer )
    .endf
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif
    .return NOT_ERROR

ParseOperator endp

    end

