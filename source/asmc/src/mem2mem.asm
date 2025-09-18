; MEM2MEM.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;

include asmc.inc
include parser.inc
include proc.inc
include hll.inc
include operands.inc
include listing.inc
include segment.inc
include expreval.inc
include qfloat.inc
include tokenize.inc
include lqueue.inc

    .data
     ofss   db T_SI,    T_DI,    T_CX,    T_CX
            db T_ESI,   T_EDI,   T_ECX,   T_ECX
            db T_RSI,   T_RDI,   T_RCX,   T_ECX
            db T_AX,    T_EAX,   T_RAX,   0
            db T_WORD,  T_DWORD, T_QWORD, 0

    .code

InlineCopy proc __ccall private uses rsi rdi rbx dst:ptr, src:ptr, count:uint_t

    movzx   eax,MODULE.Ofssize
    shl     eax,2
    lea     rbx,ofss
    add     rax,rbx
    movzx   esi,byte ptr [rax]
    movzx   edi,byte ptr [rax+1]
    movzx   ebx,byte ptr [rax+2]
    movzx   ecx,byte ptr [rax+3]

    AddLineQueueX(
        " push %r\n"
        " push %r\n"
        " push %r\n"
        " lea %r, %s\n"
        " lea %r, %s\n"
        " mov %r, %u\n"
        " rep movsb\n"
        " pop %r\n"
        " pop %r\n"
        " pop %r", esi, edi, ebx, esi, src, edi, dst, ecx, count, ebx, edi, esi )
    ret

InlineCopy endp


InlineMove proc __ccall private uses rsi rdi rbx dst:ptr, src:ptr, count:uint_t

  local type:uint_t

    movzx   ecx,MODULE.Ofssize
    lea     rbx,ofss
    movzx   esi,byte ptr [rbx+rcx+12]
    movzx   eax,byte ptr [rbx+rcx+16]
    mov     type,eax
    mov     edi,2
    shl     edi,cl

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

    .if MODULE.list
        LstWrite( LSTTYPE_DIRECTIVE, GetCurrOffset(), 0 )
    .endif
    RunLineQueue()
   .return( NOT_ERROR )

RetLineQueue endp


