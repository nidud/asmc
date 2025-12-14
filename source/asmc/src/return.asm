; RETURN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; .return [val] [.if ...]
;

include asmc.inc
include memalloc.inc
include proc.inc
include segment.inc
include hll.inc
include listing.inc
include parser.inc
include qfloat.inc
include lqueue.inc

    .code

    assume rbx:token_t

GetValue proc __ccall private uses rsi rdi rbx \
        i           : ptr int_t,
        tokenarray  : token_t,
        type        : token_t,
        count       : ptr int_t,
        directive   : ptr int_t,
        retval      : ptr int_t

    ldr  rcx,i
    ldr  rdx,tokenarray
    imul ebx,[rcx],asm_tok
    add  rbx,rdx
    ldr  rcx,type

    xor esi,esi     ; directive
    xor edi,edi     ; retval
    xor edx,edx     ; count
    mov [rcx],rdx
    mov al,[rbx].token

    .if ( al != T_FINAL )

        ; .return real4(1.0)

        .if ( al == T_STYPE && [rbx+asm_tok].token == T_OP_BRACKET )

            mov al,T_OP_BRACKET

            mov [rcx],rbx
            add rbx,asm_tok
            mov rcx,i
            inc dword ptr [rcx]
        .endif

        .if ( al == T_DIRECTIVE )

            inc esi
        .else

            mov rdi,rbx
            inc edx
            add rbx,asm_tok

            .if ( al == T_OP_BRACKET )

                .for ( ecx = 1, al = [rbx].token : al != T_FINAL : rbx += asm_tok, al = [rbx].token, edx++ )

                    .if ( al == T_OP_BRACKET )
                            inc ecx
                    .elseif ( al == T_CL_BRACKET )
                        dec ecx
                        .break .ifz
                    .endif
                .endf
                .if ( al == T_CL_BRACKET )

                    inc edx
                    add rbx,asm_tok
                .endif
            .else
                .for ( al = [rbx].token : al != T_FINAL : rbx += asm_tok, al = [rbx].token, edx++ )

                    .break .if ( al == T_DIRECTIVE )
                .endf
            .endif
            mov al,[rbx].token
            .if ( al == T_DIRECTIVE )
                inc esi
            .endif
        .endif
    .endif


    mov rax,count
    mov [rax],edx
    mov rax,rbx
    mov rbx,directive
    mov [rbx],esi
    mov rbx,retval
    mov [rbx],edi
    ret

GetValue endp

