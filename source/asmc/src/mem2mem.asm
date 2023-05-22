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
include qfloat.inc


    .code

InlineCopy proc fastcall private uses rsi rdi rbx dst:ptr, src:ptr, count:uint_t

    mov esi,T_ESI
    mov edi,T_EDI
    mov ebx,T_ECX

    .if ( ModuleInfo.Ofssize == USE64 )
        mov esi,T_RSI
        mov edi,T_RDI
        mov ebx,T_RCX
    .endif

    AddLineQueueX(
        " push %r\n"
        " push %r\n"
        " push %r\n"
        " lea %r, %s\n"
        " lea %r, %s\n"
        " mov ecx, %d\n"
        " rep movsb\n"
        " pop %r\n"
        " pop %r\n"
        " pop %r", esi, edi, ebx, esi, rdx, edi, rcx, count, ebx, edi, esi )
    ret

InlineCopy endp


InlineMove proc __ccall private uses rsi rdi rbx dst:ptr, src:ptr, count:uint_t

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

        AddLineQueueX(
            " mov %r, %r ptr %s[%d]\n"
            " mov %r ptr %s[%d], %r", esi, type, src, ebx, type, dst, ebx, esi )
    .endf

    mov esi,count

    .if ( edi == 8 && esi >= 4 )

        AddLineQueueX(
            " mov eax, dword ptr %s[%d]\n"
            " mov dword ptr %s[%d], eax", src, ebx, dst, ebx )
        sub esi,4
        add ebx,4
    .endif

    .for ( : esi : esi--, ebx++ )
        AddLineQueueX(
            " mov al, byte ptr %s[%d]\n"
            " mov byte ptr %s[%d], al", src, ebx, dst, ebx )
    .endf
    ret

InlineMove endp


RetLineQueue proc __ccall

    .if ModuleInfo.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    RunLineQueue()
   .return( NOT_ERROR )

RetLineQueue endp


SizeFromExpression proc fastcall private opnd:ptr expr

    mov rdx,rcx
    mov rcx,[rdx].expr.mbr

    .if ( [rdx].expr.mem_type != MT_EMPTY )

        movzx ecx,[rdx].expr.mem_type
        SizeFromMemtype( cl, [rdx].expr.Ofssize, [rdx].expr.type )

    .elseif ( rcx && [rcx].asym.state == SYM_STRUCT_FIELD )

        jmp symbol_size

    .else

        xor eax,eax
        mov rcx,[rdx].expr.type

        .if rcx

        symbol_size:

            mov eax,[rcx].asym.total_size

            .if [rcx].asym.flags & S_ISARRAY

                mov ecx,[rcx].asym.total_length
                xor edx,edx
                div ecx
            .endif
        .endif
    .endif
    ret

SizeFromExpression endp