SizeFromExpression proc fastcall private opnd:ptr expr

    mov rdx,rcx
    mov rcx,[rdx].expr.mbr

    .if ( [rdx].expr.mem_type != MT_EMPTY && [rdx].expr.mem_type != MT_BITS )

        movzx ecx,[rdx].expr.mem_type
        SizeFromMemtype( cl, [rdx].expr.Ofssize, [rdx].expr.type )

    .elseif ( rcx && [rcx].asym.state == SYM_STRUCT_FIELD )

        .if ( [rcx].asym.crecord )

            movzx   eax,[rcx].asym.bitf_bits
            mov     edx,eax
            shr     eax,3
            and     edx,7
            setnz   dl
            add     eax,edx
        .else
            jmp symbol_size
        .endif

    .else

        xor eax,eax
        mov rcx,[rdx].expr.type

        .if rcx

            symbol_size:

            mov eax,[rcx].asym.total_size

            .if [rcx].asym.isarray

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
   .new src         : string_t
   .new dst         : string_t
   .new comma       : string_t
   .new tok         : token_t
   .new buffer[16]  : char_t
   .new isfloat     : char_t = 0
   .new isptr       : char_t = 0

    ldr ebx,op1
    ldr edi,op2

    .if ( !( ebx & OP_M_ANY ) || !( edi & OP_M_ANY ) || MODULE.masm_compat_gencode == 1 )
        .return asmerr( 2070 )
    .endif

    and ebx,OP_MS
    and edi,OP_MS
    mov reg,MODULE.accumulator
    lea rcx,SpecialTable
    imul eax,eax,special_item
    mov eax,[rcx+rax].special_item.sflags
    and eax,SFR_SIZMSK
    mov regz,eax

    mov rcx,tokenarray
    add rcx,asm_tok
    .if ( [rcx+asm_tok*2].asm_tok.token == T_BINARY_OPERATOR &&
          [rcx+asm_tok*2].asm_tok.tokval == T_PTR )
        add rcx,asm_tok*2
    .endif
    mov dst,[rcx].asm_tok.tokpos

    .for ( rdx = rcx : [rdx].asm_tok.token != T_FINAL : rdx += asm_tok )

        .if ( [rdx].asm_tok.token == T_REG )

            mov eax,[rdx].asm_tok.tokval
            .if ( eax == T_AL || eax == T_AX || eax == T_EAX || eax == T_RAX )
                .return asmerr( 2070 )
            .endif
        .endif
        .break .if ( [rdx].asm_tok.token == T_COMMA )
    .endf
    .if ( [rdx].asm_tok.token != T_COMMA )
        .return asmerr( 2070 )
    .endif

    mov comma,[rdx].asm_tok.tokpos
    add rdx,asm_tok
    .if ( [rdx].asm_tok.token == '&' )

        inc isptr
        add rdx,asm_tok
    .endif
    mov tok,rdx
    .if ( [rdx+asm_tok].asm_tok.token == T_BINARY_OPERATOR && [rdx+asm_tok].asm_tok.tokval == T_PTR )
        add rdx,asm_tok*2
    .endif
    mov src,[rdx].asm_tok.tokpos

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

    .if ( eax != T_MOV && ( [rsi].expr.mem_type & MT_FLOAT || [rsi+expr].expr.mem_type & MT_FLOAT ) )

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
    .case OP_M32
        mov edi,T_AX
        .if ( regz > 2 )
            mov edi,T_EAX
        .endif
        .endc
    .endsw

    .switch edx
    .case OP_MS
    .case OP_M08: mov esi,T_AL  : .endc
    .case OP_M16: mov esi,T_AX  : .endc
    .case OP_M32
        mov esi,T_AX
        .if ( regz > 2 )
            mov esi,T_EAX
        .endif
        .endc
    .endsw

    .if ( esi > edi && ebx == OP_MS )
        mov edi,esi
    .endif
    .if ( edi > esi && edx == OP_MS )
        mov esi,edi
    .endif

    mov rax,comma
    mov bl,[rax]
    mov byte ptr [rax],0
    inc rax
    mov rdx,tok

    .if ( isptr )

        mov edi,ecx
        AddLineQueueX( " lea %r, %s", ecx, [rdx].asm_tok.tokpos )
        .if ( size == 4 && edi == T_RAX )
            mov edi,T_EAX
        .endif

    .elseif ( edi > esi && esi < T_EAX )

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

            mov rsi,src
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
            mov rax,comma
            mov byte ptr [rax],','

        .elseif ( size == 8 && ecx == 4 )

            mov rbx,src
            mov edi,op
            mov esi,edi
            .switch edi
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
                mov esi,T_ADC
            .case T_SUB
                .if ( edi == T_SUB )
                    mov esi,T_SBB
                .endif
            .default
                AddLineQueueX(
                    " %r dword ptr %s, dword ptr %s\n"
                    " %r dword ptr %s[4], dword ptr %s[4]", edi, dst, rbx, esi, dst, rbx )
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
            mov rcx,comma
            inc rcx
            AddLineQueueX( " %r %r, %s", op, edi, rcx )
        .else
            AddLineQueueX( " %r %s, %r", op, dst, edi )
        .endif
        mov rax,comma
        mov [rax],bl
    .endif
    RetLineQueue()
    ret

mem2mem endp

    assume rdi:token_t

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
    mov TokenCount,eax

    .for ( i = 0, rdi = result : count : count--, i++ )

        .break .ifd EvalOperand( &i, tokenarray, TokenCount, &opnd, 0 ) == ERROR
        .if opnd.mem_type & MT_FLOAT
            quad_resize(&opnd, size)
        .endif
        lea rsi,opnd
        mov ecx,size
        rep movsb
    .endf

    tstrcpy( CurrSource, &oldtok )
    Tokenize( CurrSource, 0, tokenarray, TOK_DEFAULT )
    mov TokenCount,eax

   .return( 16 )