AssignValue proc __ccall private uses rsi rdi rbx i:ptr int_t, tokenarray:token_t, type:token_t, count:int_t

  local opnd        : expr
  local reg         : int_t
  local op          : int_t
  local retval      : int_t
  local directive   : int_t
  local buffer[256] : char_t
  local address     : char_t ; v2.30.24 -- .return &address

    ldr rsi,i
    ldr rdx,tokenarray

    imul ebx,[rsi],asm_tok
    add rbx,rdx
    lea rdi,buffer
    mov reg,MODULE.accumulator
    mov op,T_MOV

    .ifd ( ExpandHllProc( rdi, [rsi], tokenarray ) != ERROR )

        .if ( byte ptr [rdi] )

            QueueTestLines( rdi )
            GetValue( rsi, tokenarray, &type, &count, &directive, &retval )
        .endif
    .endif

    .if ( count )

        imul eax,count,asm_tok
        mov  rcx,[rbx+rax].tokpos
        sub  rcx,[rbx].tokpos
        mov  rdx,rsi
        mov  rsi,[rbx].tokpos
        mov  rax,rdi
        rep  movsb
        mov  byte ptr [rdi],0
        mov  rdi,rax
        mov  rsi,rdx
    .else

        tstrcpy( rdi, [rbx].string_ptr )
    .endif

    mov address,0
    mov ecx,[rsi]
    add ecx,count

    .if ( [rbx].token == '(' && [rbx+asm_tok].token == '&' )

        .while ( byte ptr [rdi] != '&' )
            inc rdi
        .endw
        inc rdi

        .for ( rdx = rdi : byte ptr [rdx] : rdx++ )
        .endf

        .while ( byte ptr [rdx-1] <= ' ' )

            mov byte ptr [rdx-1],0
            dec rdx
        .endw

        .if ( byte ptr [rdx-1] == ')' )
            mov byte ptr [rdx-1],0
        .endif
        inc address
        add dword ptr [rsi],2

    .elseif ( byte ptr [rdi] == '&' )

        inc rdi
        inc address
        inc dword ptr [rsi]
    .endif

    .ifd ( EvalOperand( rsi, tokenarray, ecx, &opnd, EXPF_NOUNDEF ) == NOT_ERROR )

        mov esi,1

        .if ( address )

            mov op,T_LEA

        .elseif ( opnd.kind == EXPR_CONST )

            mov rdx,opnd.quoted_string

            .if ( rdx && [rdx].asm_tok.token == T_STRING )

                AddLineQueueX( " lea %r, @CStr(%s)", reg, [rdx].asm_tok.string_ptr )
                dec esi

            .else

                mov eax,opnd.value
                mov edx,opnd.hvalue

                ; v2.36.18 - removed sign test

                .if ( !edx && eax )

                    mov ecx,reg
                    .if ecx == T_RAX
                        mov ecx,T_EAX
                    .endif
                    AddLineQueueX( " mov %r, %d", ecx, eax )
                    dec esi

                .elseif ( !eax && !edx )

                    mov eax,reg
                    .if eax == T_RAX
                        mov eax,T_EAX
                    .endif
                    AddLineQueueX( " xor %r, %r", eax, eax )
                    dec esi
                .endif
            .endif

        .elseif ( opnd.kind == EXPR_REG && !( opnd.indirect ) )

            mov rbx,opnd.base_reg
            mov eax,[rbx].tokval

            .if ( eax == T_EAX || eax == T_RAX )

                dec esi
            .else

                .switch pascal SizeFromRegister(eax)
                  .case 2: mov reg,T_AX
                  .case 4: mov reg,T_EAX
                  .case 8: mov reg,T_RAX
                .endsw
            .endif

        .elseif ( opnd.kind == EXPR_FLOAT )

            .if ( type == NULL && ( ( [rbx].token == T_FLOAT && [rbx].floattype ) ||
                  ( [rbx].token == T_OP_BRACKET && [rbx+asm_tok].token == T_FLOAT &&
                    [rbx+asm_tok].floattype && [rbx+2*asm_tok].token == T_CL_BRACKET ) ) )

                ; .return [(] 3F800000r [)] [[ .if ]]

                SizeFromMemtype(opnd.mem_type, USE_EMPTY, 0 )
            .else

                mov rdx,type
                .if rdx
                    mov ecx,[rdx].asm_tok.tokval
                    mov al,GetMemtypeSp(ecx)
                .else
                    mov al,opnd.mem_type
                .endif
                SizeFromMemtype(al, USE_EMPTY, 0 )
            .endif

            .switch eax
            .case 2
                AddLineQueueX(
                    " mov ax, %s\n"
                    " movd xmm0, eax", rdi )
                .return
            .case 4
                mov op,T_MOVSS
               .endc
            .case 8
                mov op,T_MOVSD
               .endc
            .case 10
                CreateFloat( 10, &opnd, &buffer )
                AddLineQueueX( " movaps xmm0, xmmword ptr %s", &buffer )
                .return
            .case 16
                mov op,T_MOVAPS
               .endc
            .endsw

            mov reg,T_XMM0
            lea rdi,buffer
            mov ecx,eax
            CreateFloat( ecx, &opnd, rdi )

        .elseif ( opnd.kind == EXPR_ADDR )

            mov al,opnd.mem_type
            .switch al
            .case MT_BYTE
            .case MT_SBYTE
            .case MT_WORD
                mov op,T_MOVZX
                .if reg == T_RAX
                    mov reg,T_EAX
                .endif
                .endc
            .case MT_SWORD
                .if reg != T_AX
                    mov op,T_MOVSX
                    mov reg,T_EAX
                .endif
                .endc
            .case MT_DWORD
            .case MT_SDWORD
                mov reg,T_EAX
               .endc
            .case MT_OWORD
            .case MT_SOWORD
                .endc .if reg != T_RAX
                AddLineQueueX(
                    " mov rax, qword ptr %s\n"
                    " mov rdx, qword ptr %s[8]", rdi, rdi )
                .return
            .case MT_REAL2
                mov reg,T_AX
               .endc
            .case MT_REAL4
                mov reg,T_XMM0
                mov op,T_MOVSS
               .endc
            .case MT_REAL8
                mov reg,T_XMM0
                mov op,T_MOVSD
               .endc
            .case MT_REAL16
                mov reg,T_XMM0
                mov op,T_MOVAPS
               .endc
            .endsw

        .elseif ( opnd.kind == EXPR_EMPTY && byte ptr [rdi] == '{' )

            AddLineQueueX( "movaps xmm0,%s", rdi )
            xor esi,esi
        .endif

        .if ( esi )

            AddLineQueueX( "%r %r,%s", op, reg, rdi )
        .endif
    .endif
    ret

