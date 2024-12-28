; INDIRECTION.ASM--
;
; Copyright (c) The Asmc Contributors. All rights reserved.
; Consult your license regarding permissions and restrictions.
;
; Handles the unary indirection operator (.) accesses a value
; indirectly through a pointer.
;
include asmc.inc
include memalloc.inc
include parser.inc
include expreval.inc
include lqueue.inc
include assume.inc
include segment.inc
include listing.inc
include mangle.inc
include proc.inc
include qfloat.inc
include types.inc

    .code

    assume rbx:ptr asm_tok

SkipSQBackets proc fastcall private uses rbx tok:ptr asm_tok

    .for ( rbx = rcx,
           edx = 0, ; brackets
           ecx = 1, ; SQ-brackets
           rbx +=asm_tok : ecx && [rbx].token != T_FINAL : rbx += asm_tok )

        mov al,[rbx].token
        .if ( al == T_OP_BRACKET )
            inc edx
        .elseif ( al == T_CL_BRACKET )
            dec edx
        .elseif ( !edx && al == T_OP_SQ_BRACKET )
            inc ecx
        .elseif ( !edx && al == T_CL_SQ_BRACKET )
            dec ecx
            .ifz
                add rbx,asm_tok
               .return( rbx )
            .endif
        .endif
    .endf
    .return( 0 )

SkipSQBackets endp


GetSQBackets proc fastcall private uses rsi rdi tok:ptr asm_tok, buffer:string_t

    mov rdi,rdx
    mov rsi,rcx

    .if SkipSQBackets(rcx)

        mov rcx,[rax].asm_tok.tokpos
        mov rsi,[rsi].asm_tok.tokpos
        sub rcx,rsi
        rep movsb
        mov byte ptr [rdi],0
    .endif
    ret

GetSQBackets endp


FindDotSymbol proc fastcall uses rsi rdi rbx tok:ptr asm_tok

    mov rbx,rcx

    .while ( [rbx-asm_tok].token != T_COMMA && [rbx-asm_tok].token != T_DIRECTIVE )
        sub rbx,asm_tok
    .endw
    .return .if !SymSearch( [rbx].string_ptr )

    mov rsi,rax
    add rbx,asm_tok

    .while ( [rbx].token != T_FINAL )

        .if ( [rbx].token == T_COMMA )
            .return 0
        .endif
        .if ( [rbx].token == T_OP_SQ_BRACKET )
            .break .if !SkipSQBackets(rbx)
            mov rbx,rax
        .endif
        xor eax,eax
        .break .if ( [rbx].token != T_DOT )
        add rbx,asm_tok

        .if ( [rsi].asym.mem_type == MT_TYPE )
            mov rsi,[rsi].asym.type
        .endif
        .if ( [rsi].asym.mem_type == MT_PTR )
            mov rsi,[rsi].asym.target_type
        .endif
        .break .if ( !rsi )
        .break .if ( [rsi].asym.state != SYM_TYPE )

        mov rsi,SearchNameInStruct( rsi, [rbx].string_ptr, 0, 0 )
        .break .if ( !rsi )
        .break .if ( rbx == tok )
        add rbx,asm_tok
    .endw
    ret

FindDotSymbol endp