mem2mem proc __ccall uses rsi rdi rbx op1:dword, op2:dword, tokenarray:token_t, opnd:ptr expr

   .new op          : int_t
   .new reg         : int_t
   .new size        : int_t
   .new regz        : int_t
   .new dst         : string_t
   .new src         : string_t
   .new tok         : token_t
   .new buffer[16]  : char_t
   .new isfloat     : char_t = 0
   .new isptr       : char_t = 0

    ldr ebx,op1
    ldr edi,op2

    .if ( !( ebx & OP_M_ANY ) || !( edi & OP_M_ANY ) ||
          ModuleInfo.strict_masm_compat == 1 )
        .return asmerr( 2070 )
    .endif

    and ebx,OP_MS
    and edi,OP_MS
    mov reg,T_EAX
    mov regz,4

    .if ( ModuleInfo.Ofssize == USE64 )

        mov reg,T_RAX
        mov regz,8
    .endif

    mov rcx,tokenarray
    add rcx,asm_tok
    mov dst,[rcx].asm_tok.tokpos

    .for ( rdx = rcx : [rdx].asm_tok.token != T_FINAL : rdx += asm_tok )
        .if ( [rdx].asm_tok.tokval == ecx )
            .return asmerr( 2070 )
        .endif
        .break .if ( [rdx].asm_tok.token == T_COMMA )
    .endf
    .if ( [rdx].asm_tok.token != T_COMMA )
        .return asmerr( 2070 )
    .endif

    mov src,[rdx].asm_tok.tokpos
    mov tok,rdx
    .if ( [rdx+asm_tok].asm_tok.token == '&' )
        inc isptr
    .endif

    mov rsi,opnd
    mov size,SizeFromExpression( rsi )

    .if  ( !isptr )

        .if SizeFromExpression( &[rsi+expr] )
            .if eax < size
                mov size,eax
                ; added v2.31.50
            .elseif size == 0 && [rsi].expr.mem_type == MT_EMPTY
                mov size,eax
            .endif
        .endif
    .endif

    mov rdx,tokenarray
    mov op,[rdx].asm_tok.tokval

    .if ( eax != T_MOV &&
          ( [rsi].expr.mem_type & MT_FLOAT || [rsi+expr].expr.mem_type & MT_FLOAT ) )

        mov isfloat,1
        .if ( size != 4 && size != 8 )
            .return asmerr( 2070 )
        .endif
        mov reg,T_XMM0
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

    mov rax,src
    mov bl,[rax]
    mov byte ptr [rax],0
    inc rax
    mov rdx,tok

    .if ( [rdx+asm_tok].asm_tok.token == '&' )

        mov edi,ecx
        AddLineQueueX( " lea %r, %s", ecx, [rdx+asm_tok*2].asm_tok.tokpos )
        .if ( size == 4 && edi == T_RAX )
            mov edi,T_EAX
        .endif

    .elseif edi > esi && esi < T_EAX

        AddLineQueueX( " movzx eax, %s", rax )

    .else

        mov ecx,8
        .switch pascal edi
        .case T_AL:  mov ecx,1
        .case T_AX:  mov ecx,2
        .case T_EAX: mov ecx,4
        .endsw

        .if ( size <= ecx )

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
                mov rax,dst
                mov esi,T_XMM0
                mov edi,T_XMM0
            .endif
            AddLineQueueX( " %r %r, %s", ecx, esi, rax )

        .elseif ( op == T_MOV )

            mov rsi,rax
            mov edi,size
            .if regz == 8
                .if edi > 32
                    InlineCopy( dst, rsi, edi )
                .else
                    InlineMove( dst, rsi, edi )
                .endif
            .elseif edi > 16
                InlineCopy( dst, rsi, edi )
            .else
                InlineMove( dst, rsi, edi )
            .endif

            xor ebx,ebx
            mov rax,src
            mov byte ptr [rax],','

        .elseif ( size == 8 && ecx == 4 )

            mov rbx,rax
            .switch op
            .case T_CMP
                lea rdx,buffer
                GetLabelStr( GetHllLabel(), rdx )
                AddLineQueueX(
                    " mov eax, dword ptr %s[4]\n"
                    " cmp dword ptr %s[4], eax\n"
                    " jne %s\n"
                    " mov eax, dword ptr %s\n"
                    " cmp dword ptr %s, eax\n"
                    "%s:", rbx, dst, &buffer, rbx, dst, &buffer )
                .endc
            .case T_ADD
                AddLineQueueX(
                    " add dword ptr %s, dword ptr %s\n"
                    " adc dword ptr %s[4], dword ptr %s[4]", dst, rbx, dst, rbx )
                .endc
            .case T_SUB
                AddLineQueueX(
                    " sub dword ptr %s, dword ptr %s\n"
                    " sbb dword ptr %s[4], dword ptr %s[4]", dst, rbx, dst, rbx )
                .endc
            .default
                AddLineQueueX(
                    " %r dword ptr %s, dword ptr %s\n"
                    " %r dword ptr %s[4], dword ptr %s[4]", op, dst, rbx, op, dst, rbx )
                .endc
            .endsw

            mov eax,','
            mov [rbx-1],al
            xor ebx,ebx

        .else
            .return asmerr( 2070 )
        .endif
    .endif

    .if ( rbx )
        .if ( isfloat )
            mov rcx,src
            inc rcx
            AddLineQueueX( " %r %r, %s", op, edi, rcx )
        .else
            AddLineQueueX( " %r %s, %r", op, dst, edi )
        .endif
        mov rax,src
        mov [rax],bl
    .endif
    RetLineQueue()
    ret

mem2mem endp


CreateFloat proto __ccall :int_t, :expr_t, :string_t

    assume rdi:ptr asm_tok

immarray16 proc __ccall private uses rsi rdi tokenarray:token_t, result:expr_t

  local i:int_t
  local count:int_t
  local size:int_t
  local opnd:expr
  local oldtok[1024]:char_t

    tstrcpy( &oldtok, [rdi].tokpos )
    tstrcpy( CurrSource, [rdi+3*asm_tok].string_ptr )
    xor ecx,ecx
    .for ( : byte ptr [rax] : rax++ )
        .if ( byte ptr [rax] == ',' )
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

    .if ( eax != 16 )

        asmerr( 2036, CurrSource )
        mov count,1
        mov size,4
    .endif

    Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax

    .for ( i = 0, rdi = result : count : count--, i++ )

        .break .ifd EvalOperand( &i, tokenarray, ModuleInfo.token_count, &opnd, 0 ) == ERROR
        .if opnd.mem_type & MT_FLOAT
            quad_resize(&opnd, size)
        .endif
        lea rsi,opnd
        mov ecx,size
        rep movsb
    .endf

    tstrcpy( CurrSource, &oldtok )
    Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
    mov ModuleInfo.token_count,eax

   .return( 16 )

immarray16 endp


imm2xmm proc __ccall uses rsi rdi rbx tokenarray:token_t, opnd:expr_t

  local flabel[16]:char_t
  local i:int_t
  local opnd2:expr

    ldr rdi,tokenarray
    mov esi,[rdi].tokval
    ldr rcx,opnd
    mov edx,4

    .if ( [rcx].expr.mem_type == MT_REAL8 )
        mov edx,8
    .elseif ( [rcx].expr.mem_type == MT_EMPTY )
        mov edx,immarray16(rdi, rcx)
    .endif
    mov ecx,edx
    CreateFloat( ecx, opnd, &flabel )

    .if ( [rdi+asm_tok].token == T_REG )
        AddLineQueueX( " %r %r,%s", esi, [rdi+asm_tok].tokval, &flabel )
    .else
        mov rbx,[rdi+asm_tok].tokpos
        mov i,1
        EvalOperand( &i, tokenarray, ModuleInfo.token_count, &opnd2, 0 )
        imul edi,i,asm_tok
        add rdi,tokenarray
        mov rdi,[rdi].tokpos
        mov byte ptr [rdi],0
        AddLineQueueX( " %r %s,%s", esi, rbx, &flabel )
        mov byte ptr [rdi],','
    .endif
    RetLineQueue()
    ret

imm2xmm endp

    end