immarray16 endp


imm2xmm proc __ccall uses rsi rdi rbx tokenarray:token_t, opnd:expr_t, size:uint_t

  local flabel[16]:char_t
  local i:int_t
  local opnd2:expr

    ldr rdi,tokenarray
    ldr rcx,opnd

    mov esi,[rdi].tokval
    .if ( size == 16 && [rcx].expr.mem_type == MT_EMPTY )

        immarray16(rdi, rcx)


    ; added v2.34.73 - movxx reg,0.0

    .elseif ( ( esi == T_MOVSS || esi == T_MOVSD ) && [rdi+asm_tok].token == T_REG )

        mov rax,[rcx]
        or  rax,[rcx+8]
ifndef _WIN64
        or  eax,[ecx+4]
        or  eax,[ecx+12]
endif
        .if ( !rax )

            mov esi,T_XORPS
            AddLineQueueX( " %r %r, %r", esi, [rdi+asm_tok].tokval, [rdi+asm_tok].tokval )

           .return( RetLineQueue() )
        .endif
    .endif
    CreateFloat( size, opnd, &flabel )

    .if ( [rdi+asm_tok].token == T_REG )
        AddLineQueueX( " %r %r, %s", esi, [rdi+asm_tok].tokval, &flabel )
    .else
        mov rbx,[rdi+asm_tok].tokpos
        mov i,1
        EvalOperand( &i, tokenarray, TokenCount, &opnd2, 0 )
        imul edi,i,asm_tok
        add rdi,tokenarray
        mov rdi,[rdi].tokpos
        mov byte ptr [rdi],0
        AddLineQueueX( " %r %s, %s", esi, rbx, &flabel )
        mov byte ptr [rdi],','
    .endif
    RetLineQueue()
    ret

imm2xmm endp

    assume rdi:nothing

; Handle C-type RECORD fields

Const64Field proc __ccall private uses rsi rdi rbx inst:uint_t, type:uint_t, name:string_t, offs:uint_t, value:qword

   .new notinst:int_t = 0

    ldr ebx,inst
    ldr rsi,name
    ldr edi,offs

    .if ( ebx == T_AND )
        mov notinst,T_NOT
    .endif
    mov ecx,dword ptr value
    .if ( ecx )
        AddLineQueueX( " %r %r ptr %s[%d], %r 0x%x", ebx, type, rsi, edi, notinst, ecx )
    .endif
    mov ecx,dword ptr value[4]
    .if ( ecx )
        add edi,4
        AddLineQueueX( " %r %r ptr %s[%d], %r 0x%x", ebx, type, rsi, edi, notinst, ecx )
    .endif
    ret

Const64Field endp

