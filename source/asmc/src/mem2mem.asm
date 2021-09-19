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
include hllext.inc
include atofloat.inc


    .code

InlineCopy proc private uses esi edi ebx dst:ptr, src:ptr, count:uint_t

    mov esi,T_ESI
    mov edi,T_EDI
    mov ebx,T_ECX
    .if ModuleInfo.Ofssize == USE64
        mov esi,T_RSI
        mov edi,T_RDI
        mov ebx,T_RCX
    .endif
    AddLineQueueX( " push %r", esi )
    AddLineQueueX( " push %r", edi )
    AddLineQueueX( " push %r", ebx )
    AddLineQueueX( " lea %r, %s", esi, src )
    AddLineQueueX( " lea %r, %s", edi, dst )
    AddLineQueueX( " mov ecx, %d", count )
    AddLineQueue ( " rep movsb" )
    AddLineQueueX( " pop %r", ebx )
    AddLineQueueX( " pop %r", edi )
    AddLineQueueX( " pop %r", esi )
    ret

InlineCopy endp


InlineMove proc private uses esi edi ebx dst:ptr, src:ptr, count:uint_t

  local type:uint_t

    mov type,T_DWORD
    mov esi,T_EAX
    mov edi,4
    .if ModuleInfo.Ofssize == USE64
        mov type,T_QWORD
        mov esi,T_RAX
        mov edi,8
    .endif

    .for ( ebx = 0 : count >= edi : count -= edi, ebx += edi )

        AddLineQueueX( " mov %r, %r ptr %s[%d]", esi, type, src, ebx )
        AddLineQueueX( " mov %r ptr %s[%d], %r", type, dst, ebx, esi )
    .endf

    mov esi,count

    .if ( edi == 8 && esi >= 4 )

        AddLineQueueX( " mov eax, dword ptr %s[%d]", src, ebx )
        AddLineQueueX( " mov dword ptr %s[%d], eax", dst, ebx )
        sub esi,4
        add ebx,4
    .endif

    .for ( : esi : esi--, ebx++ )

        AddLineQueueX( " mov al, byte ptr %s[%d]", src, ebx )
        AddLineQueueX( " mov byte ptr %s[%d], al", dst, ebx )
    .endf
    ret

InlineMove endp

RetLineQueue proc

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    RunLineQueue()
    mov eax,NOT_ERROR
    ret

RetLineQueue endp

SizeFromExpression proc private opnd:ptr expr

    mov edx,opnd
    mov ecx,[edx].expr.mbr

    .if ecx && [ecx].asym.state == SYM_STRUCT_FIELD

        jmp symbol_size

    .elseif [edx].expr.mem_type != MT_EMPTY

        SizeFromMemtype( [edx].expr.mem_type, [edx].expr.Ofssize, [edx].expr.type )

    .else

        xor eax,eax
        mov ecx,[edx].expr.type

        .if ecx

        symbol_size:

            mov eax,[ecx].asym.total_size

            .if [ecx].asym.flag1 & S_ISARRAY

                mov ecx,[ecx].asym.total_length
                xor edx,edx
                div ecx
            .endif
        .endif
    .endif
    ret

SizeFromExpression endp

