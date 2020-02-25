; MEM2MEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include parser.inc
include hll.inc
include operands.inc
include listing.inc
include lqueue.inc
include segment.inc
include expreval.inc

    .code

SizeFromExpression proc opnd:ptr expr

    mov edx,opnd
    mov ecx,[edx].expr.mbr
    .if ecx && [ecx].asym.state == SYM_STRUCT_FIELD
        mov eax,[ecx].asym.total_size
        .if [ecx].asym.flag & S_ISARRAY
            mov ecx,[ecx].asym.total_length
            xor edx,edx
            div ecx
        .endif
    .elseif [edx].expr.mem_type != MT_EMPTY
        SizeFromMemtype([edx].expr.mem_type, [edx].expr.Ofssize, [edx].expr.type)
    .else
        mov eax,[edx].expr.type
        .if eax
            mov ecx,eax
            mov eax,[eax].asym.total_size
            .if [ecx].asym.flag & S_ISARRAY
                mov ecx,[ecx].asym.total_length
                xor edx,edx
                div ecx
            .endif
        .endif
    .endif
    ret

SizeFromExpression endp

mem2mem proc uses esi edi ebx op1:dword, op2:dword, tokenarray:tok_t, opnd:ptr expr

  local op:int_t
  local reg:int_t
  local size:int_t
  local regz:int_t
  local dst:string_t
  local src:string_t

    mov ebx,op1
    mov edi,op2

    .if ( !( ebx & OP_M_ANY ) || !( edi & OP_M_ANY ) || ModuleInfo.strict_masm_compat == 1 )

        .return asmerr( 2070 )
    .endif
    and ebx,OP_MS
    and edi,OP_MS
    mov reg,T_EAX
    mov regz,4
    .if ModuleInfo.Ofssize == USE64
        mov reg,T_RAX
        mov regz,8
    .endif

    mov size,SizeFromExpression(opnd)
    mov eax,opnd
    add eax,expr
    .if SizeFromExpression(eax)
        .if eax < size
            mov size,eax
        .endif
    .endif

    mov edx,edi
    mov ecx,reg
    mov esi,ecx
    mov edi,ecx

    .switch ebx
    .case OP_MS
    .case OP_M08: mov edi,T_AL  : .endc
    .case OP_M16: mov edi,T_AX  : .endc
    .case OP_M32: mov edi,T_EAX : .endc
    .endsw

    .switch edx
    .case OP_MS
    .case OP_M08: mov esi,T_AL  : .endc
    .case OP_M16: mov esi,T_AX  : .endc
    .case OP_M32: mov esi,T_EAX : .endc
    .endsw

    .if esi > edi && ebx == OP_MS
        mov edi,esi
    .endif
    .if edi > esi && edx == OP_MS
        mov esi,edi
    .endif

    mov ebx,tokenarray
    mov op,[ebx].asm_tok.tokval
    add ebx,16
    mov dst,[ebx].asm_tok.tokpos

    .for ( edx = ebx : [edx].asm_tok.token != T_FINAL : edx += 16 )
        .if ( [edx].asm_tok.tokval == ecx )
            .return asmerr( 2070 )
        .endif
        .break .if ( [edx].asm_tok.token == T_COMMA )
    .endf
    .if ( [edx].asm_tok.token != T_COMMA )
        .return asmerr( 2070 )
    .endif

    mov src,[edx].asm_tok.tokpos
    mov bl,[eax]
    mov byte ptr [eax],0
    inc eax

    .if [edx+16].asm_tok.token == '&'
        mov edi,ecx
        AddLineQueueX( " lea %r,%s", ecx, [edx+32].asm_tok.tokpos )
    .elseif edi > esi && esi < T_EAX
        AddLineQueueX( " movzx eax,%s", eax )
    .else
        mov ecx,8
        .switch edi
        .case T_AL:  mov ecx,1 : .endc
        .case T_AX:  mov ecx,2 : .endc
        .case T_EAX: mov ecx,4 : .endc
        .endsw

        .if size <= ecx
            AddLineQueueX( " mov %r,%s", esi, eax )
        .else

            .if ( op != T_MOV )
                .return asmerr( 2070 )
            .endif

            mov esi,eax
            mov edi,size
            .if regz == 8
                .if edi > 32
                    AddLineQueue ( " push rsi" )
                    AddLineQueue ( " push rdi" )
                    AddLineQueue ( " push rcx" )
                    AddLineQueueX( " lea rsi,%s", esi )
                    AddLineQueueX( " lea rdi,%s", dst )
                    AddLineQueueX( " mov ecx,%d", edi )
                    AddLineQueue ( " rep movsb" )
                    AddLineQueue ( " pop rcx" )
                    AddLineQueue ( " pop rdi" )
                    AddLineQueue ( " pop rsi" )
                .else
                    .for ( ebx = 0 : edi >= 8 : edi -= 8, ebx += 8 )
                        AddLineQueueX( " mov rax,qword ptr %s[%d]", esi, ebx )
                        AddLineQueueX( " mov qword ptr %s[%d],rax", dst, ebx )
                    .endf
                    .for ( : edi >= 4 : edi -= 4, ebx += 4 )
                        AddLineQueueX( " mov eax,dword ptr %s[%d]", esi, ebx )
                        AddLineQueueX( " mov dword ptr %s[%d],eax", dst, ebx )
                    .endf
                    .for ( : edi : edi--, ebx++ )
                        AddLineQueueX( " mov al,byte ptr %s[%d]", esi, ebx )
                        AddLineQueueX( " mov byte ptr %s[%d],al", dst, ebx )
                    .endf
                .endif
            .else
                .if edi > 16
                    AddLineQueue ( " push esi" )
                    AddLineQueue ( " push edi" )
                    AddLineQueue ( " push ecx" )
                    AddLineQueueX( " lea esi,%s", esi )
                    AddLineQueueX( " lea edi,%s", dst )
                    AddLineQueueX( " mov ecx,%d", edi )
                    AddLineQueue ( " rep movsb" )
                    AddLineQueue ( " pop ecx" )
                    AddLineQueue ( " pop edi" )
                    AddLineQueue ( " pop esi" )
                .else
                    .for ( ebx = 0 : edi >= 4 : edi -= 4, ebx += 4 )
                        AddLineQueueX( " mov eax,dword ptr %s[%d]", esi, ebx )
                        AddLineQueueX( " mov dword ptr %s[%d],eax", dst, ebx )
                    .endf
                    .for ( : edi : edi--, ebx++ )
                        AddLineQueueX( " mov al,byte ptr %s[%d]", esi, ebx )
                        AddLineQueueX( " mov byte ptr %s[%d],al", dst, ebx )
                    .endf
                .endif
            .endif
            xor ebx,ebx
            mov eax,src
            mov byte ptr [eax],','
        .endif
    .endif
    .if ebx
        AddLineQueueX( " %r %s,%r", op, dst, edi )
        mov eax,src
        mov [eax],bl
    .endif
    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    RunLineQueue()
    mov eax,NOT_ERROR
    ret

mem2mem endp

    end