CRecordField proc __ccall uses rsi rdi rbx token:int_t, opnd:ptr expr, opn2:ptr expr

   .new name[1024]:char_t
   .new type:int_t
   .new bits:int_t
   .new mask:qword
   .new offs:int_t
   .new dist:int_t
   .new size:int_t
   .new regsize:int_t
   .new reverse:char_t = 0
   .new aligned:char_t = 0
   .new bitexpr:char_t = 0

    ldr esi,token
    ldr rbx,opnd
    ldr rdi,opn2

    .if ( [rbx].expr.kind != EXPR_ADDR )
        xchg rbx,rdi
        inc reverse
    .endif

    .if ( [rbx].expr.indirect )

        mov rcx,[rbx].expr.base_reg
        mov rdx,[rbx].expr.idx_reg
        .if ( rdx )
            tsprintf( &name, "[%r+%r]", [rcx].asm_tok.tokval, [rdx].asm_tok.tokval )
        .else
            tsprintf( &name, "[%r]", [rcx].asm_tok.tokval )
        .endif
    .else
        mov rcx,[rbx].expr.sym
        tstrcpy( &name, [rcx].asym.name )
    .endif

    mov rdx,rdi
    mov rdi,[rbx].expr.mbr
    .if ( [rdi].asym.bitexpr )
        mov bitexpr,1
        mov [rdi].asym.bitexpr,0
    .endif
    movzx eax,[rdi].asym.bitf_bits
    mov bits,eax
    mov al,[rdi].asym.bitf_offs
    mov dist,eax
    mov offs,[rbx].expr.value
    mov eax,[rdi].asym.total_size
    .switch pascal eax
    .case 1: mov ecx,T_BYTE
    .case 2: mov ecx,T_WORD
    .case 4: mov ecx,T_DWORD
    .case 8: mov ecx,T_QWORD
    .default
        .return( asmerr( 2008, &name ) )
    .endsw
    mov type,ecx
    mov ecx,dist

    .if ( bits == 8 || bits == 16 || bits == 32 )

        .for ( edi = 0 : edi < ecx : edi+=bits )
        .endf
        .if ( ecx == edi )

            mov eax,bits
            shr eax,3
            shr ecx,3
            add offs,ecx
            mov ecx,T_BYTE
            .if ( eax == 2 )
                mov ecx,T_WORD
            .elseif ( eax == 4 )
                mov ecx,T_DWORD
            .endif
            mov type,ecx
            xor ecx,ecx
            inc aligned
        .endif
    .endif
    mov size,eax
    mov dist,ecx

    .if ( !aligned )

        mov eax,ecx
        and ecx,-8
        sub eax,ecx
        add eax,bits
        .if ( eax <= 32 )

            sub dist,ecx
            shr ecx,3
            add offs,ecx
            mov size,4
            mov type,T_DWORD
            .if ( eax <= 8 )
                mov size,1
                mov type,T_BYTE
            .elseif ( eax <= 16 )
                .if ( ecx > 4 )
                    mov size,2
                    mov type,T_WORD
                .endif
            .endif
        .endif
    .endif

    mov eax,1
    mov ecx,bits
ifdef _WIN64
    shl rax,cl
    dec rax
else
    xor edi,edi
    .if ( cl < 32 )
        shld edi,eax,cl
        shl eax,cl
    .else
        and ecx,31
        mov edi,eax
        xor eax,eax
        shl edi,cl
    .endif
    sub eax,1
    sbb edi,0
endif
    mov ecx,dist
ifdef _WIN64
    shl rax,cl
    mov mask,rax
else
    .if ( cl < 32 )
        shld edi,eax,cl
        shl eax,cl
    .else
        and ecx,31
        mov edi,eax
        xor eax,eax
        shl edi,cl
    .endif
    mov dword ptr mask[0],eax
    mov dword ptr mask[4],edi
endif
    .if ( [rdx].expr.kind == EXPR_CONST )

        xor eax,eax
        xchg rdx,rsi
ifdef _WIN64
        mov rdi,[rsi].expr.llvalue
        bsr rax,rdi
else
        mov edi,[rsi].expr.value
        mov esi,[rsi].expr.hvalue
        .if ( esi )
            bsr eax,esi
            add eax,32
        .else
            bsr eax,edi
        .endif
endif
        .if ( eax >= bits )
            .return( asmerr( 2071 ) )
        .endif
        mov rbx,rdi
ifdef _WIN64
        shl rdi,cl
else
        mov ecx,dist
        .if ( cl < 32 )
            shld esi,edi,cl
            shl edi,cl
        .else
            and ecx,31
            mov esi,edi
            xor edi,edi
            shl esi,cl
        .endif
endif

        .if ( edx == T_MOV )

            .switch
            .case ( aligned )
                jmp mem_const
            .case ( size > 4 )
                Const64Field( T_AND, T_DWORD, &name, offs, mask )
ifdef _WIN64
                Const64Field( T_OR, T_DWORD, &name, offs, rdi )
else
                Const64Field( T_OR, T_DWORD, &name, offs, esi::edi )
