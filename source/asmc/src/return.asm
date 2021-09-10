; RETURN.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; .return [val] [.if ...]
;

include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include parser.inc
include atofloat.inc

    .code

    assume ebx:ptr asm_tok

GetValue proc private uses esi edi ebx i:ptr int_t, tokenarray:ptr asm_tok,
    type:ptr int_t, count:ptr int_t, directive:ptr int_t, retval:ptr int_t

    mov edx,i
    mov ebx,[edx]
    shl ebx,4
    add ebx,tokenarray
    xor esi,esi
    xor edi,edi
    xor ecx,ecx
    mov edx,type
    mov [edx],ecx
    mov al,[ebx].token
    .if ( al != T_FINAL )

        ; .return real4(1.0)

        .if ( al == T_STYPE && [ebx+16].token == T_OP_BRACKET )

            mov al,T_OP_BRACKET
            mov [edx],ebx
            add ebx,16
            mov edx,i
            inc dword ptr [edx]
        .endif

        .if ( al == T_DIRECTIVE )

            mov esi,ebx
        .else

            mov edi,ebx
            inc ecx
            add ebx,16

            .if ( al == T_OP_BRACKET )

                .for ( edx = 1, al = [ebx].token : al != T_FINAL : ebx += 16, al = [ebx].token, ecx++ )

                    .if ( al == T_OP_BRACKET )
                            inc edx
                    .elseif ( al == T_CL_BRACKET )
                        dec edx
                        .break .ifz
                    .endif
                .endf
                .if ( al == T_CL_BRACKET )

                    inc ecx
                    add ebx,16
                .endif
            .else
                .for ( al = [ebx].token : al != T_FINAL : ebx += 16, al = [ebx].token, ecx++ )

                    .break .if ( al == T_DIRECTIVE )
                .endf
            .endif
            mov al,[ebx].token
            .if ( al == T_DIRECTIVE )
                mov esi,ebx
            .endif
        .endif
    .endif
    mov eax,ebx
    mov ebx,count
    mov [ebx],ecx
    mov ebx,directive
    mov [ebx],esi
    mov ebx,retval
    mov [ebx],edi
    ret

GetValue endp

CreateFloat proto :int_t, :expr_t, :string_t

