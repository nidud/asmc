include stdio.inc
include string.inc
include asmc.inc
include token.inc
include hll.inc

    .code

    assume ebx:ptr asmtok

AssignValue proc private uses esi edi ebx i:ptr int_t, tokenarray:ptr asmtok, count:int_t

  local opnd:expr
  local reg:int_t
  local buffer[128]:char_t

    movzx ecx,ModuleInfo.Ofssize
    mov reg,regax[ecx*4]

    mov esi,i
    mov ebx,[esi]
    shl ebx,4
    add ebx,tokenarray
    lea edi,buffer

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

    mov ecx,[esi]
    add ecx,count

    .if EvalOperand( esi, tokenarray, ecx, &opnd, EXPF_NOUNDEF ) == NOT_ERROR

        mov esi,1

        .if ( opnd.kind == EXPR_CONST )

            mov edx,dword ptr opnd.value64[4]
            mov eax,dword ptr opnd.value64

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

        .elseif ( opnd.kind == EXPR_REG && !( opnd.flags1 & EXF_INDIRECT ) )

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
        .endif

        .if esi

            AddLineQueueX( "mov %r,%s", reg, edi )
        .endif
    .endif
    ret

AssignValue endp

    assume esi:ptr hll_item

ReturnDirective proc uses esi edi ebx i:int_t, tokenarray:ptr asmtok

  local rc:int_t
  local count:int_t
  local retval:int_t
  local directive:int_t
  local buffer[128]:char_t

    mov rc,ERROR

    .repeat

        .if ( CurrProc == NULL )

            asmerr( 2012 )
            .break
        .endif

        mov esi,ModuleInfo.RetStack
        .if !esi
            mov esi,LclAlloc( sizeof( hll_item ) )
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

        mov retval,0
        mov directive,0
        mov count,0

        inc i
        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
        mov al,[ebx].token
        .if ( al != T_FINAL )
            .if ( al == T_DIRECTIVE )
                mov directive,ebx
            .else
                mov retval,ebx
                .if ( al == T_OP_BRACKET )
                    .for ( count++, edx = 1, ebx += 16, al = [ebx].token,
                         : al != T_FINAL : ebx += 16, al = [ebx].token, count++ )
                        .if ( al == T_OP_BRACKET )
                            inc edx
                        .elseif ( al == T_CL_BRACKET )
                            dec edx
                            .break .ifz
                        .endif
                    .endf
                    .break .if ( al != T_CL_BRACKET )
                    inc count
                    add ebx,16
                .else
                    .for ( count++, ebx += 16, al = [ebx].token,
                         : al != T_FINAL : ebx += 16, al = [ebx].token, count++ )
                        .break .if ( al == T_DIRECTIVE )
                    .endf
                .endif
                mov al,[ebx].token
                .if ( al == T_DIRECTIVE )
                    mov directive,ebx
                .endif
            .endif
        .endif

        lea edi,buffer
        GetLabelStr( [esi].labels[LEXIT*4], edi )

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

    .until 1
    mov eax,rc
    ret

ReturnDirective endp

    end