mem2mem proc uses esi edi ebx op1:dword, op2:dword, tokenarray:token_t, opnd:ptr expr

  local op:int_t
  local reg:int_t
  local size:int_t
  local regz:int_t
  local dst:string_t
  local src:string_t
  local buffer[16]:char_t
  local isfloat:byte

    mov ebx,op1
    mov edi,op2
    mov isfloat,0

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
    mov esi,opnd
    .if SizeFromExpression( &[esi+expr] )
        .if eax < size
            mov size,eax
            ;; added v2.31.50
        .elseif size == 0 && [esi].expr.mem_type == MT_EMPTY
            mov size,eax
        .endif
    .endif

    .if ( [esi].expr.mem_type & MT_FLOAT || [esi+expr].expr.mem_type & MT_FLOAT )

        mov isfloat,1
        .if ( size != 4 && size != 8 )
            .return asmerr( 2070 )
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
        AddLineQueueX( " lea %r, %s", ecx, [edx+32].asm_tok.tokpos )

    .elseif edi > esi && esi < T_EAX

        AddLineQueueX( " movzx eax, %s", eax )

    .else

        mov ecx,8
        .switch pascal edi
        .case T_AL:  mov ecx,1
        .case T_AX:  mov ecx,2
        .case T_EAX: mov ecx,4
        .endsw

        .if size <= ecx

            mov ecx,T_MOV
            .if ( isfloat )
                mov ecx,T_MOVSS
                mov edx,T_COMISS
                .if ( size == 8 )
                    mov ecx,T_MOVSD
                    mov edx,T_COMISD
                .endif
                .if ( op == T_CMP )
                    mov op,edx
                .endif
                mov esi,T_XMM0
                mov edi,T_XMM0
                mov eax,dst
            .endif
            AddLineQueueX( " %r %r, %s", ecx, esi, eax )

        .elseif op == T_MOV

            mov esi,eax
            mov edi,size
            .if regz == 8
                .if edi > 32
                    InlineCopy( dst, esi, edi )
                .else
                    InlineMove( dst, esi, edi )
                .endif
            .elseif edi > 16
                InlineCopy( dst, esi, edi )
            .else
                InlineMove( dst, esi, edi )
            .endif

            xor ebx,ebx
            mov eax,src
            mov byte ptr [eax],','

        .elseif size == 8 && ecx == 4

            mov ebx,eax
            .switch op
            .case T_CMP
                lea ecx,buffer
                GetLabelStr( GetHllLabel(), ecx )
                AddLineQueueX( " mov eax, dword ptr %s[4]", ebx )
                AddLineQueueX( " cmp dword ptr %s[4], eax", dst )
                AddLineQueueX( " jne %s", &buffer )

                AddLineQueueX( " mov eax, dword ptr %s", ebx )
                AddLineQueueX( " cmp dword ptr %s, eax", dst )
                AddLineQueueX( "%s:", &buffer )
                .endc
            .case T_ADD
                AddLineQueueX( " add dword ptr %s, dword ptr %s", dst, ebx )
                AddLineQueueX( " adc dword ptr %s[4], dword ptr %s[4]", dst, ebx )
                .endc
            .case T_SUB
                AddLineQueueX( " sub dword ptr %s, dword ptr %s", dst, ebx )
                AddLineQueueX( " sbb dword ptr %s[4], dword ptr %s[4]", dst, ebx )
                .endc
            .endsw

            mov eax,','
            mov [ebx-1],al
            xor ebx,ebx

        .else

            .return asmerr( 2070 )
        .endif
    .endif
    .if ebx
        .if ( isfloat )
            mov ecx,src
            inc ecx
            AddLineQueueX( " %r %r, %s", op, edi, ecx )
        .else
            AddLineQueueX( " %r %s, %r", op, dst, edi )
        .endif
        mov eax,src
        mov [eax],bl
    .endif

    RetLineQueue()
    ret

mem2mem endp

CreateFloat proto :int_t, :expr_t, :string_t

    assume edi:ptr asm_tok

immarray16 proc private uses esi edi tokenarray:token_t, result:expr_t

  local i:int_t
  local count:int_t
  local size:int_t
  local opnd:expr
  local oldtok[1024]:char_t

    strcpy( &oldtok, [edi].tokpos )
    strcpy( CurrSource, [edi+3*16].string_ptr )
    xor ecx,ecx
    .for : byte ptr [eax] : eax++
        .if byte ptr [eax] == ','
            add ecx,1
        .endif
    .endf
    inc ecx
    mov count,ecx
    mov eax,16
    cdq
    idiv ecx
    mov size,eax
    mul ecx
    .if eax != 16
        asmerr( 2036, CurrSource )
        mov count,1
        mov size,4
    .endif
    Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax
    .for i = 0, edi = result : count : count--, i++
        .break .if EvalOperand( &i, tokenarray, ModuleInfo.token_count, &opnd, 0 ) == ERROR
        .if opnd.mem_type & MT_FLOAT
            quad_resize(&opnd, size)
        .endif
        lea esi,opnd
        mov ecx,size
        rep movsb
    .endf
    strcpy( CurrSource, &oldtok )
    Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax
    mov eax,16
    ret

immarray16 endp

imm2xmm proc uses esi edi tokenarray:token_t, opnd:expr_t

  local flabel[16]:char_t

    mov edi,tokenarray
    mov esi,[edi].tokval
    mov ecx,opnd
    mov edx,4
    .if [ecx].expr.mem_type == MT_REAL8
        mov edx,8
    .elseif [ecx].expr.mem_type == MT_EMPTY
        mov edx,immarray16(edi, ecx)
    .endif
    mov edi,[edi+asm_tok].tokval
    CreateFloat( edx, opnd, &flabel )
    AddLineQueueX( " %r %r,%s", esi, edi, &flabel )
    RetLineQueue()
    ret

imm2xmm endp

    end