endif
                .endc
            .default
                mov edx,T_AND
                mov ecx,T_NOT
                .if ( bits == 1 && ebx )
                    mov edx,T_OR
                    xor ecx,ecx
                .endif
                AddLineQueueX( " %r %r ptr %s[%d], %r %u", edx, type, &name, offs, ecx, mask )
                .if ( bits > 1 && ebx )
                    mov edx,T_OR
                    jmp mem_const
                .endif
            .endsw

        .elseif ( bits == 1 || ebx == 0 )

            .if ( edx == T_CMP )

                mov edi,dword ptr mask
                mov edx,T_TEST
                .if ( !bitexpr && ebx )
                    jmp compare_reg
                .endif
            .endif
            jmp mem_const
        .elseif ( aligned || edx != T_CMP )
            jmp mem_const
        .else

compare_reg:

            mov esi,get_register( T_EAX, size )
            mov ebx,T_CMP
            mov regsize,size
            mov dist,edi
            jmp usereg
        .endif

    .else

        mov rdx,[rdx].expr.base_reg
        mov esi,[rdx].asm_tok.tokval
        lea rcx,SpecialTable
        imul eax,esi,special_item
        mov eax,[rcx+rax].special_item.sflags
        and eax,SFR_SIZMSK
        mov regsize,eax

        .if ( !reverse )

            .if ( eax > size )
                mov esi,get_register( esi, size )
            .elseif ( eax < size )
                mov esi,get_register( esi, size )
            .endif
            .if ( aligned )
                mov edx,T_MOV
                jmp mem_reg
            .endif
            .if ( dist )
                AddLineQueueX( " %r %r, %u", T_SHL, esi, dist )
            .endif
            mov edx,type
            .if ( size == 8 )
                mov edx,T_DWORD
            .endif
            Const64Field( T_AND, edx, &name, offs, mask )
            mov edx,T_OR
            jmp mem_reg
        .endif

        mov ebx,T_SHR
        .if ( aligned )

            mov dist,0
ifdef _WIN64
            mov mask,0
else
            mov dword ptr mask[0],0
            mov dword ptr mask[4],0
endif
        .endif

        .if ( eax < size )

            mov esi,get_register( esi, 4 )
            mov regsize,4
            mov eax,4
        .endif

usereg:

        mov edx,T_MOV
        .if ( size < eax )

            mov edx,T_MOVZX
            .if ( eax == 8 )
                mov esi,get_register( esi, 4 )
                mov regsize,4
                mov edx,T_MOVZX
                .if ( size == 4 )
                    mov edx,T_MOV
                .endif
            .endif
        .endif
        AddLineQueueX( " %r %r, %r ptr %s[%d]", edx, esi, type, &name, offs )

        mov  ecx,dword ptr mask[0]
        mov  edx,dword ptr mask[4]
        .if ( ecx || edx )

            imul edi,regsize,8
            sub  edi,dist
            .if ( edx == 0 )
                .if !( edi == bits && ebx == T_SHR )
                    AddLineQueueX( " %r %r, %u", T_AND, esi, ecx )
                .endif
            .else
                sub edi,bits
                .if ( edi )
                    AddLineQueueX( " %r %r, %u", T_SHL, esi, edi )
                .endif
                add edi,dist
                .if ( edi )
                    AddLineQueueX( " %r %r, %u", T_SHR, esi, edi )
                .endif
                cmp ebx,T_CMP
                jne done
            .endif
        .endif
        .if ( dist || ebx == T_CMP )
            AddLineQueueX( " %r %r, %u", ebx, esi, dist )
        .endif
    .endif
done:
    RetLineQueue()
    ret
mem_const:
    AddLineQueueX( " %r %r ptr %s[%d], %u", edx, type, &name, offs, edi )
    jmp done
mem_reg:
    AddLineQueueX( " %r %r ptr %s[%d], %r", edx, type, &name, offs, esi )
    jmp done

CRecordField endp

    end