AssignValue proc private uses esi edi ebx i:ptr int_t, tokenarray:ptr asm_tok, type:ptr asm_tok, count:int_t

  local opnd        : expr
  local reg         : int_t
  local op          : int_t
  local retval      : int_t
  local directive   : int_t
  local buffer[256] : char_t
  local address     : char_t ; v2.30.24 -- .return &address

    movzx ecx,ModuleInfo.Ofssize
    mov reg,regax[ecx*4]
    mov op,T_MOV

    mov esi,i
    mov ebx,[esi]
    shl ebx,4
    add ebx,tokenarray
    lea edi,buffer

    .if ExpandHllProc( edi, [esi], tokenarray ) != ERROR

        .if byte ptr [edi]

            QueueTestLines(edi)
            GetValue( esi, tokenarray, &type, &count, &directive, &retval )
        .endif
    .endif

    .if count
        mov eax,count
        shl eax,4
        mov ecx,[ebx+eax].tokpos
        sub ecx,[ebx].tokpos
        mov byte ptr [edi+ecx],0
        memcpy( edi, [ebx].tokpos, ecx )
    .else
        strcpy( edi, [ebx].string_ptr )
    .endif

    mov address,0
    mov ecx,[esi]
    add ecx,count
    .if [ebx].token == '(' && [ebx+16].token == '&'
        .while byte ptr [edi] != '&'
            inc edi
        .endw
        inc edi
        .for edx = edi : byte ptr [edx] : edx++
        .endf
        .while byte ptr [edx-1] <= ' '
            mov byte ptr [edx-1],0
            dec edx
        .endw
        .if byte ptr [edx-1] == ')'
            mov byte ptr [edx-1],0
        .endif
        inc address
        add dword ptr [esi],2
    .elseif byte ptr [edi] == '&'
        inc edi
        inc address
        inc dword ptr [esi]
    .endif

    .if EvalOperand( esi, tokenarray, ecx, &opnd, EXPF_NOUNDEF ) == NOT_ERROR

        mov esi,1

        .if address

            mov op,T_LEA

        .elseif ( opnd.kind == EXPR_CONST )

            mov edx,opnd.quoted_string

            .if ( edx && [edx].asm_tok.token == T_STRING )

                AddLineQueueX( " lea %r, @CStr(%s)", reg, [edx].asm_tok.string_ptr )
                dec esi

            .else

                mov edx,opnd.hvalue
                mov eax,opnd.value

                .ifs ( !edx && eax > 0 )

                    mov ecx,reg
                    .if ecx == T_RAX
                        mov ecx,T_EAX
                    .endif
                    AddLineQueueX( "mov %r,%d", ecx, eax )
                    dec esi

                .elseif ( !eax && !edx )

                    mov eax,reg
                    .if eax == T_RAX
                        mov eax,T_EAX
                    .endif
                    AddLineQueueX( "xor %r,%r", eax, eax )
                    dec esi
                .endif
            .endif

        .elseif ( opnd.kind == EXPR_REG && !( opnd.flags & E_INDIRECT ) )

            mov ebx,opnd.base_reg
            mov eax,[ebx].tokval
            .if eax == T_EAX || eax == T_RAX
                dec esi
            .else
                .switch pascal SizeFromRegister(eax)
                  .case 2: mov reg,T_AX
                  .case 4: mov reg,T_EAX
                  .case 8: mov reg,T_RAX
                .endsw
            .endif

        .elseif ( opnd.kind == EXPR_FLOAT )

            .if ( type == NULL && ( ( [ebx].token == T_FLOAT && [ebx].floattype ) || \
                  ( [ebx].token == T_OP_BRACKET && \
                    [ebx+16].token == T_FLOAT && \
                    [ebx+16].floattype && \
                    [ebx+32].token == T_CL_BRACKET ) ) )

                ; .return [(] 3F800000r [)] [[ .if ]]

                .if ( [ebx].token == T_OP_BRACKET )
                    mov ebx,[ebx+16].string_ptr
                .else
                    mov ebx,[ebx].string_ptr
                .endif
                dec strlen( ebx )
                shr eax,1
                .switch eax
                .case 3,5,9,11,17
                    .if byte ptr [ebx] == '0'
                        dec eax
                        .endc
                    .endif
                .endsw
            .else
                mov edx,type
                .if edx
                    mov ecx,[edx].asm_tok.tokval
                    mov al,GetMemtypeSp(ecx)
                .else
                    mov al,opnd.mem_type
                .endif
                SizeFromMemtype(al, USE_EMPTY, 0 )
            .endif
            .switch eax
            .case 2
                AddLineQueueX( " mov %r, %s", T_AX, edi )
                AddLineQueueX( " movd %r, %r", T_XMM0, T_EAX )
                .return
            .case 4
                AddLineQueueX( " mov %r, %s", T_EAX, edi )
                AddLineQueueX( " movd %r, %r", T_XMM0, T_EAX )
                .return
            .case 8
                AddLineQueueX( " mov %r, %s", T_RAX, edi )
                AddLineQueueX( " movq %r, %r", T_XMM0, T_RAX )
                .return
            .case 10
                CreateFloat( 10, &opnd, &buffer )
                AddLineQueueX( " movaps %r, xmmword ptr %s", T_XMM0, &buffer )
                .return
            .case 16
                CreateFloat( 16, &opnd, &buffer )
                AddLineQueueX( " movaps %r, %s", T_XMM0, &buffer )
                .return
            .endsw

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
                .endc .if reg != T_RAX
                AddLineQueueX( " mov %r, %r %r %s",    T_RAX, T_QWORD, T_PTR, edi )
                AddLineQueueX( " mov %r, %r %r %s[8]", T_RDX, T_QWORD, T_PTR, edi )
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

        .elseif ( opnd.kind == EXPR_EMPTY && byte ptr [edi] == '{' )

            AddLineQueueX( "movaps xmm0,%s", edi )
            xor esi,esi
        .endif

        .if esi

            AddLineQueueX( "%r %r,%s", op, reg, edi )
        .endif
    .endif
    ret

AssignValue endp

    assume esi:ptr hll_item

ReturnDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asm_tok

  local count       : int_t
  local retval      : int_t
  local type        : ptr asm_tok
  local directive   : int_t
  local buffer[128] : char_t

    .return asmerr(2012) .if ( CurrProc == NULL )

    mov esi,ModuleInfo.RetStack
    .if !esi
        mov esi,LclAlloc(hll_item)
        mov ModuleInfo.RetStack,eax
        xor eax,eax
        mov [esi].next,eax
        mov [esi].labels[LSTART*4],eax
        mov [esi].labels[LTEST*4],eax
        mov [esi].condlines,eax
        mov [esi].caselist,eax
        mov [esi].cmd,HLL_RETURN
        mov [esi].labels[LEXIT*4],GetHllLabel()
    .endif
    ExpandCStrings( tokenarray )

    ; .return [[val]] [[.if ...]]

    inc i
    lea edi,buffer
    GetValue( &i, tokenarray, &type, &count, &directive, &retval )
    GetLabelStr( [esi].labels[LEXIT*4], edi )

    .if ( directive )

        .if ( retval )

            mov ebx,i
            add i,count
            mov [esi].labels[LSTART*4],GetHllLabel()
            HllContinueIf(esi, &i, tokenarray, LSTART, esi, 0)
            mov i,ebx
            AssignValue( &i, tokenarray, type, count )
            AddLineQueueX( "jmp %s", edi )
            AddLineQueueX( "%s:", GetLabelStr( [esi].labels[LSTART*4], edi ) )
        .else
            add i,count
            HllContinueIf( esi, &i, tokenarray, LEXIT, esi, 1 )
        .endif

    .elseif ( retval )

        AssignValue( &i, tokenarray, type, count )
        AddLineQueueX( "jmp %s", edi )
    .else
        AddLineQueueX( "jmp %s", edi )
    .endif

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    mov eax,NOT_ERROR
    ret

ReturnDirective endp

    end
