include stdio.inc
include string.inc
include asmc.inc
include proc.inc
include hllext.inc
include expreval.inc

SIZE_DATAPTR    equ 0x68

SymLCreate      proto :string_t
GetQualifiedType proto :ptr int_t, :tok_t, :ptr qualified_type
SetLocalOffsets proto :proc_t

qualified_type  struc
size            int_t ?
symtype         asym_t ?
mem_type        db ?
is_ptr          db ?
is_far          db ?
Ofssize         db ?
ptr_memtype     db ?
qualified_type  ends

    .code

    assume ebx:tok_t
    tokid macro operator
      ifnb <operator>
        inc i
        add ebx,16
      else
        mov ebx,i
        shl ebx,4
        add ebx,tokenarray
      endif
        retm<ebx>
        endm

AddLocalDir proc uses esi edi ebx i:int_t, tokenarray:tok_t

  local name                :string_t,
        type                :string_t,
        sym                 :dsym_t,
        creat               :int_t,
        ti                  :qualified_type,
        opndx               :expr,
        constructor[128]    :sbyte ; class_class

    inc i  ; go past directive
    tokid()

    .while 1

        .return asmerr(2008, [ebx].string_ptr) .if ([ebx].token != T_ID)

        mov name,[ebx].string_ptr
        mov type,NULL

        mov ti.symtype,NULL
        mov ti.is_ptr,0
        mov ti.ptr_memtype,MT_EMPTY

        mov cl,ModuleInfo._model
        mov eax,1
        shl eax,cl
        .if (eax & SIZE_DATAPTR)
            mov ti.is_far,TRUE
        .else
            mov ti.is_far,FALSE
        .endif

        mov ti.Ofssize,ModuleInfo.Ofssize
        mov creat,0
        .if !SymFind(name)

            SymLCreate(name)
            mov creat,1
        .endif
        .return ERROR .if !eax ; if it failed, an error msg has been written already

        mov sym,eax
        .if creat
            mov [eax].asym.state,SYM_STACK
            or  [eax].asym.flag,S_ISDEFINED
            mov [eax].asym.total_length,1
        .endif

        .if (ti.Ofssize == USE16)
            .if creat
                mov [eax].dsym.sym.mem_type,MT_WORD
            .endif
            mov ti.size,sizeof(word)
        .else
            .if creat
                mov [eax].dsym.sym.mem_type,MT_DWORD
            .endif
            mov ti.size,sizeof(dword)
        .endif

        tokid(++) ; go past name
        ;
        ; .new name<[xx]>
        ;
        .if ([ebx].token == T_OP_SQ_BRACKET)

            .for (i++,         ; go past '['
                  ebx += 16,
                  esi = ebx,
                  edi = i : edi < Token_Count: edi++, ebx += 16)

                .break .if ([ebx].token == T_COMMA || [ebx].token == T_COLON)
            .endf
            .return .if EvalOperand(&i, tokenarray, edi, &opndx, 0) == ERROR

            .if (opndx.kind != EXPR_CONST)

                asmerr( 2026 )
                mov opndx.value,1
            .endif

            mov ecx,sym
            mov [ecx].asym.total_length,opndx.value
            or  [ecx].asym.flag,S_ISARRAY
            .if ([tokid()].token == T_CL_SQ_BRACKET)
                tokid(++) ; go past ']'
            .else
                asmerr(2045)
            .endif
        .endif

        mov esi,sym
        assume esi:asym_t
        ;
        ; .new name[xx]:<type>
        ;
        .if ([ebx].token == T_COLON)

            inc i
            .return .if (GetQualifiedType(&i, tokenarray, &ti) == ERROR)

            mov type,[ebx+16].string_ptr
            mov [esi].mem_type,ti.mem_type
            .if (ti.mem_type == MT_TYPE)
                mov [esi].type,ti.symtype
            .else
                mov [esi].target_type,ti.symtype
            .endif
        .endif

        .if creat
            mov [esi].is_ptr,ti.is_ptr
            .if ti.is_far
                or [esi].sint_flag,SINT_ISFAR
            .endif
            mov [esi].Ofssize,ti.Ofssize
            mov [esi].ptr_memtype,ti.ptr_memtype
            mov eax,ti.size
            mul [esi].total_length
            mov [esi].total_size,eax
        .endif

        assume esi:nothing

        .if (creat && Parse_Pass == PASS_1)

            mov eax,CurrProc
            mov edx,[eax].dsym.procinfo
            .if ([edx].proc_info.locallist == NULL)
                mov [edx].proc_info.locallist,esi
            .else
                .for(ecx = [edx].proc_info.locallist : [ecx].dsym.nextlocal :,
                     ecx = [ecx].dsym.nextlocal)
                .endf
                mov [ecx].dsym.nextlocal,esi
            .endif
        .endif

        .if ([tokid()].token != T_FINAL)

            .if ([ebx].token == T_COMMA)

                mov eax,i
                inc eax
                .if (eax < Token_Count)

                    tokid(++)
                .endif

            .elseif ([ebx].token == T_OP_BRACKET)

                lea edi,[ebx-16]
                mov esi,[ebx-16].string_ptr

                tokid(++) ; go past '('
                .for (eax = 1 : [ebx].token != T_FINAL : ebx += 16, i++)
                    .if ([ebx].token == T_OP_BRACKET)
                        inc eax
                    .elseif ([ebx].token == T_CL_BRACKET)
                        dec eax
                        .break .ifz
                    .endif
                .endf
                .return asmerr(2045) .if ([ebx].token != T_CL_BRACKET)

                tokid(++) ; go past ')'
                mov esi,strcat(strcat(strcpy(&constructor, esi), "_"), esi)
                .if (Parse_Pass > PASS_1)
                    .if SymFind(esi)
                        .if ([eax].asym.state == SYM_UNDEFINED)
                            ;
                            ; x::x proto
                            ;
                            ; undef x_x
                            ; x_x macro this
                            ;
                            mov [eax].asym.state,SYM_MACRO
                        .endif
                    .endif
                .endif

                .if ([ebx-32].token == T_OP_BRACKET)
                    .if ([edi-16].asm_tok.token == T_COLON)
                        AddLineQueueX("%s(&%s)", esi, name)
                    .elseif type
                        AddLineQueueX("mov %s,%s(0)", name, esi)
                    .else
                        AddLineQueueX("%s(0)", esi)
                    .endif
                .else
                    mov eax,[ebx-16].tokpos
                    mov byte ptr [eax],0
                    .if ([edi-16].asm_tok.token == T_COLON)
                        AddLineQueueX("%s(&%s, %s)", esi, name, [edi+32].asm_tok.tokpos)
                    .elseif type
                        AddLineQueueX("mov %s,%s(0, %s)", name, esi, [edi+32].asm_tok.tokpos)
                    .else
                        AddLineQueueX("%s(0, %s)", esi, [edi+32].asm_tok.tokpos)
                    .endif
                    mov eax,[ebx-16].tokpos
                    mov byte ptr [eax],')'
                .endif
            .else
                .return asmerr(2065, ",")
            .endif
        .endif
        mov eax,i
        .break .if (eax >= Token_Count)
    .endw

    .if (creat && Parse_Pass == PASS_1)
        mov eax,CurrProc
        SetLocalOffsets([eax].dsym.procinfo)
    .endif
    mov eax,NOT_ERROR
    ret

AddLocalDir endp

NewDirective proc i:int_t, tokenarray:tok_t

  local rc:int_t

    .return asmerr(2012) .if (CurrProc == NULL)

    mov rc,AddLocalDir(i, tokenarray)
    .if ModuleInfo.list
        LstWrite(LSTTYPE_DIRECTIVE, GetCurrOffset(), 0)
    .endif
    .if ModuleInfo.line_queue.head
        RunLineQueue()
    .endif
    mov eax,rc
    ret

NewDirective endp

    END