AssignPointer proc __ccall uses rsi rdi rbx sym:ptr asym, reg:int_t, tok:ptr asm_tok,
        pclass:ptr asym, langtype:int_t, pmacro:ptr asym

  local buffer[128]:sbyte
  local vreg:int_t
  local vtable:byte

    ldr rbx,tok
    ldr rsi,sym

    .if ( rsi == NULL )
        .if ( [rbx].token == T_REG )
            .if ( [rbx].tokval != reg )
                AddLineQueueX( " mov %r, %r", reg, [rbx].tokval )
            .endif
        .else
            AddLineQueueX( " mov %r, %s", reg, [rbx].tokpos )
        .endif
        .return( rsi )
    .endif

    mov vtable,0
    mov rdi,pclass
    .if ( rdi && [rdi].asym.flags & S_ISVTABLE )

        xor eax,eax
        .switch ( langtype )
        .case LANG_SYSCALL
            mov eax,T_RDI
           .endc
        .case LANG_FASTCALL
            mov eax,T_CX - T_AX
        .case LANG_WATCALL
        .case LANG_ASMCALL
            add eax,MODULE.accumulator
        .endsw

        .if ( eax )

            mov ecx,reg
            mov reg,eax
            mov edi,eax
            mov vreg,ecx

            add rbx,asm_tok
            .if ( [rbx].token == T_OP_SQ_BRACKET )
                .return .if !GetSQBackets( rbx, &buffer )
                mov rbx,rax
                AddLineQueueX( " lea %r, [%r]%s", edi, edi, &buffer )
            .endif
            mov rax,rsi

            .return .if ( [rbx].token != T_DOT )
            add rbx,asm_tok
            .if ( [rsi].asym.mem_type == MT_TYPE )
                mov rsi,[rsi].asym.type
            .endif
            .if ( [rsi].asym.mem_type == MT_PTR )
                mov rsi,[rsi].asym.target_type
            .endif
            .return .if ( !rsi )
            .return .if ( [rsi].asym.state != SYM_TYPE )

            AddLineQueueX( " mov %r, [%r].%s.%s", edi, edi, [rsi].asym.name, [rbx].string_ptr )
            SearchNameInStruct( rsi, [rbx].string_ptr, 0, 0 )
            xchg rsi,rax
            .return .if ( !rsi )
            mov vtable,1
        .endif
    .endif
    .if ( !vtable )
        AddLineQueueX( " mov %r, %s", reg, [rsi].asym.name )
    .endif

    add rbx,asm_tok

    .while ( [rbx].token != T_FINAL )

        .break .if ( [rbx].token == T_COMMA )

        .if ( [rbx].token == T_OP_SQ_BRACKET )

            .break .if !GetSQBackets( rbx, &buffer )

            mov rbx,rax
            AddLineQueueX( " lea %r, [%r]%s", reg, reg, &buffer )
        .endif

        .break .if ( [rbx].token != T_DOT )

        add rbx,asm_tok
        mov rax,rsi
        .if ( [rax].asym.mem_type == MT_TYPE )
            mov rax,[rax].asym.type
        .endif
        .if ( [rax].asym.mem_type == MT_PTR )
            mov rax,[rax].asym.target_type
        .endif
        .break .if ( !rax )
        .break .if ( [rax].asym.state != SYM_TYPE )
        mov rsi,rax

        AddLineQueueX( " mov %r, [%r].%s.%s", reg, reg, [rsi].asym.name, [rbx].string_ptr )
        .break .if ( !SearchNameInStruct( rsi, [rbx].string_ptr, 0, 0 ) )
        mov rsi,rax
        add rbx,asm_tok
    .endw
    .if ( vtable && !pmacro )
        AddLineQueueX( " mov %r, [%r]", vreg, reg )
    .endif
    .return( rsi )

AssignPointer endp


ifdef USE_INDIRECTION

HandleIndirection proc __ccall uses rsi rdi rbx sym:ptr asym, tokenarray:ptr asm_tok, pos:int_t

  local reg:uint_t
  local inst:uint_t
  local dest:uint_t
  local buffer[128]:sbyte

    ldr rbx,tokenarray
    .if ( pos )
        mov inst,[rbx-asm_tok].tokval    ; cmp p.p.p, expr
    .else
        mov inst,[rbx-3*asm_tok].tokval  ; cmp reg, p.p.p
        mov dest,[rbx-2*asm_tok].tokval
    .endif

    mov reg,MODULE.accumulator
    AddLineQueueX( " mov %r, %s", eax, [rbx].string_ptr )

    add rbx,asm_tok
    mov rsi,sym

    .while ( [rbx].token != T_FINAL && [rbx].token != T_COMMA )

        .if ( [rbx].token == T_OP_SQ_BRACKET )

            .break .if !GetSQBackets( rbx, &buffer )

            mov rbx,rax
            AddLineQueueX( " lea %r, [%r]%s", reg, reg, &buffer )
        .endif

        .break .if ( [rbx].token != T_DOT )
        .if ( pos )
            .if ( [rbx+asm_tok*2].token == T_OP_SQ_BRACKET )
                .break .if ( !SkipSQBackets( &[rbx+asm_tok*2] ) )
                .break .if ( [rax].asm_tok.token != T_DOT )
            .else
                .break .if ( [rbx+asm_tok*2].token != T_DOT )
            .endif
        .endif
        add rbx,asm_tok

        .if ( [rsi].asym.mem_type == MT_TYPE )
            mov rsi,[rsi].asym.type
        .endif
        .if ( [rsi].asym.mem_type == MT_PTR )
            mov rsi,[rsi].asym.target_type
        .endif

        .if ( !SearchNameInStruct( rsi, [rbx].string_ptr, 0, 0 ) )
            .return asmerr(2166)
        .endif
        mov rdi,rax
        add rbx,asm_tok
        .break .if ( [rax].asym.mem_type != MT_TYPE )
        mov rax,[rax].asym.type
        .break .if ( [rax].asym.mem_type != MT_PTR )
        AddLineQueueX( " mov %r, [%r].%s.%s", reg, reg, [rsi].asym.name, [rbx-asm_tok].string_ptr )
        mov rsi,rdi
    .endw
    .if ( [rsi].asym.mem_type == MT_TYPE )
        mov rsi,[rsi].asym.type
    .endif
    .if ( [rsi].asym.mem_type == MT_PTR )
        mov rsi,[rsi].asym.target_type
    .endif
    .if ( pos )
        AddLineQueueX( " %r [%r].%s%s", inst, reg, [rsi].asym.name, [rbx].tokpos )
    .else
        AddLineQueueX( " %r %r, [%r].%s.%s", inst, dest, reg, [rsi].asym.name, [rbx-asm_tok].tokpos )
    .endif
    RetLineQueue()
    ret

HandleIndirection endp

endif

    end
