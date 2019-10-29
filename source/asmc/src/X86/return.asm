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

    .code

    assume ebx:tok_t

GetValue proc private uses esi edi ebx i:int_t, tokenarray:tok_t,
    count:ptr int_t, directive:ptr int_t, retval:ptr int_t

    mov ebx,i
    shl ebx,4
    add ebx,tokenarray
    xor esi,esi
    xor edi,edi
    xor ecx,ecx
    mov al,[ebx].token
    .if ( al != T_FINAL )

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

AssignValue proc private uses esi edi ebx i:ptr int_t, tokenarray:tok_t, count:int_t

  local opnd:expr
  local reg:int_t
  local op:int_t
  local retval:int_t
  local directive:int_t
  local buffer[256]:char_t
  local address:char_t ; v2.30.24 -- .return &address

    movzx ecx,ModuleInfo.Ofssize
    mov reg,regax[ecx*4]
    mov op,T_MOV

    mov esi,i
    mov ebx,[esi]
    shl ebx,4
    add ebx,tokenarray
    lea edi,buffer

    .if ExpandHllProc(edi, [esi], tokenarray) != ERROR

        .if byte ptr [edi]

            QueueTestLines(edi)
            GetValue([esi], tokenarray, &count, &directive, &retval)
        .endif
    .endif

    .if count
        mov eax,count
        shl eax,4
        mov ecx,[ebx+eax].tokpos
        sub ecx,[ebx].tokpos
        mov byte ptr [edi+ecx],0
        memcpy(edi, [ebx].tokpos, ecx)
    .else
        strcpy(edi, [ebx].string_ptr)
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

        .elseif ( opnd.kind == EXPR_ADDR )

            .switch opnd.mem_type
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
                AddLineQueueX( "mov rax,qword ptr %s", edi )
                AddLineQueueX( "mov rdx,qword ptr %s[8]", edi )
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
        .endif

        .if esi

            AddLineQueueX( "%r %r,%s", op, reg, edi )
        .endif
    .endif
    ret

AssignValue endp

    assume esi:hll_t

ReturnDirective proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local count:int_t
  local retval:int_t
  local directive:int_t
  local buffer[128]:char_t

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
    ExpandCStrings(tokenarray)

    ; .return [[val]] [[.if ...]]

    inc i
    lea edi,buffer
    GetValue(i, tokenarray, &count, &directive, &retval)
    GetLabelStr([esi].labels[LEXIT*4], edi)

    .if ( directive )

        .if ( retval )

            mov ebx,i
            add i,count
            mov [esi].labels[LSTART*4],GetHllLabel()
            HllContinueIf(esi, &i, tokenarray, LSTART, esi, 0)
            mov i,ebx
            AssignValue(&i, tokenarray, count)
            AddLineQueueX( "jmp %s", edi )
            AddLineQueueX( "%s:", GetLabelStr( [esi].labels[LSTART*4], edi ) )
        .else
            add i,count
            HllContinueIf(esi, &i, tokenarray, LEXIT, esi, 1)
        .endif

    .elseif ( retval )

        AssignValue(&i, tokenarray, count)
        AddLineQueueX("jmp %s", edi)
    .else
        AddLineQueueX("jmp %s", edi)
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