AssignValue endp


    assume rsi:ptr hll_item

ReturnDirective proc __ccall uses rsi rdi rbx i:int_t, tokenarray:token_t

  local count       : int_t
  local retval      : int_t
  local type        : token_t
  local directive   : int_t
  local buffer[128] : char_t

    .if ( CurrProc == NULL )
        .return asmerr( 2012 )
    .endif

    mov rsi,MODULE.RetStack
    .if ( !rsi )

        mov rsi,LclAlloc(hll_item)
        mov MODULE.RetStack,rax
        mov [rsi].cmd,HLL_RETURN
        mov [rsi].labels[LEXIT*4],GetHllLabel()
    .endif
    ExpandCStrings( tokenarray )

    ; .return [[val]] [[.if ...]]

    inc i
    lea rdi,buffer

    GetValue( &i, tokenarray, &type, &count, &directive, &retval )
    GetLabelStr( [rsi].labels[LEXIT*4], rdi )

    .if ( directive )

        .if ( retval )

            mov ebx,i
            add i,count
            mov [rsi].labels[LSTART*4],GetHllLabel()
            HllContinueIf(rsi, &i, tokenarray, LSTART, rsi, 0)
            mov i,ebx
            AssignValue( &i, tokenarray, type, count )
            AddLineQueueX( " %r %s", T_JMP, rdi )
            AddLineQueueX( "%s:", GetLabelStr( [rsi].labels[LSTART*4], rdi ) )
        .else
            add i,count
            HllContinueIf( rsi, &i, tokenarray, LEXIT, rsi, 1 )
        .endif
    .else
        .if ( retval )

            AssignValue( &i, tokenarray, type, count )
            RunLineQueue()
        .endif
        .if ( SymFind( rdi ) ) ; v2.37.3: added - removed ORG 2 + RET

            ; this need a fix:

            mov ebx,[rax].asym.offs
            GetCurrOffset()
            mov rcx,CurrProc
            .if ( [rcx].asym.EndpOccured )
                lea ecx,[rbx-2]
                .if ( ecx == eax && Parse_Pass == 2 )
                    mov ebx,eax
                .endif
            .endif
            cmp ebx,eax
            seta al
        .endif
        .if ( al )
            AddLineQueueX( " %r %s", T_JMP, rdi )
        .endif
    .endif

    .if ( MODULE.list )
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ( MODULE.line_queue.head )
        RunLineQueue()
    .endif
    .return( NOT_ERROR )

ReturnDirective endp

    end
